#include <myengine/myengine.h>

#include <iostream>

using namespace myengine;

struct Player : Component
{
	void onTick(float deltaTs)
	{
		m_angleUpdate = false;
		//std::cout << "Ticking" << std::endl;
		rend::vec3 newPos = m_transform->getPosition();

		if (m_input->cmd_q)
		{
			m_angle += 40.0f * deltaTs;
			m_angleUpdate = true;
		}
		if (m_input->cmd_e)
		{
			m_angle -= 40.0f * deltaTs;
			m_angleUpdate = true;
		}
		if (m_angle > 360 || m_angle < -360)
		{
			m_angle = 0;
		}
		m_transform->setRotation(rend::vec3(0, m_angle, 0));
		
		if (m_input->cmd_w)
		{
			newPos += m_transform->getDirection() * 20.0f * deltaTs;
		}
		if (m_input->cmd_s)
		{
			newPos -= m_transform->getDirection() * 20.0f * deltaTs;
		}
		if (m_input->cmd_a)
		{
			newPos += m_transform->getLeft() * 10.0f * deltaTs;
		}
		if (m_input->cmd_d)
		{
			newPos -= m_transform->getLeft() * 10.0f * deltaTs;
		}
		if (m_input->cmd_space)
		{
			newPos.y += 20.0f * deltaTs;
		}
		if (m_input->cmd_lshift)
		{
			newPos.y -= 20.0f * deltaTs;
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

		m_transform = getEntity()->getTransform();

		m_angle = 180.0f;
	}

	float getAngle()
	{
		return m_angle - 180.f;
	}

	bool getAngleUpdate()
	{
		return m_angleUpdate;
	}

private:
	std::shared_ptr<Input> m_input;

	bool m_angleUpdate;

	std::shared_ptr<Transform> m_transform;

	float m_angle;
};

struct CamController : Component
{

	void onTick(float deltaTs)
	{
		float x = (m_posOffset.x * rend::cos(rend::radians(m_player->getAngle()))) + (m_posOffset.z * rend::sin(rend::radians(m_player->getAngle())));
		float y = m_posOffset.y;
		float z = (-m_posOffset.x * rend::sin(rend::radians(m_player->getAngle()))) + (m_posOffset.z * rend::cos(rend::radians(m_player->getAngle())));


		if (m_input->cmd_f)
		{
			m_xAng += 20.0f * deltaTs;
		}
		if (m_input->cmd_r)
		{
			m_xAng -= 20.0f * deltaTs;
		}
		if (m_xAng < -50.0f)
		{
			m_xAng = -50.0f;
		}
		else if (m_xAng > 10.0f)
		{
			m_xAng = 10.0f;
		}

		//y = ( y * rend::cos( rend::radians(m_xAng) ) ) - ( z * rend::sin( rend::radians(m_xAng) ) );
		//z = ( y * rend::sin( rend::radians(m_xAng) ) ) - ( z * rend::cos( rend::radians(m_xAng) ) );
		rend::vec3 newOffset = rend::vec3(x, y, z);

		getEntity()->getTransform()->setPosition(m_player->getEntity()->getTransform()->getPosition() + newOffset);
		getEntity()->getTransform()->setRotation(rend::vec3(m_xAng, m_player->getAngle(), 0));

		/*
		bool angleUpdate = m_player->getAngleUpdate();
		if (angleUpdate)
		{
			rend::translate()
			rend::vec3 camPos = getEntity()->getTransform()->getPosition() - m_posOffset;
			float x = (camPos.x * rend::cos(rend::radians(m_player->getAngle()))) + (camPos.z * rend::sin(rend::radians(m_player->getAngle())));
			float y = camPos.y;
			float z = (-camPos.x * rend::sin(rend::radians(m_player->getAngle()))) + (camPos.z * rend::cos(rend::radians(m_player->getAngle())));
			rend::vec3 newPos = rend::vec3(x, y, z) + m_posOffset;
			getEntity()->getTransform()->setPosition(newPos);
		}*/
		//translate camera to player
		//rotate camera
		//translate camera back

		///rend::mat4 transform(1);
		

		/*
		rend::mat4 transform = rend::rotate(getEntity()->getTransform()->getModel(), rend::radians(m_player->getAngle()), rend::vec3(0,1,0));
		

		if (m_player->getAngle() > 10)
		{
			int asdipo = 0;
		}
		rend::vec4 tempPos = transform * rend::vec4(getEntity()->getTransform()->getPosition(), 1);
		rend::vec3 newPos = rend::vec3(tempPos.x, tempPos.y, tempPos.z);
		getEntity()->getTransform()->setPosition(newPos);
		
		getEntity()->getTransform()->setRotation(rend::vec3(-20, m_player->getAngle(), 0));
		*/
	}

