/* scoreboard.h */

#ifndef  SCOREBOARD_H
#define  SCOREBOARD_H

#include <include/config.h>
#include <include/globals.h>
#include <include/ball.h>
#include <include/game_objects.h>
// needed for centerOrigin
#include <include/utility.h>

#include <SFML/Graphics.hpp>

class Scoreboard : public sf::Transformable, public sf::Drawable, private sf::NonCopyable
{
	public:
		Scoreboard();

		virtual ~Scoreboard();

		void		update( sf::Time timeSinceLastUpdate );
		virtual void	draw( sf::RenderTarget &target, sf::RenderStates states ) const;
		void		incrementLeft();
		void		incrementRight();
		void		centrePosition();

		bool		m_computerControlled;
		bool		m_thisIsRightScoreboard;
		bool		m_weaken;

	protected:

	private:
		sf::Font	m_scoreFont;
		sf::Text	m_scoreText;
		signed long int	m_scoreLeftSide = 0;
		signed long int	m_scoreRightSide = 0;
};

#endif	// SCOREBOARD_H

/* EOF */

