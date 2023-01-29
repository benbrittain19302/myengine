#include "TriangleRenderer.h"
#include "Entity.h"
#include "Transform.h"
#include "Core.h"
#include "Camera.h"
#include "Model.h"
#include "Texture.h"

namespace myengine
{

	TriangleRenderer::TriangleRenderer() :
		m_shader("../src/assests/shaders/basic.vert", "../src/assests/shaders/basic.frag")
		//m_shadowShader(), ///< Shadow Shader initialisation here
	{
		 
	}

	void TriangleRenderer::setMesh(std::shared_ptr<Model> _model)
	{
		m_model = _model;
	}

	void TriangleRenderer::setTexture(std::shared_ptr<ETexture> _tex)
	{
		m_texture = _tex;
	}

	void TriangleRenderer::onDisplay()
	{
		rend::Renderer r(640, 480);

		r.shader(&m_shader);
		r.mesh(m_model->m_mesh.get());
		r.texture(m_texture->m_texture.get());

		std::shared_ptr<Entity> camera = getEntity()->getCore()->getCamera();

		//r.projection(rend::perspective(rend::radians(45.0f), 1.0f, 0.1f, 100.0f));
		r.model(getEntity()->getTransform()->getModel());
		r.projection(camera->getComponent<Camera>()->getProj()); 
		r.view(camera->getComponent<Camera>()->getView()); 

		r.backfaceCull(true);
		r.depthTest(true);

		r.render();
	}

}