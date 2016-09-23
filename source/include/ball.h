/* ball.h */

#ifndef BALL_H
#define BALL_H

#include <include/config.h>
#include <include/paddle.h>
#include <include/utility.h>
#include <include/vector2d.h>

#include <SFML/Graphics.hpp>

// TODO delete this debug only line
#include <iostream>
// required for RNG
#include <random>
// required for RNG
#include <chrono>

class Ball : public sf::Transformable, public sf::Drawable, private sf::NonCopyable
{
	public:
		Ball();

		virtual ~Ball();

		void	newRound( bool throwTowardsRightSide );
		void	update( sf::Time timeSinceLastUpdate );
		void	draw( sf::RenderTarget &target, sf::RenderStates states ) const;
		float	getX()       const noexcept;
		float	getY()       const noexcept;
		float	getTop()     const noexcept;
		float	getBottom()  const noexcept;
		float	getLeft()    const noexcept;
		float	getRight()   const noexcept;
		// void	collisionDetectRespond( Paddle &objPaddle, Ball &objBall ) noexcept;
		// need to be private to process in ball.cc
		sf::Vector2f		m_velocity;

	protected:

	private:

		sf::RectangleShape	m_shape;
		sf::Vector2f		m_position;
};

#endif	// BALL_H

/* EOF */

	