/* state.h */

#ifndef STATE_H
#define STATE_H

// make configuration values to all derived classes
#include <include/config.h>
// forward declare Settings struct
#include <include/globals.h>

#include <SFML/System/Time.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

// TODO is this debug only? remove
#include <iostream>
// needed for unique_ptr
#include <memory>
// container to store observedFPS last N values
#include <deque>
// needed for round()
#include <cmath>

extern Settings	SETTINGS;
// extern Globals	GLOBALS;
// extern std::unique_ptr <Globals>	GLOBALS;

class StateMachine;

namespace sf
{
	class RenderWindow;
}

class State
{
	public:
		State( StateMachine &	machine,
		sf::RenderWindow &	window,
		bool			replace = true );
		virtual ~State() = default;
		State( const State & ) = delete;
		State & operator	=( const State & ) = delete;
		std::unique_ptr <State> next();
		virtual void		update() = 0;
		virtual void		draw() = 0;
		virtual void		pause() = 0;
		virtual void		resume() = 0;
		bool			isReplacing();
		// TODO why virtual?
		virtual void		toggleDebugShowOverlay();
		// TODO why virtual?
		virtual void		toggleDebugConsoleOutput();
		// TODO why virtual?
		virtual void		toggleDebugDynFPSConsoleOutput();
		virtual void		updateDebugOverlayTextIfEnabled( bool b );
		virtual void		updateDebugOverlayTextIfEnabled();
		virtual void		printConsoleDebugIfEnabled();
		virtual void		recordObservedFPS();
		virtual void		dynamicallyAdjustFPSLimit();
		unsigned short int	calcMedianFPS( std::deque <unsigned short int> records );
		void			restartStateClock();
		int			getStateAgeAsSeconds();

	protected:
		std::unique_ptr <State>		m_next;
		StateMachine &			m_machine;
		sf::RenderWindow &		m_window;
		bool				m_replacing;
		// TODO rename this
		static const sf::Time		TimePerFrame;
		int				m_statisticsNumFrames;
		sf::Time			m_timeSinceLastUpdate;
		sf::Time			m_elapsedTime;
		sf::Clock			m_clock;

		// hmm
		sf::Clock			m_stateBirthdate;
		sf::Time			m_stateAge;

		sf::Font			m_font;
		sf::Text			m_statisticsText;
		sf::Time			m_statisticsUpdateTime;
		unsigned short int		m_urgentUpdateNeeded;
		sf::View			m_worldView;

		std::deque <unsigned short int>	m_observedFPSLastN;
		short int			m_FPSAdjPosDelta = 0;
		short int			m_FPSAdjNegDelta = 0;
		unsigned short int		m_activeFPSLimit = CONFIG_DESIRED_FPS_INT;
		bool				m_justResumed;
};

#endif	// STATE_H

/* EOF */

