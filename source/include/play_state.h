/* play_state.h */

#ifndef PLAY_STATE_H
#define PLAY_STATE_H

#include <include/state.h>
#include <include/state_machine.h>
#include <include/main_menu_state.h>
#include <include/ingame_menu_state.h>
#include <include/pause_state.h>
#include <include/config.h>
// needed for centerOrigin
#include <include/utility.h>
#include <include/paddle.h>
#include <include/make_unique.h>
#include <include/game_objects.h>

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

// to in-line document
// needed for std::unique_ptr
#include <memory>

class StateMachine;

namespace sf
{
	class RenderWindow;
}

class PlayState : public State
{
	public:
		PlayState( StateMachine &	machine,
		sf::RenderWindow &		window,
		bool				replace = true );
		void	initializeState();
		void	processEvents();
		void	update();
		void	draw();
		void	pause();
		void	resume();

	private:
		sf::Texture	m_bgTex;
		sf::Sprite	m_bg;

		bool		m_nextThrowTowardsRight;
};

#endif	// PLAY_STATE_H

/* EOF */

