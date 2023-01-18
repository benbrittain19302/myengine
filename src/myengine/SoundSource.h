#include "Component.h"

#include <AL/al.h>
#include <AL/alc.h>

#include <vector>
#include <string>
#include <stdexcept>

namespace myengine
{
	struct Entity;
	struct Component;

	struct SoundSource : Component
	{
		SoundSource();
		~SoundSource();

		void load(const std::string& _path);
		void play();

	private:
		bool m_loaded;

		ALenum m_format;
		ALsizei m_freq;

		std::vector<unsigned char> m_bufferData;

		ALuint m_bufferId;
		ALuint m_sourceId;

		void load_ogg(const std::string& _path);

		void onTick();
	};
}