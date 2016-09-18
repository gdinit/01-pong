/* main_menu_state.h */

#ifndef MAIN_MENU_STATE_H
#define MAIN_MENU_STATE_H

#include <include/state.h>
#include <include/play_state.h>
#include <include/state_machine.h>
#include <include/config.h>
// needed for centerOrigin
#include <include/utility.h>

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
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

class MainMenuState : public State
{
	public:
		MainMenuState( StateMachine &machine,                sf::RenderWindow &window,                 bool replace = true );
		void	initializeState();
		void	processEvents();
		void	update();
		void	draw();
		void	pause();
		void	resume();

	private:
		sf::Texture	m_bgTex;
		sf::Sprite	m_bg;
		sf::Font	m_fontPressToContinue;
		sf::Text	m_textPressToContinue;
};

#endif	// MAIN_MENU_STATE_H

/* EOF */

