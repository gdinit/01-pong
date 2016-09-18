/* paddle.h */

#ifndef  PADDLE_H
#define  PADDLE_H

#include <include/config.h>
#include <include/globals.h>
#include <include/ball.h>
#include <include/game_objects.h>

#include <SFML/Graphics.hpp>

// TODO delete this debug line
#include <iostream>

class Paddle : public sf::Transformable, public sf::Drawable, private sf::NonCopyable
{
	public:
		/** Default constructor */
		// Paddle();
		Paddle( bool thisIsRightPaddle );

		/** Default destructor */
		virtual ~Paddle();

		/** Update object
		 * \param dt Delta time
		 */
		void	update( sf::Time timeSinceLastUpdate );
		void	processHumanMovement();
		void	newRound();
		float	getX()       const noexcept;
		float	getY()       const noexcept;
		float	getTop()     const noexcept;
		float	getBottom()  const noexcept;
		void	moveUp();
		void	moveDown();

		// !< Member variable "m_computerControlled"
		bool	m_computerControlled;

		// !< Member variable "m_thisIsRightPaddle"
		bool	m_thisIsRightPaddle;

		// !< Member variable "m_weaken"
		bool	m_weaken;

		virtual void draw( sf::RenderTarget &target, sf::RenderStates states ) const;

	protected:

	private:

		// !< Member variable "m_shape"
		sf::RectangleShape	m_shape;

		// !< Member variable "m_acceleration"
		sf::Vector2f		m_acceleration;

		// !< Member variable "m_position"
		sf::Vector2f		m_position;

		// !< Member variable "m_friction"
		sf::Vector2f		m_friction;
};

#endif

/* EOF */

