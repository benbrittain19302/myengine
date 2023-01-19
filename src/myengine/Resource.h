#ifndef MYENGINE_RESOURCE_H
#define MYENGINE_RESOURCE_H

#include <string.h>

namespace myengine
{
	struct Resources;

	struct Resource
	{
	private:
		std::string m_path;

		std::weak_ptr<Resources> m_resources;
	};
}

#endif