#ifndef __GAME_BASE_H__
#define __GAME_BASE_H__

#include "../engine/core/Core.hpp"
#include "StateContext.hpp"

namespace Game
{
	using sf::Event;
	using sf::Time;
	using sf::RenderTarget;
	using sf::Font;
	using sf::Text;
	using sf::Texture;
	using sf::Sprite;

	using Engine::Core::Application;
	using Engine::Core::State;
	using Engine::Core::StateManager;
	using Engine::Core::ResourceManager;

	enum States
	{
		Splash,
		Game,
		Settings,
		Pause,
		Statistics
	};

	enum Textures
	{
		Selector
	};

	enum Fonts
	{
		FiraCode,
		ProFont
	};

	class StateContext;

	typedef Application<States, StateContext> ApplicationBase;
	typedef StateManager<States, StateContext> StateManagerBase;
	typedef State<States, StateContext> StateBase;
}

#endif