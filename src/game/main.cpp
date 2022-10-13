#include <myengine/myengine.h>

#include <iostream>

using namespace myengine;

int main()
{
	std::cout << "Hello Worlds" << std::endl;

	std::shared_ptr<Core> core = Core::initialize();

	std::shared_ptr<Entity> e = core->addEntity();

	core->start();

	return 0;
}
