#include <ImageCollection.hpp>
#include <iostream>

SDL_Texture *ImageCollection::add_img(const std::string &path, Renderer renderer)
{
	SDL_Surface *srfc = IMG_Load(path.c_str());
	SDL_Texture *txtr = SDL_CreateTextureFromSurface(renderer.getRenderer(), srfc);

	SDL_FreeSurface(srfc);
	if (!txtr)
		return (NULL);
	txtr_map[path] = txtr;
	return (txtr);
}

SDL_Texture *ImageCollection::add_img(const std::string &path, Renderer renderer, const std::string &name)
{
	SDL_Surface *srfc = IMG_Load(path.c_str());
	SDL_Texture *txtr = SDL_CreateTextureFromSurface(renderer.getRenderer(), srfc);

	SDL_FreeSurface(srfc);
	if (!txtr)
		return (NULL);
	if (txtr_map.find(name) != txtr_map.end())
		return (NULL);
	txtr_map[name] = txtr;
	return (txtr);
}

ImageCollection::ImageCollection(Renderer renderer)
{
	IMG_Init(IMG_INIT_PNG);

	if (add_img("img/stars_special/bg_center.png", renderer, "background"))
		std::cout << "OK" << std::endl;
	if (add_img("img/ui_icons/icon_fuel.png", renderer, "icon"))
		std::cout << "OK" << std::endl;
	if (add_img("img/map/sector_box.png", renderer, "map"))
		std::cout << "OK" << std::endl;
}
void ImageCollection::unload_img(const std::string &name)
{
	if (txtr_map.find("name") == txtr_map.end())
		throw std::exception();
	SDL_DestroyTexture(txtr_map[name]);
}

ImageCollection::~ImageCollection(void)
{
	for (std::map<std::string, SDL_Texture *>::iterator it = txtr_map.begin(); it != txtr_map.end(); it++)
		SDL_DestroyTexture(it->second);
	IMG_Quit();
}