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
	//TextureManager::Instance()->load(".. / Assets / textures / bgp.png", "bgp");//not sure why its not working
	//TextureManager::Instance()->draw("S_bgp", 0, 0, 0, 255, false);//not sure why its not working
	//TextureManager::Instance()->load("../Assets/textures/bgp.png", "bgp");
	//auto size = TextureManager::Instance()->getTextureSize("bgp");
	//TextureManager::Instance()->draw("S_bgp", 0, 0, 0, 255, true);
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
	TextureManager::Instance()->draw("bgp", 400, 300, 0, 255, true);
	drawDisplayList();
	//SDL_SetRenderDrawColor(Renderer::Instance()->getRenderer(), 255, 255, 255, 255);
}

void PlayScene::update()
{
	auto deltaTime = TheGame::Instance()->getDeltaTime();
	updateDisplayList();

	for (auto i = 0; i < 5; i++) {
		//m_pLineSpaceShip[i]->setDestination(m_pPlayer->getTransform()->position);
		if (CollisionManager::circleAABBCheck(m_pPlayer, m_pLineSpaceShip[i]))
		{
			SoundManager::Instance().playSound("Died", 0, -1);
			std::cout << "Collision" << std::endl;
			m_pPlayer->setEnabled(false);
			m_pSpaceShip[i]->setEnabled(false);
			m_pLineSpaceShip[i]->setEnabled(false);
			m_pLineSpaceShipx[i]->setEnabled(false);
			m_pDeadLabel->setEnabled(true);
		}
	}

	for (auto i = 0; i < 5; i++) {
		//m_pLineSpaceShip[i]->setDestination(m_pPlayer->getTransform()->position);
		if (CollisionManager::circleAABBCheck(m_pPlayer, m_pLineSpaceShipx[i]))
		{
			SoundManager::Instance().playSound("Died", 0, -1);
			std::cout << "Collision" << std::endl;
			m_pPlayer->setEnabled(false);
			m_pSpaceShip[i]->setEnabled(false);
			m_pLineSpaceShip[i]->setEnabled(false);
			m_pLineSpaceShipx[i]->setEnabled(false);
			m_pDeadLabel->setEnabled(true);
		}
	}
	

	
		for (auto i = 0; i < 5; i++) {
			m_pSpaceShip[i]->setDestination(m_pPlayer->getTransform()->position);
			if (CollisionManager::circleAABBCheck(m_pPlayer, m_pSpaceShip[i]))
			{
				SoundManager::Instance().playSound("Died", 0, -1);
				std::cout << "Collision" << std::endl;
				m_pPlayer->setEnabled(false);
				m_pSpaceShip[i]->setEnabled(false);
				m_pLineSpaceShip[i]->setEnabled(false);
				m_pLineSpaceShipx[i]->setEnabled(false);
				m_pDeadLabel->setEnabled(true);
			}
		}

	
	if(CollisionManager::AABBCheck(m_pPlayer, m_pTarget))
	{
		m_pWinLabel->setEnabled(true);
	}

	if (m_pPlayer->getTransform()->position.x>=800.0f)
		m_pPlayer->getTransform()->position -= glm::vec2(5.0f, 0.0f);
	else if (m_pPlayer->getTransform()->position.x <= 0.0f)
		m_pPlayer->getTransform()->position -= glm::vec2(-5.0f, 0.0f);
	if (m_pPlayer->getTransform()->position.y >= 600.0f)
		m_pPlayer->getTransform()->position -= glm::vec2(0.0f, 5.0f);
	else if (m_pPlayer->getTransform()->position.y <= 0.0f)
		m_pPlayer->getTransform()->position -= glm::vec2(0.0f, -5.0f);
	
	
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
	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_4))
	{
		TheGame::Instance()->changeSceneState(WIN_SCENES);
	}

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_5))
	{
		TheGame::Instance()->changeSceneState(LOSE_SCENES);
	}


	if (m_pPlayer->isEnabled()==true)
	{
		//make it shoot  sitll need to get final set
	}
	if (m_pPlayer->isEnabled() == false)
	{
		TheGame::Instance()->changeSceneState(END_SCENE);
	}
	else if(CollisionManager::AABBCheck(m_pPlayer, m_pTarget))
	{
		TheGame::Instance()->changeSceneState(END_SCENE);
	}

	
}

