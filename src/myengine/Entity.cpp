#include "Entity.h"
#include "Component.h"

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

	}

}