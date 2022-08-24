#pragma once
#include "../fwddec.hpp"

namespace big
{
	#pragma pack(push, 1)

	class CharacterMovement
	{
	public:
		char pad_0000[0x150]; //0x0000
		class ACharacter* m_character_owner; //0x0150
		float m_gravity_scale; //0x0158
		float m_max_step_height; //0x015C
		float m_jump_velocity; //0x0160
		float m_jump_of_jump_z_factor; //0x0164
		float m_wakable_floor_angle; //0x0168
		float m_walkable_floor_z; //0x016C
		bool m_freeze_entity; //0x0170
		char pad_0171[43]; //0x0170
		float m_movement_speed; //0x019C
		float m_crouch_speed; //0x01A0
		float m_swim_speed; //0x01A4
		float m_fly_speed; //0x01A8
		float m_custom_move_speed; //0x01AC
		float m_max_accelerationl; //0x1B0
		char pad_01B4[36]; //0x01B4
		float m_air_boost_control_multiplier; //0x01D8
	};
	static_assert(sizeof(CharacterMovement) == 0x1DC);

	#pragma pack(pop)
}