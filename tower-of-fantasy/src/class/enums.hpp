#pragma once

enum EFindName
{
    FNAME_Find,
    FNAME_Add,
    FNAME_Replace_Not_Safe_For_Threading,
};

enum EHottaCurrencyType
{

};

enum ECharacterProficiencyType
{
	CHARACTERPROFICIENCYTYPE_NONE,
	CHARACTERPROFICIENCYTYPE_HELPEDPERSON,
	CHARACTERPROFICIENCYTYPE_HELPER,
	CHARACTERPROFICIENCYTYPE_MAX
};

enum class EGameActivityType
{
	GAT_TEAM_CLONE,
	GAT_SINGLE_CLONE,
	GAT_WORMHOLE,
	GAT_TREASURE,
	GAT_EXAM,
	GAT_WORLD_BOSS,
	GAT_ASTRAL_PLANE,
	GAT_SOLO_LEAGUE,
	GAT_REWARD_QUEST,
	GAT_WORLD_EVENT,
	GAT_HOOK_CLONE,
	GAT_GUILD_TASK,
	GAT_FEED,
	GAT_RANDOM_RUINS,
	GAT_ORIENTEERING,
	GAT_VOID_CLONE,
	GAT_SIGN,
	GAT_EXPLORE,
	GAT_DREAM_CLONE,
	GAT_GUILD_CAMPFIRE,
	GAT_GUILD_ANSWER,
	GAT_GUILD_AUCTION,
	GAT_BIG_SECRET,
	GAT_BREAK_FATE,
	GAT_2V2,
	GAT_DANGEROUS_INTRUDER,
	GAT_ABILITY_TRAINING,
	GAT_RANDOM_IDOLUM,
	GAT_SPECIAL_ASTRAL_PLANE,
	GAT_LEVY_CLONE,
	GAT_IN_MATCHING,
	GAT_INVALID,
	GAT_MAX
};

enum ETowerExploreType
{
	ETE_Type_Easy,
	ETE_Type_Normal,
	ETE_Type_Hard,
	ETE_Type_Crazy,
	ETE_Type_Unknown,
	ETE_Type_MAX
};

struct HottaAwardProgressData
{
	int64_t m_award_id;
	int m_today_available_count;
	int m_today_obtained_count;
	struct LastUpdateTime
	{

	};
};