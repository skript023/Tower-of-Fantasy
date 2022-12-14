#pragma once
#include "fwddec.hpp"
#include "unreal_engine/game_instance.hpp"
#include "unreal_engine/ulevel_array.hpp"
#include "unreal_engine/quest_component.hpp"

namespace big
{
	#pragma pack(push, 1)

	class PlayerNavigation
	{
	public:
		char pad_0000[0x1E0];
		Vector3 m_position;
	};

	class GetNavigation
	{
	public:
		char pad_0000[0xC8];
		class PlayerNavigation* m_player_navigation; //0x00C8
	};

	class Navigation
	{
	public:
		char pad_0000[0x9F4];
		class GetNavigation* m_get_navigation; //0x09F4
	};

	class GWorld : public UObject
	{
	public:
		void* pad_0028; //0x0028
		class PersistentLevel* m_persist_level; //0x0030
		class NetDriver* m_net_driver; //0x0038
		class LineBatcher* m_line_batcher; //0x0040
		class PersistentLineBatcher* m_persist_line_batcher; //0x0048
		class ForegroundLineBatcher* m_forground_line_batcher; //0x0050
		char pad_0058[0xD0]; //0x0058
		class GameState* m_game_state; //0x0128
		char pad_0130[0x10]; //0x0130
		TArray<class ULevel*> m_level; //0x0140
		char pad_0150[0x38]; //0x0150
		class OwningGameInstance* m_game_instance; //0x0188
	};
	static_assert(sizeof(GWorld) == 0x190);

	class Engine : public UObject
	{
	public:
		char pad_0028[136]; //0x0000
		class UFont* m_font; //0x00B0
		char pad_00B8[1736]; //0x00B8
		class GameViewport** m_viewport; //0x0780
	};
	static_assert(sizeof(Engine) == 0x788);

	#pragma pack(pop)
}