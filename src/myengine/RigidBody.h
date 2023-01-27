#include "Component.h"

#include <rend/rend.h>

namespace myengine
{
	struct Rigidbody : Component
	{
		void onTick();
	private:
		int m_colCount;
	};
}