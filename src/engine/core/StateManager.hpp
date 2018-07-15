#ifndef __ENGINE_CORE_STATE_MANAGER_H__
#define __ENGINE_CORE_STATE_MANAGER_H__

#include <vector>
#include <map>
#include <memory>
#include <functional>
#include <assert.h>
#include <SFML/Graphics.hpp>
#include "State.hpp"

namespace Engine
{
	namespace Core
	{
		template <class StateId, class StateContext>
		class StateManager
		{

		private:		
			typedef std::unique_ptr<State<StateId, StateContext>> StatePointer;

			enum RequestType
			{
				Push,
				Pop
			};

			struct Request
			{
				const RequestType type;
				const StateId stateId;

				Request(RequestType type, StateId stateId) : type(type), stateId(stateId)
				{
				}
			};

		public:
			StateManager();

			void processEvents(const sf::Event& event);
			void update(const sf::Time& time);
			void fixUpdate(const sf::Time& time);
			void render(sf::RenderTarget& renderTarget);

			template <class StateType>
			void registerState(StateId stateId, StateContext& context);
			void requestPush(const StateId stateId);
			void requestPop();
			void applyChanges();

		private:
			StatePointer createState(StateId stateId)
			{
				auto factory = stateFactory.find(stateId);
				assert(factory != stateFactory.end());
				auto state = (factory->second)();
				state->start();

				return state;
			}

		private:
			std::vector<StatePointer> states;
			std::vector<Request> requests;
			std::map<StateId, std::function<StatePointer()>> stateFactory;
		};
	}
}

#include "StateManager.inl"

#endif