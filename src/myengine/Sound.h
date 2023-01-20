#include "Resource.h"

#include <AL/al.h>

namespace myengine
{
	struct SoundSource;

	struct Sound : Resource
	{
		void onLoad();
	private:
		friend struct SoundSource;

		ALuint m_bufferId;
	};
}