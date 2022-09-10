#pragma once
#include "../fwddec.hpp"
#include "../uobject.hpp"

namespace big
{
#pragma pack(push, 1)
	class CAcceptedObjectiveProgress
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
	static_assert(sizeof(CAcceptedObjectiveProgress) == 0x24);

	class CObjectiveProgress
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
		char pad_0024[140];
	};
	static_assert(sizeof(CObjectiveProgress) == 0xB0);

	class AcceptedObjectiveProgress
	{
	public:
		CAcceptedObjectiveProgress m_accepted_objective[20];
	};

	class ObjectiveProgress
	{
	public:
		CObjectiveProgress m_objective_progress[20];
	};

	class CAutoAcceptQuestArray
	{
	public:
		int64_t m_quest_id; //0x0000
		int m_time_left; //0x0008
		bool m_is_not_satisfy; //0x000C
		bool m_has_accept; //0x000D
		char pad_000E[0x2]; //0x000E
		AcceptedObjectiveProgress* m_objective_progress; //0x0010
		int m_num_objective;
		int m_max_objective;
		bool m_need_nortify_teammate; //0x0020
		bool m_need_rpc; //0x0021
		char pad_0022[0x6]; //0x0022
	public:
		std::vector<CAcceptedObjectiveProgress> object_progress()
		{
			std::vector<CAcceptedObjectiveProgress> vector;
			for (int i = 0; i < m_num_objective; i++)
			{
				auto quest = this->m_objective_progress->m_accepted_objective[i];
				if (!quest.m_quest_id) continue;
				vector.push_back(quest);
			}
			return vector;
		}
	}; //0x00
	static_assert(sizeof(CAutoAcceptQuestArray) == 0x28);

	class CQuestInProgress
	{
	public:
		int64_t m_quest_id; //0x0000
		ObjectiveProgress* m_objective_progress; //0x0008
		int m_num_objective; //0x0010
		int m_max_objective; //0x0014
		int m_quest_status; //0x0018
		uint8_t m_need_remove; //0x0019
		char pad_0020[0x53]; //0x0020
	public:
		std::vector<CObjectiveProgress> object_progress()
		{
			std::vector<CObjectiveProgress> vector;
			for (int i = 0; i < m_num_objective; i++)
			{
				auto quest = this->m_objective_progress->m_objective_progress[i];
				if (!quest.m_quest_id) continue;
				vector.push_back(quest);
			}
			return vector;
		}
	};
	static_assert(sizeof(CQuestInProgress) == 0x70);

	class AutoAcceptQuestArray
	{
	public:
		CAutoAcceptQuestArray m_auto_accept_quest[20];
	};

	class QuestInProgress
	{
	public:
		CQuestInProgress m_quest_in_progress[20];
	};
	
	class QuestComponent : public UObject
	{
	public:
		char pad_0028[144]; //0x0028
		QuestInProgress* m_quest_in_progress; //0x00B8
		int m_num_progress;
		int m_max_progress;
		TArray<class QuestSubmitted*> m_quest_submitted; //0x00C8
		int64_t m_last_submitted_quest; //0x00D8
		int64_t m_last_tracking_quest; //0x00E0
		int m_tracking_quest; //0xE8
		TArray<class TrackQuestArray*> m_track_quest_array; //0x00F0
		AutoAcceptQuestArray* m_auto_accept_quest_array; //0x0100
		int m_num_accepted_quest;
		int m_max_accepted_quest;

	public:
		std::vector<CQuestInProgress> quest_in_progress()
		{
			std::vector<CQuestInProgress> vector;
			for (int i = 0; i < m_num_progress; i++)
			{
				auto quest = this->m_quest_in_progress->m_quest_in_progress[i];
				if (!quest.m_quest_id) continue;
				vector.push_back(quest);
			}
			return vector;
		}

		std::vector<CAutoAcceptQuestArray> accepted_quest()
		{
			std::vector<CAutoAcceptQuestArray> vector;
			for (int i = 0; i < m_num_accepted_quest; i++)
			{
				auto quest = this->m_auto_accept_quest_array->m_auto_accept_quest[i];
				if (!quest.m_quest_id) continue;
				vector.push_back(quest);
			}
			return vector;
		}
	};
	static_assert(sizeof(QuestComponent) == 0x10C);
#pragma pack(pop)
}