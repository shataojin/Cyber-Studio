#include "PlayScene.h"
#include "Game.h"
#include "EventManager.h"

// required for IMGUI
#include "imgui.h"
#include "imgui_sdl.h"
#include "Renderer.h"
#include "Util.h"

PlayScene::PlayScene()
{
	PlayScene::start();
	TextureManager::Instance()->load(".. / Assets / textures / s_bgp.png", "S_bgp");//not sure why its not working
	TextureManager::Instance()->draw("S_bgp", 0, 0, 0, 255, false);//not sure why its not working
	TextureManager::Instance()->load("../Assets/textures/s_bgp.png", "S_bgp");
	auto size = TextureManager::Instance()->getTextureSize("S_bgp");
	TextureManager::Instance()->draw("S_bgp", 0, 0, 0, 255, true);
	//setWidth(size.x);
	//setHeight(size.y);
	SoundManager::Instance().load("../Assets/audio/Bgm_2.mp3", "Bgm_2", SOUND_MUSIC);
	SoundManager::Instance().load("../Assets/audio/died.wav", "Died", SOUND_SFX);
	SoundManager::Instance().load("../Assets/audio/win.wav", "yay", SOUND_SFX);
	SoundManager::Instance().playMusic("Bgm_2", -1, 0);
	SoundManager::Instance().setMusicVolume(15);
	SoundManager::Instance().setSoundVolume(20);
}

PlayScene::~PlayScene()
= default;

void PlayScene::draw()
{
	if(EventManager::Instance().isIMGUIActive())
	{
		GUI_Function();
	}

	drawDisplayList();
	//SDL_SetRenderDrawColor(Renderer::Instance()->getRenderer(), 255, 255, 255, 255);
}

void PlayScene::update()
{
	updateDisplayList();

	
		CollisionManager::AABBCheck(m_pPlayer, m_pTarget);
	

	m_pSpaceShip[0]->setDestination(m_pPlayer->getTransform()->position);
	m_pSpaceShip[1]->setDestination(m_pPlayer->getTransform()->position);
	m_pSpaceShip[2]->setDestination(m_pPlayer->getTransform()->position);
	m_pSpaceShip[3]->setDestination(m_pPlayer->getTransform()->position);

	if (CollisionManager::circleAABBCheck(m_pPlayer, m_pSpaceShip[0]))
	{
		SoundManager::Instance().playSound("Died", 0, -1);
		std::cout << "Collision" << std::endl;
		m_pPlayer->setEnabled(false);
		m_pSpaceShip[0]->setEnabled(false);
		m_pDeadLabel->setEnabled(true);
	}
	if (CollisionManager::circleAABBCheck(m_pPlayer, m_pSpaceShip[1]))
	{
		SoundManager::Instance().playSound("Died", 0, -1);
		std::cout << "Collision" << std::endl;
		m_pPlayer->setEnabled(false);
		m_pSpaceShip[1]->setEnabled(false);
		m_pDeadLabel->setEnabled(true);
	}
	if (CollisionManager::circleAABBCheck(m_pPlayer, m_pSpaceShip[2]))
	{
		SoundManager::Instance().playSound("Died", 0, -1);
		std::cout << "Collision" << std::endl;
		m_pPlayer->setEnabled(false);
		m_pSpaceShip[2]->setEnabled(false);
		m_pDeadLabel->setEnabled(true);
	}
	if (CollisionManager::circleAABBCheck(m_pPlayer, m_pSpaceShip[3]))
	{
		SoundManager::Instance().playSound("Died", 0, -1);
		std::cout << "Collision" << std::endl;
		m_pPlayer->setEnabled(false);
		m_pSpaceShip[3]->setEnabled(false);
		m_pDeadLabel->setEnabled(true);
	}
	if(CollisionManager::AABBCheck(m_pPlayer, m_pTarget))
	{
		m_pWinLabel->setEnabled(true);
	}
	
}

void PlayScene::clean()
{
	removeAllChildren();
}

void PlayScene::handleEvents()
{
	if (SDL_NumJoysticks() < 1)
	{
		if (EventManager::Instance().isKeyDown(SDL_SCANCODE_A))
		{
			m_pPlayer->setAnimationState(PLAYER_RUN_LEFT);
			m_playerFacingRight = false;
		}
		
		else if (EventManager::Instance().isKeyDown(SDL_SCANCODE_D))
		{
			m_pPlayer->setAnimationState(PLAYER_RUN_RIGHT);
			m_playerFacingRight = true;
		}
		
		else if (EventManager::Instance().isKeyDown(SDL_SCANCODE_W))
		{
			m_pPlayer->setAnimationState(PLAYER_RUN_UP);
			m_playerFacingRight = true;
		}
		
		else if (EventManager::Instance().isKeyDown(SDL_SCANCODE_S))
		{
			m_pPlayer->setAnimationState(PLAYER_RUN_DOWN);
			m_playerFacingRight = true;
		}
		
		else
		{
			if (m_playerFacingRight)
			{
				m_pPlayer->setAnimationState(PLAYER_IDLE_RIGHT);
			}
			else
			{
				m_pPlayer->setAnimationState(PLAYER_IDLE_LEFT);
			}
		}
	}
	
	EventManager::Instance().update();

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_ESCAPE))
	{
		TheGame::Instance()->quit();
	}

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_1))
	{
		TheGame::Instance()->changeSceneState(START_SCENE);
	}

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_2))
	{
		TheGame::Instance()->changeSceneState(END_SCENE);
	}
	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_3))
	{
		PlayScene::clean();
		PlayScene::start();
	}
	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_0))
	{
		PlayScene::start();
	}
	
}

