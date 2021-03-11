#pragma once
#ifndef _BULLET_
#define _BULLET_

#include "DisplayObject.h"
#include "TextureManager.h"
#include "Sprite.h"


class Bullet :public Sprite
{
public:
	Bullet(float rotation, glm::vec2 position, bool enable);

	~Bullet();

	void draw() override;
	void update() override;
	void clean() override;

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
	bool bulletShot = false;
	void Shoot();
	void move();
private:

	glm::vec2 m_destination;
	glm::vec2 m_targetDirection;
	glm::vec2 m_orientation;
	float m_rotationAngle;
	float m_maxSpeed=5;
	float m_turnRate;
	float m_accelerationRate;

};
#endif


