#include <vector>

namespace myengine
{
	struct Resource;

	struct Resources
	{
	private:
		std::weak_ptr<Resources> m_self;
		std::vector<std::shared_ptr<Resource> > m_resources;
		std::weak_ptr<Core> m_core;
	};	
}