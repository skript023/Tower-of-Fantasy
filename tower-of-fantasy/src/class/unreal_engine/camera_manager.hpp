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
		Vector3 project_world_to_screen(Vector3 location)
		{
			Vector3 m_screen_location = Vector3(0, 0, 0);

			Matrix m_matrix = this->m_view_info.m_rotation;

			Vector3 axisX, axisY, axisZ;

			axisX = Vector3(m_matrix.m[0][0], m_matrix.m[0][1], m_matrix.m[0][2]);
			axisY = Vector3(m_matrix.m[1][0], m_matrix.m[1][1], m_matrix.m[1][2]);
			axisZ = Vector3(m_matrix.m[2][0], m_matrix.m[2][1], m_matrix.m[2][2]);

			Vector3 v_delta = location - this->m_view_info.m_location;
			Vector3 v_transformed = Vector3(v_delta.dot(axisY), v_delta.dot(axisZ), v_delta.dot(axisX));

			if (v_transformed.z < 1.f)
				v_transformed.z = 1.f;

			float FovAngle = this->m_view_info.m_field_of_view + 0x18;

			iVector2 m_screen_divider{ 20, 20 };
			iVector2 m_screen_center = m_screen_divider / *g_pointers->m_screen;

			m_screen_location.x = m_screen_center.x + v_transformed.x * (m_screen_center.x / tanf(FovAngle * (float)M_PI / 360.f)) / v_transformed.z;
			m_screen_location.y = m_screen_center.y - v_transformed.y * (m_screen_center.y / tanf(FovAngle * (float)M_PI / 360.f)) / v_transformed.z;

			return m_screen_location;
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