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
	if (EventManager::Instance().isIMGUIActive())
	{
		GUI_Function();
	}
	//TextureManager::Instance()->draw("bgp", 400, 300, 0, 255, true);
	drawDisplayList();

	//SDL_SetRenderDrawColor(Renderer::Instance()->getRenderer(), 255, 255, 255, 255);
}

void PlayScene::update()
{
	auto deltaTime = TheGame::Instance()->getDeltaTime();
	updateDisplayList();


	//TODO 墙与玩家碰撞。

	for (int i = 0; i < 20; i++) {

		if (CollisionManager::circleAABBCheck(m_field[i], m_pPlayer)) {

			float X_right = m_field[i]->getTransform()->position.x - m_pPlayer->getTransform()->position.x;
			float X_left = m_pPlayer->getTransform()->position.x - m_field[i]->getTransform()->position.x;
			float Y_down = m_field[i]->getTransform()->position.y - m_pPlayer->getTransform()->position.y;
			float Y_top = m_pPlayer->getTransform()->position.y - m_field[i]->getTransform()->position.y;

			if ((X_right > X_left) && (X_right > Y_down) && (X_right > Y_top))
				m_pPlayer->getTransform()->position -= glm::vec2(5.0f, 0.0f);
			else if ((X_left > X_right) && (X_left > Y_down) && (X_left > Y_top))
				m_pPlayer->getTransform()->position -= glm::vec2(-5.0f, 0.0f);
			if ((Y_down > X_right) && (Y_down > X_left) && (Y_down > Y_top))
				m_pPlayer->getTransform()->position -= glm::vec2(0.0f, 5.0f);
			else if ((Y_top > X_right) && (Y_top > X_left) && (Y_top > Y_down))
				m_pPlayer->getTransform()->position -= glm::vec2(0.0f, -5.0f);
		}
	}









	for (auto i = 0; i < 5; i++) {
		//m_pLineSpaceShip[i]->setDestination(m_pPlayer->getTransform()->position);
		if (CollisionManager::circleAABBCheck(m_pPlayer, m_pLineSpaceShip[i]))
		{
			SoundManager::Instance().playSound("Died", 0, -1);
			std::cout << "Collision" << std::endl << std::endl;
			m_pPlayer->setEnabled(false);
			m_pSpaceShip[i]->setEnabled(false);
			m_pLineSpaceShip[i]->setEnabled(false);
			m_pLineSpaceShipx[i]->setEnabled(false);
			m_field[i]->setEnabled(false);
			m_pDeadLabel->setEnabled(true);
			std::cout << "m_pLineSpaceShip die" << std::endl << std::endl;
		}
	}

	for (auto i = 0; i < 5; i++) {
		//m_pLineSpaceShip[i]->setDestination(m_pPlayer->getTransform()->position);
		if (CollisionManager::circleAABBCheck(m_pPlayer, m_pLineSpaceShipx[i]))
		{
			SoundManager::Instance().playSound("Died", 0, -1);
			std::cout << "Collision" << std::endl << std::endl;
			m_pPlayer->setEnabled(false);
			m_pSpaceShip[i]->setEnabled(false);
			m_pLineSpaceShip[i]->setEnabled(false);
			m_pLineSpaceShipx[i]->setEnabled(false);
			m_field[i]->setEnabled(false);
			m_pDeadLabel->setEnabled(true);
			std::cout << "m_pLineSpaceShipx die" << std::endl << std::endl;
		}
	}



	for (auto i = 0; i < 5; i++) {
		m_pSpaceShip[i]->setDestination(m_pPlayer->getTransform()->position);
		if (CollisionManager::circleAABBCheck(m_pPlayer, m_pSpaceShip[i]))
		{
			SoundManager::Instance().playSound("Died", 0, -1);
			std::cout << "Collision" << std::endl << std::endl;
			m_pPlayer->setEnabled(false);
			m_pSpaceShip[i]->setEnabled(false);
			m_pLineSpaceShip[i]->setEnabled(false);
			m_pLineSpaceShipx[i]->setEnabled(false);
			m_field[i]->setEnabled(false);
			m_pDeadLabel->setEnabled(true);
			std::cout << "m_pSpaceShip die" << std::endl << std::endl;
		}
	}


	if (CollisionManager::AABBCheck(m_pPlayer, m_pTarget))
	{
		m_pTarget->setEnabled(false);
		m_pWinLabel->setEnabled(true);
		std::cout << std::endl << "m_pTarget die" << std::endl << std::endl;
	}

	if (m_pPlayer->getTransform()->position.x >= 800.0f)
		m_pPlayer->getTransform()->position -= glm::vec2(5.0f, 0.0f);
	else if (m_pPlayer->getTransform()->position.x <= 0.0f)
		m_pPlayer->getTransform()->position -= glm::vec2(-5.0f, 0.0f);
	if (m_pPlayer->getTransform()->position.y >= 600.0f)
		m_pPlayer->getTransform()->position -= glm::vec2(0.0f, 5.0f);
	else if (m_pPlayer->getTransform()->position.y <= 0.0f)
		m_pPlayer->getTransform()->position -= glm::vec2(0.0f, -5.0f);


	//not working and no effect 
	for (int i = 0; i < 5; i++)
	{
		if (m_pLineSpaceShipx[i]->getTransform()->position.x >= 800.0f || m_pLineSpaceShipx[i]->getTransform()->position.x <= 0.0f
			|| m_pLineSpaceShipx[i]->getTransform()->position.y >= 600.0f || m_pLineSpaceShipx[i]->getTransform()->position.y <= 0.0f)
		{
			m_pLineSpaceShipx[i - 1] = new linemoveTT;
		}
	}






}

