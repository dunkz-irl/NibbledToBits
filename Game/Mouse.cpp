#include "Play.h"
#include "Mouse.h"

Mouse::Mouse(Play::Point2f pos)
{
	m_pos = pos;
}

void Mouse::Update()
{
	throw std::logic_error("The method or operation is not implemented.");
}

void Mouse::Draw()
{
	throw std::logic_error("The method or operation is not implemented.");
}
