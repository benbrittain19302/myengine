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
		//rend::Shader m_shadowShader; ///< Shadow Shader data here
		rend::Texture m_texture;
		
		//std::shared_ptr<Model> m_model ///< Switch to Resource Management Model
		//std::shared_ptr<Texture> m_texture; ///< Switch to Resource Management Texture

		void onDisplay();
	};

}