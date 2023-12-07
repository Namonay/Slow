#ifndef IMAGE_H
# define IMAGE_H

# include <map>
# include <SDL2/SDL.h>
# include <string>
# include <Renderer.hpp>

class ImageCollection
{
	public:
		ImageCollection(void) = default;
		~ImageCollection(void);
		SDL_Texture *add_img(const std::string &name, Renderer renderer);
		inline SDL_Texture *get_txtr(const std::string &name) noexcept {return txtr_map[name]; };
		void unload_img(const std::string &name);
	private:
		std::map<std::string, SDL_Texture *> txtr_map;
};

#endif