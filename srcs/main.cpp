#include <Window.hpp>
#include <Renderer.hpp>
#include <ImageCollection.hpp>
#include <iostream>
#include <GameState.hpp>
#include <PlayerShip.hpp>
# define STB_IMAGE_IMPLEMENTATION
# define SDL_RENDERER_PRESENTVSYNC

std::map<int, bool> keys;

void update_keys(SDL_Event *event)
{
	while (SDL_PollEvent(event))
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

void handle_player_movement(PlayerShip &player1, PlayerShip &player2, Window &window)
{
	if (keys[SDLK_w])
		player1.move(0, -5);
	if (keys[SDLK_s])
		player1.move(0, 5);
	if (keys[SDLK_a])
		player1.move(-5, 0);
	if (keys[SDLK_d])
		player1.move(5, 0);
	if (keys[SDLK_KP_8])
		player2.move(0, -5);
	if (keys[SDLK_KP_5])
		player2.move(0, 5);
	if (keys[SDLK_KP_4])
		player2.move(-5, 0);
	if (keys[SDLK_KP_6])
		player2.move(5, 0);
}

void handle_shooting(PlayerShip &player1, PlayerShip &player2, Window &window, Renderer &renderer, ImageCollection &images)
{
	if (keys[SDLK_SPACE])
	{
		player1.projectiles.push_back(player1.get_rect());
		keys[SDLK_SPACE] = false;
	}
	if (keys[SDLK_KP_0])
	{
		player2.projectiles.push_back(player2.get_rect());
		keys[SDLK_KP_0] = false;
	}
	if (player1.projectiles.size() != 0 && player1.projectiles.front().x > window.getWidth())
		player1.projectiles.pop_front();
	if (player2.projectiles.size() != 0 && player2.projectiles.front().x < -100)
		player2.projectiles.pop_front();
	for (SDL_Rect &rect : player1.projectiles)
	{
		rect.x += 10;
		SDL_RenderCopy(renderer.getRenderer(), images.get_txtr("laser"), nullptr, &rect);
	}
	for (SDL_Rect &rect : player2.projectiles)
	{
		rect.x -= 10;
		SDL_RenderCopy(renderer.getRenderer(), images.get_txtr("laser"), nullptr, &rect);
	}

}

void process_input(GameState &gamestate, Renderer &renderer, ImageCollection &images, Window &window)
{
	static PlayerShip player1("first", images.get_txtr("ship"), window, 0, window.getHeight() / 2);
	static PlayerShip player2("second", images.get_txtr("ship"), window, window.getWidth() - images.img_get_width("ship") / 2, window.getHeight() / 2);
	static SDL_Event event;
	static SDL_Point point = {images.img_get_width("ship") / 4, images.img_get_height("ship") / 4};
	update_keys(&event);
	if (keys[SDLK_ESCAPE])
		gamestate.unset_event("game");
	handle_player_movement(player1, player2, window);
	SDL_RenderCopy(renderer.getRenderer(), images.get_txtr("ship"), nullptr, &player1.get_rect());
	SDL_RenderCopyEx(renderer.getRenderer(), images.get_txtr("ship"), nullptr, &player2.get_rect(), 180.0f, &point, SDL_FLIP_NONE);
	handle_shooting(player1, player2, window, renderer, images);
	SDL_Delay(1000 / 60);
}

int main()
{
	Window window;
	Renderer renderer;
	renderer.init(window.getWindow());
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