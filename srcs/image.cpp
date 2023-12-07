#include <ImageCollection.hpp>

SDL_Texture *ImageCollection::add_img(const std::string &name, Renderer renderer)
{
	SDL_Texture *txtr;
	SDL_Surface *srfc;

	srfc = SDL_LoadBMP(name.c_str());
	txtr = SDL_CreateTextureFromSurface(renderer.getRenderer(), srfc);
	SDL_FreeSurface(srfc);
	if (!txtr)
		return (NULL);
	txtr_map[name] = txtr;
	return (txtr);
}

ImageCollection::~ImageCollection(void)
{
	for (std::map<std::string, SDL_Texture *>::iterator it = txtr_map.begin(); it != txtr_map.end(); it++)
		SDL_DestroyTexture(it->second);
}