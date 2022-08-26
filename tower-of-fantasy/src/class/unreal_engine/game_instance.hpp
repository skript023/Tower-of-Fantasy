#pragma once
#include "../fwddec.hpp"
#include "pawn.hpp"
#include "attribute_set.hpp"
#include "character_movement.hpp"
#include "skill_component.hpp"
#include "camera_manager.hpp"

namespace big
{
	#pragma pack(push, 1)

	class Unk_1
	{
	public:
		char pad000[0x64];
		uint8_t no_clip;
	};

	class PlayerController
	{
	public:
		char pad_0000[0x260];
		class Pawn* m_pawn; //0x260
		char pad_0268[72]; //0x268
		class Unk_1* m_unk; //0x2B0
		char pad_2B8[16]; //0x2B8
		class PlayerCameraManager* m_camera_manager; //0x2C8

		Vector3 project_world_to_screen_ex(Vector3 location)
		{
			Vector3 m_screen_location = Vector3(0, 0, 0);

			auto m_camera_manager = this->m_camera_manager;
			if (*(uintptr_t*)m_camera_manager == NULL) return Vector3(0.f, 0.f, 0.f);

			auto camera_cache = m_camera_manager->m_camera_cache;

			Matrix m_matrix(camera_cache.m_view_info.m_rotation);

			Vector3 axisX, axisY, axisZ;

			axisX = Vector3(m_matrix.m[0][0], m_matrix.m[0][1], m_matrix.m[0][2]);
			axisY = Vector3(m_matrix.m[1][0], m_matrix.m[1][1], m_matrix.m[1][2]);
			axisZ = Vector3(m_matrix.m[2][0], m_matrix.m[2][1], m_matrix.m[2][2]);

			Vector3 v_delta = location - camera_cache.m_view_info.m_location;
			Vector3 v_transformed = Vector3(v_delta.dot(axisY), v_delta.dot(axisZ), v_delta.dot(axisX));

			if (v_transformed.z < 1.f)
				v_transformed.z = 1.f;

			float FovAngle = camera_cache.m_view_info.m_field_of_view + 0x18;

			iVector2 m_screen_divider{ 20, 20 };
			iVector2 m_screen_center = m_screen_divider / *g_pointers->m_screen;

			m_screen_location.x = m_screen_center.x + v_transformed.x * (m_screen_center.x / tanf(FovAngle * (float)M_PI / 360.f)) / v_transformed.z;
			m_screen_location.y = m_screen_center.y - v_transformed.y * (m_screen_center.y / tanf(FovAngle * (float)M_PI / 360.f)) / v_transformed.z;

			return m_screen_location;
		}
	};
	static_assert(sizeof(PlayerController) == 0x2D0);

	class Player
	{
	public:
		char pad_0000[0x30];
		class PlayerController* m_player_controller;
	};

	class LocalPlayer
	{
	public:
		class Player* m_player[30];
	};

	class GameState
	{
	public:
		virtual ~GameState() = default;
		int m_game_state; 
	};

	class OwningGameInstance
	{
	public:
		char pad_0000[0x38]; //0x0000
		class LocalPlayer* m_local_player; //0x0038
	};

	#pragma pack(pop)
}