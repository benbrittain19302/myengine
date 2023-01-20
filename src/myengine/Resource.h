#ifndef MYENGINE_RESOURCE_H
#define MYENGINE_RESOURCE_H

#include <string>
#include <memory>

namespace myengine
{
	struct Resources;

	struct Resource
	{
		std::string getPath() { return m_path; }//move to cpp later

		virtual void onLoad() {}

	private:
		friend struct Resources;

		void load() { onLoad(); }

		std::string m_path;

		std::weak_ptr<Resources> m_resources;
	};
}

#endif