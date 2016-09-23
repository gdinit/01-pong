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
		Paddle( bool thisIsRightPaddle );

		virtual ~Paddle();

		void		update( sf::Time timeSinceLastUpdate );
		void		processHumanMovement();
		void		newRound();
		float		getX()       const noexcept;
		float		getY()       const noexcept;
		float		getTop()     const noexcept;
		float		getBottom()  const noexcept;
		float		getLeft()    const noexcept;
		float		getRight()   const noexcept;
		void		moveUp();
		void		moveDown();

		bool			m_computerControlled;
		bool			m_thisIsRightPaddle;
		bool			m_weaken;

		virtual void	draw( sf::RenderTarget &target, sf::RenderStates states ) const;

	protected:

	private:
		sf::RectangleShape	m_shape;
		sf::Vector2f		m_position;
};

#endif	// PADDLE_H

/* EOF */

