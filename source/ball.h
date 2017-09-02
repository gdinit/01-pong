/* ball.h */

#ifndef BALL_H
#define BALL_H

#include "config.h"
#include "utility.h"
#include "vector2d.h"
#include "paddle.h"

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

// required for RNG
#include <random>
// required for RNG
#include <chrono>

class Ball : public sf::Transformable, public sf::Drawable, private
	   sf::NonCopyable
{
	public:
		Ball();

		virtual ~Ball();

		void	newRound( bool throwTowardsRightSide );
		void	collisionDetectRespond( void ) noexcept;
		void	update( sf::Time timeSinceLastUpdate );
		void	draw( sf::RenderTarget &target, sf::RenderStates
		states ) const;
		float	getX()       const noexcept;
		float	getY()       const noexcept;
		float	getTop()     const noexcept;
		float	getBottom()  const noexcept;
		float	getLeft()    const noexcept;
		float	getRight()   const noexcept;
		sf::Vector2f	m_velocity;

	protected:

	private:
		sf::Sprite	m_sprite;
		sf::Vector2f	m_position;
		sf::Texture	m_texture;
		sf::SoundBuffer m_sbColPaddle;
		sf::SoundBuffer m_sbColWall;
		sf::SoundBuffer m_sbColGoal;
		sf::Sound	m_sColPaddle;
		sf::Sound	m_sColWall;
		sf::Sound	m_sColGoal;
};

#endif	// BALL_H

/* EOF */

