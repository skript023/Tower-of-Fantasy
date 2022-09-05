#pragma once
#include "../fwddec.hpp"
#include "../uobject.hpp"

namespace big
{
#pragma pack(push, 1)
	class ObjectiveProgress
	{
	public:
		int64_t m_quest_id; //0x0000
		int64_t m_objective_id; //0x0008
		bool m_is_completed; //0x0010
		bool m_optional; //0x0011
		int16_t m_is_failed;  //0x0012
		int m_progress;  //0x0014
		int m_needed_amount;  //0x0018
		int m_cur_failed_time;  //0x001C
		int m_max_failed_time;  //0x0020
	};
	static_assert(sizeof(ObjectiveProgress) == 0x24);

	class AutoAcceptQuestArray
	{
	public:
		int64_t m_quest_id; //0x0000
		int m_time_left; //0x0008
		bool m_is_not_satisfy; //0x000C
		bool m_has_accept; //0x000D
		char pad_000E[0x2]; //0x000E
		TArray <ObjectiveProgress*> m_objective_progress; //0x0010
		bool m_need_nortify_teammate; //0x0020
		bool m_need_rpc; //0x0021
		char pad_0022[0x6]; //0x0022
	}; //0x00
	static_assert(sizeof(AutoAcceptQuestArray) == 0x28);

	class QuestInProgress
	{
	public:
		int m_quest_id; //0x0000
		TArray <ObjectiveProgress*> m_objective_progress; //0x0008
		int m_quest_status; //0x0018
		uint8_t m_need_remove; //0x0019
		char pad_0020[0x57];
	};
	static_assert(sizeof(QuestInProgress) == 0x70);

	class QuestComponent : public UObject
	{
	public:
		char pad_0028[144]; //0x0028
		TArray<QuestInProgress*> m_quest_in_progress; //0x00B8
		TArray<class QuestSubmitted*> m_quest_submitted; //0x00C8
		int64_t m_last_submitted_quest; //0x00D8
		int64_t m_last_tracking_quest; //0x00E0
		int m_tracking_quest; //0xE8
		TArray<class TrackQuestArray*> m_track_quest_array; //0x00F0
		TArray<AutoAcceptQuestArray*> m_auto_accept_quest_array; //0x0100
	};
	static_assert(sizeof(QuestComponent) == 0x10C);
#pragma pack(pop)
}