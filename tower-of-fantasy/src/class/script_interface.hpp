#pragma once
#include "fwddec.hpp"

namespace big
{
#pragma pack(push, 1)
	class FScriptInterface
	{
	private:
		UObject* ObjectPointer;
		void* InterfacePointer;

	public:
		inline UObject* GetObjects()
		{
			return ObjectPointer;
		}

		inline UObject*& GetObjectRef()
		{
			return ObjectPointer;
		}

		inline void* GetInterface() const
		{
			return ObjectPointer != nullptr ? InterfacePointer : nullptr;
		}
	};

	template<class InterfaceType>
	class TScriptInterface : public FScriptInterface
	{
	public:
		inline InterfaceType* operator->() const
		{
			return (InterfaceType*)GetInterface();
		}

		inline InterfaceType& operator*() const
		{
			return *((InterfaceType*)GetInterface());
		}

		inline operator bool() const
		{
			return GetInterface() != nullptr;
		}
	};
#pragma pack(pop)
}