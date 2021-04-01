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
	void random();
	const float speed = 1.0f;
	bool moveup= true;
	bool moveright = true;
private:
	int MD = rand() % 4 + 1;
	
};

#endif /* defined (__LINE_MOVE_TT__) */