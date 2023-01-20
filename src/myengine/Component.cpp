#include "Component.h"
#include "Entity.h"

namespace myengine
{
	void Component::onTick() { } ///< Empty base onTick function
	void Component::onDisplay() { } ///< Empty base onDisplay function

	void Component::tick()
	{
		onTick(); ///< When ticking, call overridden onTick if it exists
	}

	void Component::display()
	{
		onDisplay(); ///< When displaying, call overridden onDisplay if it exists
	}

	std::shared_ptr<Entity> Component::getEntity()
	{
		return m_entity.lock(); ///< Return reference to component's Entity
	}
}