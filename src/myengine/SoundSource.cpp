#include "SoundSource.h"
#include "Entity.h"
#include "Transform.h"
#include "Core.h"
#include "Sound.h"

#include <rend/rend.h>

namespace myengine
{
	SoundSource::SoundSource()
	{
		loop = false;

		m_sourceId = 0;

		alGenSources(1, &m_sourceId);
	}

	SoundSource::~SoundSource()
	{
		alDeleteSources(1, &m_sourceId);
	}

	void SoundSource::play()
	{
		alSourcePlay(m_sourceId);		
	}

	void SoundSource::setSound(std::shared_ptr<Sound> _sound)
	{
		m_sound = _sound;

		alSourcei(m_sourceId, AL_BUFFER, m_sound->m_bufferId);
	}

	void SoundSource::setLoop(bool _loop)
	{
		loop = _loop;
	}

	bool SoundSource::isPlaying()
	{
		ALenum state;

		alGetSourcei(m_sourceId, AL_SOURCE_STATE, &state);

		return state == AL_PLAYING;
	}

	void SoundSource::onTick(float deltaTs)
	{
		rend::vec3 myPos = getEntity()->getTransform()->getPosition();
		rend::vec3 cameraPos = getEntity()->getCore()->getCamera()->getTransform()->getPosition();
		
		alSource3f(m_sourceId, AL_POSITION, myPos.x, myPos.y, myPos.z);
		alListener3f(AL_POSITION, cameraPos.x, cameraPos.y, cameraPos.z);

		if (loop)
		{
			if (!isPlaying())
			{
				play();
			}
		}
	}
}