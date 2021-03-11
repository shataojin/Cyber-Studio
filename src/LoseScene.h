#pragma once
#ifndef _LOSE_SCENES_
#define __LOSE_SCENES_

#include "Scene.h"
#include "Label.h"
#include "Button.h"

class LoseScene final : public Scene
{
public:
	LoseScene();
	~LoseScene();

	// Inherited via Scene
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;
	virtual void handleEvents() override;
	virtual void start() override;

private:
	Label* m_label{};

	Button* m_pRestartButton;
	Button* m_nextButton;
	Button* m_exitbutton;
};

#endif /* defined (__LOSE_SCENES__) */