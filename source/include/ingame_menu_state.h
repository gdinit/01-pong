/* ingame_menu_state.h */

#ifndef INGAME_MENU_STATE_H
#define INGAME_MENU_STATE_H

#include <include/state.h>
#include <include/state_machine.h>
#include <include/config.h>

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <include/config.h>

#include <SFML/System/Time.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

// TODO delete this debug line
#include <iostream>
// for FPS text
#include <string>

class StateMachine;

namespace sf
{
	class RenderWindow;
}

class InGameMenuState : public State
{
	public:
		InGameMenuState( StateMachine &machine, sf::RenderWindow &window, bool replace = true );
		void	initializeState();
		void	processEvents();
		void	update();
		void	draw();
		void	pause();
		void	resume();

	private:
		sf::Texture	m_bgTex;
		sf::Sprite	m_bg;
};

#endif	// INGAME_MENU_STATE_H

/* EOF */

