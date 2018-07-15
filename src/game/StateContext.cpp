#include "StateContext.hpp"

namespace Game
{
	StateContext::StateContext(BattleTankApplication* application) :
		application(application)
	{
	}

	BattleTankApplication* StateContext::getApplication() 
	{
		return application;
	}
}