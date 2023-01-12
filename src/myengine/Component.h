#ifndef MYENGINE_COMPONENT_H
#define MYENGINE_COMPONENT_H

#include <memory>

namespace myengine
{
	struct Entity;

	struct Component
	{
		virtual void onTick();
		virtual void onDisplay();

		std::shared_ptr<Entity> getEntity();
	private:
		friend struct Entity;

		std::weak_ptr<Entity> m_entity;

		void tick();
		void display();
	};
}

#endif // !MYENGINE_COMPONENT_H