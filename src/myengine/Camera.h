#include "Component.h"

#include <rend/rend.h>

#include <memory>

namespace myengine
{
	struct Transform;

	struct Camera : Component
	{
		Camera();

		rend::mat4 getView();
		rend::mat4 getProj();

		void onInit();

	private:
		rend::vec3 m_up;

		float m_speed;

		float m_mouseSpeed;

		rend::vec2 m_oldMousePos;
	};
}