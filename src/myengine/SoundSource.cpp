#include "SoundSource.h"
#include "Entity.h"
#include "Transform.h"
#include "Core.h"

#include <rend/rend.h>

#include "stb_vorbis.c"

namespace myengine
{
	SoundSource::SoundSource()
	{
		m_format = 0;
		m_freq = 0;
		m_bufferId = 0;
		m_sourceId = 0;
		m_loaded = false;
	}

	SoundSource::~SoundSource()
	{
		if (m_loaded)
		{
			alDeleteSources(1, &m_sourceId);
			alDeleteBuffers(1, &m_bufferId);
		}
	}

	void SoundSource::load(const std::string& _path)
	{

		load_ogg("../src/assests/sounds/bingchilling.ogg");

		alGenBuffers(1, &m_bufferId);

		alBufferData(m_bufferId, m_format, &m_bufferData.at(0), static_cast<ALsizei>(m_bufferData.size()), m_freq);

		alGenSources(1, &m_sourceId);

		alSourcei(m_sourceId, AL_BUFFER, m_bufferId);

		m_loaded = true;
	}

	void SoundSource::play()
	{
		if (m_loaded)
		{
			alSourcePlay(m_sourceId);
		}
	}
	
	void SoundSource::load_ogg(const std::string& _path)
	{
		int channels = 0;
		int sampleRate = 0;
		short* output = NULL;

		size_t samples = stb_vorbis_decode_filename(_path.c_str(),
			&channels, &sampleRate, &output);

		if (samples == -1)
		{
			throw std::runtime_error("Failed to open file '" + _path + "' for decoding");
		}

		// Record the format required by OpenAL
		if (channels < 2)
		{
			m_format = AL_FORMAT_MONO16;
		}
		else
		{
			m_format = AL_FORMAT_STEREO16;
		}

		// Copy (# samples) * (1 or 2 channels) * (16 bits == 2 bytes == short)
		m_bufferData.resize(samples * channels * sizeof(short));
		memcpy(&m_bufferData.at(0), output, m_bufferData.size());

		// Record the sample rate required by OpenAL
		m_freq = sampleRate;

		// Clean up the read data
		free(output);
	}

	void SoundSource::onTick()
	{
		rend::vec3 myPos = getEntity()->getTransform()->getPosition();
		rend::vec3 cameraPos = getEntity()->getCore()->getCamera()->getTransform()->getPosition();
		if (m_loaded)
		{
			alSource3f(m_sourceId, AL_POSITION, myPos.x, myPos.y, myPos.z);
			alListener3f(AL_POSITION, cameraPos.x, cameraPos.y, cameraPos.z);
		}
	}
}