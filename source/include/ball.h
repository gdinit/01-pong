/* ball.h */

#ifndef BALL_H
#define BALL_H

#include <include/config.h>

#include <SFML/Graphics.hpp>

// TODO delete this debug line
#include <iostream>

class Ball : public sf::Transformable, public sf::Drawable, private sf::NonCopyable
{
	public:
		/** Default constructor */
		Ball();

		/** Default destructor */
		virtual ~Ball();

		void	newRound( bool throwTowardsRightSide );
		void	update( sf::Time timeSinceLastUpdate );
		void	draw( sf::RenderTarget &target, sf::RenderStates states ) const;
		// void	moveLittle();
		float	getX()       const noexcept;
		float	getY()       const noexcept;
		float	getTop()     const noexcept;
		float	getBottom()  const noexcept;

	protected:

	private:

		// !< Member variable "m_shape"
		sf::RectangleShape	m_shape;

		// !< Member variable "m_cfg_acceleration_value_f"
		float			m_cfg_acceleration_val;
		// !< Member variable "m_acceleration"
		sf::Vector2f		m_acceleration;
		// !< Member variable "m_velocity"
		sf::Vector2f		m_velocity;
		// !< Member variable "m_position"
		sf::Vector2f		m_position;
		// !< Member variable "m_friction"
		// each update will slow down the ball this much
		sf::Vector2f		m_friction;
};

#endif	// BALL_H

/* EOF */

