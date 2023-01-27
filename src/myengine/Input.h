#include <SDL2/SDL.h>
#include <rend/glm/glm.hpp>
#include <vector>

using namespace std;


/**
*  Input class captures and processs keyboard and mouse events
*/
namespace myengine
{
	struct Input
	{

	public:
		Input();
		~Input();


		void update();

		bool Quit;

		int mouse_x, mouse_y;

		bool cmd_mouseleft, cmd_mouseleftUp, cmd_mouseright, cmd_mouserightUp;
		bool cmd_s, cmd_a, cmd_d, cmd_w, cmd_z, cmd_x, cmd_c, cmd_space, cmd_lshift, cmd_rshift;
		bool once;

		glm::vec2 getMouseDelta();

	private:

		SDL_Event eventQueue;
		glm::vec2 mouseDelta;

		static bool getKey(int keyCode);
		static bool getKeyDown(int keyCode); // Was the key pressed this frame?
		static bool getKeyUp(int keyCode);

		static std::vector<int> keys;
		static std::vector<int> upKeys;
		static std::vector<int> downKeys;

		bool keyDown;

		bool showMouse;

		void keyboard(unsigned char key);
		void keyboardUp(unsigned char key);

		void _keyboard(int key);
		void _keyboardUp(int key);

	};
}