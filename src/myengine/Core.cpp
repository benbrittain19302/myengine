#include "Core.h"

namespace myengine
{

	std::shared_ptr<Core> Core::initialize()
	{
		//Core core = new Core();
		std::shared_ptr<Core> rtn = std::make_shared<Core>();

		return rtn;
	}

}