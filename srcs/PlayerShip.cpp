#include <PlayerShip.hpp>

PlayerShip::PlayerShip(const std::string &name, SDL_Texture *ship, Window &window, int x, int y) : _name(name), _window(window)
{
	_hp = 3;
	_ship = ship;
	SDL_QueryTexture(ship, 0, 0, &ship_rect.w, &ship_rect.h);
	ship_rect.w /= 2;
	ship_rect.h /= 2;
	ship_rect.x = x; 
	ship_rect.y = y;
}

void PlayerShip::set_pos(int x, int y)
{
	ship_rect.x = x;
	ship_rect.y = y;
}

void PlayerShip::move(int x, int y)
{
	if (ship_rect.x + x + ship_rect.w > _window.getWidth() || ship_rect.x + x + ship_rect.w < ship_rect.w)
		return ;
	ship_rect.x += x; 
	if (ship_rect.y + y + ship_rect.h > _window.getHeight() || ship_rect.y + y + ship_rect.h < ship_rect.h)
		return ;
	ship_rect.y += y;
}