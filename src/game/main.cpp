#include <myengine/myengine.h>

#include <iostream>

using namespace myengine;

struct Player : Component
{
	void onTick()
	{
		std::cout << "Ticking" << std::endl;
	}
};

int main()
{
	std::cout << "Hello Worlds" << std::endl;

	std::shared_ptr<Core> core = Core::initialize();

	std::shared_ptr<Entity> e = core->addEntity();

	e->addComponent<Player>();

	core->start();

	return 0;
}
