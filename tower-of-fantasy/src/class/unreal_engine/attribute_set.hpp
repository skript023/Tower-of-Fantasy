#pragma once
#include "../fwddec.hpp"

namespace big
{
	#pragma pack(push, 1)

	class AttributeSet
	{
	public:
		char pad_0000[0x218]; //0x0000
		float m_critical_base; //0x0218
		char pad_021C[112]; //0x021C
		float m_attack; //0x28C
	};
	static_assert(sizeof(AttributeSet) == 0x290);

	#pragma pack(pop)
}