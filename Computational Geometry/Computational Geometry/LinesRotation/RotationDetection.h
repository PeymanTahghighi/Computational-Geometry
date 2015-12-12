#pragma once
#include<string>

#define LINE_COUNT 2

class RotationDetection
{
public:
	struct Line
	{
		float x1, y1, x2, y2;
		Line() = default;
		Line(float X1, float Y1, float X2, float Y2) : x1(X1), y1(Y1), x2(X2), y2(Y2) {}
		Line(const Line & l)
		{
			this->x1 = l.x1;
			this->x2 = x2;
			this->y2 = y2;
			this->y1 = l.y1;
		}
	};



public:
	RotationDetection();

	void AddLineStart(float x, float y,int lineId);
	void AddLineEnd(float x, float y, int lineId);

	std::string CalculateRotationDirection();

	Line &GetLineProperty(int lineID) { return this->m_lines[lineID]; }

private:

	Line m_lines[LINE_COUNT];
	static int counter;

};

extern RotationDetection *RD;

