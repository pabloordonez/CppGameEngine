#ifndef __GAME_BATTLE_TANK_GAME_H__
#define __GAME_BATTLE_TANK_GAME_H__

#include "Base.hpp"

namespace Game
{
	class BattleTankApplication : public ApplicationBase
	{
	public:
		BattleTankApplication();
		void start();
		ResourceManager* getResourceManager();

	protected:
		void initialize();		

	private:
		StateContext context;
		ResourceManager resourceManager;
	};
}

#endif