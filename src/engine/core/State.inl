namespace Engine
{
	namespace Core
	{
		template <class StateId, class StateContext>
		State<StateId, StateContext>::State(StateManager<StateId, StateContext>& manager, StateContext context) :
			manager(&manager),
			context(context)
		{
		}

		template <class StateId, class StateContext>
		StateManager<StateId, StateContext>* State<StateId, StateContext>::getManager()
		{
			return manager;
		}

		template <class StateId, class StateContext>
		StateContext& State<StateId, StateContext>::getContext()
		{
			return context;
		}
	}
}