#include "Camera.h"
#include "Entity.h"
#include "Transform.h"

namespace myengine
{
	Camera::Camera()
	{
		//m_transform = getEntity()->getTransform();

		//m_transform->setPosition(rend::vec3(0, 5, 0));

		rend::vec3 initTarget = rend::vec3(-100, 0, 0);

		m_speed = 0.1f;
		m_mouseSpeed = 0.005f;

		m_oldMousePos = rend::vec2(0);

		m_up = rend::vec3(0, 1, 0);

		m_proj = rend::perspective(rend::radians(45.0f), 1.0f, 0.1f, 100.0f);
		//m_view = rend::lookAt(m_transform->getPosition(), initTarget, m_up);
	}

	rend::mat4 Camera::getView()
	{
		return m_view;
	}

	rend::mat4 Camera::getProj()
	{
		return m_proj;
	}
}