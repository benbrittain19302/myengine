#include "Component.h"

#include <AL/al.h>
#include <AL/alc.h>

namespace myengine
{

	struct SoundSource : Component
	{
		SoundSource();
		
	private:
		ALenum format;
		ALsizei freq;

		ALuint bufferId;
		ALuint sourceId;
	};
}