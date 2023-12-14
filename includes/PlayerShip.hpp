#ifndef PLAYERSHIP_H
# define PLAYERSHIP_H
# include <string>
# include <Window.hpp>
# include <SDL2/SDL.h>
# include <SDL2/SDL_image.h>
# include <deque>
class PlayerShip
{
	public:
		PlayerShip(const std::string &name, SDL_Texture *ship, Window &window, int x, int y);
		inline SDL_Rect &get_rect(void) noexcept {return (ship_rect); };
		void set_pos(int x, int y);
		unsigned int get_hp(void) const noexcept {return (_hp); };
		void take_damage(unsigned int amount) {(_hp > amount) ? _hp = 0 : _hp -= amount; };
		void move(int x, int y);
		std::deque<SDL_Rect> projectiles;
	private:
		unsigned int _hp;
		const std::string _name;
		SDL_Rect ship_rect;
		SDL_Texture *_ship;
		Window &_window;
};
# endif