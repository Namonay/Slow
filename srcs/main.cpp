#include <Window.hpp>
#include <Renderer.hpp>
#include <ImageCollection.hpp>
#include <iostream>
#include <map>
# define STB_IMAGE_IMPLEMENTATION
# define SDL_RENDERER_PRESENTVSYNC

std::map<int, bool> keys;

void update_keys(SDL_Event *event)
{
	while(SDL_PollEvent(event))
	{
		switch (event->type) 
		{
        case SDL_QUIT:
            break;
		if (event->type == SDL_QUIT)
			break;
		case SDL_KEYDOWN:
            keys[event->key.keysym.sym] = true;
            break;
        case SDL_KEYUP:
            keys[event->key.keysym.sym] = false;
            break;
		}
	}
}

void process_input(bool *game)
{
	static SDL_Event event;

	update_keys(&event);
	if (keys[SDLK_ESCAPE])
		*game = false;
}

SDL_Rect *create_rect(int x, int y, int w, int h, SDL_Rect *rect)
{
	static int xa = 0;
	static int ya = 0;

	if (keys[SDLK_w])
		xa++;
	if (keys[SDLK_s])
		xa--;
	if (keys[SDLK_a])
		ya++;
	if (keys[SDLK_d])
		ya--;
	rect->x = x - ya;
	rect->y = y - xa;
	rect->w = w;
	rect->h = h;
	return (rect);
}
int main()
{
	Window window;
	Renderer renderer;
	ImageCollection Images;
	bool game = true;
	SDL_Rect rect;
	window.init("Slow");
	renderer.init(window.getWindow());
	SDL_RenderClear(renderer.getRenderer());
	SDL_RenderPresent(renderer.getRenderer());
	if (Images.add_img("img/stars_special/bg_center.bmp", renderer))
		std::cout << "OK" << std::endl;
	if (Images.add_img("img/ui_icons/icon_fuel.bmp", renderer))
		std::cout << "OK" << std::endl;
	while (game)
	{
		SDL_RenderClear(renderer.getRenderer());
		SDL_RenderCopy(renderer.getRenderer(), Images.get_txtr("img/stars_special/bg_center.bmp"), nullptr, nullptr);
		process_input(&game);
		SDL_RenderCopy(renderer.getRenderer(), Images.get_txtr("img/ui_icons/icon_fuel.bmp"), nullptr, create_rect(100, 100, 100, 100, &rect));
		SDL_RenderPresent(renderer.getRenderer());
	}
	renderer.destroy();
	window.destroy();
	return 0;
}