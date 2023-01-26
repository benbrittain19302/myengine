#include "Transform.h"

namespace myengine
{

	Transform::Transform() :
		m_scale(1, 1, 1)
	{}

	rend::mat4 Transform::getModel()
	{
		rend::mat4 rtn = rend::mat4(1.0f);

		rtn = rend::translate(rtn, m_position);

		rtn = rend::rotate(rtn, rend::radians(m_rotation.y), rend::vec3(0, 1, 0));
		rtn = rend::rotate(rtn, rend::radians(m_rotation.x), rend::vec3(1, 0, 0));
		rtn = rend::rotate(rtn, rend::radians(m_rotation.z), rend::vec3(0, 0, 1));

		rtn = rend::scale(rtn, m_scale);

		return rtn;
	}

	void Transform::setPosition(const rend::vec3& _position)
	{
		m_position = _position;
	}

	void Transform::setRotation(const rend::vec3& _rotation)
	{
		m_rotation = _rotation;
	}

	void Transform::setScale(const rend::vec3& _scale)
	{
		m_scale = _scale;
	}

	rend::vec3 Transform::getPosition() 
	{
		return m_position;
	}

	rend::vec3 Transform::getRotation() 
	{
		return m_rotation; 
	}

	rend::vec3 Transform::getScale()
	{ 
		return m_scale; 
	}
}