#pragma once
#include "uobject.hpp"
#include "enums.hpp"

namespace big
{
	struct FWeakObjectPtr
	{
	public:
		inline bool SerialNumbersMatch(FUObjectItem* ObjectItem) const
		{
			return ObjectItem->m_serial_number == this->m_object_serial_number;
		}

		bool IsValid() const
		{
			return Internal_IsValid(false, false);
		}

		UObject* Get() const
		{
			Internal_Get(false);
		}

		int32_t m_object_index;
		int32_t m_object_serial_number;
	private:
		inline bool Internal_IsValid(bool bEvenIfPendingKill, bool bThreadsafeTest) const
		{
			if (m_object_serial_number == 0)
			{
				assert(m_object_index == 0 || m_object_index == -1); // otherwise this is a corrupted weak pointer
				return false;
			}
			if (m_object_index < 0)
			{
				return false;
			}
			FUObjectItem* object_item = UObject::get_global_object()->get_item_by_index(m_object_index);
			if (!object_item)
			{
				return false;
			}
			if (!SerialNumbersMatch(object_item))
			{
				return false;
			}
			if (bThreadsafeTest)
			{
				return true;
			}
			return object_item->is_valid(bEvenIfPendingKill);
		}

		inline UObject* Internal_Get(bool bEvenIfPendingKill) const
		{
			UObject* result = nullptr;

			if (Internal_IsValid(true, true))
			{
				FUObjectItem* object_item = UObject::get_global_object()->get_item_by_index(m_object_index);
				if (object_item->is_valid(bEvenIfPendingKill))
				{
					result = object_item->m_object;
				}
			}
			return result;
		}
	};

	template<class T, class TWeakObjectPtrBase = FWeakObjectPtr>
	struct TWeakObjectPtr : public TWeakObjectPtrBase
	{
	public:
		inline T* Get() const 
		{
			return (T*)TWeakObjectPtrBase::Get();
		}

		inline T& operator*() const 
		{
			return *Get();
		}

		inline T* operator->() const
		{
			return Get();
		}

		inline bool IsValid() const
		{
			return TWeakObjectPtrBase::IsValid();
		}
	};
}