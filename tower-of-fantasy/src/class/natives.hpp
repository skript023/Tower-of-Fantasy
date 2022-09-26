#pragma once
#include "fname_pool.hpp"
#include "vector.hpp"
#include "enums.hpp"
#include <class/fhit_result.hpp>

namespace big
{
	struct WorldToScreenParam
	{
		Vector3 m_world_location;
		Vector2 m_screen_location;
		bool m_viewport_relative;
		bool m_return;
	};

	struct ServerQuestUpdateProgress
	{
		FName m_quest_id;
		FName m_objective_id;
		int m_progress;
		bool m_is_add;
	};

	struct ServerBuyGHAIntegral
	{
		EHottaCurrencyType m_currency_type;
		int m_amount;
	};

	struct Server_MatchSoloLeague
	{
		bool m_is_battle_ai;
	};

	struct Server_PayTransferServerReq
	{
		int m_server_id;
	};

	struct ServerSpawnExtraEquipedWeapon
	{
		int64_t m_weapon_item;
	};

	struct ServerUnlockAvatar
	{
		uint8_t m_in_avatar_type;
		int64_t m_in_avatar_id;
		bool m_in_permanent_unlock;
		float m_in_expiration_time;
	};

	struct TeleportWithLoading
	{
		FVector m_location;
		Rotator m_rotator;
	};

	struct SpawnArtifactArrow
	{
		float m_duration_time;
	};

	struct ClientSetTreasureOpened
	{
		FName m_treasure_box_id;
		bool m_static;
		int64_t m_open_time;
	};

	struct ServerResetTreasureBox
	{
		FName m_treasure_box_id;
		bool m_static;
	};

	struct SetCharacterExp
	{
		int m_new_exp;
		bool m_return_value;
	};

	struct ServerRecordAbnormalJumpSectionData
	{
		std::string m_collect_info;
		std::string m_comment2;
		uint8_t m_anti_type;
	};

	struct ClientUpdateAccumulateCurrencyArraySingle
	{
		EHottaCurrencyType m_currency_type;
		int m_amount;
	};

	struct ClientOnCurrencyAmountChanged
	{
		EHottaCurrencyType m_currency_type;
		int64_t m_add_amount;
		int64_t m_current_value;
		EHottaOutputPathType m_path_type;
		bool m_need_show_tips;
		bool m_need_show_in_chat;
	};

	struct ServerAddExp
	{
		int m_value;
		int m_limit_index;
	};

	struct ServerUpgradeItem
	{
		FName m_item_id;
		FName m_target_id;
		int m_target_count;
	};

	struct ServerCheckQuestRpcRequire
	{
		EQuestRpcRequireType m_require_type;
		FName m_quest_id;
		FName m_objective_id;
	};

	struct ServerRecordExploreProgress
	{
		FName m_drop_id;
		int m_drop_num;
	};

	struct ServerMatrixStrengthen
	{
		int m_slot_index;
		EItemContainType m_contain_type;
	};

	struct ServerUpgradeStarLevel
	{
		int m_choose_item_slot;
		EItemContainType m_contain_type;
	};

	struct ServerMatrixUnequiped
	{
		int m_weapon_slot;
		EItemContainType m_contain_type;
		EWeaponMatrixSlot m_weapon_matrix_slot;
	};

	struct ServerMatrixEquiped
	{
		int m_weapon_slot;
		EItemContainType m_contain_type;
		EWeaponMatrixSlot m_weapon_matrix_slot;
		int m_matrix_slot;
	};

	struct Conv_TextToString
	{
		struct FText m_in_text;
		struct FString m_return_value;
	};

	struct Server_ProjectileActorHit
	{
		void* m_self;
		void* m_target;
		struct SimpleHit* m_simple_hit;
		char padding[88];
		struct PredictionKey* m_prediction_key;
	};

	struct SetProjectileTrackActor
	{
		void* m_actor;
	};

	struct ServerSetHP
	{
		float m_health;
		EDamageReason m_damage_reason;
	};

	struct SetHP
	{
		float m_health;
		EDamageReason m_damage_reason;
		bool m_is_read_damage;
		float m_read_damage;
	};

	struct ServerSetCharacterLevel
	{
		int m_level;
	};

	struct ServerSetLocationAndRotation
	{
		FVector m_location;
		Rotator m_rotation;
		bool m_close_server_accept_client_authoritative_position;
	};

	struct ServerSetHaveFallDamage
	{
		bool m_in_have_fall_damage;
	};

	struct ServerKickPlayer
	{
		FString m_target;
	};

