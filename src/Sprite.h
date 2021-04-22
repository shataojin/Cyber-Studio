#pragma once
#ifndef __SPRITE__
#define __SPRITE__

#include "DisplayObject.h"
#include "Animation.h"
#include <unordered_map>
#include "SpriteSheet.h"

class Sprite : public DisplayObject
{
public:
	Sprite();
	virtual ~Sprite();

	// Life Cycle Functions
	virtual void draw()override = 0;
	virtual void update()override = 0;
	virtual void clean()override = 0;

	// getters
	SpriteSheet* getSpriteSheet();
	Animation& getAnimation(const std::string& name);

	// setters
	void setSpriteSheet(SpriteSheet* sprite_sheet);
	void setAnimation(const Animation& animation);

	glm::vec2 getGridPosition() const;
	void setGridPosition(float col, float row);


	glm::vec2 getOrientation() const { return m_orientation; }
	void setOrientation(glm::vec2 orientation) { m_orientation = orientation; }

private:
	// private utility functions
	bool m_animationExists(const std::string& id);

	SpriteSheet* m_pSpriteSheet;

	std::unordered_map<std::string, Animation> m_pAnimations;

	glm::vec2 m_gridPosition;
	glm::vec2 m_orientation;
};

#endif /* defined (__SPRITE__) */