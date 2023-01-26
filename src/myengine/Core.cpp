#include "Core.h"
#include "Entity.h"
#include "Transform.h"
#include "Camera.h"
#include "Resources.h"
#include "Input.h"

#include <rend/rend.h>

#include <stdexcept>

namespace myengine
{
	/**
	* Initialization of Game engine Core
	*/
	std::shared_ptr<Core> Core::initialize()
	{
		///< Equivalent of "Core core = new Core();" to create Core 
		std::shared_ptr<Core> rtn = std::make_shared<Core>();

		/**
		* Set reference to self and intialise engine state member variable
		*/
		rtn->m_self = rtn;
		rtn->m_running = false;

		/**
		* Intialisation of SDL, OpenGL and OpenAL for Game engine
		*/
		if (SDL_Init(SDL_INIT_VIDEO) < 0)
		{
			throw std::runtime_error("failed to init sdl");
		}

		if (!(rtn->m_window = SDL_CreateWindow("MP Engine", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
			INITIAL_WIDTH, INITIAL_HEIGHT, SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL) ) )
		{
			SDL_Quit();
			throw std::runtime_error("Failed to create Window");
		}

		if (!(rtn->m_context = SDL_GL_CreateContext(rtn->m_window)))
		{
			SDL_DestroyWindow(rtn->m_window);
			SDL_Quit();
			throw std::runtime_error("Failed to create OpenGL context");
		}

		rtn->m_aDevice = alcOpenDevice(NULL);

		if (!rtn->m_aDevice)
		{
			throw std::runtime_error("Failed to open audio device");
		}

		rtn->m_aContext = alcCreateContext(rtn->m_aDevice, NULL);

		if (!rtn->m_aContext)
		{
			alcCloseDevice(rtn->m_aDevice);
			throw std::runtime_error("Failed to create audio context");
		}

		if (!alcMakeContextCurrent(rtn->m_aContext))
		{
			alcDestroyContext(rtn->m_aContext);
			alcCloseDevice(rtn->m_aDevice);
			throw std::runtime_error("Failed to make context current");
		}

		alListener3f(AL_POSITION, 0.0f, 0.0f, 0.0f); ///< Default audio listener position at Origin, gets updated frame by frame to Camera Entity's position

		rtn->m_input = std::make_shared<Input>(); ///< Initialize input management

		rtn->m_resources = std::make_shared<Resources>(); ///< Initialize list of resources

		return rtn; ///< Return Core
	}

	/**
	* Core destructor, Memory cleanup
	*/
	Core::~Core()
	{
		alcMakeContextCurrent(NULL);
		alcDestroyContext(m_aContext);
		alcCloseDevice(m_aDevice);
		SDL_GL_DeleteContext(m_context);
		SDL_DestroyWindow(m_window);
		SDL_Quit();
	}

	/**
	* Start Game engine and run main Game loop
	*/
	void Core::start()
	{
		m_running = true; ///< Game is running

		while (m_running) ///< Whilst Game is running
		{
			m_input->update();
			if (m_input->Quit)
			{
				m_running = false;
			}

			/**
			* For each Entity, update Entity
			*/
			for (std::list<std::shared_ptr<Entity> >::iterator itr = m_entities.begin(); itr != m_entities.end(); itr++)
			{
				(*itr)->tick();
			}

			/**
			* Define Renderer for screen and clear the screen
			*/
			rend::Renderer r(INITIAL_WIDTH, INITIAL_HEIGHT);
			r.clear();

			/**
			* For each Entity, display Entity
			*/
			for (std::list<std::shared_ptr<Entity> >::iterator itr = m_entities.begin(); itr != m_entities.end(); itr++)
			{
				(*itr)->display();
			}

			SDL_GL_SwapWindow(m_window); ///< Set Correct window display
		}
	}

	/**
	* Stop/Kill Game engine
	*/
	void Core::stop()
	{
		m_running = false;
	}

	/**
	* Add an Entity to Entity list
	*/
	std::shared_ptr<Entity> Core::addEntity()
	{
		std::shared_ptr<Entity> rtn = std::make_shared<Entity>(); ///< Create new Entity instance

		rtn->m_core = m_self; ///< Set reference to core
		rtn->m_self = rtn; ///< Set reference to self Entity

		rtn->m_transform = rtn->addComponent<Transform>(); ///< Add Transform component to Entity

		m_entities.push_back(rtn); ///< Add Entity to entity list

		return rtn; ///< Return Entity reference
	}

	/**
	* Get reference to Camera Entity from the Entity list
	*/
	std::shared_ptr<Entity> Core::getCamera()
	{
		//std::shared_ptr<Entity> rtn = m_entities.; ///< Create new instance of an entity
		
		/**
		* Go through each Entity
		*/
		//for (std::list<std::shared_ptr<Entity> >::iterator itr = m_entities.begin(); itr != m_entities.end(); itr++)
		//{

			/** 
			* Go through each component in entity
			*/
			//for (std::vector<std::shared_ptr<Component> >::iterator iter = (*itr)->m_components.begin(); iter != (*itr)->m_components.end(); iter++)
			//{
				//std::shared_ptr<Component> c = (*iter); ///< Create Component equal to type iter

				//std::shared_ptr<Camera> t = std::dynamic_pointer_cast<Camera>(c); ///< Attempt to dynamic cast iter Component to type Camera

				/**
				* If dynamic cast is successful, make rtn Entity equal to itr and return
				*/
				//if (t)
				//{
					//rtn = (*itr);
					//return rtn;
				//}
			//}
		//}
		return m_camera;
	}

	std::shared_ptr<Resources> Core::getResources()
	{
		return m_resources;
	}

	std::shared_ptr<Input> Core::getInput()
	{
		return m_input;
	}
}