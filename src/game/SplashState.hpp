#ifndef	__GAME_SPLASH_STATE_H__
#define __GAME_SPLASH_STATE_H__

#include "Base.hpp"

namespace Game 
{
	class SplashState : public StateBase
	{
	public:
		SplashState(StateManagerBase& manager, StateContext context);

		virtual void start();
		virtual void end();

		virtual bool processEvents(const Event& event);
		virtual void update(const Time& time);
		virtual void fixUpdate(const Time& time);
		virtual void render(RenderTarget& renderTarget);

	private:
		Text titleText;
		Text startText;
		Text quitText;
		Sprite selectorSprite;
		int selectedOption;
		float movingForward;
	};
}

#endif