#include <Hobo/Hobo.h>

namespace HoboConsoleGraphics {
	class Window {
	public:
		char* Screen;
		int Width, Height;
		float AspectWindow, Aspect;

		void RenderScreen();
		Hobo::vec2 NormalizedCoord(int x, int y);
		Hobo::vec2 NormalizedCoord(Hobo::vec2 pos);
		Hobo::vec2 NormalizedCoordAspect(int x, int y);
		Hobo::vec2 NormalizedCoordAspect(Hobo::vec2 pos);

		Window(int width, int height);
		~Window();
	};
}