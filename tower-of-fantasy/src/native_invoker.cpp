#include "native_invoker.hpp"
#include "utility/unreal_engine_utility.hpp"

namespace big
{
	NativeInvoker::NativeInvoker()
	{
		g_native_invoker = this;
	}

	NativeInvoker::~NativeInvoker()
	{
		g_native_invoker = nullptr;
	}

	template <typename T>
	T NativeInvoker::get_class(std::string name)
	{
		if (auto uclass = UObject::find_class(name))
		{
			return static_cast<T>(uclass);
		}

		return nullptr;
	}

	UFunction* NativeInvoker::get_native(std::string_view name)
	{
		if (auto function = UObject::find_object<UFunction*>(name); function)
		{
			return function;
		}
		return nullptr;
	}

	UFunction* NativeInvoker::get_native(uint32_t name)
	{
		if (auto function = UObject::find_object<UFunction*>(name); function)
		{
			return function;
		}
		return nullptr;
	}

	void NativeInvoker::execute_native_function(std::string className, std::string functionName, void* parameters)
	{
		if (!m_class) m_class = UObject::find_class(className);
		if (!m_function) m_function = UObject::find_object<UFunction*>(functionName);

		m_class->process_event(m_function, parameters);
	}

	void NativeInvoker::execute_native_function(UClass* classInstance, std::string functionName, void* parameters)
	{
		if (!m_function) m_function = UObject::find_object<UFunction*>(functionName);

		classInstance->process_event(m_function, parameters);
	}

	std::string NativeInvoker::quest_require_type(EQuestRpcRequireType requireType)
	{
	#define ENUM_STR(x)    \
		case x:             \
			return #x;

		switch (requireType)
		{
			ENUM_STR(EQuestRpcRequireType::QRT_COMPLETE)
			ENUM_STR(EQuestRpcRequireType::QRT_UPDATE)
			ENUM_STR(EQuestRpcRequireType::QRT_ACCEPT)
			ENUM_STR(EQuestRpcRequireType::QRT_MAX)
		}

		#undef ENUM_STR

		return "Invalid";
	}

	std::string NativeInvoker::get_output_path_type(EHottaOutputPathType PathType)
	{
		#define ENUM_STR(x)    \
			case x:             \
				return #x;

		switch (PathType)
		{
			ENUM_STR(EHottaOutputPathType::OutputPathType_None)
			ENUM_STR(EHottaOutputPathType::OutputPathType_Notify)
			ENUM_STR(EHottaOutputPathType::OutputPathType_ConfigChange)
			ENUM_STR(EHottaOutputPathType::OutputPathType_FromBag)
		}

		#undef ENUM_STR

		return "None";
	}
}