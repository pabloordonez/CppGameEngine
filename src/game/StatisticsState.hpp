#ifndef	__GAME_STATISTICS_STATE_H__
#define __GAME_STATISTICS_STATE_H__

#include "Base.hpp"

namespace Game
{
	class StatisticsState : public StateBase
	{
	public:
		StatisticsState(StateManagerBase& manager, StateContext context);

		virtual void start();
		virtual void end();

		virtual bool processEvents(const Event& event);
		virtual void update(const Time& time);
		virtual void fixUpdate(const Time& time);
		virtual void render(RenderTarget& renderTarget);

	private:
		Font font;
		Text fpsText;
		Time elapsed;
		int lastSecondFrames;
		int currentFrames;
	};
}

#endif