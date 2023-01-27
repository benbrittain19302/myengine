#include <SDL2/SDL.h>
#include <AL/al.h>
#include <AL/alc.h>

#include <memory>
#include <vector>
#include <list>

#define INITIAL_WIDTH 640
#define INITIAL_HEIGHT 480

namespace myengine
{
	struct Entity; ///< Forward declare for Entity
	struct Resources; ///< Forward declare for Resources
	struct Camera;
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

		std::shared_ptr<Input> getInput(); ///< Get reference to input

		/**
		* Find all Components of type T
		*/
		template <typename T>
		void find(std::vector<std::shared_ptr<T> >& _out)
		{
			///< Go through each Entity in Core.
			for (std::list<std::shared_ptr<Entity> >::iterator itr = m_entities.begin(); itr != m_entities.end(); itr++)
			{
				std::shared_ptr<Entity> e = (*itr);
				///< Go through each Component in Entity.
				for (std::vector<std::shared_ptr<Component> >::iterator iter = e->m_components.begin(); iter != e->m_components.end(); iter++)
				{
					std::shared_ptr<Component> c = (*iter);
					///< Try to dynamic cast the Component to a T.
					std::shared_ptr<T> t = std::dynamic_pointer_cast<T>(c);
					///< If succeeds then add it to the output array.
					if (t)
					{
						_out.push_back(t);
					}
				}
			}
		}

	private:
		friend struct Camera;

		std::list<std::shared_ptr<Entity> > m_entities; ///< List of Entities

		std::shared_ptr<Input> m_input; ///< Reference to Input

		std::weak_ptr<Core> m_self; ///< Reference to self

		std::shared_ptr<Entity> m_camera; ///< Reference to Camera Entity

		int m_dummy;

		bool m_running; ///< Is Game running bool

		unsigned int lastTime; ///< The last frames time
		unsigned int currentTime; ///< The current frames time
		float deltaTime; ///< The delta between the last frame and current frame times

		std::shared_ptr<Resources> m_resources; ///< Reference to resources list

		SDL_Window* m_window; ///< Reference to SDL Window

		SDL_GLContext m_context; ///< OpenGL Context

		ALCdevice* m_aDevice; ///< OpenAL Device reference

		ALCcontext* m_aContext; ///< OpenAL Context
	};

}