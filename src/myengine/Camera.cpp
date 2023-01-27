#include "Camera.h"
#include "Entity.h"
#include "Transform.h"
#include "Core.h"

namespace myengine
{
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
		return  rend::perspective(rend::radians(45.0f), 1.0f, 0.1f, 1000.0f);
	}
}