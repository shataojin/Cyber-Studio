#include "linemoveTT.h"


#include "SoundManager.h"
#include "TextureManager.h"
#include "EventManager.h"

linemoveTT::linemoveTT()
{
	TextureManager::Instance()->load("../Assets/textures/drone.png", "drone");

	auto size = TextureManager::Instance()->getTextureSize("drone");
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
	TextureManager::Instance()->draw("drone", 
		getTransform()->position.x, getTransform()->position.y, 0, 255, true);
}

void linemoveTT::handleEvents()
{/*
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
	*/
	switch (MD)
	{
	case 1:getTransform()->position.x += speed;
		break;
	case 2:getTransform()->position.x -= speed;
		break;
	case 3:getTransform()->position.y += speed;
		break;
	case 4:getTransform()->position.y -= speed;
		break;
	}
}
//Ã»ÓÃ
void linemoveTT::random()
{/*
	int MD = rand() % 4 + 1;
	switch (MD)
	{
	case 1:getTransform()->position.x += speed;
		break;
	case 2:getTransform()->position.x -= speed;
		break;
	case 3:getTransform()->position.y += speed;
		break;
	case 4:getTransform()->position.y -= speed;
		break;
	}
	*/
}
void linemoveTT::update()
{
	
	switch (MD)
	{
	case 1:getTransform()->position.x += speed;
		break;
	case 2:getTransform()->position.x -= speed;
		break;
	case 3:getTransform()->position.y += speed;
		break;
	case 4:getTransform()->position.y -= speed;
		break;
	}

	if (getTransform()->position.y += speed)
	{
		moveup == true;
		if(getTransform()->position.y == 580)
		{
			moveup = false;
		}
	}


	if (getTransform()->position.y -= speed)
	{
		moveup == false;
		if (getTransform()->position.y ==20)
		{
			moveup = true;
		}
	}

	if (getTransform()->position.x += speed)
	{
		moveright = true;
		if (getTransform()->position.x == 780)
		{
			moveright = false;
		}
	}


	if (getTransform()->position.x -= speed)
	{
		moveright = false;
		if (getTransform()->position.x ==20)
		{
			moveright = true;
		}
	}

	
if(moveup == true)
{
	getTransform()->position.y += speed;
}
else if (moveup == false)
{
	getTransform()->position.y -= speed;
}
if (moveright == true)
{
	getTransform()->position.x -= speed;
}
else if (moveright == false)
{
	getTransform()->position.x += speed;
}
}

void  linemoveTT::clean()
{
}
