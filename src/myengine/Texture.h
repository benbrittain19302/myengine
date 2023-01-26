#include "Resource.h"

#include <rend/rend.h>

namespace myengine
{
	struct ETexture : Resource
	{

		void onLoad();

	private:
		friend struct TriangleRenderer;

		std::shared_ptr<rend::Texture> m_texture;
	};
}