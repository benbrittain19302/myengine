#include "Input.h"

namespace myengine
{
	/**
	*  Input class captures and processs keyboard and mouse events
	*
	*/
	Input::Input()
	{
		Quit = showMouse = cmd_s = cmd_a = cmd_w = cmd_d = keyDown = cmd_mouseleft = cmd_mouseleftUp = cmd_mouseright = cmd_mouserightUp = 
			once = cmd_z = cmd_x = cmd_c = cmd_space = cmd_lshift = cmd_rshift = cmd_lctrl = cmd_rctrl = cmd_q = cmd_e = cmd_r = cmd_f = false;
	}

	std::vector<int> Input::keys;
	std::vector<int> Input::downKeys;
	std::vector<int> Input::upKeys;

	Input::~Input()
	{
	}

	glm::vec2 Input::getMouseDelta()
	{
		return mouseDelta;
	}

	void Input::update()
	{
		mouseDelta.x = 0;
		mouseDelta.y = 0;


		while (SDL_PollEvent(&eventQueue) != 0)
		{
			if (eventQueue.type == SDL_QUIT)
			{
				Quit = 1;
			}
			else if (eventQueue.type == SDL_MOUSEMOTION)
			{

				mouse_x = eventQueue.motion.x;
				mouse_y = eventQueue.motion.y;

				mouseDelta.x += mouse_x - 400;
				mouseDelta.y += mouse_y - 300;

			}
			else if (eventQueue.type == SDL_MOUSEBUTTONDOWN && eventQueue.button.button == SDL_BUTTON_RIGHT)
			{
				mouse_x = eventQueue.motion.x;
				mouse_y = eventQueue.motion.y;

			}
			else if (eventQueue.type == SDL_MOUSEBUTTONUP && eventQueue.button.button == SDL_BUTTON_RIGHT)
			{

				mouseDelta.x = -1;
				mouseDelta.y = -1;
			}
			else if (eventQueue.type == SDL_KEYDOWN)
			{
				if (eventQueue.key.keysym.sym == SDLK_UP || eventQueue.key.keysym.sym == SDLK_w)
				{
					//mouseDelta.y = 10;
					cmd_w = true;
				}
				else if (eventQueue.key.keysym.sym == SDLK_DOWN || eventQueue.key.keysym.sym == SDLK_s)
				{
					//mouseDelta.y = -10;
					cmd_s = true;
				}
				else if (eventQueue.key.keysym.sym == SDLK_RIGHT || eventQueue.key.keysym.sym == SDLK_d)
				{
					//mouseDelta.x = 10;
					cmd_d = true;
				}
				else if (eventQueue.key.keysym.sym == SDLK_LEFT || eventQueue.key.keysym.sym == SDLK_a)
				{
					//mouseDelta.x = -10;
					cmd_a = true;
				}
				else if (eventQueue.key.keysym.sym == SDLK_x)
				{
					cmd_x = true;
				}
				else if (eventQueue.key.keysym.sym == SDLK_ESCAPE)
				{
					showMouse = !showMouse;
				}
				else if (eventQueue.key.keysym.sym == SDLK_SPACE)
				{
					cmd_space = true;
				}
				else if (eventQueue.key.keysym.sym == SDLK_LSHIFT)
				{
					cmd_lshift = true;
				}
				else if (eventQueue.key.keysym.sym == SDLK_RSHIFT)
				{
					cmd_rshift = true;
				}
				else if (eventQueue.key.keysym.sym == SDLK_LCTRL)
				{
					cmd_lctrl = true;
				}
				else if (eventQueue.key.keysym.sym == SDLK_RCTRL)
				{
					cmd_rctrl = true;
				}
				else if (eventQueue.key.keysym.sym == SDLK_q)
				{
					cmd_q = true;
				}
				else if (eventQueue.key.keysym.sym == SDLK_e)
				{
					cmd_e = true;
				}
				else if (eventQueue.key.keysym.sym == SDLK_f)
				{
					cmd_f = true;
				}
				else if (eventQueue.key.keysym.sym == SDLK_r)
				{
					cmd_r = true;
				}


			}
			else if (eventQueue.type == SDL_KEYUP)
			{
				if (eventQueue.key.keysym.sym == SDLK_UP || eventQueue.key.keysym.sym == SDLK_w ||
					eventQueue.key.keysym.sym == SDLK_DOWN || eventQueue.key.keysym.sym == SDLK_s)
				{
					//mouseDelta.y = 0;
					cmd_w = false;
					cmd_s = false;

				}
				else if (eventQueue.key.keysym.sym == SDLK_RIGHT || eventQueue.key.keysym.sym == SDLK_d ||
					eventQueue.key.keysym.sym == SDLK_LEFT || eventQueue.key.keysym.sym == SDLK_a)
				{
					//mouseDelta.x = 0;
					cmd_a = false;
					cmd_d = false;
				}
				else if (eventQueue.key.keysym.sym == SDLK_SPACE)
				{
					cmd_space = false;
				}
				else if (eventQueue.key.keysym.sym == SDLK_LSHIFT)
				{
					cmd_lshift = false;
				}
				else if (eventQueue.key.keysym.sym == SDLK_RSHIFT)
				{
					cmd_rshift = false;
				}
				else if (eventQueue.key.keysym.sym == SDLK_LCTRL)
				{
					cmd_lctrl = false;
				}
				else if (eventQueue.key.keysym.sym == SDLK_RCTRL)
				{
					cmd_rctrl = false;
				}
				else if (eventQueue.key.keysym.sym == SDLK_q)
				{
					cmd_q = false;
				}
				else if (eventQueue.key.keysym.sym == SDLK_e)
				{
					cmd_e = false;
				}
				else if (eventQueue.key.keysym.sym == SDLK_f)
				{
					cmd_f = false;
				}
				else if (eventQueue.key.keysym.sym == SDLK_r)
				{
					cmd_r = false;
				}

			}

			/// move the mouse back to the middle of the screen each frame
			if (!showMouse) { SDL_WarpMouseInWindow(NULL, 400, 300); } 
			SDL_ShowCursor(showMouse);

		}

	}

