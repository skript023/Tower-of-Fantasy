#pragma once
#include "fwddec.hpp"
#include "static_indirect_array_thread_safe.hpp"

namespace big
{
    template <typename T>
    FORCEINLINE constexpr T Align(T Val, uint64_t Alignment)
    {
        return (T)(((uint64_t)Val + Alignment - 1) & ~(Alignment - 1));
    }

    constexpr uint32_t fname_max_block_bits = 13;
    constexpr uint32_t fname_block_offset_bits = 16;
    constexpr uint32_t  fname_max_block = 1 << fname_max_block_bits;
    constexpr uint32_t fname_block_offset = 1 << fname_block_offset_bits;

    struct FNameEntryId
    {
        FNameEntryId() : m_value(0) {}

        FNameEntryId(uint32_t Id) : m_value(Id) {}

        explicit operator bool() const { return m_value != 0; }

        FORCEINLINE static FNameEntryId from_unstable_int(uint32_t UnstableInt)
        {
            FNameEntryId Id;
            Id.m_value = UnstableInt;
            return Id;
        }

        FORCEINLINE uint32_t to_unstable_int() const 
        {
            return m_value;
        }

        uint32_t m_value;
    };

    struct FNameEntryHandle
    {
        uint32_t m_block = 0;
        uint32_t m_offset = 0;

        FNameEntryHandle(uint32_t InBlock, uint32_t InOffset)
            : m_block(InBlock)
            , m_offset(InOffset)
        {}

        FNameEntryHandle(FNameEntryId Id)
            : m_block(Id.to_unstable_int() >> fname_block_offset_bits)
            , m_offset(Id.to_unstable_int()& (fname_block_offset - 1))
        {}

        FNameEntryHandle(uint32_t id) : m_block(id >> fname_block_offset_bits), m_offset(id & 65535) {};

        operator FNameEntryId() const
        {
            return FNameEntryId::from_unstable_int((m_block << fname_block_offset_bits) | m_offset);
        }

        static uint32_t get_type_hash(FNameEntryHandle Handle)
        {
            return (Handle.m_block << (32 - fname_max_block_bits)) + Handle.m_block
                + (Handle.m_offset << fname_block_offset_bits) + Handle.m_offset
                + (Handle.m_offset >> 4);
        }

        uint32_t get_type_hash(FNameEntryId Id)
        {
            return get_type_hash(FNameEntryHandle(Id));
        }

        explicit operator bool() const { return m_block | m_offset; }
    };


    struct FNameEntryHeader
    {
        uint16_t b_is_wide : 1;
#ifdef WITH_CASE_PRESERVING_NAME
        uint16_t m_len : 15;
#else
        static constexpr uint32_t m_probe_hash_bits = 5;
        uint16_t m_lower_case_probe_hash : m_probe_hash_bits;
        uint16_t m_len : 10;
#endif
    };

    struct FNameEntry
    {
        enum { NAME_SIZE = 1024 };
    public:
        uint32_t get_length() const
        {
            return m_header.m_len;
        }

        bool is_wide() const
        {
            return m_header.b_is_wide;
        }

        inline const char* get_ansi_name_ex() const
        {
            return m_ansi_name;
        }
        inline const wchar_t* get_wide_name_ex() const
        {
            return m_wide_name;
        }

        std::string get_ansi_name() const
        {
            auto len = get_length();
            if (len > 1024) return "[Error: Overflow]";

            return std::string((const char*)m_ansi_name, len);
        }

        std::wstring get_wide_name() const
        {
            auto len = get_length();
            return std::wstring((const wchar_t*)m_wide_name, len);
        }

        std::string get_string() const
        {
            if (is_wide())
            {
                int size = WideCharToMultiByte(CP_UTF8, 0, m_wide_name, m_header.m_len, nullptr, 0, nullptr, nullptr);
                std::string str(size, 0);
                WideCharToMultiByte(CP_UTF8, 0, m_wide_name, m_header.m_len, &str[0], size, nullptr, nullptr);
                return str;
            }
            return std::string(m_ansi_name, m_header.m_len);
        }