void PlayScene::clean()
{
	removeAllChildren();
}

void PlayScene::handleEvents()
{




	//shoot
	if (EventManager::Instance().getMouseButton(0))
	{
		if (m_pPlayer->isEnabled() == true)
		{
			m_pBullet.push_back(new Bullet(m_pPlayer->m_rotationAngle, m_pPlayer->getTransform()->position, true));
			//addChild(m_pBullet[TotalBullets]);
			TotalBullets++;
		}
	}




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
		PlayScene::clean();
		TheGame::Instance()->quit();
	}

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_1))
	{
		PlayScene::clean();
		TheGame::Instance()->changeSceneState(START_SCENE);
	}

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_2))
	{
		PlayScene::clean();
		TheGame::Instance()->changeSceneState(END_SCENE);
	}

	/*
	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_3))
	{
		PlayScene::clean();
		PlayScene::start();
	}*/

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_0))
	{
		PlayScene::start();

	}
	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_4))
	{
		PlayScene::clean();
		TheGame::Instance()->changeSceneState(WIN_SCENES);
	}

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_5))
	{
		PlayScene::clean();
		TheGame::Instance()->changeSceneState(LOSE_SCENES);
	}


	if (m_pPlayer->isEnabled() == true)
	{
		//make it shoot  sitll need to get final set
	}
	if (m_pPlayer->isEnabled() == false)
	{
		TheGame::Instance()->changeSceneState(LOSE_SCENES);
	}
	if (m_pTarget->isEnabled() == true)
	{
		//something
	}
	if (m_pTarget->isEnabled() == false)
	{
		/*计算回合不能
		m_RoundCounter-> winround == true;
		*/
		if (Game::Instance()->round >= 0 && Game::Instance()->round <= 2)
		{
			Game::Instance()->round++;
			std::cout << "round numebr is : " << Game::Instance()->round << std::endl;
			TheGame::Instance()->changeSceneState(WIN_SCENES);
		}
		else if (Game::Instance()->round = 3)
		{
			std::cout << "round numebr is : " << Game::Instance()->round << std::endl;
			TheGame::Instance()->changeSceneState(END_SCENE);
		}

	}





	//TODO 无法检查和上一个障碍物位置是否一致
	/*
	if(m_field[i]->getTransform()->position == m_field[i - 1]->getTransform()->position)
	{
		m_field[i - 1] = new TileC("../Assets/grid/Wall.png", "w");
	}
	*/

	/*
	for (int i = 0; i < 20; i++)
	{
		for (int x = 0; x < 5; x++)
		{
			const float speed = 3.0f;
			if (m_pLineSpaceShipx[x]->getTransform()->position.x >= 800.0f)
			{

				m_pLineSpaceShipx[x]->getTransform()->position.x -= speed;


			}
			if (m_pLineSpaceShipx[x]->getTransform()->position.x <= 0.0f)
			{
				m_pLineSpaceShipx[x]->getTransform()->position.x += speed;

			}

			if (m_pLineSpaceShipx[x]->getTransform()->position.y >= 600.0f)
			{

				m_pLineSpaceShipx[x]->getTransform()->position.y -= speed;

			}
			if (m_pLineSpaceShipx[x]->getTransform()->position.y <= 0.0f)
			{

				m_pLineSpaceShipx[x]->getTransform()->position.y += speed;
			}
		}
	}
}


			*/




			/*
			if (m_pLineSpaceShipx[x]->getTransform()->position.x >= 800.0f || m_pLineSpaceShipx[x]->getTransform()->position.x <= 0.0f ||
				m_pLineSpaceShipx[x]->getTransform()->position.y >= 600.0f || m_pLineSpaceShipx[x]->getTransform()->position.y <= 0.0f ||
				CollisionManager::CircleAABBarea(m_field[i], m_pLineSpaceShipx[x]))
			{
				const float speed = 1.0f;
				int MD = rand() % 4 + 1;
				switch (MD)
				{
				case 1:m_pLineSpaceShipx[x]->getTransform()->position.x += speed;
					break;
				case 2:m_pLineSpaceShipx[x]->getTransform()->position.x -= speed;
					break;
				case 3:m_pLineSpaceShipx[x]->getTransform()->position.y += speed;
					break;
				case 4:m_pLineSpaceShipx[x]->getTransform()->position.y -= speed;
					break;
				}
			}
			*/
			/*
			for (int i = 0; i < 20; i++)
			{
				for (int x = 0; x < 5; x++)
				{
					const float speed = 1.0f;
					int MD = rand() % 4 + 1;
					if (m_pLineSpaceShipx[x]->getTransform()->position.x >= 800.0f || m_pLineSpaceShipx[x]->getTransform()->position.x <= 0.0f ||
						m_pLineSpaceShipx[x]->getTransform()->position.y >= 600.0f || m_pLineSpaceShipx[x]->getTransform()->position.y <= 0.0f ||
						CollisionManager::CircleAABBarea(m_field[i], m_pLineSpaceShipx[x])) {
						if (MD = 1) {
							m_pLineSpaceShipx[x]->getTransform()->position.x += speed;
						}
						else if (MD = 2) {
							m_pLineSpaceShipx[x]->getTransform()->position.x -= speed;
						}
						else if (MD = 3) {
							m_pLineSpaceShipx[x]->getTransform()->position.y += speed;
						}
						else if (MD = 4) {
							m_pLineSpaceShipx[x]->getTransform()->position.y -= speed;
						}
					}
				}
			}
		}*/

		/*
		for(int i=0;i<20;i++)
		{
			if(m_pTarget->getTransform()->position== m_field[i]->getTransform()->position)
			{
				Target* currentTargetLocaltion = m_pTarget;
				delete currentTargetLocaltion;
				currentTargetLocaltion = nullptr;
				m_pTarget = new Target;
			}
		}
		*/

}






