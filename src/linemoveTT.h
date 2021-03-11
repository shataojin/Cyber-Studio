#pragma once
#ifndef __LINE_MOVE_TT__
#define __LINE_MOVE_TT__
#include "DisplayObject.h"

class linemoveTT final : public DisplayObject
{
public:
	// constructors
	linemoveTT();
	
	// destructor
	~linemoveTT();
	
	// life cycle functions
	void draw() override;
	void update() override;
	void clean() override;
	void handleEvents() ;
	bool movetop = true;
	bool moveright = true;
private:
	int i = 1 + (rand() % 8);
	const float speed = 2.0f;
};

#endif /* defined (__LINE_MOVE_TT__) */