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

struct HottaAwardProgressData
{
	int64_t m_award_id;
	int m_today_available_count;
	int m_today_obtained_count;
	struct LastUpdateTime
	{

	};
};