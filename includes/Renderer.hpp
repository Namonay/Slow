#ifndef RENDERER_H
# define RENDERER_H

# include <SDL2/SDL.h>

class Renderer
{
	public:
		Renderer(void) = default;
		~Renderer(void) = default;
		void init(SDL_Window *window);
		void destroy();
		inline SDL_Renderer *getRenderer(void) noexcept { return (renderer); }
	private:
		SDL_Renderer *renderer = nullptr;
};

#endif