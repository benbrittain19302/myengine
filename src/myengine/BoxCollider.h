#include "Component.h"

#include <rend/rend.h>

namespace myengine
{
	struct RigidBody;

	struct BoxCollider : Component
	{
		BoxCollider();

		void setSize(rend::vec3 _size);

		rend::vec3 getSize();

		bool colliding(std::shared_ptr<BoxCollider> _other);

		bool isColliding(rend::vec3 _position, rend::vec3 _size);
		bool isColliding(rend::vec3 _position, rend::vec3 _size, rend::vec3 _testPos);

		rend::vec3 getColResponse(rend::vec3 _position, rend::vec3 _size);

	private:
		friend struct RigidBody;

		rend::vec3 m_size;
	};
}