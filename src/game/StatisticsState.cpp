#include <iostream>
#include "StatisticsState.hpp"
#include "BattleTankApplication.hpp"

namespace Game
{
	StatisticsState::StatisticsState(StateManagerBase& manager, StateContext context) :
		StateBase::State(manager, context),
		font(),
		fpsText(),
		elapsed(Time::Zero),
		lastSecondFrames(0),
		currentFrames(0)
	{
	}

	void StatisticsState::start()
	{
		if (!font.loadFromFile("assets/FiraCode.ttf"))
		{
			std::cout << "Problems loading the pro font.";
			return;
		}

		fpsText.setFillColor(sf::Color::White);
		fpsText.setFont(font);
		fpsText.setCharacterSize(12);
		fpsText.setPosition(10, 10);
	}

	bool StatisticsState::processEvents(const Event& event)
	{
		return false;
	}

	void StatisticsState::update(const Time& time)
	{
		elapsed += time;
		currentFrames ++;

		if (elapsed.asSeconds() > 1)
		{
			elapsed = Time::Zero;
			lastSecondFrames = currentFrames;
			currentFrames = 0;			
		}
	}

	void StatisticsState::fixUpdate(const Time& time)
	{
	}

	void StatisticsState::render(RenderTarget& render)
	{
		fpsText.setString("FPS: " + Engine::Core::Strings::toString(lastSecondFrames));
		render.setView(render.getDefaultView());
		render.draw(fpsText);
	}

	void StatisticsState::end()
	{

	}
}