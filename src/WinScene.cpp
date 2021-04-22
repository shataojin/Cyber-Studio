#include "WinScene.h"
#include <algorithm>
#include "Game.h"
#include "glm/gtx/string_cast.hpp"
#include "EventManager.h"

WinScene::WinScene()
{
	WinScene::start();
	SoundManager::Instance().load("../Assets/audio/win.mp3", "WBgm", SOUND_MUSIC);
	SoundManager::Instance().playMusic("WBgm", 0, 0);
	SoundManager::Instance().setMusicVolume(100);
	SoundManager::Instance().setSoundVolume(20);
}

WinScene::~WinScene()
= default;

void WinScene::draw()
{
	TextureManager::Instance()->draw("winbgp", 400, 300, 0, 255, true);
	drawDisplayList();
}

void WinScene::update()
{
	updateDisplayList();
}

void WinScene::clean()
{
	removeAllChildren();
}

void WinScene::handleEvents()
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

void WinScene::start()
{
	TextureManager::Instance()->load("../Assets/textures/winbgp.jpg", "winbgp");
	const SDL_Color blue = { 0, 0, 255, 255 };
	m_label = new Label("GG", "Dock51", 80, blue, glm::vec2(400.0f, 100.0f));
	m_label->setParent(this);
	addChild(m_label);

	// Restart Button
	m_pRestartButton = new Button("../Assets/textures/restartButton.png", "restartButton");
	m_pRestartButton->getTransform()->position = glm::vec2(400.0f, 200.0f);
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
	m_nextButton = new Button("../Assets/textures/nextButton.png", "nextButton");
	m_nextButton->getTransform()->position = glm::vec2(400.0f, 300.0f);
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
	m_exitbutton = new Button("../Assets/textures/QuitButton.png", "quit");
	m_exitbutton->getTransform()->position = glm::vec2(400.0f, 400.0f);
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
