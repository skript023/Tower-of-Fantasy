#pragma once
#include "../fwddec.hpp"
#include "../vector.hpp"

namespace big
{
#pragma pack(push, 1)
	struct FMinimalViewInfo
	{
		Vector3 m_location; // 0x00(0x0c)
		Vector3 m_rotation; // 0x0c(0x0c)
		float m_field_of_view; // 0x18(0x04)
		float m_desired_fov; // 0x1c(0x04)
		float m_ortho_width; // 0x20(0x04)
		float m_ortho_near_clip_plane; // 0x24(0x04)
		float m_ortho_far_clip_plane; // 0x28(0x04)
		float m_aspect_ratio; // 0x2c(0x04)
	};

	struct FCameraCacheEntry
	{
		float m_time_stamp; // 0x00(0x04)
		char pad_4[0xc]; // 0x04(0x0c)
		FMinimalViewInfo m_view_info; // 0x10(0x5e0)
		bool project_world_to_screen(Vector3 location, Vector2& m_screen_location)
		{
			auto m_matrix = matrix(this->m_view_info.m_rotation);

			Vector3 axisX, axisY, axisZ;

			axisX = Vector3(m_matrix.m[0][0], m_matrix.m[0][1], m_matrix.m[0][2]);
			axisY = Vector3(m_matrix.m[1][0], m_matrix.m[1][1], m_matrix.m[1][2]);
			axisZ = Vector3(m_matrix.m[2][0], m_matrix.m[2][1], m_matrix.m[2][2]);

			Vector3 v_delta = location - this->m_view_info.m_location;
			Vector3 v_transformed = Vector3(v_delta.dot(axisY), v_delta.dot(axisZ), v_delta.dot(axisX));

			if (v_transformed.z < 1.f) v_transformed.z = 1.f;

			float fov_angle = this->m_view_info.m_field_of_view + 24.f;

			iVector2 m_screen_center(g_pointers->m_screen->x / 2, g_pointers->m_screen->y / 2);

			m_screen_location.x = (float)m_screen_center.x + v_transformed.x * (m_screen_center.x / tanf(fov_angle * (float)M_PI / 360.f)) / v_transformed.z;
			m_screen_location.y = (float)m_screen_center.y - v_transformed.y * (m_screen_center.y / tanf(fov_angle * (float)M_PI / 360.f)) / v_transformed.z;

			return true;
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
		FCameraCacheEntry m_camera_cache;
	};
#pragma pack(pop)
}