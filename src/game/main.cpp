#include <myengine/myengine.h>

#include <iostream>

using namespace myengine;

struct Player : Component
{
	void onTick()
	{
		std::cout << "Ticking" << std::endl;
		m_angle += 0.25f;

		getEntity()->getTransform()->setRotation(rend::vec3(0, m_angle, 0));
	}

	void onDisplay()
	{
		std::cout << "Displaying" << std::endl;
	}

private:

	float m_angle;
};

int main(int argc, char *argv[])
{
	std::shared_ptr<Core> core = Core::initialize();

	std::shared_ptr<Entity> e = core->addEntity();
	e->addComponent<Player>();
	e->addComponent<TriangleRenderer>();
	std::shared_ptr<SoundSource> ss = e->addComponent<SoundSource>();
	//e->getComponent<SoundSource>()->load("../src/assests/sounds/bingchilling.ogg");
	std::shared_ptr<Sound> sound = core->getResources()->load<Sound>("../src/assests/sounds/bingchilling.ogg");
	ss->setSound(sound);

	e->getTransform()->setPosition(rend::vec3(0, 0, -5));

	std::shared_ptr<Entity> Cam = core->addEntity();
	Cam->addComponent<Camera>();

	core->start();

	return 0;
}
