#include <Window.hpp>

void Window::init(const char *title)
{
	window = SDL_CreateWindow(title, 0, 0, 1920, 1080, SDL_WINDOW_FULLSCREEN_DESKTOP);
	SDL_GetWindowSize(window, &width, &height);
}

void Window::destroy()
{
	SDL_DestroyWindow(window);
}
