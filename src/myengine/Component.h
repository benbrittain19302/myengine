#ifndef MYENGINE_COMPONENT_H
#define MYENGINE_COMPONENT_H


namespace myengine
{
	struct Entity;

	struct Component
	{
	private:
		friend struct Entity;

		virtual void onTick();
		virtual void onDisplay();

		void tick();
		void display();
	};
}

#endif // !MYENGINE_COMPONENT_H