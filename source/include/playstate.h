/* playstate.h */

#ifndef PLAYSTATE_H
#define PLAYSTATE_H

#include <include/state.h>
#include <include/statemachine.h>
#include <include/mainmenustate.h>
#include <include/ingamemenustate.h>
#include <include/pausestate.h>
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

// TODO delete this debug line
#include <iostream>
// to in-line document
// TODO remove this debug only
#include <string>
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

		// on newRound(), we set the ball throw direction based on this
		bool		m_nextThrowTowardsRight;
};

#endif	// PLAYSTATE_H

/* EOF */

