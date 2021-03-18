#pragma once
#ifndef __PLAY_SCENE__
#define __PLAY_SCENE__

#include "Scene.h"
#include "Button.h"
#include "Label.h"
#include "LineMoveE.h"
#include "SpaceShip.h"
#include "Target.h"
#include "Player.h"
#include "Tile.h"
#include "TiledLevel.h"
#include "Bullet.h"
#include <vector>
#include "TileA.h"

#include "linemoveTT.h"
#include "playerGun.h"

#define ROWS 48
#define COLS 64

class PlayScene : public Scene
{
public:
	PlayScene();
	~PlayScene();

	// Scene LifeCycle Functions
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;
	virtual void handleEvents() override;
	virtual void start() override;

	
private:
	// IMGUI Function
	void GUI_Function() const;
	std::string m_guiTitle;
	
	glm::vec2 m_mousePosition;

	SpaceShip* m_pSpaceShip[10];
	LineMoveE* m_pLineSpaceShip[10];
	linemoveTT* m_pLineSpaceShipx[10];
	Target* m_pTarget;
	Player* m_pPlayer;
	playerGun* m_pPlayerGun;
	bool m_playerFacingRight;
	bool m_player;
	
	// UI Items
	Label* m_pInstructionsLabel;
	Label* m_pDeadLabel;
	Label* m_pWinLabel;

	//map
	SDL_Texture* m_pTileText;
	std::map<char, Tile*> m_tiles;
	std::vector<std::vector<Tile*>> m_level;
	TileC* m_field[10];
	//PlatformPlayer* m_pPlayer;或许用到玩家上
	bool m_bgScrollX = false, m_bgScrollY = false;
	Tile* m_getTile(int col, int row) const;
	Tile* m_getTile(glm::vec2 grid_position) const;
	//tiles
	void m_setGridEnabled(bool state) const;
	std::vector<Tile*> m_pGrid;
	void m_buildGrid();
	void m_computeTileCosts();
	std::vector<NavigationObject*>m_pMap;
	//bullet
	std::vector<Bullet*>m_pBullet;
	std::vector<Bullet*>m_pEnemyBullet;
};

#endif /* defined (__PLAY_SCENE__) */