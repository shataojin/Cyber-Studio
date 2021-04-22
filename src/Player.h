#pragma once
#ifndef __PLAYER__
#define __PLAYER__

#include "PlayerAnimationState.h"
#include "Sprite.h"

class Player : public Sprite
{
public:
	Player();
	~Player();

	// Life Cycle Methods
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;

	// setters
	void setAnimationState(PlayerAnimationState new_state);
	void CollisionWall();
	glm::vec2 getOrientation() const;
	void setOrientation(glm::vec2 orientation);
	glm::vec2 m_orientation;
	float getRotation() const;
	void setRotation(float angle);
	float m_rotationAngle;

private:
	void m_buildAnimations();

	PlayerAnimationState m_currentAnimationState;
};

#endif /* defined (__PLAYER__) */