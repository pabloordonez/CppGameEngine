#ifndef __ENGINE_CORE_STATE_H__
#define __ENGINE_CORE_STATE_H__

#include <SFML/Graphics.hpp>

namespace Engine
{
	namespace Core
	{
		template <class StateId, class StateContext>
		class StateManager;

		template <class StateId, class StateContext>
		class State
		{
		public:
			State(StateManager<StateId, StateContext>& manager, StateContext context);

			virtual void start() = 0;
			virtual void end() = 0;

			virtual bool processEvents(const sf::Event& event) = 0;
			virtual void update(const sf::Time& time) = 0;
			virtual void fixUpdate(const sf::Time& time) = 0;
			virtual void render(sf::RenderTarget& renderTarget) = 0;

		protected:
			StateManager<StateId, StateContext>* getManager();
			StateContext& getContext();

		private:
			StateManager<StateId, StateContext>* manager;
			StateContext context;
		};
	}
}

#include "State.inl"

#endif