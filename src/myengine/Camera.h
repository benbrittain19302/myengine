#include "Component.h"

#include <rend/rend.h>

#include <memory>

namespace myengine
{
	struct Transform;

	struct Camera : Component
	{
		rend::mat4 getView();
		rend::mat4 getProj();

		void onInit();

	private:
	};
}