#include "Entity.h"
#include "Component.h"
#include "Core.h"
#include "Transform.h"
#include "SoundSource.h"

namespace myengine
{
	void Entity::tick()
	{
		for (std::vector<std::shared_ptr<Component> >::iterator itr = m_components.begin(); itr != m_components.end(); itr++)
		{
			(*itr)->tick();
		}
	}

	void Entity::display()
	{
		for (std::vector<std::shared_ptr<Component> >::iterator itr = m_components.begin(); itr != m_components.end(); itr++)
		{
			(*itr)->display();
		}
	}

	std::shared_ptr<Core> Entity::getCore()
	{
		return m_core.lock();
	}

	std::shared_ptr<Transform> Entity::getTransform()
	{
		return m_transform.lock();
	}
}