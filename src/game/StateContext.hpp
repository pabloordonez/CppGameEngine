#ifndef __GAME_STATE_CONTEXT_H__
#define __GAME_STATE_CONTEXT_H__

#include "Base.hpp"

namespace Game
{
	class BattleTankApplication;

	class StateContext
	{
	public:
		explicit StateContext(BattleTankApplication* application);
		
		BattleTankApplication* getApplication();

	private:
		BattleTankApplication* application;
	};
}

#endif