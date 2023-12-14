#ifndef IMAGE_H
# define IMAGE_H

# include <map>
# include <SDL2/SDL.h>
# include <string>
# include <Renderer.hpp>
# include <SDL2/SDL_image.h>
class ImageCollection
{
	public:
		ImageCollection(void);
		ImageCollection(Renderer renderer);
		~ImageCollection(void);
		SDL_Texture *add_img(const std::string &path, Renderer renderer, const std::string &name);
		SDL_Texture *add_img(const std::string &path, Renderer renderer);
		void LoadAssets(Renderer renderer);
		inline SDL_Texture *get_txtr(const std::string &name) noexcept {return txtr_map[name]; };
		void unload_img(const std::string &name);
	private:
		std::map<std::string, SDL_Texture *> txtr_map;
};

#endif