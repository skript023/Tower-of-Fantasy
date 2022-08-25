#pragma once
#include "imgui.h"

#pragma warning(disable:4244 4267 )

namespace big::draw
{
	typedef struct
	{
		DWORD R;
		DWORD G;
		DWORD B;
		DWORD A;
	}RGBA;

	inline std::string string_to_utf8(const std::string& str)
	{
		int nwLen = ::MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1.f, NULL, 0);
		wchar_t* pwBuf = new wchar_t[nwLen + 1.f];
		ZeroMemory(pwBuf, nwLen * 2 + 2);
		::MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.length(), pwBuf, nwLen);
		int nLen = ::WideCharToMultiByte(CP_UTF8, 0, pwBuf, -1.f, NULL, NULL, NULL, NULL);
		char* pBuf = new char[nLen + 1.f];
		ZeroMemory(pBuf, nLen + 1.f);
		::WideCharToMultiByte(CP_UTF8, 0, pwBuf, nwLen, pBuf, nLen, NULL, NULL);
		std::string retStr(pBuf);
		delete[]pwBuf;
		delete[]pBuf;
		pwBuf = NULL;
		pBuf = NULL;
		return retStr;
	}

	inline void draw_stroke_text(float x, float y, RGBA* color, const char* str)
	{
		ImFont a;
		std::string utf_8_1 = std::string(str);
		std::string utf_8_2 = string_to_utf8(utf_8_1);
		ImGui::GetForegroundDrawList()->AddText(ImVec2(x, y - 1.f), ImGui::ColorConvertFloat4ToU32(ImVec4(1.f / 255.0f, 1.f / 255.0f, 1.f / 255.0f, 255 / 255.0f)), utf_8_2.c_str());
		ImGui::GetForegroundDrawList()->AddText(ImVec2(x, y + 1.f), ImGui::ColorConvertFloat4ToU32(ImVec4(1.f / 255.0f, 1.f / 255.0f, 1.f / 255.0f, 255 / 255.0f)), utf_8_2.c_str());
		ImGui::GetForegroundDrawList()->AddText(ImVec2(x - 1.f, y), ImGui::ColorConvertFloat4ToU32(ImVec4(1.f / 255.0f, 1.f / 255.0f, 1.f / 255.0f, 255 / 255.0f)), utf_8_2.c_str());
		ImGui::GetForegroundDrawList()->AddText(ImVec2(x + 1.f, y), ImGui::ColorConvertFloat4ToU32(ImVec4(1.f / 255.0f, 1.f / 255.0f, 1.f / 255.0f, 255 / 255.0f)), utf_8_2.c_str());
		ImGui::GetForegroundDrawList()->AddText(ImVec2(x, y), ImGui::ColorConvertFloat4ToU32(ImVec4(color->R / 255.0f, color->G / 255.0f, color->B / 255.0f, color->A / 255.0f)), utf_8_2.c_str());
	}

	inline void draw_filled_rect(float x, float y, float w, float h, RGBA* color)
	{
		ImGui::GetForegroundDrawList()->AddRectFilled(ImVec2(x, y), ImVec2(x + w, y + h), ImGui::ColorConvertFloat4ToU32(ImVec4(color->R / 255.0f, color->G / 255.0f, color->B / 255.0f, color->A / 255.0f)), 0, 0);
	}

	inline void draw_circle_filled(float x, float y, float radius, RGBA* color)
	{
		ImGui::GetForegroundDrawList()->AddCircleFilled(ImVec2(x, y), radius, ImGui::ColorConvertFloat4ToU32(ImVec4(color->R / 255.0f, color->G / 255.0f, color->B / 255.0f, color->A / 255.0f)));
	}

	inline void draw_circle(float x, float y, float radius, RGBA* color, int segments)
	{
		ImGui::GetForegroundDrawList()->AddCircle(ImVec2(x, y), radius, ImGui::ColorConvertFloat4ToU32(ImVec4(color->R / 255.0f, color->G / 255.0f, color->B / 255.0f, color->A / 255.0f)), segments);
	}

	inline void draw_triangle(float x1, float y1, float x2, float y2, float x3, float y3, RGBA* color, float thickne)
	{
		ImGui::GetForegroundDrawList()->AddTriangle(ImVec2(x1, y1), ImVec2(x2, y2), ImVec2(x3, y3), ImGui::ColorConvertFloat4ToU32(ImVec4(color->R / 255.0f, color->G / 255.0f, color->B / 255.0f, color->A / 255.0f)), thickne);
	}

	inline void draw_triangle_filled(float x1, float y1, float x2, float y2, float x3, float y3, RGBA* color)
	{
		ImGui::GetForegroundDrawList()->AddTriangleFilled(ImVec2(x1, y1), ImVec2(x2, y2), ImVec2(x3, y3), ImGui::ColorConvertFloat4ToU32(ImVec4(color->R / 255.0f, color->G / 255.0f, color->B / 255.0f, color->A / 255.0f)));
	}

	inline void draw_line(float x1, float y1, float x2, float y2, RGBA* color, float thickness)
	{
		ImGui::GetForegroundDrawList()->AddLine(ImVec2(x1, y1), ImVec2(x2, y2), ImGui::ColorConvertFloat4ToU32(ImVec4(color->R / 255.0f, color->G / 255.0f, color->B / 255.0f, color->A / 255.0f)), thickness);
	}

	inline void draw_corner_box(float x, float y, float w, float h, float borderPx, RGBA* color)
	{
		draw_filled_rect(x + borderPx, y, w / 3, borderPx, color);
		draw_filled_rect(x + w - w / 3 + borderPx, y, w / 3, borderPx, color);
		draw_filled_rect(x, y, borderPx, h / 3, color);
		draw_filled_rect(x, y + h - h / 3 + borderPx * 2, borderPx, h / 3, color);
		draw_filled_rect(x + borderPx, y + h + borderPx, w / 3, borderPx, color);
		draw_filled_rect(x + w - w / 3 + borderPx, y + h + borderPx, w / 3, borderPx, color);
		draw_filled_rect(x + w + borderPx, y, borderPx, h / 3, color);
		draw_filled_rect(x + w + borderPx, y + h - h / 3 + borderPx * 2, borderPx, h / 3, color);
	}
}