void PlayScene::start()
{
	// Set GUI Title
	m_guiTitle = "Play Scene";

	
	m_pTarget = new Target();
	m_pTarget->getTransform()->position = glm::vec2(700.0f, 300.0f);
	addChild(m_pTarget);

	m_pPlayer = new Player();
	m_pPlayer->getTransform()->position = glm::vec2(100.0f, 300.0f);
	addChild(m_pPlayer);
	m_playerFacingRight = true;

	
	// instantiating spaceship
	m_pSpaceShip[0] = new SpaceShip();
	m_pSpaceShip[0]->getTransform()->position = glm::vec2(700.0f, 100.0f);
	addChild(m_pSpaceShip[0]);
	
	m_pSpaceShip[1] = new SpaceShip();
	m_pSpaceShip[1]->getTransform()->position = glm::vec2(500.0f, 200.0f);
	addChild(m_pSpaceShip[1]);

	m_pSpaceShip[2] = new SpaceShip();
	m_pSpaceShip[2]->getTransform()->position = glm::vec2(700.0f, 400.0f);
	addChild(m_pSpaceShip[2]);

	m_pSpaceShip[3] = new SpaceShip();
	m_pSpaceShip[3]->getTransform()->position = glm::vec2(300.0f, 600.0f);
	addChild(m_pSpaceShip[3]);

	/* Instructions Label */
	m_pInstructionsLabel = new Label("WASD control", "Consolas");
	m_pInstructionsLabel->getTransform()->position = glm::vec2(Config::SCREEN_WIDTH * 0.5f, 10.0f);
	addChild(m_pInstructionsLabel);
	//die label
	m_pDeadLabel = new Label("you died, press 3 to retry ", "Consolas", 50);
	m_pDeadLabel->getTransform()->position = glm::vec2(Config::SCREEN_WIDTH * 0.5f, Config::SCREEN_HEIGHT * 0.5f);
	addChild(m_pDeadLabel);
	m_pDeadLabel->setEnabled(false);
	//win label
	m_pWinLabel = new Label("GG", "Consolas", 100);
	m_pWinLabel->getTransform()->position = glm::vec2(Config::SCREEN_WIDTH * 0.5f, Config::SCREEN_HEIGHT * 0.5f);
	m_pWinLabel->setEnabled(false);
}

void PlayScene::GUI_Function() const
{
/*	// Always open with a NewFrame
	ImGui::NewFrame();

	// See examples by uncommenting the following - also look at imgui_demo.cpp in the IMGUI filter
	//ImGui::ShowDemoWindow();
	
	ImGui::Begin("Your Window Title Goes Here", NULL, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_MenuBar);

	static float speed = 10.0f;
	if(ImGui::SliderFloat("MaxSpeed", &speed, 0.0f, 100.0f))
	{
		m_pSpaceShip->setMaxSpeed(speed);
	}

	static float angleInRadians = m_pSpaceShip->getRotation();
	if(ImGui::SliderAngle("Orientation Angle", &angleInRadians))
	{
		m_pSpaceShip->setRotation(angleInRadians * Util::Rad2Deg);
	}
	
	if(ImGui::Button("Start"))
	{
		m_pSpaceShip->setEnabled(true);
	}

	ImGui::SameLine();
	
	if (ImGui::Button("Reset"))
	{
		m_pSpaceShip->getTransform()->position = glm::vec2(100.0f, 100.0f);
		m_pSpaceShip->setEnabled(false);
	}

	ImGui::Separator();

	static float targetPosition[2] = { m_pTarget->getTransform()->position.x, m_pTarget->getTransform()->position.y};
	if(ImGui::SliderFloat2("Target", targetPosition, 0.0f, 800.0f))
	{
		m_pTarget->getTransform()->position = glm::vec2(targetPosition[0], targetPosition[1]);
//		m_pSpaceShip->setDestination(m_pTarget->getTransform()->position);
	}

	ImGui::End();

	// Don't Remove this
	ImGui::Render();
	ImGuiSDL::Render(ImGui::GetDrawData());
	ImGui::StyleColorsDark();*/
}
