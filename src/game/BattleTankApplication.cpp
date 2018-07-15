#include "BattleTankApplication.hpp"
#include "StateContext.hpp"
#include "SplashState.hpp"
#include "StatisticsState.hpp"

namespace Game
{
	BattleTankApplication::BattleTankApplication() :
		ApplicationBase::Application(),
		context(this),
		resourceManager()
	{
	}

	void BattleTankApplication::start()
	{
		ApplicationBase::getWindow()->setVerticalSyncEnabled(true);
		ApplicationBase::start("Battle Tank", 800, 600, 32, false);
	}

	void BattleTankApplication::initialize()
	{
		auto stateManager = ApplicationBase::getStateManager();
		
		stateManager->registerState<SplashState>(States::Splash, context);
		stateManager->registerState<StatisticsState>(States::Statistics, context);
		stateManager->requestPush(States::Splash);
		stateManager->requestPush(States::Statistics);
	}

	ResourceManager* BattleTankApplication::getResourceManager()
	{
		return &resourceManager;
	}
}