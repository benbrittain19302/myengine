#include <memory>
#include <list>

namespace myengine
{
	struct Entity;

	struct Core
	{
		static std::shared_ptr<Core> initialize();

		void start();

		void stop();

		std::shared_ptr<Entity> addEntity();

	private:
		int m_dummy;

		bool m_running;

		std::list<std::shared_ptr<Entity> > m_entities;
	};

}