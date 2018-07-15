#include <iostream>
#include "SplashState.hpp"
#include "BattleTankApplication.hpp"

namespace Game
{
	SplashState::SplashState(StateManagerBase& manager, StateContext context) :
		StateBase::State(manager, context),
		titleText(),
		startText(),
		quitText(),
		selectorSprite(),
		selectedOption(0),
		movingForward(0.1f)
	{
	}

	void SplashState::start()
	{
		auto context = StateBase::getContext();
		auto manager = context.getApplication()->getResourceManager();
		auto textureContainer = manager->getTextureContainer();
		auto fontContainer = manager->getFontContainer();

		textureContainer->registerResource(Textures::Selector, "assets/selector.png");
		fontContainer->registerResource(Fonts::ProFont, "assets/ProFont.ttf");
		fontContainer->registerResource(Fonts::FiraCode, "assets/FiraCode.ttf");

		manager->loadAll([](ResourceManager::ResourceType type, int id, const std::string& fileName) -> void
		{ 
			std::cout << type << " - " << id << " - " << fileName << std::endl; 
		});

		titleText.setFont(*fontContainer->get(Fonts::ProFont));
		startText.setFont(*fontContainer->get(Fonts::FiraCode));
		quitText.setFont(*fontContainer->get(Fonts::FiraCode));

		titleText.setCharacterSize(64);
		startText.setCharacterSize(32);
		quitText.setCharacterSize(32);

		titleText.setFillColor(sf::Color::Red);
		startText.setFillColor(sf::Color::White);
		quitText.setFillColor(sf::Color::White);

		titleText.setString("Battle Tank");
		startText.setString("Start");
		quitText.setString("quit");

		auto titleRect = titleText.getLocalBounds();
		titleText.setOrigin(titleRect.left + titleRect.width / 2.0f, titleRect.top + titleRect.height / 2.0f);

		auto startRect = startText.getLocalBounds();
		startText.setOrigin(startRect.left + startRect.width / 2.0f, startRect.top + startRect.height / 2.0f);

		auto quitRect = quitText.getLocalBounds();
		quitText.setOrigin(quitRect.left + quitRect.width / 2.0f, quitRect.top + quitRect.height / 2.0f);

		auto selectorTexture = textureContainer->get(Textures::Selector);
		auto selectorRect = selectorTexture->getSize();
		selectorSprite.setTexture(*selectorTexture);
		selectorSprite.setColor(sf::Color::White);
		selectorSprite.setOrigin(selectorRect.x / 2.0f, selectorRect.y / 2.0f);
	}

	bool SplashState::processEvents(const Event& event)
	{
		if (event.type == sf::Event::EventType::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Down)
			{
				this->selectedOption++;
			}

			if (event.key.code == sf::Keyboard::Up)
			{
				this->selectedOption--;
			}

			this->selectedOption = Engine::Core::Numeric::clamp(this->selectedOption, 0, 1);
		}

		return false;
	}

	void SplashState::update(const Time& time)
	{
		auto size = StateBase::getContext().getApplication()->getSize();

		auto screenWidth = size.x;
		auto screenHeight = size.y;

		auto titlePosition = sf::Vector2f(screenWidth / 2.0f, 100);
		titleText.setPosition(titlePosition);

		auto startPosition = sf::Vector2f(screenWidth / 2.0f, 300);
		startText.setPosition(startPosition);

		auto quitPosition = sf::Vector2f(screenWidth / 2.0f, 350);
		quitText.setPosition(quitPosition);

		auto selectorPosition = selectorSprite.getPosition();
		selectorPosition.x += movingForward;

		if (selectorPosition.x < startPosition.x - 100)
		{
			movingForward = .15f;
			selectorPosition.x = startPosition.x - 100;
		}

		if (selectorPosition.x > startPosition.x - 80)
		{
			movingForward = -.15f;
			selectorPosition.x = startPosition.x - 80;
		}

		selectorPosition.x += movingForward * time.asSeconds();
		selectorPosition.y = (selectedOption == 0) ? startPosition.y : quitPosition.y;
		selectorSprite.setPosition(selectorPosition);
	}

	void SplashState::fixUpdate(const Time& time)
	{
	}

	void SplashState::render(RenderTarget& render)
	{
		render.draw(titleText);
		render.draw(startText);
		render.draw(quitText);
		render.draw(selectorSprite);
	}

	void SplashState::end()
	{
		StateBase::getContext().getApplication()->getResourceManager()->clearAll();
	}
}