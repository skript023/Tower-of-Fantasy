#pragma once
#include "../fwddec.hpp"
#include "../vector.hpp"

namespace big
{
#pragma pack(push, 1)
	class FMinimalViewInfo
	{
	public:
		Vector3 m_location; // 0x1B00
		Vector3 m_rotation; // 0x1B0C
		float m_field_of_view; // 0x1B18
		float m_desired_fov; // 0x0x1B1C
		float m_ortho_width; // 0x0x1B20
		float m_ortho_near_clip_plane; // 0x0x1B24
		float m_ortho_far_clip_plane; // 0x0x1B28
		float m_aspect_ratio; // 0x0x1B2C
	};


	class FCameraCacheEntry
	{
	public:
		float m_time_stamp; // 0x1AF0
		char pad_4[0xC]; // 0x1AF4
		FMinimalViewInfo m_view_info; // 0x1B00

	public:
		Vector2 project_world_to_screen(Vector3 location)
		{
			Vector2 m_screen_location;
			Matrix m_matrix = this->m_view_info.m_rotation;
			Vector3 axisX, axisY, axisZ;

			axisX = Vector3(m_matrix.m[0][0], m_matrix.m[0][1], m_matrix.m[0][2]);
			axisY = Vector3(m_matrix.m[1][0], m_matrix.m[1][1], m_matrix.m[1][2]);
			axisZ = Vector3(m_matrix.m[2][0], m_matrix.m[2][1], m_matrix.m[2][2]);

			Vector3 v_delta = location - this->m_view_info.m_location;
			Vector3 v_transformed(v_delta.dot(axisY), v_delta.dot(axisZ), v_delta.dot(axisX));

			if (v_transformed.z < 1.f) v_transformed.z = 1.f;

			Vector2 m_screen_center(float(g_pointers->m_screen->x / 2), float(g_pointers->m_screen->y / 2));
			float fov_angle = (g_pointers->m_screen->x / g_pointers->m_screen->y) / (16.0f / 9.0f) * tanf(this->m_view_info.m_field_of_view * (float)M_PI / 360.f);

			m_screen_location.x = ((float)g_pointers->m_screen->x * .5f) + v_transformed.x * ((float)g_pointers->m_screen->x * .5f) / fov_angle / v_transformed.z;
			m_screen_location.y = ((float)g_pointers->m_screen->y * .5f) - v_transformed.y * ((float)g_pointers->m_screen->x * .5f) / fov_angle / v_transformed.z;
			return m_screen_location;
		}

	private:
		D3DXMATRIX matrix(Vector3 rot, Vector3 origin = { 0.f, 0.f, 0.f })
		{
			float radPitch = (rot.x * float(M_PI) / 180.f);
			float radYaw = (rot.y * float(M_PI) / 180.f);
			float radRoll = (rot.z * float(M_PI) / 180.f);

			float SP = sinf(radPitch);
			float CP = cosf(radPitch);
			float SY = sinf(radYaw);
			float CY = cosf(radYaw);
			float SR = sinf(radRoll);
			float CR = cosf(radRoll);

			D3DMATRIX matrix;
			matrix.m[0][0] = CP * CY;
			matrix.m[0][1] = CP * SY;
			matrix.m[0][2] = SP;
			matrix.m[0][3] = 0.f;

			matrix.m[1][0] = SR * SP * CY - CR * SY;
			matrix.m[1][1] = SR * SP * SY + CR * CY;
			matrix.m[1][2] = -SR * CP;
			matrix.m[1][3] = 0.f;

			matrix.m[2][0] = -(CR * SP * CY + SR * SY);
			matrix.m[2][1] = CY * SR - CR * SP * SY;
			matrix.m[2][2] = CR * CP;
			matrix.m[2][3] = 0.f;

			matrix.m[3][0] = origin.x;
			matrix.m[3][1] = origin.y;
			matrix.m[3][2] = origin.z;
			matrix.m[3][3] = 1.f;

			return matrix;
		}
	};

	class PlayerCameraManager
	{
	public:
		char pad_0000[0x1AF0]; //0x0000
		FCameraCacheEntry m_camera_cache; //0x1AF0
	};
#pragma pack(pop)
}