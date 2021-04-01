#include "LineMoveE.h"
#include "Util.h"
#include "Game.h"
#include "TextureManager.h"
LineMoveE::LineMoveE()
{
	TextureManager::Instance()->load("../Assets/textures/Landmine.png", "Landmine");

	auto size = TextureManager::Instance()->getTextureSize("Landmine");
	setWidth(size.x);
	setHeight(size.y);

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
}

LineMoveE::~LineMoveE()
= default;

void LineMoveE::draw()
{
	TextureManager::Instance()->draw("Landmine",
		getTransform()->position.x, getTransform()->position.y, m_rotationAngle, 255, true);

	Util::DrawLine(getTransform()->position, (getTransform()->position + m_orientation * 60.0f));
}

void LineMoveE::update()
{
	m_Move();
}

void LineMoveE::clean()
{
}

void LineMoveE::setDestination(const glm::vec2 destination)
{
	m_destination = destination;
}

void LineMoveE::setMaxSpeed(const float speed)
{
	m_maxSpeed = speed;
}

glm::vec2 LineMoveE::getOrientation() const
{
	return m_orientation;
}

void LineMoveE::setOrientation(glm::vec2 orientation)
{
	m_orientation = orientation;
}

float LineMoveE::getTurnRate() const
{
	return m_turnRate;
}

void LineMoveE::setTurnRate(const float rate)
{
	m_turnRate = rate;
}

float LineMoveE::getAccelerationRate() const
{
	return m_accelerationRate;
}

void LineMoveE::setAccelerationRate(const float rate)
{
	m_accelerationRate = rate;
}

void LineMoveE::setRotation(float angle)
{
	m_rotationAngle = angle;

	const auto offset = -90.0f;
	const auto angle_in_radians = (angle + offset) * Util::Deg2Rad;

	const auto x = cos(angle_in_radians);
	const auto y = sin(angle_in_radians);

	// convert the angle to a normalized vector and store it in Orientation
	setOrientation(glm::vec2(x, y));
}

float LineMoveE::getRotation() const
{
	return m_rotationAngle;
}

void LineMoveE::m_Move()
{
	auto deltaTime = TheGame::Instance()->getDeltaTime();
	if (move == true)
	{
		setMaxSpeed(1.0f);
		// direction with magnitude
		m_targetDirection = m_destination - getTransform()->position;

		// normalized direction
		m_targetDirection = Util::normalize(m_targetDirection);

		auto target_rotation = Util::signedAngle(getOrientation(), m_targetDirection);

		auto turn_sensitivity = 5.0f;

		if (abs(target_rotation) > turn_sensitivity)
		{
			if (target_rotation > 0.0f)
			{
				setRotation(getRotation() + getTurnRate());
			}
			else if (target_rotation < 0.0f)
			{
				setRotation(getRotation() - getTurnRate());
			}
		}

		/*if (moveUp == true) {
			getTransform()->position.y += m_maxSpeed;
			if (getTransform()->position.y == 550) {
				moveUp = false;
			}
		}
		else if (moveUp == false) {
			getTransform()->position.y -= m_maxSpeed;
			if (getTransform()->position.y == 50) {
				moveUp = true;
			}
		}*/

		getRigidBody()->acceleration = m_targetDirection;

		// using the formula pf = pi + vi*t + 0.5ai*t^2
		//getRigidBody()->velocity += getOrientation() * (deltaTime)+
		//	0.5f * getRigidBody()->acceleration * (deltaTime);

		getRigidBody()->velocity = Util::clamp(getRigidBody()->velocity, m_maxSpeed);

		getTransform()->position += getRigidBody()->velocity;
	}
}
