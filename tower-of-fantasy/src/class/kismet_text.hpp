#pragma once
#include "native_invoker.hpp"

namespace big
{
	class UKismetTextLibrary : public UObject
	{
	public:
		static UClass* static_class()
		{
			if (!g_native_invoker->m_kismet_text_library) 
				g_native_invoker->m_kismet_text_library = g_native_invoker->get_class<UClass*>("Class Engine.KismetTextLibrary");

			return g_native_invoker->m_kismet_text_library;
		}

		FString convert_text_to_string(const FText& InText)
		{
			static auto fn = g_native_invoker->get_native("Function Engine.KismetTextLibrary.Conv_TextToString");

			g_native_invoker->m_convert_text_to_string_params.m_in_text = InText;

			this->process_event(fn, &g_native_invoker->m_convert_text_to_string_params);

			return g_native_invoker->m_convert_text_to_string_params.m_return_value;
		}
	};
}