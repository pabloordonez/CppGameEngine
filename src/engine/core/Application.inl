namespace Engine
{
	namespace Core
	{
		template <class StateId, class StateContext>
		Application<StateId, StateContext>::Application() :
			title("Game"),
			size(800, 600),
			bpp(32),
			fixedFps(60),
			window(),
			clock(),
			time(),
			previousVideoMode(),
			stateManager()
		{
		}

		template <class StateId, class StateContext>
		void Application<StateId, StateContext>::start(const std::string title, const sf::Vector2i size, const int bpp, const bool fullScreen)
		{
			// gets the current video mode and check if the new one is valid.
			this->title = title;
			this->size = size;
			this->bpp = bpp;

			previousVideoMode = sf::VideoMode::getDesktopMode();
			currentVideoMode = sf::VideoMode(size.x, size.y);

			if (!currentVideoMode.isValid()) {
				std::cout << "Video mode not allowed.";
				return;
			}

			// creates the window.
			window.create(currentVideoMode, title, fullScreen ? sf::Style::Fullscreen : sf::Style::Default);

			// initialize the application.
			initialize();
			stateManager.applyChanges();

			// run the application.
			run();
		}

		template <class StateId, class StateContext>
		void Application<StateId, StateContext>::start(const std::string title, const int width, const int height, const int bpp, const bool fullScreen)
		{
			start(title, sf::Vector2i(width, height), bpp, fullScreen);
		}

		template <class StateId, class StateContext>
		void Application<StateId, StateContext>::close()
		{
			window.close();
		}

		template <class StateId, class StateContext>
		const sf::Vector2i Application<StateId, StateContext>::getSize() const
		{
			return this->size;
		}

		template <class StateId, class StateContext>
		const std::string Application<StateId, StateContext>::getTitle() const
		{
			return this->title;
		}

		template <class StateId, class StateContext>
		const int Application<StateId, StateContext>::getBpp() const
		{
			return this->bpp;
		}

		template <class StateId, class StateContext>
		const int Application<StateId, StateContext>::getFixedFps() const
		{
			return this->fixedFps;
		}

		template <class StateId, class StateContext>
		void Application<StateId, StateContext>::processEvents()
		{
			sf::Event event;

			while (window.pollEvent(event))
			{
				stateManager.processEvents(event);

				switch (event.type)
				{
				case sf::Event::Closed:
					close();
					break;
				}
			}
		}

		template <class StateId, class StateContext>
		void Application<StateId, StateContext>::update(const sf::Time& time)
		{
			stateManager.update(time);
		}

		template <class StateId, class StateContext>
		void Application<StateId, StateContext>::fixUpdate(const sf::Time& time)
		{
			stateManager.fixUpdate(time);
		}

		template <class StateId, class StateContext>
		void Application<StateId, StateContext>::render(sf::RenderTarget& renderTarget)
		{
			stateManager.render(renderTarget);
		}

		template <class StateId, class StateContext>
		sf::RenderWindow* Application<StateId, StateContext>::getWindow()
		{
			return &window;
		}

		template <class StateId, class StateContext>
		StateManager<StateId, StateContext>* Application<StateId, StateContext>::getStateManager()
		{
			return &stateManager;
		}

		template <class StateId, class StateContext>
		void Application<StateId, StateContext>::setFixedFramesPerSecond(int fps)
		{
			fixedFps = fps;
		}

		template <class StateId, class StateContext>
		void Application<StateId, StateContext>::run()
		{
			auto fixedDeltaTime = 1.0f / (float)fixedFps;
			auto timeSinceLastUpdate = sf::Time::Zero;

			while (window.isOpen())
			{
				time = clock.restart();
				timeSinceLastUpdate += time;

				if (timeSinceLastUpdate.asSeconds() > fixedDeltaTime)
				{
					fixUpdate(timeSinceLastUpdate);
					timeSinceLastUpdate = sf::Time::Zero;
				}

				processEvents();
				update(time);

				window.clear();
				render(window);
				window.display();
			}
		}
	}
}