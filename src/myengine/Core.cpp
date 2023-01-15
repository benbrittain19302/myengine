#include "Core.h"
#include "Entity.h"
#include "Transform.h"

#include <rend/rend.h>

#include <stdexcept>

namespace myengine
{

	std::shared_ptr<Core> Core::initialize()
	{
		//Core core = new Core();
		std::shared_ptr<Core> rtn = std::make_shared<Core>();

		rtn->m_self = rtn;
		rtn->m_running = false;

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

		return rtn;
	}

	Core::~Core()
	{
		SDL_GL_DeleteContext(m_context);
		SDL_DestroyWindow(m_window);
		SDL_Quit();
	}

	void Core::start()
	{
		m_running = true;
		SDL_Event event = {0};

		while (m_running)
		{
			while (SDL_PollEvent(&event))
			{
				if (event.type == SDL_QUIT)
				{
					m_running = false;
				}
			}
			for (std::list<std::shared_ptr<Entity> >::iterator itr = m_entities.begin(); itr != m_entities.end(); itr++)
			{
				(*itr)->tick();
			}

			rend::Renderer r(INITIAL_WIDTH, INITIAL_HEIGHT);
			r.clear();

			for (std::list<std::shared_ptr<Entity> >::iterator itr = m_entities.begin(); itr != m_entities.end(); itr++)
			{
				(*itr)->display();
			}

			SDL_GL_SwapWindow(m_window);
		}
	}

	void Core::stop()
	{
		m_running = false;
	}

	std::shared_ptr<Entity> Core::addEntity()
	{
		std::shared_ptr<Entity> rtn = std::make_shared<Entity>();

		rtn->m_core = m_self;
		rtn->m_self = rtn;

		rtn->m_transform = rtn->addComponent<Transform>();

		m_entities.push_back(rtn);

		return rtn;
	}

}