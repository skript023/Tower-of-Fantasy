#pragma once
#include "fwddec.hpp"
#include "fname_pool.hpp"

namespace big
{
	enum class EInternalObjectFlags : int32_t
	{
		None = 0,
		Native = 1 << 25,
		Async = 1 << 26,
		AsyncLoading = 1 << 27,
		Unreachable = 1 << 28,
		PendingKill = 1 << 29,
		RootSet = 1 << 30,
		NoStrongReference = 1 << 31
	};

	template<typename Fn>
	inline Fn GetVFunction(const void* instance, std::size_t index)
	{
		auto vtable = *reinterpret_cast<const void***>(const_cast<void*>(instance));
		return reinterpret_cast<Fn>(vtable[index]);
	}

	class FUObjectItem
	{
	public:
		UObject* m_object; //0x0000
		int32_t m_flags; //0x0008
		int32_t m_cluster_index; //0x000C
		int32_t m_serial_number; //0x0010
		
		inline bool is_unreachable() const
		{
			return !!(m_flags & static_cast<std::underlying_type_t<EInternalObjectFlags>>(EInternalObjectFlags::Unreachable));
		}
		inline bool is_pending_kill() const
		{
			return !!(m_flags & static_cast<std::underlying_type_t<EInternalObjectFlags>>(EInternalObjectFlags::PendingKill));
		}
		UObject* get_valid_object();
	};
	static_assert(sizeof(FUObjectItem) == 0x18);

	class TUObjectArray
	{
	public:
		inline int32_t num() const
		{
			return m_num_elements;
		}

		inline int32_t capacity() const
		{
			return m_max_elements;
		}

		inline bool valid_index(int index) const
		{
			return index < num() && index >= 0;
		}

		inline UObject* get_by_index(uint32_t index)
		{
			if (valid_index(index))
			{
				auto object_items = get_object_pointer(index);
				if (object_items && object_items->get_valid_object())
				{
					return object_items->get_valid_object();
				}
			}

			return nullptr;
		}

		inline FUObjectItem* get_item_by_index(uint32_t index)
		{
			if (index < m_num_elements)
			{
				return m_objects[index];
			}
			return nullptr;
		}

		inline FUObjectItem* get_object_pointer(uint32_t index)
		{
			uint32_t chunk_index = index / num_elements_per_chunks;
			uint32_t within_chunk_index = index % num_elements_per_chunks;

			if (!valid_index(index)) return nullptr;

			if (chunk_index >= m_num_chunks) return nullptr;

			if (index >= m_max_elements) return nullptr;

			auto m_chunk = m_objects[chunk_index];
			if (!m_chunk) return nullptr;

			return m_chunk + within_chunk_index;
		}

		int64_t get_allocated_size() const
		{
			return m_max_chunks * sizeof(FUObjectItem*) + m_num_chunks * num_elements_per_chunks * sizeof(FUObjectItem);
		}

		inline FUObjectItem& operator[](int Index)
		{
			FUObjectItem* item_pointer = get_object_pointer(Index);
			if (item_pointer) return *item_pointer;
		}

	private:
		FUObjectItem** m_objects; //0x0010
		FUObjectItem* m_pre_allocate_object; //0x0018
		uint32_t m_max_elements; //0x0020
		uint32_t m_num_elements; //0x0024
		uint32_t m_max_chunks; //0x0028
		uint32_t m_num_chunks; //0x002C
		enum
		{
			num_elements_per_chunks = 64 * 1024,
		};
	};
	static_assert(sizeof(TUObjectArray) == 0x20);

	class FUObjectArray
	{
	public:
		int32_t m_obj_first_gc_Index; //0x0000
		int32_t m_obt_last_non_gc_index; //0x0004
		int32_t m_max_objects_not_considered_by_gc; //0x0008
		bool m_open_for_disregard_for_gc; //0x000C
		TUObjectArray m_obj_objects; //0x0010

