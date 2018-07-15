#ifndef __ETERNITY_CORE_GAME_H__
#define __ETERNITY_CORE_GAME_H__

#include <vector>
#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include "StateManager.hpp"
#include "Utility.hpp"

namespace Engine
{
	namespace Core
	{
		template <class StateId, class StateContext>
		class Application
		{
		public:
			Application();

			void start(const std::string title, const sf::Vector2i size, const int bpp, const bool fullScreen);
			void start(const std::string title, const int width, const int height, const int bpp, const bool fullScreen);
			void close();

			const sf::Vector2i getSize() const;
			const std::string getTitle() const;
			const int getBpp() const;
			const int getFixedFps() const;
			sf::RenderWindow* getWindow();
			StateManager<StateId, StateContext>* getStateManager();

		protected:
			virtual void initialize() = 0;

			void processEvents();
			void update(const sf::Time& time);
			void fixUpdate(const sf::Time& time);
			void render(sf::RenderTarget& renderTarget);

			void setFixedFramesPerSecond(int fps);

		private:
			void run();

		private:
			std::string title;
			sf::Vector2i size;
			int bpp;
			int fixedFps;

			sf::RenderWindow window;
			sf::Clock clock;
			sf::Time time;
			sf::VideoMode currentVideoMode;
			sf::VideoMode previousVideoMode;
			
			StateManager<StateId, StateContext> stateManager;
		};
	}
}

#include "Application.inl"

#endif