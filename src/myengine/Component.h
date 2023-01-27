#ifndef MYENGINE_COMPONENT_H
#define MYENGINE_COMPONENT_H

#include <memory>

namespace myengine
{
	struct Entity; ///< Forward declare for Entity

	/**
	* Struct defining a base Component
	*/
	struct Component
	{
		virtual void onTick(float deltaTs); ///< Base definition for onTick function
		virtual void onDisplay(); ///< Base definition for onDisplay function
		virtual void onInit();

		std::shared_ptr<Entity> getEntity(); ///< Returns a component's Entity
	private:
		friend struct Entity; ///< Entity is a friend struct to Component

		std::weak_ptr<Entity> m_entity; ///< Reference to a component's Entity

		void tick(float deltaTs); ///< Base Tick function
		void display(); ///< Base Display function
	};
}

#endif // !MYENGINE_COMPONENT_H