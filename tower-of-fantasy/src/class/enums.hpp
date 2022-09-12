#pragma once

enum EFindName
{
    FNAME_Find,
    FNAME_Add,
    FNAME_Replace_Not_Safe_For_Threading,
};

enum class EHottaCurrencyType
{
	Gold,
	FakeDiamond,
	Diamond,
	AchievementScore,
	WormholeCoin,
	Gem,
	GuildContribution,
	ArtifactCoin,
	EquipFragment,
	WormholeLuckyCoin,
	SoloLeagueCoin,
	Gem2,
	Gem3,
	LocalReputation1,
	LocalReputation2,
	LocalReputation3,
	LocalReputation4,
	LocalReputation5,
	HookCloneAssistContribution,
	Stamina,
	PrimaryEnergy,
	WeaponFragment,
	GenePointAttack,
	GuildCaption,
	PrimaryEnergy2,
	GuildMeritorious,
	LifeCrystal,
	HomeOre,
	HomePumpkin,
	HomeRattan,
	HomeMeat,
	HomeTwigs,
	HomeFish,
	HomeFishBones,
	HomeShellfish,
	HomeShell,
	GenePointAssist,
	GenePointDef,
	RegressionCoin,
	PrimaryEnergy3,
	PrimaryEnergy4,
	MiniGameCoin,
	HopkinsOrder1,
	SharePhotoCoin,
	WeaponFragmentUP1,
	WeaponFragmentUP2,
	EquipFragmentUP1,
	EquipFragmentUP2,
	HopkinsOrder2,
	IncarnationCoin,
	WeaponFragmentUP3,
	WeaponFragmentUP4,
	WeaponFragmentUP5,
	WeaponFragmentUP6,
	WeaponFragmentUP7,
	WeaponFragmentUP8,
	WeaponFragmentUP9,
	WeaponFragmentUP10,
	WeaponFragmentUP11,
	WeaponFragmentUP12,
	WeaponFragmentUP13,
	WeaponFragmentUP14,
	WeaponFragmentUP15,
	WeaponFragmentUP16,
	WeaponFragmentUP17,
	WeaponFragmentUP18,
	WeaponFragmentUP19,
	WeaponFragmentUP20,
	EquipFragmentUP3,
	EquipFragmentUP4,
	EquipFragmentUP5,
	EquipFragmentUP6,
	EquipFragmentUP7,
	EquipFragmentUP8,
	EquipFragmentUP9,
	EquipFragmentUP10,
	EquipFragmentUP11,
	EquipFragmentUP12,
	EquipFragmentUP13,
	EquipFragmentUP14,
	EquipFragmentUP15,
	EquipFragmentUP16,
	EquipFragmentUP17,
	EquipFragmentUP18,
	EquipFragmentUP19,
	EquipFragmentUP20,
	IncarnationCoin1,
	IncarnationCoin2,
	IncarnationCoin3,
	IncarnationCoin4,
	IncarnationCoin5,
	GameActivityCoin1,
	GameActivityCoin2,
	GameActivityCoin3,
	GameActivityCoin4,
	GameActivityCoin5,
	GameActivityCoin6,
	GameActivityCoin7,
	GameActivityCoin8,
	GameActivityCoin9,
	GameActivityCoin10,
	RegressionHelpCoin,
	CurrencyCount,
	EHottaCurrencyType_MAX
};

enum class ECharacterProficiencyType
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

enum class ETowerExploreType
{
	ETE_Type_Easy,
	ETE_Type_Normal,
	ETE_Type_Hard,
	ETE_Type_Crazy,
	ETE_Type_Unknown,
	ETE_Type_MAX
};

enum class EAntiplugCode
{
	Unkown,
	MontagePlayRate,
	TickDeltaTime,
	SkillFollow,
	EvadeBean,
	CheckSpeed,
	CheckLocation,
	GamePlayEvent,
	JumpSection,
	SendAttackTargetSpeed,
	GamePlayEventCount,
	SpawnActorRPC,
	Max
};

enum class EQuestRpcRequireType
{
    QRT_COMPLETE,
	QRT_UPDATE,
	QRT_ACCEPT,
	QRT_MAX
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