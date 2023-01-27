#include <vector>
#include <memory>
#include <string>
#include <stdexcept>

namespace myengine
{
	struct Core; ///< Forward Declare for Core
	struct Component; ///< Forward Declare for Component
	struct Transform; ///< Forward Declare for Transform


	/**
	*Struct defining an Entity
	*/
	struct Entity
	{
		/**
		* Add Component to Entity of template type T
		*/
		template <typename T>
		std::shared_ptr<T> addComponent()
		{
			std::shared_ptr<T> rtn = std::make_shared<T>(); ///< Create a Component of type T

			rtn->m_entity = m_self; ///< Ensure Component has a reference to it's Entity

			rtn->onInit();

			m_components.push_back(rtn); ///< Add Component to Entity List

			return rtn;
		}

		/**
		* Find Component of template type CT
		*/
		template <typename CT>
		std::shared_ptr<CT> getComponent()
		{
			///< Go through each component
			for (std::vector<std::shared_ptr<Component> >::iterator itr = m_components.begin(); itr != m_components.end(); itr++)
			{
				///< Create Copy of Component itr
				std::shared_ptr<Component> c = (*itr);

				///< Try to dynamic cast the Component to a CT
				std::shared_ptr<CT> t = std::dynamic_pointer_cast<CT>(c);

				///< If it succeeds, return component
				if (t)
				{
					return t;
				}
			}

			throw std::runtime_error("Failed to find component");
		}
		/**
		* Return reference to Core
		*/
		std::shared_ptr<Core> getCore();

		/**
		* Shortcut return transform
		*/
		std::shared_ptr<Transform> getTransform();

	private:
		friend struct Core; ///< Core is a friend struct to Entity

		std::weak_ptr<Core> m_core; ///< Reference to Core
		std::weak_ptr<Entity> m_self; ///< Reference to self

		std::vector<std::shared_ptr<Component> > m_components; ///< List of Entity Components

		std::weak_ptr<Transform> m_transform; ///< Shortcut to own Transform Component

		bool m_alive;

		void tick(float deltaTs); ///< Update Entity

		void display(); ///< Display Entity
	};
}