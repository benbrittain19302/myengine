#include <myengine/myengine.h>

#include <iostream>

using namespace myengine;

struct Enemy : Component
{
	void onTick()
	{
		//std::cout << "Ticking" << std::endl;
		m_angle += 0.25f;

		getEntity()->getTransform()->setRotation(rend::vec3(0, m_angle, 0));
	}

	void onDisplay()
	{
		//std::cout << "Displaying" << std::endl;
	}

private:

	float m_angle;
};

struct CamController : Component
{

	void onTick()
	{
		rend::vec3 newPos = getEntity()->getTransform()->getPosition();
		if (m_input->cmd_w)
		{
			newPos.z -= 0.25f;
		}
		if (m_input->cmd_s)
		{
			newPos.z += 0.25f;
		}
		if (m_input->cmd_a)
		{
			newPos.x -= 0.25f;
		}
		if (m_input->cmd_d)
		{
			newPos.x += 0.25f;
		}
		if (m_input->cmd_space)
		{
			newPos.y += 0.25f;
		}
		if (m_input->cmd_lshift)
		{
			newPos.y -= 0.25f;
		}
		getEntity()->getTransform()->setPosition(newPos);
	}

	void onDisplay()
	{
		//std::cout << "Displaying" << std::endl;
	}

	void onInit()
	{
		m_input = getEntity()->getCore()->getInput();

		rend::vec3 startPos = rend::vec3(0, 2, 0);
		rend::vec3 startRot = rend::vec3(-10, 0, 0);

		getEntity()->getTransform()->setPosition(startPos);
		getEntity()->getTransform()->setRotation(startRot);
	}

private:
	std::shared_ptr<Input> m_input;
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

	std::shared_ptr<BoxCollider> bc = e->addComponent<BoxCollider>();
	bc->setSize(rend::vec3(1, 3, 1));

	/**
	* Default Camera creation to ensure a camera is present
	*/
	std::shared_ptr<Entity> camE = core->addEntity();
	camE->addComponent<Camera>();
	camE->addComponent<CamController>();

	std::shared_ptr<BoxCollider> bc2 = camE->addComponent<BoxCollider>();
	camE->addComponent<Rigidbody>();

	core->start();

	return 0;
}
