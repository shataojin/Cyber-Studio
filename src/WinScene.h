#pragma once
#ifndef _WIN_SCENES_
#define _WIN_SCENES_

#include "Scene.h"
#include "Label.h"
#include "Button.h"

class WinScene final : public Scene
{
public:
	WinScene();
	~WinScene();

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

#endif /* defined (__WIN_SCENES__) */