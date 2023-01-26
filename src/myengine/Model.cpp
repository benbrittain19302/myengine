#include "Model.h"


namespace myengine
{
	void Model::onLoad()
	{
		m_mesh = std::make_shared<rend::Mesh>(getPath().c_str());
	}
}