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

		//void play();

		void setSound(std::shared_ptr<Sound> _sound);

	private:
		std::shared_ptr<Sound> m_sound;

		ALuint m_sourceId;

		void onTick();
	};
}