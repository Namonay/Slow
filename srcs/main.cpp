#include <Window.hpp>
#include <Renderer.hpp>
#include <ImageCollection.hpp>
#include <iostream>
#include <map>
#include <GameState.hpp>
#include <cstdlib>
#include <vector>
#include <queue>
# define STB_IMAGE_IMPLEMENTATION
# define SDL_RENDERER_PRESENTVSYNC

std::map<int, bool> keys;

void update_keys(SDL_Event *event)
{
	bool key_pressed = 0;
	while (SDL_PollEvent(event))
	{
		switch (event->type) 
		{
        case SDL_QUIT:
            break;
		if (event->type == SDL_QUIT)
			break;
		case SDL_KEYDOWN:
			if (!key_pressed)
			{
            	keys[event->key.keysym.sym] = true;
				key_pressed = true;
			}
            break;
        case SDL_KEYUP:
            keys[event->key.keysym.sym] = false;
			key_pressed = false;
            break;
		}
	}
}


SDL_Rect *create_rect_from_img(int x, int y, SDL_Texture *txtr)
{
	SDL_Rect rect;

	rect.x = x;
	rect.y = y;
	SDL_QueryTexture(txtr, NULL, NULL, &rect.w, &rect.h);
	return (&rect);
}

void open_map(Window &window, ImageCollection &Images, Renderer renderer)
{
	int mapw;
	int maph;
	SDL_QueryTexture(Images.get_txtr("map"), NULL, NULL, &mapw, &maph);
	SDL_Rect rect = {(window.getWidth() - mapw) / 2, (window.getHeight() - maph) / 2, mapw, maph};
	SDL_RenderCopy(renderer.getRenderer(), Images.get_txtr("map"), nullptr, &rect);
	SDL_QueryTexture(Images.get_txtr("beacon1"), NULL, NULL, &mapw, &maph);
	SDL_RenderCopy(renderer.getRenderer(), Images.get_txtr("beacon1"), nullptr, create_rect_from_img((window.getWidth() - mapw) / 2, (window.getHeight() - maph) / 2, Images.get_txtr("beacon1")));
}

SDL_Rect *create_rect(int x, int y, int w, int h, SDL_Rect &rect)
{
	static int xa = 0;
	static int ya = 0;

	if (keys[SDLK_w])
		xa += 5;
	if (keys[SDLK_s])
		xa -= 5;
	if (keys[SDLK_a])
		ya += 5;
	if (keys[SDLK_d])
		ya -= 5;
	rect.x = x - ya;
	rect.y = y - xa;
	rect.w = w;
	rect.h = h;
	return (&rect);
}

void shoot_laser(SDL_Rect &position, std::deque<SDL_Rect> &projectiles)
{
	position.h /= 2;
	position.w /= 2;
	position.x += position.w / 2 + 15;
	position.y += position.h / 2;
	projectiles.push_back(position);
}

void update_projectiles(std::deque<SDL_Rect> &projectiles, Renderer &renderer, ImageCollection &Images, Window &window)
{
	while (projectiles.size() != 0 && projectiles.front().x > window.getWidth())
		projectiles.pop_front();
	for (SDL_Rect &rect : projectiles)
	{
		SDL_RenderCopy(renderer.getRenderer(), Images.get_txtr("laser"), nullptr, &rect);
		rect.x += 15;
	}
}

void process_input(GameState &game, Renderer &renderer, ImageCollection &Images, Window &window)
{
	static SDL_Event event;
	static SDL_Rect rect;
	static std::deque<SDL_Rect> projectiles;

	update_keys(&event);
	SDL_RenderCopy(renderer.getRenderer(), Images.get_txtr("icon"), nullptr, create_rect(100, 100, 100, 100, rect));
	if (keys[SDLK_SPACE])
	{
		shoot_laser(rect, projectiles);
		keys[SDLK_SPACE] = false;
	}
	if (keys[SDLK_ESCAPE] && game.get_event("map") == false)
		game.unset_event("game");
	if ((keys[SDLK_ESCAPE] || keys[SDLK_m]) && game.get_event("map"))
	{
		game.unset_event("map");
		keys[SDLK_ESCAPE] = false;
		keys[SDLK_m] = false;
	}
	else if (keys[SDLK_m])
	{
		game.set_event("map");
		keys[SDLK_m] = false;
	}
	if (game.get_event("map"))
		open_map(window, Images, renderer);
	update_projectiles(projectiles, renderer, Images, window);
	SDL_Delay(1000 / 60);
}

int main()
{
	Window window;
	Renderer renderer;
	ImageCollection Images;
	GameState gamestate;

	srand(time(NULL));
	window.init("Slow");
	gamestate.set_event("game");
	renderer.init(window.getWindow());
	SDL_RenderClear(renderer.getRenderer());
	SDL_RenderPresent(renderer.getRenderer());
	Images.LoadAssets(renderer);
	while (gamestate.get_event("game"))
	{
		SDL_RenderClear(renderer.getRenderer());
		SDL_RenderCopy(renderer.getRenderer(), Images.get_txtr("background"), nullptr, nullptr);
		process_input(gamestate, renderer, Images, window);
		SDL_RenderPresent(renderer.getRenderer());
	}
	renderer.destroy();
	window.destroy();
	return 0;
}