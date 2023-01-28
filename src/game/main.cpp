#include <myengine/myengine.h>
#include "gameStructs.h"

#include <iostream>

using namespace myengine;

int main(int argc, char *argv[])
{
	///< Player and Camera Creation

	std::shared_ptr<Core> core = Core::initialize();

	std::shared_ptr<Entity> playerEntity = core->addEntity();
	playerEntity->addComponent<Player>();
	std::shared_ptr<TriangleRenderer> tr = playerEntity->addComponent<TriangleRenderer>();
	tr->setMesh(core->getResources()->load<Model>("assests/models/curuthers.obj"));
	tr->setTexture(core->getResources()->load<ETexture>("assests/models/textures/Whiskers_diffuse.png"));

	std::shared_ptr<SoundSource> ss = playerEntity->addComponent<SoundSource>();
	std::shared_ptr<Sound> bingChilling = core->getResources()->load<Sound>("assests/sounds/bingchilling.ogg");
	ss->setSound(bingChilling);

	playerEntity->getTransform()->setPosition(rend::vec3(1, 0, -4));
	playerEntity->getTransform()->setScale(rend::vec3(0.5f, 0.5f, 0.5f));

	std::shared_ptr<BoxCollider> bc = playerEntity->addComponent<BoxCollider>();
	playerEntity->addComponent<Rigidbody>();
	bc->setSize(rend::vec3(1, 3, 1));

	std::shared_ptr<Entity> camE = core->addEntity();
	camE->addComponent<Camera>(); 
	camE->getTransform()->setPosition(rend::vec3(2, 3, 1));

	std::shared_ptr<CamController> camCon = camE->addComponent<CamController>();
	camCon->setPlayer(playerEntity->getComponent<Player>());

	std::shared_ptr<BoxCollider> bc2 = camE->addComponent<BoxCollider>();


	///< Wall & Floor creation

	std::shared_ptr<Entity> floor = core->addEntity();
	floor->getTransform()->setPosition(rend::vec3(0, -3, 0));
	floor->getTransform()->setScale(rend::vec3(250.0f, 1.0f, 250.0f));

	std::shared_ptr<TriangleRenderer> trfloor = floor->addComponent<TriangleRenderer>();
	trfloor->setMesh(core->getResources()->load<Model>("assests/models/floor.obj"));
	trfloor->setTexture(core->getResources()->load<ETexture>("assests/models/textures/floor.png"));

	std::shared_ptr<BoxCollider> fBC = floor->addComponent<BoxCollider>();
	fBC->setSize(rend::vec3(5000.0f, 1.0f, 5000.0f));

	std::shared_ptr<Entity> wallN = core->addEntity();
	std::shared_ptr<Transform> wallNT = wallN->getTransform();

	wallNT->setPosition(rend::vec3(0, 0, -200));
	wallNT->setRotation(rend::vec3(90, 0, 180));
	wallNT->setScale(rend::vec3(100.0f, 1.0f, 100.0f));
	std::shared_ptr<BoxCollider> fBCwallN = wallN->addComponent<BoxCollider>();
	fBCwallN->setSize(rend::vec3(1000, 1000, 10.0f));

	std::shared_ptr<TriangleRenderer> trfloorWallN = wallN->addComponent<TriangleRenderer>();
	trfloorWallN->setMesh(core->getResources()->load<Model>("assests/models/floor.obj"));
	trfloorWallN->setTexture(core->getResources()->load<ETexture>("assests/models/textures/sky.png"));

	std::shared_ptr<Entity> wallE = core->addEntity();
	std::shared_ptr<Transform> wallET = wallE->getTransform();

	wallET->setPosition(rend::vec3(-200, 0, 0));
	wallET->setRotation(rend::vec3(90, 90, 180));
	wallET->setScale(rend::vec3(100.0f, 1.0f, 100.0f));
	std::shared_ptr<BoxCollider> fBCwallE = wallE->addComponent<BoxCollider>();
	fBCwallE->setSize(rend::vec3(10.0f, 1000, 1000));

	std::shared_ptr<TriangleRenderer> trfloorWallE = wallE->addComponent<TriangleRenderer>();
	trfloorWallE->setMesh(core->getResources()->load<Model>("assests/models/floor.obj"));
	trfloorWallE->setTexture(core->getResources()->load<ETexture>("assests/models/textures/sky.png"));

	std::shared_ptr<Entity> wallS = core->addEntity();
	std::shared_ptr<Transform> wallST = wallS->getTransform();

	wallST->setPosition(rend::vec3(0, 0, 200));
	wallST->setRotation(rend::vec3(90, 0, 180));
	wallST->setScale(rend::vec3(100.0f, 1.0f, 100.0f));
	std::shared_ptr<BoxCollider> fBCwallS = wallS->addComponent<BoxCollider>();
	fBCwallS->setSize(rend::vec3(1000, 1000, 10.0f));

	std::shared_ptr<TriangleRenderer> trfloorWallS = wallS->addComponent<TriangleRenderer>();
	trfloorWallS->setMesh(core->getResources()->load<Model>("assests/models/floor.obj"));
	trfloorWallS->setTexture(core->getResources()->load<ETexture>("assests/models/textures/sky.png"));

	std::shared_ptr<Entity> wallW = core->addEntity();
	std::shared_ptr<Transform> wallWT = wallW->getTransform();

	wallWT->setPosition(rend::vec3(200, 0, 0));
	wallWT->setRotation(rend::vec3(90, 90, 180));
	wallWT->setScale(rend::vec3(100.0f, 1.0f, 100.0f));
	std::shared_ptr<BoxCollider> fBCwallW = wallW->addComponent<BoxCollider>();
	fBCwallW->setSize(rend::vec3(10.0f, 1000, 1000));

	std::shared_ptr<TriangleRenderer> trfloorWallW = wallW->addComponent<TriangleRenderer>();
	trfloorWallW->setMesh(core->getResources()->load<Model>("assests/models/floor.obj"));
	trfloorWallW->setTexture(core->getResources()->load<ETexture>("assests/models/textures/sky.png"));

	///< Obstacle Creation

	std::vector< std::shared_ptr<Entity> > pickups;

	for (int i = 0; i < 50; i++)
	{
		pickups.push_back(core->addEntity());
		std::shared_ptr<Transform> milkT = pickups.at(i)->getTransform();
		milkT->setScale(rend::vec3(0.1f, 0.1f, 0.1f));

		std::shared_ptr<BoxCollider> milkCollider = pickups.at(i)->addComponent<BoxCollider>();
		milkCollider->setSize(rend::vec3(1.2f, 2.0f, 1.2f));

		std::shared_ptr<TriangleRenderer> milkCarton = pickups.at(i)->addComponent<TriangleRenderer>();
		milkCarton->setMesh(core->getResources()->load<Model>("assests/models/Milk.obj"));
		milkCarton->setTexture(core->getResources()->load<ETexture>("assests/models/textures/Milk.png"));

		std::shared_ptr<Milk> milkPickup = pickups.at(i)->addComponent<Milk>();
		milkPickup->setData(playerEntity, milkCollider);
		milkPickup->randomisePos();
	}

	std::vector< std::shared_ptr<Entity> > obstacles;

	for (int i = 0; i < 20; i++)
	{
		obstacles.push_back(core->addEntity());
		std::shared_ptr<Transform> ObT = obstacles.at(i)->getTransform();
		ObT->setScale(rend::vec3(0.5f, 0.5f, 0.5f));

		std::shared_ptr<BoxCollider> bcOb = obstacles.at(i)->addComponent<BoxCollider>();
		bcOb->setSize(rend::vec3(1.0f, 2.0f, 1.0f));

		std::shared_ptr<TriangleRenderer> Cube = obstacles.at(i)->addComponent<TriangleRenderer>();
		Cube->setMesh(core->getResources()->load<Model>("assests/models/Block.obj"));
		Cube->setTexture(core->getResources()->load<ETexture>("assests/models/textures/GrassBlock.png"));

		std::shared_ptr<Obstacle> CubeOb = obstacles.at(i)->addComponent<Obstacle>();
		CubeOb->setData(playerEntity, bcOb);
		CubeOb->randomisePos();
	}

	///< Sound announcement
	std::shared_ptr<Entity> aEntity = core->addEntity();
	std::shared_ptr<Announcement> ancmt = aEntity->addComponent<Announcement>();
	std::shared_ptr<SoundSource> announcementSource = aEntity->addComponent<SoundSource>();
	std::shared_ptr<Sound> announcement = core->getResources()->load<Sound>("assests/sounds/announcement.ogg");
	announcementSource->setSound(announcement);
	announcementSource->play();

	std::shared_ptr<Entity> emptySound = core->addEntity();
	std::shared_ptr<SoundSource> songSource = floor->addComponent<SoundSource>();
	std::shared_ptr<Sound> songSound = core->getResources()->load<Sound>("assests/sounds/rockefellerstreet.ogg");
	songSource->setSound(songSound);
	std::shared_ptr<Song> song = emptySound->addComponent<Song>();

	ancmt->setData(announcementSource, song, playerEntity->getTransform());
	song->setData(songSource, playerEntity->getTransform());

	core->start();

	int totalScore = 0;

	for (int i = 0; i < 50; i++)
	{
		totalScore += pickups.at(i)->getComponent<Milk>()->getScore();
	}

	std::cout << "Score: " << totalScore << "! Well done!" << std::endl;

	std::string wait;
	std::getline(std::cin, wait);

	return 0;
}