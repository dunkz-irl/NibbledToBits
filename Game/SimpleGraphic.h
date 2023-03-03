#pragma once
class SimpleGraphic
{
public:
	SimpleGraphic(Play::Point2f pos, int spriteID);

	virtual void Update() = 0;
	void Draw();

protected:
	Play::Matrix2D m_matrix = Play::MatrixIdentity();
	int m_spriteID;
	Play::Point2f m_pos;
};
