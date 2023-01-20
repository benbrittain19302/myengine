#include <SDL2/SDL.h>
#include <AL/al.h>
#include <AL/alc.h>

#include <memory>
#include <list>

#define INITIAL_WIDTH 640
#define INITIAL_HEIGHT 480

namespace myengine
{
	struct Entity;
	struct Resources;

	struct Core
	{
		static std::shared_ptr<Core> initialize();
		~Core();

		void start();

		void stop();

		std::shared_ptr<Entity> addEntity();

		std::shared_ptr<Entity> getCamera();

		std::shared_ptr<Resources> getResources();

	private:
		std::weak_ptr<Core> m_self;

		int m_dummy;

		bool m_running;

		std::list<std::shared_ptr<Entity> > m_entities;

		std::shared_ptr<Resources> m_resources;

		SDL_Window* m_window;

		SDL_GLContext m_context;

		ALCdevice* m_aDevice;

		ALCcontext* m_aContext;
	};

}