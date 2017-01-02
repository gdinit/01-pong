/* brick.cc */

#include <include/brick.h>

extern std::unique_ptr <Settings> SETTINGS;

Brick::Brick()
{
	// ctor

	m_textureWhite.loadFromFile( "assets/textures/white.png" );
	m_textureBlack.loadFromFile( "assets/textures/black.png" );

	for ( int n = 1; n < CONFIG_INITIAL_BRICK_PIECES; n++ ) {
		if ( n % 2 == 0 ) {
			m_bricks [ n ].setTexture( m_textureWhite );
		} else {
			m_bricks [ n ].setTexture( m_textureBlack );
		}
		m_bricks [ n ].setTextureRect( sf::IntRect( 0, 0, CONFIG_BRICK_WIDTH, CONFIG_BRICK_HEIGHT ) );
		m_bricks [ n ].setPosition( CONFIG_WIN_WIDTH / 2, n * CONFIG_BRICK_HEIGHT );
	}
}

Brick::~Brick() {}

void Brick::draw( sf::RenderTarget &target, sf::RenderStates states ) const {
	for ( int n = 1; n < CONFIG_INITIAL_BRICK_PIECES; n++ ) {
		target.draw( this->m_bricks [ n ] );
	}
}

/* EOF */

