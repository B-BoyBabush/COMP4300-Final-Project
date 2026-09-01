#pragma once

class GameEngine;

class Scene
{
	GameEngine* m_gamePtr{};
	size_t		m_currentFrame{ 0 };

public:
	Scene(GameEngine* gamePtr)
		: m_gamePtr{ gamePtr }
	{ }

	// Actions, rendering, and other systems left to derived Scene classes
	virtual void sRegisterActions() = 0;
	virtual void sDoAction() = 0;
	virtual void sRender() = 0;
	virtual void sUpdate() = 0;
};