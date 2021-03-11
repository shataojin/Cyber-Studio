#include "LoseScene.h"
#include <algorithm>
#include "Game.h"
#include "glm/gtx/string_cast.hpp"
#include "EventManager.h"

LoseScene::LoseScene()
{
	LoseScene::start();
}

LoseScene::~LoseScene()
= default;

void LoseScene::draw()
{
	drawDisplayList();
}

void LoseScene::update()
{
	updateDisplayList();
}

void LoseScene::clean()
{
	removeAllChildren();
}

void LoseScene::handleEvents()
{
	EventManager::Instance().update();

	// Button Events
	m_pRestartButton->update();

	// Keyboard Events
	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_ESCAPE))
	{
		TheGame::Instance()->quit();
	}

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_1))
	{
		TheGame::Instance()->changeSceneState(PLAY_SCENE);
	}
}

void LoseScene::start()
{
	TextureManager::Instance()->load("../Assets/textures/background.png", "background");
	const SDL_Color blue = { 0, 0, 255, 255 };
	m_label = new Label("GG", "Dock51", 80, blue, glm::vec2(400.0f, 40.0f));
	m_label->setParent(this);
	addChild(m_label);

	// Restart Button
	m_pRestartButton = new Button("../Assets/textures/restartButton.png", "restartButton");
	m_pRestartButton->getTransform()->position = glm::vec2(400.0f, 400.0f);
	m_pRestartButton->addEventListener(CLICK, [&]()-> void
		{
			m_pRestartButton->setActive(false);
			TheGame::Instance()->changeSceneState(PLAY_SCENE);
		});

	m_pRestartButton->addEventListener(MOUSE_OVER, [&]()->void
		{
			m_pRestartButton->setAlpha(128);
		});

	m_pRestartButton->addEventListener(MOUSE_OUT, [&]()->void
		{
			m_pRestartButton->setAlpha(255);
		});

	addChild(m_pRestartButton);

	//next level button
	m_nextButton = new Button("../Assets/textures/restartButton.png", "restartButton");
	m_nextButton->getTransform()->position = glm::vec2(500.0f, 400.0f);
	m_nextButton->addEventListener(CLICK, [&]()-> void
		{
			m_nextButton->setActive(false);
			TheGame::Instance()->changeSceneState(PLAY_SCENE);
		});

	m_nextButton->addEventListener(MOUSE_OVER, [&]()->void
		{
			m_nextButton->setAlpha(128);
		});

	m_nextButton->addEventListener(MOUSE_OUT, [&]()->void
		{
			m_nextButton->setAlpha(255);
		});

	addChild(m_nextButton);

	// exit button
	m_exitbutton = new Button("../Assets/textures/restartButton.png", "restartButton");
	m_exitbutton->getTransform()->position = glm::vec2(600.0f, 400.0f);
	m_exitbutton->addEventListener(CLICK, [&]()-> void
		{
			m_exitbutton->setActive(false);
			TheGame::Instance()->changeSceneState(END_SCENE);
		});

	m_exitbutton->addEventListener(MOUSE_OVER, [&]()->void
		{
			m_exitbutton->setAlpha(128);
		});

	m_exitbutton->addEventListener(MOUSE_OUT, [&]()->void
		{
			m_exitbutton->setAlpha(255);
		});

	addChild(m_exitbutton);
}