void PlayScene::start()
{
	int ainumber = 6 + Game::Instance()->round;
	// Set GUI Title
	m_guiTitle = "Play Scene";
	//TextureManager::Instance()->load("../Assets/textures/bgp.png", "bgp");

	auto offsetTiles1 = glm::vec2(Config::TILE_SIZE * 0.5f, Config::TILE_SIZE * 0.5f);


	m_buildGrid();

	Background = new TileC("../Assets/textures/bgppc.png", "bgppc");
	Background->getTransform()->position.x = 800.0f / 2;
	Background->getTransform()->position.y = 600.0f / 2;
	addChild(Background, 0);

	for (int i = 0; i < 20; i++)
	{
		int RLT_x = rand() % 18;
		int RLT_y = rand() % 15;
		m_field[i] = new TileC("../Assets/textures/Wall.png", "wall");
		m_field[i]->getTransform()->position = m_getTile(RLT_x, RLT_y)->getTransform()->position + offsetTiles1;
		addChild(m_field[i], 2);
		m_pMap.push_back(m_field[i]);
	}

	/*
	for (int RLT_x = rand() % 39)
	{
		for (int RLT_y = rand() % 39;
		{
			m_field[0] = new TileC("../Assets/grid/Wall.png", "wall");
			m_field[0]->getTransform()->position = m_getTile(RLT_x, RLT_y)->getTransform()->position + offsetTiles1;
			addChild(m_field[0], 1);
			m_pMap.push_back(m_field[0]);
			m_field[1] = new TileC("../Assets/grid/Wall.png", "wall");
			m_field[1]->getTransform()->position = m_getTile(RLT_x, RLT_y)->getTransform()->position + offsetTiles1;
			addChild(m_field[1], 1);
			m_pMap.push_back(m_field[1]);
			m_field[2] = new TileC("../Assets/grid/Wall.png", "wall");
			m_field[2]->getTransform()->position = m_getTile(RLT_x, RLT_y)->getTransform()->position + offsetTiles1;
			addChild(m_field[2], 1);
			m_pMap.push_back(m_field[2]);
			m_field[3] = new TileC("../Assets/grid/Wall.png", "wall");
			m_field[3]->getTransform()->position = m_getTile(RLT_x, RLT_y)->getTransform()->position + offsetTiles1;
			addChild(m_field[3], 1);
			m_pMap.push_back(m_field[3]);
			m_field[4] = new TileC("../Assets/grid/Wall.png", "wall");
			m_field[4]->getTransform()->position = m_getTile(RLT_x, RLT_y)->getTransform()->position + offsetTiles1;
			addChild(m_field[4], 1);
			m_pMap.push_back(m_field[4]);
			m_field[5] = new TileC("../Assets/grid/Wall.png", "wall");
			m_field[5]->getTransform()->position = m_getTile(RLT_x, RLT_y)->getTransform()->position + offsetTiles1;
			addChild(m_field[5], 1);
			m_pMap.push_back(m_field[5]);
		}

	}
	*/




	m_pTarget = new Target();
	m_pTarget->getTransform()->position = glm::vec2(TargetL_x, TargetL_y);
	addChild(m_pTarget, 2);

	m_pPlayer = new Player();
	m_pPlayer->getTransform()->position = glm::vec2(50.0f, 300.0f);
	addChild(m_pPlayer, 2);
	m_playerFacingRight = true;
	//理念为与玩家绑定得一个OBJ+无移动速度得追逐鼠标。

	/*
	m_pPlayerGun = new playerGun();
	m_pPlayerGun ->getTranaform()->position = glm::vec2(100.0f, 300.0f);
	m_pPlayerGun->getTransform()->position = m_pPlayerGun->getTransform()->position;//should lock the postiton toghter
	m_pPlayerGun->setDestination()->destination= GetCursorPos;
	addChild(m_pPlayerGun);
	*/

	// instantiating spaceship

	/*
	for(int i=0;i<4;i++)
	{
		m_pSpaceShip[i] = new SpaceShip();
		m_pSpaceShip[i]->getTransform()->position = glm::vec2(700.0f, 100.0f);
		addChild(m_pSpaceShip[i]);
	}
	*/
	for (int i = 0; i < ainumber; i++)
	{
		int RL_x = (rand() % 19 + 6) * 40;
		int RL_y = (rand() % 14 + 5) * 40;
		m_pSpaceShip[i] = new SpaceShip();
		m_pSpaceShip[i]->getTransform()->position = glm::vec2(RL_x, RL_y);
		addChild(m_pSpaceShip[i], 4);
	}

	/*
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
	*/

	//instantiating ship
	//静止敌人
	for (int i = 0; i < ainumber; i++)
	{
		int RL_x = (rand() % 18 + 4) * 40 - 20;
		int RL_y = (rand() % 14 + 1) * 40 - 20;
		m_pLineSpaceShip[i] = new LineMoveE();
		m_pLineSpaceShip[i]->getTransform()->position = glm::vec2(RL_x, RL_y);
		addChild(m_pLineSpaceShip[i], 4);
	}
	/*
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
	*/

	for (int i = 0; i < ainumber; i++)
	{
		int RL_x = (rand() % 19 + 5) * 40;
		int RL_y = (rand() % 14 + 5) * 40;
		m_pLineSpaceShipx[i] = new linemoveTT();
		m_pLineSpaceShipx[i]->getTransform()->position = glm::vec2(RL_y, RL_x);
		addChild(m_pLineSpaceShipx[i], 4);
	}
	/*
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
	*/

	/* Instructions Label */
	m_pInstructionsLabel = new Label("WASD control", "Consolas");
	m_pInstructionsLabel->getTransform()->position = glm::vec2(Config::SCREEN_WIDTH * 0.5f, 10.0f);
	addChild(m_pInstructionsLabel, 4);
	//die label
	m_pDeadLabel = new Label("you died, press 3 to retry ", "Consolas", 50);
	m_pDeadLabel->getTransform()->position = glm::vec2(Config::SCREEN_WIDTH * 0.5f, Config::SCREEN_HEIGHT * 0.5f);
	//addChild(m_pDeadLabel);
	m_pDeadLabel->setEnabled(false);
	//win label
	m_pWinLabel = new Label("GG", "Consolas", 100);
	m_pWinLabel->getTransform()->position = glm::vec2(Config::SCREEN_WIDTH * 0.5f, Config::SCREEN_HEIGHT * 0.5f);
	//	addChild(m_pWinLabel);
	m_pWinLabel->setEnabled(false);

	m_computeTileCosts();
}