void PlayScene::start()
{
	// Set GUI Title
	m_guiTitle = "Play Scene";
	TextureManager::Instance()->load("../Assets/textures/bgp.png", "bgp");
	
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

	m_pSpaceShip[4] = new SpaceShip();
	m_pSpaceShip[4]->getTransform()->position = glm::vec2(400.0f, 100.0f);
	addChild(m_pSpaceShip[4]);

	//instantiating ship
	m_pLineSpaceShip[0] = new LineMoveE();
	m_pLineSpaceShip[0]->getTransform()->position = glm::vec2(500.0f, 200.0f);
	addChild(m_pLineSpaceShip[0]);
	m_pLineSpaceShip[1] = new LineMoveE();
	m_pLineSpaceShip[1]->getTransform()->position = glm::vec2(600.0f, 150.0f);
	addChild(m_pLineSpaceShip[1]);
	m_pLineSpaceShip[2] = new LineMoveE();
	m_pLineSpaceShip[2]->getTransform()->position = glm::vec2(550.0f, 300.0f);
	addChild(m_pLineSpaceShip[2]);
	m_pLineSpaceShip[3] = new LineMoveE();
	m_pLineSpaceShip[3]->getTransform()->position = glm::vec2(800.0f, 200.0f);
	addChild(m_pLineSpaceShip[3]);
	m_pLineSpaceShip[4] = new LineMoveE();
	m_pLineSpaceShip[4]->getTransform()->position = glm::vec2(300.0f, 70.0f);
	addChild(m_pLineSpaceShip[4]);

	m_pLineSpaceShipx[0] = new linemoveTT();
	m_pLineSpaceShipx[0]->getTransform()->position = glm::vec2(500.0f, 200.0f);
	addChild(m_pLineSpaceShipx[0]);
	m_pLineSpaceShipx[1] = new linemoveTT();
	m_pLineSpaceShipx[1]->getTransform()->position = glm::vec2(600.0f, 150.0f);
	addChild(m_pLineSpaceShipx[1]);
	m_pLineSpaceShipx[2] = new linemoveTT();
	m_pLineSpaceShipx[2]->getTransform()->position = glm::vec2(550.0f, 300.0f);
	addChild(m_pLineSpaceShipx[2]);
	m_pLineSpaceShipx[3] = new linemoveTT();
	m_pLineSpaceShipx[3]->getTransform()->position = glm::vec2(800.0f, 200.0f);
	addChild(m_pLineSpaceShipx[3]);
	m_pLineSpaceShipx[4] = new linemoveTT();
	m_pLineSpaceShipx[4]->getTransform()->position = glm::vec2(300.0f, 70.0f);
	addChild(m_pLineSpaceShipx[4]);

	
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
	addChild(m_pWinLabel);
	m_pWinLabel->setEnabled(false);

}

/*
void PlayScene::m_buildGrid()
{

	auto tileSize = Config::TILE_SIZE;
	//
	std::ifstream inFile("../Assets/data/Tiledata.txt");
	if (inFile.is_open())
	{
		char key;
		int x, y;
		bool o, h;
		while (!inFile.eof())
		{
			inFile >> key >> x >> y >> o >> h;
			m_tiles.emplace(key, new TileC({ x * tileSize,y * tileSize, }, { 0.0f, 0.0f }, o, h));
		}
	}
	inFile.close();
	for (int row = 0; row < Config::ROW_NUM; ++row)
	{
		for (int col = 0; col < Config::COL_NUM; ++col)
		{
			Tile* tile = new Tile();//Create empty tile
			tile->getTransform()->position = glm::vec2(col * tileSize, row * tileSize);
			tile->setGridPosition(col, row);
			addChild(tile);
			tile->addLabels();
			tile->setTileCost(tile->getGridPosition().x);
			tile->setTileStatus(tile->getGridPosition().y);
			tile->setEnabled(false);
			m_pGrid.push_back(tile);
			
	for (int row = 0; row < Config::ROW_NUM; ++row)
	{
		for (int col = 0; col < Config::COL_NUM; ++col)
		{
			Tile* tile = m_getTile(col, row);

			if (row == 0)
			{
				tile->setNeighbourTile(TOP_TILE, nullptr);
			}
			else
			{
				tile->setNeighbourTile(TOP_TILE, m_getTile(col, row - 1));
			}
			if (col == Config::COL_NUM - 1)
			{
				tile->setNeighbourTile(RIGHT_TILE, nullptr);
			}
			else
			{
				tile->setNeighbourTile(RIGHT_TILE, m_getTile(col + 1, row));

			}
			if (row == Config::ROW_NUM - 1)
			{
				tile->setNeighbourTile(BOTTOM_TILE, nullptr);
			}
			else
			{
				tile->setNeighbourTile(BOTTOM_TILE, m_getTile(col, row + 1));

			}
			if (col == 0)
			{
				tile->setNeighbourTile(LEFT_TILE, nullptr);
			}
			else
			{
				tile->setNeighbourTile(LEFT_TILE, m_getTile(col - 1, row));
			}
		}

	}



	std::cout << m_pGrid.size() << std::endl;
}
		
void PlayScene::m_setGridEnabled(bool state) const
{
	for (auto tile : m_pGrid)
	{
		tile->setEnabled(state);
		tile->setLabelsEnabled(state);
	}
	if (state == false)
	{
		SDL_RenderClear(Renderer::Instance()->getRenderer());
	}
}


Tile* PlayScene::m_getTile(const int col, const int row) const
{
	return m_pGrid[(row * Config::COL_NUM) + col];
}

Tile* PlayScene::m_getTile(glm::vec2 grid_position) const
{
	const auto col = grid_position.x;
	const auto row = grid_position.y;
	return m_pGrid[(row * Config::COL_NUM) + col];
}
*/


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
