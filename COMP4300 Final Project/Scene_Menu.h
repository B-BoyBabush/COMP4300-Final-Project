#pragma once

#include "Scene.h"

class Scene_Menu : private Scene
{
	// Whatever text stuff is needed

public:
	Scene_Menu(GameEngine* gamePtr)
		: Scene(gamePtr)
	{ }

	void sRegisterActions();
	void sDoAction();
	void sRender();
	void sUpdate();
};