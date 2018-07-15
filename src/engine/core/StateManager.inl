namespace Engine
{
	namespace Core
	{
		template <class StateId, class StateContext>
		StateManager<StateId, StateContext>::StateManager() :
			states(),
			requests(),
			stateFactory()
		{
		}

		template <class StateId, class StateContext>
		void StateManager<StateId, StateContext>::processEvents(const sf::Event& event)
		{
			// iterate the stack in reverse.
			for (auto iterator = states.rbegin(); iterator != states.rend(); ++iterator)
			{
				if ((*iterator)->processEvents(event))
				{
					break;
				}
			}

			applyChanges();
		}

		template <class StateId, class StateContext>
		void StateManager<StateId, StateContext>::update(const sf::Time& time)
		{
			// iterate the stack in reverse.
			for (auto iterator = states.rbegin(); iterator != states.rend(); ++iterator)
			{
				(*iterator)->update(time);
			}
		}

		template <class StateId, class StateContext>
		void StateManager<StateId, StateContext>::fixUpdate(const sf::Time& time)
		{
			// iterates the stack in reverse.
			for (auto iterator = states.rbegin(); iterator != states.rend(); ++iterator)
			{
				(*iterator)->fixUpdate(time);
			}
		}

		template <class StateId, class StateContext>
		void StateManager<StateId, StateContext>::render(sf::RenderTarget& renderTarget)
		{
			for (auto iterator = states.begin(); iterator != states.end(); ++iterator)
			{
				(*iterator)->render(renderTarget);
			}
		}

		template <class StateId, class StateContext>
		void StateManager<StateId, StateContext>::applyChanges()
		{
			for (auto request : requests)
			{
				switch (request.type)
				{
				case RequestType::Push:
					states.push_back(createState(request.stateId));
					break;

				case RequestType::Pop:
					assert(!states.empty());

					auto lastState = states.end();

					(*lastState)->end();
					states.pop_back();
					break;
				}
			}

			requests.clear();
		}

		template <class StateId, class StateContext>
		template <class StateType>
		void StateManager<StateId, StateContext>::registerState(StateId stateId, StateContext& context)
		{
			auto factory = stateFactory.find(stateId);

			// the state shouldn't exists in the factory.
			assert(factory == stateFactory.end());

			stateFactory[stateId] = [this, context]()
			{
				return StatePointer(new StateType(*this, context));
			};
		}

		template <class StateId, class StateContext>
		void StateManager<StateId, StateContext>::requestPush(const StateId stateId)
		{
			requests.push_back(Request(RequestType::Push, stateId));
		}

		template <class StateId, class StateContext>
		void StateManager<StateId, StateContext>::requestPop()
		{
			requests.push_back(Request(RequestType::Pop, stateId));
		}
	}
}