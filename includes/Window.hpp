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
		inline int getWidth(void) const noexcept { return (width); }
		inline int getHeight(void) const noexcept { return (height); }
	private:
		SDL_Window *window = nullptr;
		int width;
		int height;
};

#endif