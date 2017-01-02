/* brick.h */

#ifndef  BRICK_H
#define  BRICK_H

#include <include/config.h>
#include <include/globals.h>
// #include <include/ball.h>
// #include <include/game_objects.h>

#include <SFML/Graphics.hpp>

class Brick : public sf::Transformable, public sf::Drawable, private sf::NonCopyable
{
	public:
		Brick();

		virtual ~Brick();

		virtual void draw( sf::RenderTarget &target, sf::RenderStates states ) const;

		sf::Sprite	m_bricks [ CONFIG_INITIAL_BRICK_PIECES ];
		sf::Vector2f	m_position;
		sf::Texture	m_textureWhite;
		sf::Texture	m_textureBlack;

	protected:

	private:
};

#endif	// BRICK_H

/* EOF */

