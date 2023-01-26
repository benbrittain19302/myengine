#include "Component.h"

#include <rend/rend.h>

namespace myengine
{

	struct Transform : Component
	{
		Transform();

		rend::mat4 getModel();

		void setPosition(const rend::vec3& _position);
		void setRotation(const rend::vec3& _rotation);
		void setScale(const rend::vec3& _scale);

		rend::vec3 getPosition();
		rend::vec3 getRotation();
		rend::vec3 getScale();

	private:
		rend::vec3 m_position;
		rend::vec3 m_rotation;
		rend::vec3 m_scale;
	};

}