#ifndef WINDOW_H
# define WINDOW_H

# include <SDL2/SDL.h>

class Window
{
	public:
		void init(const char *title = "Slow");
		void destroy();
		Window() = default;
		~Window() = default;
		inline SDL_Window *getWindow(void) noexcept { return (window); }
	private:
		SDL_Window *window = nullptr;

};

#endif