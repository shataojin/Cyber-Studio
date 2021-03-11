#include "Bullet.h"

#include "Game.h"
#include "Util.h"
#include "EventManager.h"

Bullet::Bullet(float rotation, glm::vec2 position, bool enable)
{
	TextureManager::Instance()->load("../Assets/textures/bullet.png", "bullet");

	auto size = TextureManager::Instance()->getTextureSize("bullet");
	setWidth(size.x);
	setHeight(size.y);
	/*
	getTransform()->position = glm::vec2(400.0f, 300.0f);
	getRigidBody()->velocity = glm::vec2(0.0f, 0.0f);
	getRigidBody()->acceleration = glm::vec2(0.0f, 0.0f);
	getRigidBody()->isColliding = false;
	setType(LINE_MOVE_E);
	setMaxSpeed(1.0f);
	setOrientation(glm::vec2(0.0f, -1.0f));
	setRotation(0.0f);
	//setAccelerationRate(10.0f);
	setTurnRate(2.0f);
	*/
	getTransform()->position = position;
	getRigidBody()->velocity = glm::vec2(0.0f, 0.0f);
	getRigidBody()->acceleration = glm::vec2(0.0f, 0.0f);
	getRigidBody()->isColliding = false;
	setType(BULLET);
	setRotation(rotation);
	
}

Bullet::~Bullet()
= default;

void Bullet::draw()
{
	TextureManager::Instance()->draw("bullet",
		getTransform()->position.x, getTransform()->position.y,
		m_rotationAngle, 255, true);
}

void Bullet::update()
{
	move();
}

void Bullet::clean()
{

}
void Bullet::setDestination(const glm::vec2 destination)
{
	m_destination = destination;
}

void Bullet::setMaxSpeed(const float speed)
{
	m_maxSpeed = speed;
}

glm::vec2 Bullet::getOrientation() const
{
	return m_orientation;
}

void Bullet::setOrientation(glm::vec2 orientation)
{
	m_orientation = orientation;
}

float Bullet::getTurnRate() const
{
	return m_turnRate;
}

void Bullet::setTurnRate(const float rate)
{
	m_turnRate = rate;
}


float Bullet::getAccelerationRate() const
{
	return m_accelerationRate;
}

void Bullet::setAccelerationRate(float rate)
{
	m_accelerationRate = rate;
}

void Bullet::setRotation(float angle)
{
	m_rotationAngle = angle;

	const auto offset = -90.0f;
	const auto angle_in_radians = (angle + offset) * Util::Deg2Rad;

	const auto x = cos(angle_in_radians);
	const auto y = sin(angle_in_radians);

	// convert the angle to a normalized vector and store it in Orientation
	setOrientation(glm::vec2(x, y));
}

float Bullet::getRotation() const
{
	return m_rotationAngle;
}



void Bullet::move()
{
	auto deltaTime = TheGame::Instance()->getDeltaTime();
	EventManager::Instance().update();


	setAccelerationRate(10.0f);
	getRigidBody()->acceleration = getOrientation() * getAccelerationRate();

	// using the formula pf = pi + vi*t + 0.5ai*t^2
	getRigidBody()->velocity += getOrientation() * (deltaTime)+
		0.5f * getRigidBody()->acceleration * (deltaTime);

	getRigidBody()->velocity = Util::clamp(getRigidBody()->velocity, m_maxSpeed);

	getTransform()->position += getRigidBody()->velocity;

}


void Bullet::Shoot()
{
	bulletShot = true;
}