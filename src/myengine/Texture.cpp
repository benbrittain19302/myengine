#include "Texture.h"

namespace myengine
{
	void ETexture::onLoad()
	{
		m_texture = std::make_shared<rend::Texture>(getPath().c_str());
	}
}