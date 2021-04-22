#include "EndScene.h"
#include <algorithm>
#include "Game.h"
#include "glm/gtx/string_cast.hpp"
#include "EventManager.h"

EndScene::EndScene()
{
	EndScene::start();
	SoundManager::Instance().load("../Assets/audio/win.mp3", "WBgm", SOUND_MUSIC);
	SoundManager::Instance().playMusic("WBgm", 0, 0);
	SoundManager::Instance().setMusicVolume(30);
	SoundManager::Instance().setSoundVolume(20);
}

EndScene::~EndScene()
= default;

void EndScene::draw()
{
	TextureManager::Instance()->draw("EndBpg", 400, 300, 0, 255, true);
	drawDisplayList();
}

void EndScene::update()
{
	updateDisplayList();
}

void EndScene::clean()
{
	removeAllChildren();
}

void EndScene::handleEvents()
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

void EndScene::start()
{
	TextureManager::Instance()->load("../Assets/textures/EndBpg.jpg", "EndBpg");
	const SDL_Color blue = { 0, 0, 255, 255 };
	m_label = new Label("you win !!!", "Dock51", 80, blue, glm::vec2(400.0f, 40.0f));
	m_label->setParent(this);
	addChild(m_label);

	// Restart Button
	m_pRestartButton = new Button("../Assets/textures/restartButton.png", "restartButton", RESTART_BUTTON);
	m_pRestartButton->getTransform()->position = glm::vec2(300.0f, 200.0f);
	m_pRestartButton->addEventListener(CLICK, [&]()-> void
		{
			Game::Instance()->round = 0;
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

	// exit button
	m_exitbutton = new Button("../Assets/textures/QuitButton.png", "quit");
	m_exitbutton->getTransform()->position = glm::vec2(500.0f, 200.0f);
	m_exitbutton->addEventListener(CLICK, [&]()-> void
		{
			m_exitbutton->setActive(false);
			TheGame::Instance()->quit();
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
