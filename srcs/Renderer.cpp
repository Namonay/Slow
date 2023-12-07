#include <Renderer.hpp>
#include <iostream>

void Renderer::init(SDL_Window *window)
{
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}

void Renderer::destroy()
{
	SDL_DestroyRenderer(renderer);
}