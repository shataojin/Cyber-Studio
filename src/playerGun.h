#pragma once
#ifndef __PLAYER_GUN__
#define __PLAYER_GUN__
#include "DisplayObject.h"
#include "TextureManager.h"

class playerGun final : public DisplayObject
{
public:
	// constructor(s)
	playerGun();

	// destructor
	~playerGun();

	// life-cycle methods inherited from DisplayObject
	void draw() override;
	void update() override;
	void clean() override;

	// getters and setters
	void setDestination(glm::vec2 destination);
	void setMaxSpeed(float speed);
	glm::vec2 getOrientation() const;
	void setOrientation(glm::vec2 orientation);
	float getRotation() const;
	void setRotation(float angle);
	float getTurnRate() const;
	void setTurnRate(float rate);
	float getAccelerationRate() const;
	void setAccelerationRate(float rate);
	bool moveUp = true;

private:

	glm::vec2 m_destination;
	glm::vec2 m_targetDirection;
	glm::vec2 m_orientation;
	float m_rotationAngle;
	float m_maxSpeed;
	float m_turnRate;
	float m_accelerationRate;

	// private function
	void m_Move();
};

#endif /* defined (__PLAYER_GUN___) */