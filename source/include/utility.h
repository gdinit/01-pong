/* utility.h */

#ifndef UTILITY_H
#define UTILITY_H

// needed for centerOrigin
#include <cmath>
// needed for centerOrigin
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Vector2.hpp>

void		centerOrigin( sf::Text &text );

static float	magnitude( sf::Vector2f v );
float		magnitude( float x, float y );
int		magnitude( int x, int y );

float		magnitudeSquared( float x, float y );
int		magnitudeSquared( int x, int y );

sf::Vector2f	normalize( sf::Vector2f v );

#endif	// UTILITY_H

/* EOF */

