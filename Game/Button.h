#pragma once

class Button
{
public:
	Button();
	Button(int sprite, Play::Point2D position, Play::Vector2D size);

	virtual void Update();
	virtual void Draw();

	virtual bool Pressed();
	virtual bool Held();
	virtual bool Hovering();

	virtual void DrawSprite(Play::Point2D position);

	virtual void SetPos(Play::Point2D pos);

	Play::Vector2D GetSize();
	Play::Vector2D GetPosition();

protected:
	Play::Point2D m_pos;
	int m_sprite;
	Play::Vector2D m_size;

private:

};