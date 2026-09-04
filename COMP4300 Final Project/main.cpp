#include "EntityManager.h"
#include "MemoryPool.h"
#include "GameEngine.h"

#include <iostream>

int main()
{
	EntityManager entityMgmt{};

	Entity boshko{ entityMgmt.addEntity("Boshko") };
	boshko.addComponent<CTransform>(Vec2{ 130, 250 }, Vec2{ 3, 1 });

	std::cout << "Boshko's position is " << boshko.getComponent<CTransform>().pos.x << ", " << boshko.getComponent<CTransform>().pos.y
		<< " and his velocity is " << boshko.getComponent<CTransform>().vel.x << ", " << boshko.getComponent<CTransform>().vel.y << '\n';

	entityMgmt.update();

	GameEngine gameEngine{};
	gameEngine.run();

	return 0;
}