	void onDisplay()
	{
		//std::cout << "Displaying" << std::endl;
	}

	void onInit()
	{
		m_input = getEntity()->getCore()->getInput();

		m_xAng = -20.0f;
	}

	void setPlayer(std::shared_ptr<Player> _player)
	{
		std::shared_ptr<Transform> myPos = getEntity()->getTransform();
		m_player = _player;
		m_posOffset = myPos->getPosition() - m_player->getEntity()->getTransform()->getPosition();
	}

private:
	std::shared_ptr<Input> m_input;

	std::shared_ptr<Player> m_player;

	rend::vec3 m_posOffset;

	float m_xAng;
};

struct Obstacle : Component
{
	void onInit()
	{
		randomisePos();
	}

	void randomisePos()
	{

	}

	void onTick(float deltaTs)
	{
		std::shared_ptr<BoxCollider> playerCollider = m_player->getComponent<BoxCollider>();

		if (playerCollider->isColliding(getEntity()->getTransform()->getPosition(), m_collider->getSize() * 1.01f))
		{
			m_player->getComponent<SoundSource>()->play();
			//std::cout << "COLLIDE" << std::endl;
		}
	}

	void setData(std::shared_ptr<Entity> _player, std::shared_ptr<BoxCollider> _collider)
	{
		m_player = _player;
		m_collider = _collider;
	}
private:
	std::shared_ptr<Entity> m_player;

