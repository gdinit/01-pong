/* utility.cc */

#include <include/utility.h>

void centerOrigin( sf::Text &text )
{
	sf::FloatRect bounds = text.getLocalBounds();
	text.setOrigin( std::floor( bounds.left + bounds.width / 2.f ), std::floor( bounds.top + bounds.height / 2.f ) );
}

// find length (or Magnitude)
int magnitude( int x, int y )
{
	return( sqrt( x * x + y * y ) );
}

float magnitude( float x, float y )
{
	return( sqrt( x * x + y * y ) );
}

int magnitudeSquared( int x, int y )
{
	return( x * x + y * y );
}

float magnitudeSquared( float x, float y )
{
	return( x * x + y * y );
}

/* EOF */

