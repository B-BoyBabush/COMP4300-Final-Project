#pragma once

#include "Scene.h"

class Scene_Editor : public Scene
{
public:
	// currentlySelectedEntity
	// 


	void sRegisterActions();

	Scene_Editor(GameEngine* gamePtr)
		: Scene(gamePtr)
	{
		sRegisterActions();
	}

	// Load editor
	// 

	void sDoAction(const Action& action);
	void sRender();
	void sUpdate();
};