#include <myengine/myengine.h>

#include <iostream>

using namespace myengine;

struct Player : Component
{
	void onTick()
	{
		//std::cout << "Ticking" << std::endl;
		
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
		
	}

	void onDisplay()
	{
		//std::cout << "Displaying" << std::endl;
	}

	void onInit()
	{

	}

private:
	
};

int main(int argc, char *argv[])
{
	std::shared_ptr<Core> core = Core::initialize();

	std::shared_ptr<Entity> e = core->addEntity();
	e->addComponent<Player>();
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
	camE->getTransform()->setPosition(rend::vec3(0, 3, 0));
	camE->getTransform()->setRotation(rend::vec3(-20, 0, 0));

	std::shared_ptr<BoxCollider> bc2 = camE->addComponent<BoxCollider>();
	camE->addComponent<Rigidbody>();

	core->start();

	return 0;
}