		inline FUObjectItem* index_to_object(int32_t Index)
		{
			if (Index < m_obj_objects.num())
			{
				return const_cast<FUObjectItem*>(&m_obj_objects[Index]);
			}
			return nullptr;
		}
	};
	static_assert(sizeof(FUObjectArray) == 0x30);

	class UObject
	{
	public:
		FPointer m_vtable_object; //0x0000
		int32_t m_object_flags; //0x0008
		int32_t m_internal_index; //0x000C
		UClass* m_class; //0x0010
		FName m_name; //0x0018
		UObject* m_outer; //0x0020
	public:
		static TUObjectArray* get_global_object();

		std::string get_name() const;

		std::string get_fullname() const;

		const char* get_name_ex() const;

		const char* get_fullname_ex() const;

		template<typename T>
		inline static T find_object(const std::string& name)
		{
			for (int i = 0; i < get_global_object()->num(); ++i)
			{
				auto object = get_global_object()->get_by_index(i);
				
				if (object)
				{
					if (object->get_fullname() == name)
					{
						return static_cast<T>(object);
					}
				}
			}
			return nullptr;
		}

		inline static UClass* find_class(const std::string& name)
		{
			return find_object<UClass*>(name);
		}

		template<typename T>
		inline static T* get_object_casted(std::size_t index)
		{
			return static_cast<T*>(get_global_object()->get_by_index(index));
		}

		bool IsA(UClass* cmp) const;

		template<typename T>
		inline T* CreateDefaultObject()
		{
			return static_cast<T*>(CreateDefaultObject());
		}

		inline static UClass* static_class()
		{
			static auto ptr = UObject::find_class("Class CoreUObject.Object");
			return ptr;
		}

		void process_event(UFunction* function, void* parms);
		void Process_event(UFunction* func, void* params);
	};
	static_assert(sizeof(UObject) == 0x28, "UObject not properly sized.");

	class UField : public UObject
	{
	public:
		UField* Next;
	};

	class UEnum : public UField
	{
	public:
		FString CppType; //0x0030 
		TArray<TPair<FName, uint64_t>> Names; //0x0040 
		__int64 CppForm; //0x0050 
	};

	class UStruct : public UField
	{
	public:
		UStruct* SuperField;
		UField* Children;
		int32_t PropertySize;
		int32_t MinAlignment;
		char pad_0x0048[0x40];
	};

	class UScriptStruct : public UStruct
	{
	public:
		char pad_0x0088[0x10]; //0x0088
	};

	class UFunction : public UStruct
	{
	public:
		__int32 FunctionFlags; //0x0088
		__int16 RepOffset; //0x008C
		__int8 NumParms; //0x008E
		char pad_0x008F[0x1]; //0x008F
		__int16 ParmsSize; //0x0090
		__int16 ReturnValueOffset; //0x0092
		__int16 RPCId; //0x0094
		__int16 RPCResponseId; //0x0096
		class UProperty* FirstPropertyToInit; //0x0098
		UFunction* EventGraphFunction; //0x00A0
		__int32 EventGraphCallOffset; //0x00A8
		char pad_0x00AC[0x4]; //0x00AC
		void* Func; //0x00B0
	};

	class UClass : public UStruct
	{
	public:
		char pad_0x0088[0x198]; //0x0088

		inline UObject* CreateDefaultObject(class UFunction* function, void* parms)
		{
			return GetVFunction<UObject* (*)(UClass*)>(this, 0x73)(this);
		}
	};

	class UProperty : public UField
	{
	public:
		__int32 m_array_dim; //0x0030 
		__int32 m_element_size; //0x0034 
		FQWord m_property_flags; //0x0038
		__int32 m_property_size; //0x0040 
		char pad_0x0044[0xC]; //0x0044
		__int32 m_offset; //0x0050 
		char pad_0x0054[0x24]; //0x0054
	};
}