	std::shared_ptr<BoxCollider> m_collider;
};

int main(int argc, char *argv[])
{
	///< Player and Camera Creation

	std::shared_ptr<Core> core = Core::initialize();

	std::shared_ptr<Entity> playerEntity = core->addEntity();
	playerEntity->addComponent<Player>();
	std::shared_ptr<TriangleRenderer> tr = playerEntity->addComponent<TriangleRenderer>();
	tr->setMesh(core->getResources()->load<Model>("../src/assests/models/curuthers.obj"));
	tr->setTexture(core->getResources()->load<ETexture>("../src/assests/models/textures/Whiskers_diffuse.png"));

	std::shared_ptr<SoundSource> ss = playerEntity->addComponent<SoundSource>();
	std::shared_ptr<Sound> sound = core->getResources()->load<Sound>("../src/assests/sounds/bingchilling.ogg");
	ss->setSound(sound);

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
	trfloor->setMesh(core->getResources()->load<Model>("../src/assests/models/floor.obj"));
	trfloor->setTexture(core->getResources()->load<ETexture>("../src/assests/models/textures/floor.png"));

	std::shared_ptr<BoxCollider> fBC = floor->addComponent<BoxCollider>();
	fBC->setSize(rend::vec3(5000.0f, 1.0f, 5000.0f));

	std::shared_ptr<Entity> wallN = core->addEntity();
	std::shared_ptr<Transform> wallNT = wallN->getTransform();

	wallNT->setPosition(rend::vec3(0, 0, -500));
	wallNT->setRotation(rend::vec3(90, 0, 180));
	wallNT->setScale(rend::vec3(250.0f, 1.0f, 250.0f));
	std::shared_ptr<BoxCollider> fBCwallN = wallN->addComponent<BoxCollider>();
	fBCwallN->setSize(rend::vec3(1000, 1000, 10.0f));

	std::shared_ptr<TriangleRenderer> trfloorWallN = wallN->addComponent<TriangleRenderer>();
	trfloorWallN->setMesh(core->getResources()->load<Model>("../src/assests/models/floor.obj"));
	trfloorWallN->setTexture(core->getResources()->load<ETexture>("../src/assests/models/textures/sky.png"));

	std::shared_ptr<Entity> wallE = core->addEntity();
	std::shared_ptr<Transform> wallET = wallE->getTransform();

	wallET->setPosition(rend::vec3(-500, 0, 0));
	wallET->setRotation(rend::vec3(90, 90, 180));
	wallET->setScale(rend::vec3(250.0f, 1.0f, 250.0f));
	std::shared_ptr<BoxCollider> fBCwallE = wallE->addComponent<BoxCollider>();
	fBCwallE->setSize(rend::vec3(10.0f, 1000, 1000));

	std::shared_ptr<TriangleRenderer> trfloorWallE = wallE->addComponent<TriangleRenderer>();
	trfloorWallE->setMesh(core->getResources()->load<Model>("../src/assests/models/floor.obj"));
	trfloorWallE->setTexture(core->getResources()->load<ETexture>("../src/assests/models/textures/sky.png"));

	std::shared_ptr<Entity> wallS = core->addEntity();
	std::shared_ptr<Transform> wallST = wallS->getTransform();

	wallST->setPosition(rend::vec3(0, 0, 500));
	wallST->setRotation(rend::vec3(90, 0, 180));
	wallST->setScale(rend::vec3(250.0f, 1.0f, 250.0f));
	std::shared_ptr<BoxCollider> fBCwallS = wallS->addComponent<BoxCollider>();
	fBCwallS->setSize(rend::vec3(1000, 1000, 10.0f));

	std::shared_ptr<TriangleRenderer> trfloorWallS = wallS->addComponent<TriangleRenderer>();
	trfloorWallS->setMesh(core->getResources()->load<Model>("../src/assests/models/floor.obj"));
	trfloorWallS->setTexture(core->getResources()->load<ETexture>("../src/assests/models/textures/sky.png"));

	std::shared_ptr<Entity> wallW = core->addEntity();
	std::shared_ptr<Transform> wallWT = wallW->getTransform();

	wallWT->setPosition(rend::vec3(500, 0, 0));
	wallWT->setRotation(rend::vec3(90, 90, 180));
	wallWT->setScale(rend::vec3(250.0f, 1.0f, 250.0f));
	std::shared_ptr<BoxCollider> fBCwallW = wallW->addComponent<BoxCollider>();
	fBCwallW->setSize(rend::vec3(10.0f, 1000, 1000));

	std::shared_ptr<TriangleRenderer> trfloorWallW = wallW->addComponent<TriangleRenderer>();
	trfloorWallW->setMesh(core->getResources()->load<Model>("../src/assests/models/floor.obj"));
	trfloorWallW->setTexture(core->getResources()->load<ETexture>("../src/assests/models/textures/sky.png"));

	///< Obstacle Creation

	std::shared_ptr<Entity> Ob1 = core->addEntity();
	std::shared_ptr<Transform> ObT = Ob1->getTransform();
	ObT->setScale(rend::vec3(0.5f, 0.5f, 0.5f));

	std::shared_ptr<BoxCollider> bcOb = Ob1->addComponent<BoxCollider>();

	std::shared_ptr<TriangleRenderer> Cube = Ob1->addComponent<TriangleRenderer>();
	Cube->setMesh(core->getResources()->load<Model>("../src/assests/models/Block.obj"));
	Cube->setTexture(core->getResources()->load<ETexture>("../src/assests/models/textures/GrassBlock.png"));

	std::shared_ptr<Obstacle> CubeOb = Ob1->addComponent<Obstacle>();
	CubeOb->setData(playerEntity, bcOb);

	



	core->start();

	return 0;
}
