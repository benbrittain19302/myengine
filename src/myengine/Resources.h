#include <vector>
#include <memory>
#include <string>

namespace myengine
{
	struct Resource;
	struct Core;

	struct Resources
	{
		template <typename T>
		std::shared_ptr<T> load(const std::string& _path)
		{
			for (std::vector< std::shared_ptr<Resource> >::iterator itr = m_resources.begin(); itr != m_resources.end(); itr++)
			{
				if (itr->get()->getPath() == _path)
				{
					return std::dynamic_pointer_cast<T>(*itr);
				}
			}
			std::shared_ptr<T> rtn = std::make_shared<T>();
			rtn->m_path = _path;
			rtn->load();
			m_resources.push_back(rtn);
			return rtn;
		}

	private:
		std::weak_ptr<Resources> m_self;
		std::vector<std::shared_ptr<Resource> > m_resources;
		std::weak_ptr<Core> m_core;
	};	
}