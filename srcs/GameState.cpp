#include <GameState.hpp>

bool GameState::get_event(const std::string &event_name)
{
	if (event_map.find(event_name) == event_map.end())
		return (false);
	return (event_map[event_name]);
}