#include "TriangleRenderer.h"

namespace myengine
{

	TriangleRenderer::TriangleRenderer() :
		m_mesh(rend::Mesh::TRIANGLE),
		m_shader(rend::Shader::BASIC)
	{}

	void TriangleRenderer::onDisplay()
	{
		rend::Renderer r(640, 480);

		r.shader(&m_shader);
		r.mesh(&m_mesh);

		r.projection(rend::perspective(rend::radians(45.0f), 1.0f, 0.1f, 100.0f));
		r.model(rend::translate(rend::mat4(1.0f), rend::vec3(0, 0, -10)));

		r.render();
	}

}