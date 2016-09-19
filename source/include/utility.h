/* utility.h */

#ifndef UTILITY_H
#define UTILITY_H

// needed for centerOrigin
#include <cmath>
// needed for centerOrigin
#include <SFML/Graphics/Text.hpp>

void	centerOrigin( sf::Text &text );

int	magnitude( int x, int y );
float	magnitude( float x, float y );

int	magnitudeSquared( int x, int y );
float	magnitudeSquared( float x, float y );

#endif	// UTILITY_H

/* EOF */

