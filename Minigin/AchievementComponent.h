#pragma once
#include "BaseComponent.h"
#include "IObserver.h"
#include <steam_api.h>

#define _ACH_ID( id, name ) { id, #id, name, "", 0, 0 }

namespace GameEngine
{
	class GameObject;

	struct Achievement_t
	{
		int m_eAchievementID;
		const char* m_pchAchievementID;
		char m_rgchName[128];
		char m_rgchDescription[256];
		bool m_bAchieved;
		int m_iIconImage;
	};

	enum EAchievements
	{
		ACH_WIN_ONE_GAME = 0,
		ACH_WIN_100_GAMES = 1,
		ACH_TRAVEL_FAR_ACCUM = 2,
		ACH_TRAVEL_FAR_SINGLE = 3,
	};


	class CSteamAchievements final: public BaseComponent, public IObserver<int>
	{
	public:
		CSteamAchievements(GameObject* pGameObject);
		~CSteamAchievements();

		bool RequestStats();
		bool SetAchievement(const char* ID);

		STEAM_CALLBACK(CSteamAchievements, OnUserStatsReceived, UserStatsReceived_t,
			m_CallbackUserStatsReceived);
		STEAM_CALLBACK(CSteamAchievements, OnUserStatsStored, UserStatsStored_t,
			m_CallbackUserStatsStored);
		STEAM_CALLBACK(CSteamAchievements, OnAchievementStored,
			UserAchievementStored_t, m_CallbackAchievementStored);

		void Notify(const int& messageFromSubject)override;

	private:
		int m_iAppID; // Our current AppID
		Achievement_t m_Achievement; // Achievements data
		int m_iNumAchievements; // The number of Achievements
		bool m_bInitialized; // Have we called Request stats and received the callback?

		const int m_ScoreAchievement = 500;
	};
}


