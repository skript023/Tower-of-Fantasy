#pragma once
#include "../fwddec.hpp"
#include "pawn.hpp"
#include "attribute_set.hpp"
#include "character_movement.hpp"
#include "skill_component.hpp"

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
		char pad_028[72]; //0x268
		class Unk_1* m_unk;
	};

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