#include "../LinesRotation/RotationDetection.h"


int RotationDetection::counter = 0;

RotationDetection *RD = new RotationDetection();

RotationDetection::RotationDetection()
{
	
}


void RotationDetection::AddLineStart(float x, float y, int lineId)
{
	this->m_lines[lineId].x1 = x;
	this->m_lines[lineId].y1 = y;
}


void RotationDetection::AddLineEnd(float x, float y, int lineId)
{
	this->m_lines[lineId].x2 = x;
	this->m_lines[lineId].y2 = y;
}

std::string RotationDetection::CalculateRotationDirection()
{
	
	float crossProduct = ((this->m_lines[0].x2 - this->m_lines[0].x1)*(this->m_lines[1].y2 - this->m_lines[1].y1))
		- ((this->m_lines[1].x2 - this->m_lines[0].x1)*(this->m_lines[0].y2 - this->m_lines[0].y1));
	if (crossProduct > 0)
	{
		return "CW";
	}
	return "CCW";
}
