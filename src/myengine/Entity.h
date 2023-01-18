#include <vector>
#include <memory>
#include <string>

namespace myengine
{
	struct Core;
	struct Component;
	struct Transform;
	struct SoundSource;

	struct Entity
	{
		template <typename T>
		std::shared_ptr<T> addComponent()
		{
			std::shared_ptr<T> rtn = std::make_shared<T>();

			rtn->m_entity = m_self;

			m_components.push_back(rtn);

			return rtn;
		}

		//Component Template (CT)
		template <typename CT>
		std::shared_ptr<CT> getComponent()
		{
			//Go through each component
			for (std::vector<std::shared_ptr<Component> >::iterator itr = m_components.begin(); itr != m_components.end(); itr++)
			{
				std::shared_ptr<Component> c = (*itr);

				//Try to dynamic cast the Component to a CT
				std::shared_ptr<CT> t = std::dynamic_pointer_cast<CT>(c);

				//If it succeeds, return component
				if (t)
				{
					return t;
				}
			}
		}

		std::shared_ptr<Core> getCore();
		std::shared_ptr<Transform> getTransform();

	private:
		friend struct Core;

		std::weak_ptr<Core> m_core;
		std::weak_ptr<Entity> m_self;

		std::vector<std::shared_ptr<Component> > m_components;

		std::weak_ptr<Transform> m_transform;

		bool m_alive;

		void tick();

		void display();
	};
}