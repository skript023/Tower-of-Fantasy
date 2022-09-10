#pragma once
#include "../fwddec.hpp"

namespace big
{
	#pragma pack(push, 1)
	class CapsuleComponent
	{
	public:
		char pad_0000[0x1E0];
		Vector3 m_position;//0x1E0
	};

	class Pawn
	{
	public:
		char pad_0000[0x61]; //0x0000
		uint8_t m_godmode; //0x0061
		char pad_0062[0x236]; //0x0062
		class CharacterMovement* m_chara_movement; //0x0298
		class CapsuleComponent* m_capsule_component; //0x02A0
		char pad_02A8[0x98]; //0x02A8
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
		class StandAloneHottaAttribute* m_stand_alone_attributes; //0x0790
		bool m_is_ability_initialized; //0x0798
		char pad_0799[0x5CF]; //0x0799
		int m_selected_waeapon_id; //0x0D68
		char pad_0D6C[0x67B]; //0x0D6C
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
		char pad_1AA4[0x61C]; //1AA4
		bool m_cant_second_jump; //0x20C0
		bool m_cant_be_change_weapon; //0x20C2
		bool m_cant_open_bag; //0x20C3
		bool m_cant_use_evade_skill; //0x20C4
		bool m_cant_use_professional_skill; //0x20C5
		bool m_cant_use_artifact_skill; //0x20C6
		bool m_cant_show_artifact_skill; //0x20C7
		bool m_cant_use_item; //0x20C0
		bool m_cant_weapon_hold_in_hand; //0x20C8
		bool m_cant_jump; //0x20C9
		bool m_cant_crouch; //0x20CA
		bool m_cant_surmount; //0x20CB
		bool m_cant_use_locked_direction_actor; //0x20CC
		char pad_20CD[0x27]; //0x20CD
		int m_trigger_open_treasure_box;
		int m_guide_id_in_not_ready;
		char pad_20FC[0xD4]; //0x20FC
		int m_rand_bean; //0x21D0
		int m_cur_bean_count; //0x21D4
		int64_t m_change_time; //0x21D8
		char pad_21E0[0x188];
		bool m_skateboard_starting; //0x2368
		bool m_skateboard_sliding; //0x2369
		bool m_skateboard_stopping; //0x236A
		char pad_236B;
		bool m_skateboard_sprint_flag; //0x236C
		bool m_is_skateboard_jumping; //0x236D
		short pad_236E;
		class CurrentSkateBoard* m_current_skate_board; //0x2370
		int m_skateboard_type; //0x2378
		char pad_237C[0x23C]; //0x237C
		float m_gravity; //0x25B8
		char pad_25BC[0x24]; //0x25BC
		float m_max_swim_speed; //0x25E0
		char pad_25E4[0x11B0];
		float m_server_current_exp_mult; //0x3794
		char pad_3798[0x1E00]; //0x3798
		bool m_glide_sprint_launching_flag; //0x5598
		bool m_start_gliding; //0x5599
		bool m_gliding; //0x559A
		bool m_gliding_aiming; //0x559B
		bool m_glide_launching; //0x559C
		char pad_559D[0x57]; //0x559D
		float m_min_gliding_height; //0x55F4
		float m_jump_height; //0x55F8
		bool m_gliding_sprinted; //0x55FC
	};
	static_assert(sizeof(Pawn) == 0x55FD);

	#pragma pack(pop)
}