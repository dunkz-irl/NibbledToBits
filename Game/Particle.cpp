#include "Play.h"
#include "Particle.h"

const char* ShapeSprites[17]
{
	"circle",
	"cloud",
	"disc",
	"explosion",
	"flare",
	"fluid",
	"line",
	"pixel",
	"ring",
	"smoke",
	"snow",
	"spark",
	"sphere",
	"square",
	"star",
	"swiss_panel",
	"win-text"
};

Particle::Particle(ParticleShape _shape, Play::Point2f _pos, Play::Point2f _velocity, Play::Point2f _acceleration, float _rotSpeed, Play::Colour _colour)
{
	shape = _shape;
	spriteName = ShapeSprites[_shape];
	pos = _pos;
	velocity = _velocity;
	acceleration = _acceleration;
	rotSpeed = _rotSpeed;
	colour = _colour;
}