	struct ServerLotteryExtract
	{
		FName m_module_name;
		int m_extract_count;
		bool m_is_discount;
	};

	struct ServerPickItem
	{
		FName m_item_id;
		int m_amount;
		class ItemActor* m_owner;
		int m_slot;
	};

	struct ServerOpenTreasureBox
	{
		FName m_tresure_id;
		int m_quality;
		bool m_static;
		int64_t m_recover_time;
		int64_t m_open_time;
	};

	struct SetEnergy
	{
		float m_energy;
	};

	struct SetCharacterLevel
	{
		int m_level;
		bool m_refresh_attribute;
		bool m_server_rep;
		bool m_return;
	};

	struct GetMaxMana
	{
		float m_return;
	};

	struct ClientSetAutoCombat
	{
		bool m_enable;
	};

	struct K2_SetActorLocationAndRotation
	{
		FVector m_new_location; //0x0000
		Rotator m_new_rotation; //0x000C
		bool m_sweep; //0x0018
		char pad_0019[3]; //0x0019
		FHitResult m_sweep_hit_result; //0x001C
		bool m_teleport; //0x00A8
		bool m_return; //0x00A9
	};

	struct K2_SetActorLocation
	{
		FVector m_new_location; //0x0000
		bool m_sweep; //0x000C
		char pad_000D[3]; //0x000D
		FHitResult m_sweep_hit_result; //0x0010
		bool m_teleport; //0x009C
		bool m_return; //0x009D
	};

	struct K2_SetActorRelativeLocation
	{
		FVector m_new_location; //0x0000
		bool m_sweep; //0x000C
		char pad_000D[3]; //0x000D
		FHitResult m_sweep_hit_result; //0x0010
		bool m_teleport; //0x009C
	};

	struct K2_GetRootComponent
	{
		class RootComponent* m_return;
	};

	struct K2_TeleportTo
	{
		FVector m_location;
		Rotator m_rotation;
		bool m_return;
	};
	
	struct K2_AddRelativeLocation
	{
		FVector m_new_location; //0x0000
		bool m_sweep; //0x000C
		char pad_000D[3]; //0x000D
		FHitResult m_sweep_hit_result; //0x0010
		bool m_teleport; //0x009C
	};

	struct K2_AddLocalOffset
	{
		FVector m_new_location; //0x0000
		bool m_sweep; //0x000C
		char pad_000D[3]; //0x000D
		FHitResult m_sweep_hit_result; //0x0010
		bool m_teleport; //0x009C
	};

	struct K2_SetRelativeLocation
	{
		FVector m_new_location; //0x0000
		bool m_sweep; //0x000C
		char pad_000D[3]; //0x000D
		FHitResult m_sweep_hit_result; //0x0010
		bool m_teleport; //0x009C
	};

	struct GetForwardVector
	{
		FVector m_return;
	};

	struct ReceivePointDamage
	{
		float m_damage;
		EDamageType m_damage_type;
		FVector m_hit_location;
		FVector m_hit_normal;
		class PrimitiveComponent* m_hit_component;
		FName m_bone_name;
		FVector m_shot_from_direction;
		PlayerController* m_insigned_by;
		AActor* m_damage_cuaser;
		FHitResult m_hit_info;
	};

	struct K2_DrawText 
	{
		void* m_render_font;
		FString m_render_text;
		FVector2D m_screen_pos;
		FVector2D m_scale;
		FLinearColor m_render_color;
		float m_kerning;
		FLinearColor m_shadow_color;
		FVector2D m_shadow_offset;
		bool m_center_x;
		bool m_center_y;
		bool m_outlined;
		FLinearColor m_outline_color;
	};

	struct K2_DrawLine
	{
		FVector2D m_position_a;
		FVector2D m_position_b;
		float m_thickness;
		FLinearColor m_render_color;
	};

	struct K2_DrawBox
	{
		FVector2D m_position;
		FVector2D m_size;
		float m_thickness;
		FLinearColor m_render_color;
	};

	struct ServerSetRotation
	{
		FRotator m_rotation;
	};

	struct ClientSetRotation
	{
		FRotator m_rotation;
		bool m_reset_camera;
	};

	struct ServerTriggerAnotherOmnislashLinkedEffect
	{
		AcknowledgedPawn* m_hotta_character;
		FVector m_location;
		FRotator m_rotation;
		bool m_reset;
	};

	struct ServerTriggerOmnislashLinkedEffect
	{
		AcknowledgedPawn* m_hotta_character;
		FVector m_new_attached_location;
		FVector m_last_attached_location;
		bool m_reset;
		bool m_change_target;
	};
}