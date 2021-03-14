
//直线移动的AI需要地图更新然后添加移动（可用，但应该只能作为展示而不能作为实际游戏中）
#include "linemoveTT.h"
#include "SoundManager.h"
#include "TextureManager.h"
#include "EventManager.h"

linemoveTT::linemoveTT()
{
	TextureManager::Instance()->load("../Assets/textures/plane.png", "plane");

	auto size = TextureManager::Instance()->getTextureSize("plane");
	setWidth(size.x);
	setHeight(size.y);

	getTransform()->position = glm::vec2(500.0f, 500.0f);
	setType(LINE_MOVE_TT);
	getRigidBody()->isColliding = false;
}

linemoveTT::~linemoveTT()
= default;

void linemoveTT::draw()
{
	TextureManager::Instance()->draw("plane", 
		getTransform()->position.x, getTransform()->position.y, 0, 255, true);
}
/*
void linemoveTT::handleEvents()
{
	if (getTransform()->position.y == 600 || getTransform()->position.y == 0 || getTransform()->position.x == 0 || getTransform()->position.x == 800)
	{
		switch (i)
		{
		case 1:
			getTransform()->position.y += speed;
			getTransform()->position.x += speed;
			break;
		case 2:
			getTransform()->position.y -= speed;
			getTransform()->position.x -= speed;
			break;
		case 3:
			getTransform()->position.y += speed;
			getTransform()->position.x -= speed;
			break;
		case 4:
			getTransform()->position.y -= speed;
			getTransform()->position.x += speed;
			break;
		case 5:
			getTransform()->position.y += speed;
			getTransform()->position.x = 0;
			break;
		case 6:
			getTransform()->position.y -= speed;
			getTransform()->position.x = 0;
			break;
		case 7:
			getTransform()->position.y = 0;
			getTransform()->position.x += speed;
			break;
		case 8:
			getTransform()->position.y = 0;
			getTransform()->position.x -= speed;
			break;
		}
	}
	
}
*/
void linemoveTT::update()
{
		if (movetop == true) {
			getTransform()->position.y += speed;
			if (getTransform()->position.y == 600) {
				movetop = false;
			}
		}
		else if (movetop == false) {
			getTransform()->position.y -= speed;
			if (getTransform()->position.y == 0) {
				movetop = true;
			}
		}

		if (moveright == true) {
			getTransform()->position.x += speed;
			if (getTransform()->position.x == 800) {
				moveright = false;
			}
		}
		else if (moveright == false) {
			getTransform()->position.x -= speed;
			if (getTransform()->position.x == 0) {
				moveright = true;
			}
		}

}

void  linemoveTT::clean()
{
}
