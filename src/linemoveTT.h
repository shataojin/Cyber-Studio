#pragma once
#ifndef __LINE_MOVE_TT__
#define __LINE_MOVE_TT__
#include "DisplayObject.h"
#include "NavigationObject.h"
#include "PlayerAnimationState.h"

class linemoveTT final :public NavigationObject
{
public:
	// constructors
	linemoveTT();

	// destructor
	~linemoveTT();

	// life cycle functions
	void draw() override;
	void update() override;
	void handleEvents();
	void clean() override;
	void random();
	// setters
	void setAnimationState(PlayerAnimationState new_state);
	void CollisionWall();
	glm::vec2 getOrientation() const;
	void setOrientation(glm::vec2 orientation);
	glm::vec2 m_orientation;
	float getRotation() const;
	void setRotation(float angle);
	float m_rotationAngle;
	const float speed = 1.0f;
	bool moveup = true;
	bool moveright = true;
private:
	int MD = rand() % 4 + 1;
	void m_buildAnimations();

	PlayerAnimationState m_currentAnimationState;

};

#endif /* defined (__LINE_MOVE_TT__) */