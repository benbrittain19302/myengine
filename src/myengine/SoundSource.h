#include "Component.h"

#include <AL/al.h>
#include <memory>

namespace myengine
{
	struct Sound;

	struct SoundSource : Component
	{
		SoundSource();
		~SoundSource();

		void play();

		void setSound(std::shared_ptr<Sound> _sound);

		void setLoop(bool _loop);

		bool isPlaying();

	private:
		bool loop;

		std::shared_ptr<Sound> m_sound;

		ALuint m_sourceId;

		void onTick(float deltaTs);
	};
}