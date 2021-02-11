#pragma once
#ifndef __PLAY_SCENE__
#define __PLAY_SCENE__

#include "Scene.h"
#include "Button.h"
#include "Label.h"
#include "SpaceShip.h"
#include "Target.h"
#include "Player.h"

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

	SpaceShip* m_pSpaceShip[4];
	Target* m_pTarget;
	Player* m_pPlayer;
	bool m_playerFacingRight;
	
	// UI Items
	Label* m_pInstructionsLabel;
	Label* m_pDeadLabel;
	Label* m_pWinLabel;
};

#endif /* defined (__PLAY_SCENE__) */