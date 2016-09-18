/* application.h */

#ifndef APPLICATION_H
#define APPLICATION_H

#include <include/introstate.h>
#include <include/statemachine.h>
// configuration values defined here
#include <include/config.h>
// configuration values loaded into this struct to mke them globally toggle-able at runtime
#include <include/globals.h>

#include <SFML/Graphics/RenderWindow.hpp>

class Application
{
	public:
		Application();
		void	loadSettings();
		void	loadGlobals();
		void	run();

	private:
		StateMachine		m_machine;
		sf::RenderWindow	m_window;
};

#endif	// APPLICATION_H

/* EOF */

