#include <myengine/myengine.h>

#include <iostream>

using namespace myengine;

struct Enemy : Component
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

struct PlayerController : Component
{
	void onTick()
	{
		if (m_input->cmd_w)
		{
			m_posZ -= 0.25f;
		}
		if (m_input->cmd_s)
		{
			m_posZ += 0.25f;
		}
		if (m_input->cmd_a)
		{
			m_posX -= 0.25f;
		}
		if (m_input->cmd_d)
		{
			m_posX += 0.25f;
		}
		if (m_input->cmd_space)
		{
			m_posY += 0.25f;
		}
		if (m_input->cmd_shift)
		{
			m_posY -= 0.25f;
		}

		getEntity()->getComponent<Transform>()->setPosition(rend::vec3(m_posX, m_posY, m_posZ));
	}

	void onDisplay()
	{
		std::cout << "Displaying" << std::endl;
	}

	void onInit()
	{
		m_input = getEntity()->getCore()->getInput();
	}

private:
	std::shared_ptr<Input> m_input;

	float m_posZ;
	float m_posY;
	float m_posX;
};

int main(int argc, char *argv[])
{
	std::shared_ptr<Core> core = Core::initialize();

	std::shared_ptr<Entity> e = core->addEntity();
	e->addComponent<Enemy>();
	std::shared_ptr<TriangleRenderer> tr = e->addComponent<TriangleRenderer>();
	tr->setMesh(core->getResources()->load<Model>("../src/assests/models/curuthers.obj"));
	tr->setTexture(core->getResources()->load<ETexture>("../src/assests/models/textures/Whiskers_diffuse.png"));

	std::shared_ptr<SoundSource> ss = e->addComponent<SoundSource>();
	//e->getComponent<SoundSource>()->load("../src/assests/sounds/bingchilling.ogg");
	std::shared_ptr<Sound> sound = core->getResources()->load<Sound>("../src/assests/sounds/bingchilling.ogg");
	ss->setSound(sound);
	ss->play();

	e->getTransform()->setPosition(rend::vec3(0, 0, -5));
	e->getTransform()->setScale(rend::vec3(0.5f, 0.5f, 0.5f));

	/**
	* Default Camera creation to ensure a camera is present
	*/
	std::shared_ptr<Entity> playerE = core->addEntity();
	playerE->addComponent<Camera>();
	playerE->addComponent<PlayerController>();

	core->start();

	return 0;
}
