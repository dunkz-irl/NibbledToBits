#pragma once

class Confetti : public Emitter
{
public:
	Confetti(Play::Point2f pos, float lifetime);
};

class CheeseConfetti : public Emitter
{
public:
	CheeseConfetti(Play::Point2f pos, float lifetime);
};

class SmokePuff : public Emitter
{
public:
	SmokePuff(Play::Point2f pos, float lifetime);
};

class Smoke : public Emitter
{
public:
	Smoke(Play::Point2f pos, float lifetime);
};

class Portal : public PolygonEmitter
{
public:
	Portal(Play::Point2f pos, float lifetime, float scale = 1.f);
};