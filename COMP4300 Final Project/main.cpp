#include "EntityManager.h"
#include "MemoryPool.h"

#include <iostream>

int main()
{
	EntityManager entityMgmt{};

	Entity boshko{ entityMgmt.addEntity("Boshko") };
	boshko.addComponent<CTransform>(200, 16);

	std::cout << "Boshko's position is " << boshko.getComponent<CTransform>().pos << " and his velocity is " << boshko.getComponent<CTransform>().vel << '\n';

	entityMgmt.update();

	return 0;
}