#include "gameStructs.h"

#include <iostream>
#include <chrono>

using namespace myengine;

void Player::onTick(float deltaTs)
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

void Player::onInit()
{
	m_input = getEntity()->getCore()->getInput();

	rend::vec3 startPos = rend::vec3(0, 2, 0);
	rend::vec3 startRot = rend::vec3(-10, 0, 0);

	getEntity()->getTransform()->setPosition(startPos);
	getEntity()->getTransform()->setRotation(startRot);

	m_transform = getEntity()->getTransform();

	m_angle = 180.0f;
}

float Player::getAngle()
{
	return m_angle - 180.f;
}

void CamController::onTick(float deltaTs)
{
	if (m_input->cmd_lctrl && !camTog)
	{
		rCam = !rCam;
		camTog = true;
	}
	else if (!m_input->cmd_lctrl)
	{
		camTog = false;
	}

	if (rCam)
	{
		m_posOffset.x = 1;
	}
	else
	{
		m_posOffset.x = -1;
	}

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
	if (m_xAng < -45.0f)
	{
		m_xAng = -45.0f;
	}
	else if (m_xAng > 5.0f)
	{
		m_xAng = 5.0f;
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

void CamController::onInit()
{
	m_input = getEntity()->getCore()->getInput();

	m_xAng = -15.0f;

	rCam = true;
	camTog = false;
}

void CamController::setPlayer(std::shared_ptr<Player> _player)
{
	std::shared_ptr<Transform> myPos = getEntity()->getTransform();
	m_player = _player;
	m_posOffset = myPos->getPosition() - m_player->getEntity()->getTransform()->getPosition();
}

void Milk::onInit()
{
	m_hitCount = 0;
}

void Milk::onTick(float deltaTs)
{
	std::shared_ptr<BoxCollider> playerCollider = m_player->getComponent<BoxCollider>();

	if (playerCollider->isColliding(getEntity()->getTransform()->getPosition(), m_collider->getSize() * 1.1f))
	{
		m_player->getComponent<SoundSource>()->play();
		m_hitCount++;
		//std::cout << "COLLIDE" << std::endl;
		randomisePos();
	}
}

void Milk::randomisePos()
{
	srand(std::chrono::steady_clock::now().time_since_epoch().count());
	int randX = (rand() % 201) - 100;
	srand(std::chrono::steady_clock::now().time_since_epoch().count());
	int randZ = (rand() % 201) - 100;

	if (-3 <= randX && randX <= 3)
	{
		if (randX % 2 == 0)
		{
			randX += 3;
		}
		else
		{
			randX -= 3;
		}
	}
	if (-3 <= randZ && randZ <= 3)
	{
		if (randZ % 2 == 0)
		{
			randZ += 3;
		}
		else
		{
			randZ -= 3;
		}
	}

	getEntity()->getTransform()->setPosition(rend::vec3(randX, 0, randZ));

	std::vector<std::shared_ptr<BoxCollider> > colliders;
	std::shared_ptr<Core> core = getEntity()->getCore();

	core->find<BoxCollider>(colliders);

	for (std::vector<std::shared_ptr<BoxCollider> >::iterator itr = colliders.begin(); itr != colliders.end(); itr++)
	{
		std::shared_ptr<Entity> other = (*itr)->getEntity();
		if (!(getEntity() == other))
		{
			if (m_collider->colliding((*itr)))
			{
				randomisePos();
			}
		}
	}
}

void Milk::setData(std::shared_ptr<Entity> _player, std::shared_ptr<BoxCollider> _collider)
{
	m_player = _player;
	m_collider = _collider;
}

int Milk::getScore()
{
	return m_hitCount;
}

void Obstacle::onTick(float deltaTs)
{
	std::shared_ptr<BoxCollider> playerCollider = m_player->getComponent<BoxCollider>();

	if (playerCollider->isColliding(getEntity()->getTransform()->getPosition(), m_collider->getSize() * 1.1f))
	{
		system("CLS");
		std::cout << "YOU DIED!" << std::endl;
		getEntity()->getCore()->stop();
	}
}

void Obstacle::randomisePos()
{
	srand(std::chrono::steady_clock::now().time_since_epoch().count());
	int randX = (rand() % 201) - 100;
	srand(std::chrono::steady_clock::now().time_since_epoch().count());
	int randZ = (rand() % 201) - 100;

	if (-3 <= randX && randX <= 3)
	{
		if (randX % 2 == 0)
		{
			randX += 3;
		}
		else
		{
			randX -= 3;
		}
	}
	if (-3 <= randZ && randZ <= 3)
	{
		if (randZ % 2 == 0)
		{
			randZ += 3;
		}
		else
		{
			randZ -= 3;
		}
	}

	getEntity()->getTransform()->setPosition(rend::vec3(randX, 0, randZ));

	std::vector<std::shared_ptr<BoxCollider> > colliders;
	std::shared_ptr<Core> core = getEntity()->getCore();

	core->find<BoxCollider>(colliders);

	for (std::vector<std::shared_ptr<BoxCollider> >::iterator itr = colliders.begin(); itr != colliders.end(); itr++)
	{
		std::shared_ptr<Entity> other = (*itr)->getEntity();
		if (!(getEntity() == other))
		{
			if (m_collider->colliding((*itr)))
			{
				randomisePos();
			}
		}
	}
}

void Obstacle::setData(std::shared_ptr<Entity> _player, std::shared_ptr<BoxCollider> _collider)
{
	m_player = _player;
	m_collider = _collider;
}

void Song::onInit()
{
	m_check = false;
}

void Song::onTick(float deltaTs)
{
	if (m_check && !m_song->isPlaying())
	{
		system("CLS");
		std::cout << "YOU SURVIVED!" << std::endl;
		getEntity()->getCore()->stop();
	}

	getEntity()->getTransform()->setPosition(m_playerTransform->getPosition());
}

void Song::play()
{
	m_song->play();
}

void Song::setCheck(bool _check)
{
	m_check = _check;
}

void Song::setData(std::shared_ptr<SoundSource> _song, std::shared_ptr<Transform> _playerTransform)
{
	m_song = _song;
	m_playerTransform = _playerTransform;
}

void Announcement::onInit()
{
	m_doPlay = true;
}

void Announcement::onTick(float deltaTs)
{
	if (m_doPlay && !m_self->isPlaying())
	{
		m_doPlay = false;
		m_song->setCheck(true);
		m_song->play();
	}

	getEntity()->getTransform()->setPosition(m_playerTransform->getPosition());
}

void Announcement::setData(std::shared_ptr<SoundSource> _self, std::shared_ptr<Song> _song, std::shared_ptr<Transform> _player)
{
	m_self = _self;
	m_song = _song;
	m_playerTransform = _player;
}