void PlayScene::m_buildGrid()
{
	auto tileSize = Config::TILE_SIZE;

	// add tiles to the grid
	for (int row = 0; row < Config::ROW_NUM; ++row)
	{
		for (int col = 0; col < Config::COL_NUM; ++col)
		{
			Tile* tile = new Tile(); // create empty tile
			tile->getTransform()->position = glm::vec2(col * tileSize, row * tileSize);
			tile->setGridPosition(col, row);
			addChild(tile);
			tile->addLabels();
			tile->setEnabled(false);
			m_pGrid.push_back(tile);
		}
	}

	// create references for each tile to its neighbours
	for (int row = 0; row < Config::ROW_NUM; ++row)
	{
		for (int col = 0; col < Config::COL_NUM; ++col)
		{
			Tile* tile = m_getTile(col, row);

			// Topmost row
			if (row == 0)
			{
				tile->setNeighbourTile(TOP_TILE, nullptr);
			}
			else
			{
				tile->setNeighbourTile(TOP_TILE, m_getTile(col, row - 1));
			}

			// rightmost column
			if (col == Config::COL_NUM - 1)
			{
				tile->setNeighbourTile(RIGHT_TILE, nullptr);
			}
			else
			{
				tile->setNeighbourTile(RIGHT_TILE, m_getTile(col + 1, row));
			}

			// bottommost row
			if (row == Config::ROW_NUM - 1)
			{
				tile->setNeighbourTile(BOTTOM_TILE, nullptr);
			}
			else
			{
				tile->setNeighbourTile(BOTTOM_TILE, m_getTile(col, row + 1));
			}

			// leftmost  column
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
	m_setGridEnabled(true);
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

void PlayScene::m_computeTileCosts()
{
	for (auto tile : m_pGrid)
	{
		auto distance = Util::distance(m_pTarget->getGridPosition(), tile->getGridPosition());
		//tile->setTileCost(distance);
	}
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
