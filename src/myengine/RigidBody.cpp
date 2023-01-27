#include "RigidBody.h"
#include "Core.h"
#include "Entity.h"
#include "Transform.h"
#include "BoxCollider.h"

#include <vector>
#include <iostream>

namespace myengine
{
	void Rigidbody::onTick()
	{
		std::vector<std::shared_ptr<BoxCollider> > colliders;
		std::shared_ptr<Core> core = getEntity()->getCore();

		core->find<BoxCollider>(colliders);

		for (std::vector<std::shared_ptr<BoxCollider> >::iterator itr = colliders.begin(); itr != colliders.end(); itr++)
		{
			std::shared_ptr<Entity> other = (*itr)->getEntity();
			if ( !(getEntity() == other) )
			{
				if (getEntity()->getComponent<BoxCollider>()->colliding((*itr)))
				{
					std::cout << "COLLIDE" << m_colCount << std::endl;
					m_colCount++;

					rend::vec3 otherPos = other->getTransform()->getPosition();
					rend::vec3 otherSize = (*itr)->getSize();

					rend::vec3 newPos = getEntity()->getComponent<BoxCollider>()->getColResponse(otherPos, otherSize);

					getEntity()->getTransform()->setPosition(newPos);
				}
			}
		}
	}
}