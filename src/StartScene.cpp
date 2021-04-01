#include "StartScene.h"
#include <algorithm>
#include "Game.h"
#include "glm/gtx/string_cast.hpp"
#include "EventManager.h"

StartScene::StartScene()
{
	StartScene::start();
	SoundManager::Instance().load("../Assets/audio/Button.wav", "BT", SOUND_SFX);
	SoundManager::Instance().load("../Assets/audio/Bgm_1.mp3", "Bgm", SOUND_MUSIC);
	SoundManager::Instance().playMusic("Bgm", -1, 0);
	SoundManager::Instance().setMusicVolume(15);
	SoundManager::Instance().setSoundVolume(20);
}

StartScene::~StartScene()
= default;

void StartScene::draw()
{
	TextureManager::Instance()->draw("bgp", 400, 300, 0, 255, true);
	drawDisplayList();
}

void StartScene::update()
{
	updateDisplayList();
}

void StartScene::clean()
{
	removeAllChildren();
}

void StartScene::handleEvents()
{
	EventManager::Instance().update();

	// Keyboard Events
	if(EventManager::Instance().isKeyDown(SDL_SCANCODE_ESCAPE))
	{
		TheGame::Instance()->quit();
	}

	if(EventManager::Instance().isKeyDown(SDL_SCANCODE_1))
	{
		TheGame::Instance()->changeSceneState(PLAY_SCENE);
	}
}

void StartScene::start()
{
	TextureManager::Instance()->load("../Assets/textures/bgp.jpg", "bgp");
	
	const SDL_Color orange = { 255, 165, 0, 255 };
	m_pStartLabel = new Label("Cyber Link", "Consolas", 80, orange, glm::vec2(400.0f, 130.0f));
	m_pStartLabel->setParent(this);
	addChild(m_pStartLabel);
	
	const SDL_Color blue = { 0, 0, 255, 255 };
	m_pInstructionsLabel = new Label("Fight for your survival", "Consolas", 40, blue, glm::vec2(400.0f, 120.0f));
	m_pInstructionsLabel->setParent(this);
	//addChild(m_pInstructionsLabel);
	//

	m_pShip = new Ship();
	m_pShip->getTransform()->position = glm::vec2(400.0f, 300.0f); 
//	addChild(m_pShip); 

	// Start Button
	m_pStartButton = new Button();
	m_pStartButton->getTransform()->position = glm::vec2(400.0f, 400.0f);

	m_pStartButton->addEventListener(CLICK, [&]()-> void
		{
			SoundManager::Instance().playSound("BT", 0, -1);
			m_pStartButton->setActive(false);
			TheGame::Instance()->changeSceneState(PLAY_SCENE);
		});

	m_pStartButton->addEventListener(MOUSE_OVER, [&]()->void
		{
			m_pStartButton->setAlpha(128);
		});

	m_pStartButton->addEventListener(MOUSE_OUT, [&]()->void
		{
			m_pStartButton->setAlpha(255);
		});
	addChild(m_pStartButton);

	// Quit Button
	m_pQuitButton = new Button("../Assets/textures/QuitButton.png", "QuitButton");
	m_pQuitButton->getTransform()->position = glm::vec2(400.0f, 500.0f);

	m_pQuitButton->addEventListener(CLICK, [&]()-> void
		{
			SoundManager::Instance().playSound("BT", 0, -1);
			m_pQuitButton->setActive(false);
			TheGame::Instance()->quit();
		});

	m_pQuitButton->addEventListener(MOUSE_OVER, [&]()->void
		{
			m_pQuitButton->setAlpha(128);
		});

	m_pQuitButton->addEventListener(MOUSE_OUT, [&]()->void
		{
			m_pQuitButton->setAlpha(255);
		});
	addChild(m_pQuitButton);


	
}

