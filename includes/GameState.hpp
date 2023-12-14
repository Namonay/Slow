#ifndef GAMESTATE_H
# define GAMESTATE_H

# include <map>
# include <string>
class GameState
{
	public:
		GameState(void) = default;
		~GameState(void) = default;
		void set_event(const std::string &event_name) { event_map[event_name] = true; };
		bool get_event(const std::string &event_name);
		void unset_event(const std::string &event_name) { event_map[event_name] = false; };
		void toggle_event(const std::string &event_name) { event_map[event_name] = !event_map[event_name]; };
	private:
		std::map<std::string, bool> event_map;
};

#endif