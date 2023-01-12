#include <vector>
#include <memory>

namespace myengine
{
	struct Core;

	struct Component;

	struct Entity
	{
		template <typename T>
		std::shared_ptr<T> addComponent()
		{
			std::shared_ptr<T> rtn = std::make_shared<T>();

			m_components.push_back(rtn);

			return rtn;
		}

	private:
		friend struct Core;

		std::vector<std::shared_ptr<Component> > m_components;

		bool m_alive;

		void tick();

		void display();
	};
}