	bool Input::getKey(int keyCode)
	{

		/*for (int i = 0; i < keys.size(); i++)
		{
			if (keys.at(i) == keyCode)
			{
				return true;
			}
		}*/

		return false;
	}

	bool Input::getKeyDown(int keyCode)
	{

		/*for (int i = 0; i < downKeys.size(); i++)
		{
			if (keys.at(i) == keyCode)
			{
				return true;
			}
		}*/

		return false;

	}

	bool Input::getKeyUp(int keyCode)
	{

		/*for (int i = 0; i < upKeys.size(); i++)
		{
			if (upKeys.at(i) == keyCode)
			{
				return true;
			}
		}*/

		return false;
	}

	void Input::keyboard(unsigned char key)
	{
		//_keyboard(key);
	}

	void Input::_keyboard(int key)
	{
		// Display key value to show response to keypress
		// Notice when a key is held there is a delay before it repeats
		// And how many times the up key can be polled before another key repeat is called

		//keys.push_back(key); // Add key to currently pressed keys
		//downKeys.push_back(key); // Register that this key was pressed this frame (will be cleared when display refreshes next frame)
								 // 122 120 99
		/*for (size_t i = 0; i < keys.size(); i++)
		{
			if (keys.at(i) == SDLK_ESCAPE)
			{
				Quit = true;
			}
			else if (keys.at(i) == SDLK_s)
			{
				cmd_s = true;
			}
			else if (keys.at(i) == SDLK_a)
			{
				cmd_a = true;
			}
			else if (keys.at(i) == SDLK_w)
			{
				cmd_w = true;
			}
			else if (keys.at(i) == SDLK_d)
			{
				cmd_d = true;
			}
			else if (keys.at(i) == SDLK_z)
			{
				cmd_z = true;
			}
			else if (keys.at(i) == SDLK_x)
			{
				cmd_x = true;
			}
			else if (keys.at(i) == SDLK_c)
			{
				cmd_c = true;
			}
			else
			{
				std::cout << key << std::endl;
			}
		}*/

	}

	void Input::keyboardUp(unsigned char key)
	{
		_keyboardUp(key);
	}

	void Input::_keyboardUp(int key)
	{
		upKeys.push_back(key); // Register that this key was released this frame

		//for (size_t i = 0; i < keys.size(); i++)
		//{
		//	if (keys.at(i) == key)
		//	{
		//		if (key == SDLK_s)
		//		{
		//			cmd_s = false;

		//			once = false;
		//		}
		//		else if (keys.at(i) == SDLK_a)
		//		{
		//			cmd_a = false;
		//		}
		//		else if (keys.at(i) == SDLK_w)
		//		{
		//			cmd_w = false;
		//		}
		//		else if (keys.at(i) == SDLK_d)
		//		{
		//			cmd_d = false;
		//		}
		//		else if (keys.at(i) == SDLK_z)
		//		{
		//			cmd_z = false;
		//		}
		//		else if (keys.at(i) == SDLK_x)
		//		{
		//			cmd_x = false;
		//		}
		//		else if (keys.at(i) == SDLK_c)
		//		{
		//			cmd_c = false;
		//		}
		//		keys.erase(keys.begin() + i); // Remove key from currently pressed keys
		//		i--;
		//	}
		//}
	}
}