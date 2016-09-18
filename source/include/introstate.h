/* introstate.h */

#ifndef INTROSTATE_H
#define INTROSTATE_H

#include <include/state.h>
#include <include/statemachine.h>
#include <include/playstate.h>
#include <include/config.h>
// needed for centerOrigin
#include <include/utility.h>

#include <SFML/System/Time.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

// TODO delete this debug line
#include <iostream>
// for FPS text
#include <string>

class StateMachine;

namespace sf
{
	class RenderWindow;
}

class IntroState : public State
{
	public:
		IntroState( StateMachine &	machine,
		sf::RenderWindow &		window,
		bool				replace = true );
		void	initializeState();
		void	processEvents();
		void	update();
		void	draw();
		void	pause();
		void	resume();

	private:
		sf::Texture		m_bgTex;
		sf::Sprite		m_bg;
		sf::RectangleShape	m_fader;
		sf::Color		m_alpha;
		sf::Font		m_fontPressToContinue;
		sf::Text		m_textPressToContinue;
};

#endif	// INTROSTATE_H

/* EOF */

