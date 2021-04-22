#include "Player.h"
#include "TextureManager.h"
#include "Util.h"

Player::Player() : m_currentAnimationState(PLAYER_IDLE_RIGHT)
{
	TextureManager::Instance()->loadSpriteSheet(
		"../Assets/sprites/atlas.txt",
		"../Assets/sprites/player.png",
		"spritesheet");

	setSpriteSheet(TextureManager::Instance()->getSpriteSheet("spritesheet"));

	// set frame width
	setWidth(30);

	// set frame height
	setHeight(30);

	getTransform()->position = glm::vec2(400.0f, 300.0f);
	getRigidBody()->velocity = glm::vec2(0.0f, 0.0f);
	getRigidBody()->acceleration = glm::vec2(0.0f, 0.0f);
	getRigidBody()->isColliding = false;
	setType(PLAYER);
	m_buildAnimations();
}

Player::~Player()
= default;

void Player::draw()
{
	// alias for x and y
	const auto x = getTransform()->position.x;
	const auto y = getTransform()->position.y;

	// draw the player according to animation state
	switch (m_currentAnimationState)
	{
	case PLAYER_IDLE_RIGHT:
		TextureManager::Instance()->playAnimation("spritesheet", getAnimation("idle"),
			x, y, 0.12f, 0, 255, true);
		break;
	case PLAYER_IDLE_LEFT:
		TextureManager::Instance()->playAnimation("spritesheet", getAnimation("idle"),
			x, y, 0.12f, 0, 255, true, SDL_FLIP_HORIZONTAL);
		break;
	case PLAYER_RUN_RIGHT:
		TextureManager::Instance()->playAnimation("spritesheet", getAnimation("run"),
			x, y, 0.25f, 0, 255, true);
		break;
	case PLAYER_RUN_LEFT:
		TextureManager::Instance()->playAnimation("spritesheet", getAnimation("run"),
			x, y, 0.25f, 0, 255, true, SDL_FLIP_HORIZONTAL);
		break;
	default:
		TextureManager::Instance()->playAnimation("spritesheet", getAnimation("idle"),
			x, y, 0.12f, 0, 255, true);
		break;
	}

}



void Player::update()
{
	if (m_currentAnimationState == PLAYER_RUN_RIGHT)
	{
		getTransform()->position += glm::vec2(5.0f, 0.0f);
	}

	if (m_currentAnimationState == PLAYER_RUN_LEFT)
	{
		getTransform()->position += glm::vec2(-5.0f, 0.0f);
	}

	if (m_currentAnimationState == PLAYER_RUN_DOWN)
	{
		getTransform()->position += glm::vec2(0.0f, 5.0f);
	}

	if (m_currentAnimationState == PLAYER_RUN_UP)
	{
		getTransform()->position += glm::vec2(0.0f, -5.0f);
	}
}

void Player::CollisionWall()
{
	if (m_currentAnimationState == PLAYER_RUN_RIGHT)
	{
		getTransform()->position -= glm::vec2(5.0f, 0.0f);
	}

	if (m_currentAnimationState == PLAYER_RUN_LEFT)
	{
		getTransform()->position -= glm::vec2(-5.0f, 0.0f);
	}

	if (m_currentAnimationState == PLAYER_RUN_DOWN)
	{
		getTransform()->position -= glm::vec2(0.0f, 5.0f);
	}

	if (m_currentAnimationState == PLAYER_RUN_UP)
	{
		getTransform()->position -= glm::vec2(0.0f, -5.0f);
	}
}

void Player::clean()
{
}
void Player::setAnimationState(const PlayerAnimationState new_state)
{
	m_currentAnimationState = new_state;
}

glm::vec2 Player::getOrientation() const
{
	return m_orientation;
}

void Player::setOrientation(glm::vec2 orientation)
{
	m_orientation = orientation;
}


void Player::m_buildAnimations()
{
	Animation idleAnimation = Animation();

	idleAnimation.name = "idle";
	idleAnimation.frames.push_back(getSpriteSheet()->getFrame("megaman-idle-0"));
	idleAnimation.frames.push_back(getSpriteSheet()->getFrame("megaman-idle-1"));
	idleAnimation.frames.push_back(getSpriteSheet()->getFrame("megaman-idle-2"));
	idleAnimation.frames.push_back(getSpriteSheet()->getFrame("megaman-idle-3"));

	setAnimation(idleAnimation);

	Animation runAnimation = Animation();

	runAnimation.name = "run";
	runAnimation.frames.push_back(getSpriteSheet()->getFrame("megaman-run-0"));
	runAnimation.frames.push_back(getSpriteSheet()->getFrame("megaman-run-1"));
	runAnimation.frames.push_back(getSpriteSheet()->getFrame("megaman-run-2"));
	runAnimation.frames.push_back(getSpriteSheet()->getFrame("megaman-run-3"));

	setAnimation(runAnimation);
}


float Player::getRotation() const
{
	return m_rotationAngle;
}

void Player::setRotation(const float angle)
{
	m_rotationAngle = angle;

	const auto offset = -90.0f;
	const auto angle_in_radians = (angle + offset) * Util::Deg2Rad;

	const auto x = cos(angle_in_radians);
	const auto y = sin(angle_in_radians);

	// convert the angle to a normalized vector and store it in Orientation
	setOrientation(glm::vec2(x, y));
}
