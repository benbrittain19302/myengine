#include "Resource.h"

#include <rend/rend.h>

namespace myengine
{
	struct TriangleRenderer;

	struct Model : Resource
	{
		void onLoad();

	private:
		friend struct TriangleRenderer;

		std::shared_ptr<rend::Mesh> m_mesh;
	};
}