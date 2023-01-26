#include "Component.h"

#include <rend/rend.h>

namespace myengine
{
	struct ETexture;
	struct Model;
	
	struct TriangleRenderer : Component
	{
		TriangleRenderer();

		void setMesh(std::shared_ptr<Model> _model);
		void setTexture(std::shared_ptr<ETexture> _tex);

	private:
		rend::Shader m_shader;
		//rend::Shader m_shadowShader; ///< Shadow Shader data here
		//rend::Texture m_texture;
		
		std::shared_ptr<Model> m_model; ///< Switch to Resource Management Model  
		std::shared_ptr<ETexture> m_texture; ///< Switch to Resource Management Texture

		void onDisplay();
	};

}