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
		
		if (m_angle > 20.0f && !sound)
		{
			getEntity()->getComponent<SoundSource>()->play();
			sound = true;
		}
	}

	void onDisplay()
	{
		std::cout << "Displaying" << std::endl;
	}

private:

	float m_angle;

	bool sound = false;
};

int main(int argc, char *argv[])
{
	std::shared_ptr<Core> core = Core::initialize();

	std::shared_ptr<Entity> e = core->addEntity();
	e->addComponent<Player>();
	e->addComponent<TriangleRenderer>();
	e->addComponent<SoundSource>();
	e->getComponent<SoundSource>()->load("../src/assests/sounds/bingchilling.ogg");
	std::shared_ptr<Entity> Cam = core->addEntity();
	Cam->addComponent<Camera>();
	e->getTransform()->setPosition(rend::vec3(0, 0, -5));

	core->start();

	return 0;
}
