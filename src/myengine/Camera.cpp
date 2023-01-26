#include "Camera.h"
#include "Entity.h"
#include "Transform.h"
#include "Core.h"

namespace myengine
{
	Camera::Camera()
	{
		m_speed = 0.1f;
		m_mouseSpeed = 0.005f;

		m_oldMousePos = rend::vec2(0);

		m_up = rend::vec3(0, 1, 0);
	}

	void Camera::onInit()
	{
		getEntity()->getCore()->m_camera = getEntity();
	}

	rend::mat4 Camera::getView()
	{
		return rend::inverse(getEntity()->getTransform()->getModel());
	}

	rend::mat4 Camera::getProj()
	{
		return  rend::perspective(rend::radians(45.0f), 1.0f, 0.1f, 100.0f);
	}
}