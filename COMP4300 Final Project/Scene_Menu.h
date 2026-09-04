#pragma once

#include "Scene.h"

class Scene_Menu : public Scene
{
	// Whatever text stuff is needed

public:
	void sRegisterActions();
	
	Scene_Menu(GameEngine* gamePtr)
		: Scene(gamePtr)
	{
		sRegisterActions();
	}
	
	void sDoAction(const Action& action);
	void sRender();
	void sUpdate();
};