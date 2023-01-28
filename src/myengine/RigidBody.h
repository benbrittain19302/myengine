#include "Component.h"

#include <rend/rend.h>

namespace myengine
{
	struct Rigidbody : Component
	{
		void onTick(float deltaTs);
	private:
		int m_colcount;
	};
}