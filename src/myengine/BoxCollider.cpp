#include "BoxCollider.h"
#include "Entity.h"
#include "Transform.h"
#include "Core.h"

namespace myengine
{
	BoxCollider::BoxCollider()
	{
		m_size = rend::vec3(1, 1, 1);
	}

	void BoxCollider::setSize(rend::vec3 _size)
	{
		m_size = _size;
	}

	rend::vec3 BoxCollider::getSize()
	{
		return m_size;
	}

	bool BoxCollider::colliding(std::shared_ptr<BoxCollider> _other)
	{
		rend::vec3 otherPos = _other->getEntity()->getTransform()->getPosition();
		rend::vec3 otherSize = _other->m_size;
		/*
		rend::vec3 a = getEntity()->getTransform()->getPosition();
		rend::vec3 b = _other->getEntity()->getTransform()->getPosition();
		rend::vec3 ahs = m_size / 2.0f;
		rend::vec3 bhs = _other->m_size / 2.0f;

		if (a.x > b.x)
		{
			if (b.x + bhs.x < a.x - ahs.x)
			{
				return false;
			}
		}
		else
		{
			if (a.x + ahs.x < b.x - bhs.x)
			{
				return false;
			}
		}
		if (a.y > b.y)
		{
			if (b.y + bhs.y < a.y - ahs.y)
			{
				return false;
			}
		}
		else
		{
			if (a.y + ahs.y < b.y - bhs.y)
			{
				return false;
			}
		}
		if (a.z > b.z)
		{
			if (b.z + bhs.z < a.z - ahs.z)
			{
				return false;
			}
		}
		else
		{
			if (a.z + ahs.z < b.z - bhs.z)
			{
				return false;
			}
		}

		return true;*/

		return isColliding(otherPos, otherSize);
	}

	bool BoxCollider::isColliding(rend::vec3 _position, rend::vec3 _size)
	{
		rend::vec3 a = getEntity()->getTransform()->getPosition();
		rend::vec3 b = _position;
		rend::vec3 ahs = m_size / 2.0f;
		rend::vec3 bhs = _size / 2.0f;

		if (a.x > b.x)
		{
			if (b.x + bhs.x < a.x - ahs.x)
			{
				return false;
			}
		}
		else
		{
			if (a.x + ahs.x < b.x - bhs.x)
			{
				return false;
			}
		}
		if (a.y > b.y)
		{
			if (b.y + bhs.y < a.y - ahs.y)
			{
				return false;
			}
		}
		else
		{
			if (a.y + ahs.y < b.y - bhs.y)
			{
				return false;
			}
		}
		if (a.z > b.z)
		{
			if (b.z + bhs.z < a.z - ahs.z)
			{
				return false;
			}
		}
		else
		{
			if (a.z + ahs.z < b.z - bhs.z)
			{
				return false;
			}
		}

		return true;

		/*
		std::vector<std::shared_ptr<BoxCollider> > colliders;
		std::shared_ptr<Core> core = getEntity()->getCore();

		core->find<BoxCollider>(colliders);

		for (std::vector<std::shared_ptr<BoxCollider> >::iterator itr = colliders.begin(); itr != colliders.end(); itr++)
		{
			std::shared_ptr<Entity> other = (*itr)->getEntity();
			if (!(getEntity() == other))
			{
				rend::vec3 a = _position;
				rend::vec3 b = other->getTransform()->getPosition();
				rend::vec3 ahs = _size / 2.0f;
				rend::vec3 bhs = other->getComponent<BoxCollider>()->m_size / 2.0f;

				if (a.x > b.x)
				{
					if (b.x + bhs.x < a.x - ahs.x)
					{
						return false;
					}
				}
				else
				{
					if (a.x + ahs.x < b.x - bhs.x)
					{
						return false;
					}
				}
				if (a.y > b.y)
				{
					if (b.y + bhs.y < a.y - ahs.y)
					{
						return false;
					}
				}
				else
				{
					if (a.y + ahs.y < b.y - bhs.y)
					{
						return false;
					}
				}
				if (a.z > b.z)
				{
					if (b.z + bhs.z < a.z - ahs.z)
					{
						return false;
					}
				}
				else
				{
					if (a.z + ahs.z < b.z - bhs.z)
					{
						return false;
					}
				}

				return true;
			}
		}
		*/
	}

	bool BoxCollider::isColliding(rend::vec3 _position, rend::vec3 _size, rend::vec3 _testPos)
	{
		rend::vec3 a = _testPos;
		rend::vec3 b = _position;
		rend::vec3 ahs = m_size / 2.0f;
		rend::vec3 bhs = _size / 2.0f;

		if (a.x > b.x)
		{
			if (b.x + bhs.x < a.x - ahs.x)
			{
				return false;
			}
		}
		else
		{
			if (a.x + ahs.x < b.x - bhs.x)
			{
				return false;
			}
		}
		if (a.y > b.y)
		{
			if (b.y + bhs.y < a.y - ahs.y)
			{
				return false;
			}
		}
		else
		{
			if (a.y + ahs.y < b.y - bhs.y)
			{
				return false;
			}
		}
		if (a.z > b.z)
		{
			if (b.z + bhs.z < a.z - ahs.z)
			{
				return false;
			}
		}
		else
		{
			if (a.z + ahs.z < b.z - bhs.z)
			{
				return false;
			}
		}

		return true;
	}


	rend::vec3 BoxCollider::getColResponse(rend::vec3 _position, rend::vec3 _size)
	{
		float amount = 0.1f;
		float step = 0.1f;

		rend::vec3 testPos = getEntity()->getTransform()->getPosition();

		while (true)
		{
			if (!isColliding(_position, _size, testPos)) break;
			testPos.x += amount;
			if (!isColliding(_position, _size, testPos)) break;
			testPos.x -= amount;
			testPos.x -= amount;
			if (!isColliding(_position, _size, testPos)) break;
			testPos.x += amount;
			testPos.z += amount;
			if (!isColliding(_position, _size, testPos)) break;
			testPos.z -= amount;
			testPos.z -= amount;
			if (!isColliding(_position, _size, testPos)) break;
			testPos.z += amount;
			testPos.y += amount;
			if (!isColliding(_position, _size, testPos)) break;
			testPos.y -= amount;
			testPos.y -= amount;
			if (!isColliding(_position, _size, testPos)) break;
			testPos.y += amount;
			amount += step;
		}

		return testPos;
	}
}