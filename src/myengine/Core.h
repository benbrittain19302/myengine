#include <SDL2/SDL.h>
#include <AL/al.h>
#include <AL/alc.h>

#include <memory>
#include <list>

#define INITIAL_WIDTH 640
#define INITIAL_HEIGHT 480

namespace myengine
{
	struct Entity; ///< Forward declare for Entity
	struct Resources; ///< Forward declare for Resources
	class Input; ///< Forward declare for Input

	/**
	* Definition for Core struct of game engine
	*/
	struct Core
	{
		static std::shared_ptr<Core> initialize(); ///< Core Intializer
		~Core(); ///< Core Destructor

		void start(); ///< Start Game engineand run main Game loop			

		void stop(); ///< Stop/Kill Game engine

		std::shared_ptr<Entity> addEntity(); ///< Add an Entity to Entity list

		std::shared_ptr<Entity> getCamera(); ///< Get reference to Camera Entity from the Entity list

		std::shared_ptr<Resources> getResources(); ///< Get reference to list of resources

	private:
		std::shared_ptr<Input> m_input;

		std::weak_ptr<Core> m_self; ///< Reference to self

		std::shared_ptr<Entity> m_camera; ///< Reference to Camera Entity

		int m_dummy;

		bool m_running; ///< Is Game running bool

		unsigned int lastTime; ///< The last frames time
		unsigned int currentTime; ///< The current frames time
		float deltaTime; ///< The delta between the last frame and current frame times

		std::list<std::shared_ptr<Entity> > m_entities; ///< List of Entities

		std::shared_ptr<Resources> m_resources; ///< Reference to resources list

		SDL_Window* m_window; ///< Reference to SDL Window

		SDL_GLContext m_context; ///< OpenGL Context

		ALCdevice* m_aDevice; ///< OpenAL Device reference

		ALCcontext* m_aContext; ///< OpenAL Context
	};

}