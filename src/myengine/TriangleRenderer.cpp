#include "TriangleRenderer.h"
#include "Entity.h"
#include "Transform.h"
#include "Core.h"
#include "Camera.h"

namespace myengine
{

	TriangleRenderer::TriangleRenderer() :
		m_mesh("../src/assests/models/curuthers.obj"),
		m_shader("../src/assests/shaders/basic.vert", "../src/assests/shaders/basic.frag"),
		//m_shadowShader(), ///< Shadow Shader initialisation here
		m_texture("../src/assests/models/textures/Whiskers_diffuse.png")
	{
		//m_camera = getEntity()->getCore()->getCamera(); SHARED POINTER ISSUE
	}

	void TriangleRenderer::onDisplay()
	{
		rend::Renderer r(640, 480);

		r.shader(&m_shader);
		r.mesh(&m_mesh);
		r.texture(&m_texture);

		r.projection(rend::perspective(rend::radians(45.0f), 1.0f, 0.1f, 100.0f));
		r.model(getEntity()->getTransform()->getModel());
		//r.projection(m_camera->getComponent<Camera>()->getProj()); SHARED POINTER ISSUE
		//r.view(m_camera->getComponent<Camera>()->getView()); SHARED POINTER ISSUE

		r.backfaceCull(true);
		r.depthTest(true);

		r.render();
	}

}