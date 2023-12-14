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

int ImageCollection::img_get_height(const std::string &name)
{
	int height;

	SDL_QueryTexture(txtr_map[name], 0, 0, 0, &height);
	return (height);
}

int ImageCollection::img_get_width(const std::string &name)
{
	int width;

	SDL_QueryTexture(txtr_map[name], 0, 0, &width, 0);
	return (width);
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

ImageCollection::ImageCollection(void)
{
	IMG_Init(IMG_INIT_PNG);
}

void ImageCollection::LoadAssets(Renderer renderer)
{
	if (add_img("img/stars_special/bg_center.png", renderer, "background"))
		std::cout << "OK" << std::endl;
	if (add_img("img/ship/mup_smuggler_b_base.png", renderer, "ship"))
		std::cout << "OK" << std::endl;
	if (add_img("img/map/sector_box.png", renderer, "map"))
		std::cout << "OK" << std::endl;
	if (add_img("img/map/map_fuel_WAIT_select2.png", renderer, "beacon1"))
		std::cout << "OK" << std::endl;
	if (add_img("img/artillery_player/artillery_freemantis_glow.png", renderer, "laser"))
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