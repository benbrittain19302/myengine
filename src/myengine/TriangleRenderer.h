#include "Component.h"

#include <rend/rend.h>

namespace myengine
{
	struct Texture;
	
	struct TriangleRenderer : Component
	{
		TriangleRenderer();

	private:
		rend::Mesh m_mesh;
		rend::Shader m_shader;
		rend::Texture m_texture;
		
		//std::shared_ptr<Texture> m_texture;

		void onDisplay();
	};

}