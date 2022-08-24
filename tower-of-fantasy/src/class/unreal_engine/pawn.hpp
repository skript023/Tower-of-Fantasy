#pragma once
#include "../fwddec.hpp"

namespace big
{
	#pragma pack(push, 1)

	class Pawn
	{
	public:
		char pad_0000[0x61]; //0x0000
		uint8_t m_godmode; //0x0061
		char pad_0062[0x236]; //0x0062
		class CharacterMovement* m_chara_movement; //0x0298
		char pad_02A0[0xA0]; //0x02A0
		bool m_is_crouch; //0x0340
		char pad_0341[0x17]; //0x0341
		int m_jump_count; //0x0358
		char pad_035C[0x2D0]; //0x035C
		bool m_is_armor_break; //0x062C
		char pad_62D[0x63]; //0x062D
		int m_level; //0x0690
		char pad_0694[0xEC]; //0x0694
		class SkillComponent* m_skill_component; //0x780
		class AttributeSet* m_attribute_set; //0x0788
		char pad_0790[0xC57]; //0x0790
		bool m_freeze_mobs; //0x13E7
		char pad_13E8[0x4B8]; //0x13E8
		bool m_fall_damage; //0x18A0
		char pad_18A1[0x1BF]; //0x18A1
		float m_game_speed; //0x1A60
		char pad_01A64[0x28]; //0x1A64
		int m_show_damage_distance; //0x1A8C
		int m_post_net_receive_velocity; //0x1A90
		int m_enable_rep_root_motion_source_flags;//0x1A94
		int pad_1A98; //0x1A98
		int m_dead_collision_profile_name;//0x1A9C
		int m_collision_capsule_r;//0x1AA0
		char pad_1AA4[0x72C]; //1AA4
		int m_rand_bean; //0x21D0
		int m_cur_bean_count; //0x21D4
		int64_t m_change_time; //0x21D8
		char pad_21E0[0x3D8];
		float m_gravity; //0x25B8
		char pad_25BC[0x24]; //0x25BC
		float m_swim_speed; //0x25E0
	};
	static_assert(sizeof(Pawn) == 0x25E4);

	#pragma pack(pop)
}