#include <Hobo/Console/HoboConsoleGraphics.h>

void HoboConsoleGraphics::Window::RenderScreen() {
	fwrite(Screen, Width * Height, 1, stdout);
}
Hobo::vec2 HoboConsoleGraphics::Window::NormalizedCoord(int x, int y) {
	return Hobo::vec2(
		2 * (x / (float)Width) - 1,
		2 * (y / (float)Height) - 1
	);
}
Hobo::vec2 HoboConsoleGraphics::Window::NormalizedCoordAspect(int x, int y) {
	return Hobo::vec2(
		(2 * (x / (float)Width) - 1) * Aspect,
		2 * (y / (float)Height) - 1
	);
}
Hobo::vec2 HoboConsoleGraphics::Window::NormalizedCoord(Hobo::vec2 pos) {
	return Hobo::vec2(
		2 * (pos.x / (float)Width) - 1,
		2 * (pos.y / (float)Height) - 1
	);
}
Hobo::vec2 HoboConsoleGraphics::Window::NormalizedCoordAspect(Hobo::vec2 pos) {
	return Hobo::vec2(
		(2 * (pos.x / (float)Width) - 1) * Aspect,
		2 * (pos.y / (float)Height) - 1
	);
}
HoboConsoleGraphics::Window::Window(int width, int height) {
	Width = width;
	Height = height;

	AspectWindow = (float)Width / Height;
	Aspect = AspectWindow * (11.0f / 24.0f);

	Screen = new char[Width * Height + 1];
	Screen[Width * Height] = '\n';
}
HoboConsoleGraphics::Window::~Window() {
	delete[] Screen;
}