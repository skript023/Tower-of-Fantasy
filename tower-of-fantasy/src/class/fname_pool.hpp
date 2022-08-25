#pragma once
#include "fwddec.hpp"

namespace big
{
#pragma pack(push, 1)
    struct FNameEntry
    {
    public:
        int16_t m_key;

        union
        {
            char m_ansi_name[1024];
            wchar_t m_wide_name[1024];
        };

        uint32_t get_length() const
        {
            return m_key >> 6;
        }

        bool is_wide() const
        {
            return m_key & 1;
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
    };

    class FNameEntryAllocator
    {
    private:
        char frwLock[0x8];
    public:
        int32_t m_current_block;
        int32_t m_current_byte_cursor;
        int8_t* m_block[8192];

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
            return static_cast<uint32_t>(m_current_block + 1);
        }

        bool is_valid_index(int32_t key) const
        {
            uint32_t block = key >> 16;
            uint16_t offset = key;
            return is_valid_index(key, block, offset);
        }

        bool is_valid_index(int32_t key, uint32_t block, uint16_t offset) const
        {
            return (key >= 0 && block < num_blocks() && offset * 2 < 0x1FFFE);
        }
    };

	class FNamePool
	{
	public:
		FNameEntryAllocator m_entry_allocator;
		uint32_t ansi_count;
		uint32_t wide_count;
	};
#pragma pack(pop)
}