    private:
#ifdef WITH_CASE_PRESERVING_NAME
        FNameEntryId m_comparison_id;
#endif
        FNameEntryHeader m_header;

        union
        {
            char m_ansi_name[NAME_SIZE];
            wchar_t m_wide_name[NAME_SIZE];
        };
    };

    class FNameEntryAllocator
    {
    private:
        enum { stride = alignof(FNameEntry) };
        enum { block_size = stride * fname_block_offset };
        enum { max_size = 0x1FFFE };
        char frwLock[0x8];
    public:
        uint32_t m_current_block;
        uint32_t m_current_byte_cursor;
        uint8_t* m_block[fname_max_block];

        FNameEntry& get_by_id(int32_t key) const
        {
            uint32_t block = key >> 16;
            uint16_t offset = key;

            if (!is_valid_index(key, block, offset))
                return *reinterpret_cast<FNameEntry*>(m_block[0] + 0); // "None"

            return *reinterpret_cast<FNameEntry*>(m_block[block] + (uint32_t)(2 * offset));
        }

        uint32_t num_blocks() const
        {
            return m_current_block + 1;
        }

        bool is_valid_index(int32_t key) const
        {
            uint32_t block = key >> 16;
            uint16_t offset = key;
            return is_valid_index(key, block, offset);
        }

        FNameEntry* resolve(FNameEntryHandle handle) const
        {
            if (handle.m_offset < 0 && handle.m_block > num_blocks() && handle.m_offset * stride < fname_block_offset)
            {
                g_logger->error("Invalid FNameEntryHandle Passed To FNameEntryAllocator::Resolve.");
                return reinterpret_cast<FNameEntry*>(m_block[0] + 0);
            }

            return reinterpret_cast<FNameEntry*>(m_block[handle.m_block] + stride * handle.m_offset);
        }

        bool is_valid_index(int32_t key, uint32_t block, uint16_t offset) const
        {
            return (key >= 0 && block < num_blocks() && offset * stride < block_size);
        }
    };

	class FNamePool
	{
	public:
		FNameEntryAllocator m_entry_allocator;
		uint32_t ansi_count;
		uint32_t wide_count;
	};

    class FName
    {
    public:
        FNameEntryId m_comparison_index;
#ifdef WITH_CASE_PRESERVING_NAME
        /** Index into the Names array (used to find String portion of the string/number pair used for display) */
        FNameEntryId m_display_index;
#endif
        int32_t m_number;
        inline FNameEntryId get_display_index() const
        {
#ifdef WITH_CASE_PRESERVING_NAME
            return m_display_index;
#else
            return m_comparison_index;
#endif
        }
        inline int32_t get_number() const
        {
            return m_number;
        }

#ifndef WITH_CASE_PRESERVING_NAME
        inline uint64_t comparable_int() const
        {
            static_assert(sizeof(*this) == sizeof(uint64_t), "");
            alignas(uint64_t) FName AlignedCopy = *this;
            return reinterpret_cast<uint64_t&>(AlignedCopy);
        }
#endif

        std::string get_name() const;
        inline bool operator==(const FName& other) const
        {
#ifndef WITH_CASE_PRESERVING_NAME
            return comparable_int() == other.comparable_int();
#else
            return (m_comparison_index == other.m_comparison_index & (get_number() == other.get_number()));
#endif
        };

        inline bool operator!=(FName Other) const
        {
            return !(*this == Other);
        }

        FName() :
            m_comparison_index(FNameEntryId()),
            m_number(0)
        { }

        FName(int32_t i, int32_t n = 0) :
            m_comparison_index(FNameEntryId(i)),
            m_number(n)
        { }

        const FNameEntry* get_display_name_entry() const;
    };
    static_assert(sizeof(FName) == 0x8);
}