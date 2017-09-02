/* paddle.h */

#ifndef  PADDLE_H
#define  PADDLE_H

#include "config.h"
#include "globals.h"
#include "ball.h"
#include "game_objects.h"

#include <SFML/Graphics.hpp>

// TODO switch to printf
// for texture open failure
#include <iostream>

class Paddle : public sf::Transformable, public sf::Drawable, private
	     sf::NonCopyable
{
	public:
		explicit Paddle( bool thisIsRightPaddle );

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

		bool		m_computerControlled = true;
		bool		m_thisIsRightPaddle;

		virtual void	draw( sf::RenderTarget &target, sf::RenderStates
		states ) const;

		sf::Sprite	m_sprite;
		sf::Vector2f	m_position;
		sf::Texture	m_texture;

	protected:

	private:
};

#endif	// PADDLE_H

/* EOF */

