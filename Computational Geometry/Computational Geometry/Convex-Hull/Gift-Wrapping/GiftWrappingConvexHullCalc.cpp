#include "GiftWrappingConvexHullCalc.h"
#include<algorithm>
#include<thread>

GiftWrappingConvexHullCalc *GWC = new GiftWrappingConvexHullCalc();

bool PointComparer(Point A, Point B)
{
	return A.y > B.y;
}
GiftWrappingConvexHullCalc::GiftWrappingConvexHullCalc()
{
}


GiftWrappingConvexHullCalc::~GiftWrappingConvexHullCalc()
{
}

void GiftWrappingConvexHullCalc::CalculateConvexHullPoints()
{
	vector<Point> points = this->GetAllPoints();
	vector<Point> selectedPoints;
	HBRUSH brush1 = CreateSolidBrush(RGB(0, 255, 0));
	HBRUSH brush2 = CreateSolidBrush(RGB(255, 0, 0));
	HBRUSH brush3 = CreateSolidBrush(RGB(255, 255, 255));
	std::sort(points.begin(), points.end(), PointComparer);
	Point p = points[0];
	Point q;
	
	int indice = 0;
	for (int i = 1; i < points.size(); i++)
	{
		bool canSelect = true;
		for (int j = 1; j < points.size(); j++)
		{
			if (i != j)
			{
				if (CalculateTripletOrientation(p, points[j], points[i]) > 0)
				{
					canSelect = false;
					break;
				}	
			}
		}
		if (canSelect)
		{
			q = points[i];
			break;
		}
	}

	selectedPoints.push_back(p);
	selectedPoints.push_back(q);
	std::this_thread::sleep_for(std::chrono::seconds(1));

	SelectObject(this->GetHDC(), brush1);
	Ellipse(this->GetHDC(), q.x - 5, q.y - 5, q.x+5, q.y+5);

	
	SelectObject(this->GetHDC(), brush2);
	Ellipse(this->GetHDC(), p.x - 5, p.y - 5, p.x+5, p.y+5);


	DrawLine(p, q, RGB(25, 25, 25));

	Point r;

	while (q != points[0])
	{
		Line l1(p, q);
		float minAngle = INT_MAX;
		Point nextPoint;
		for (auto & member : points)
		{
			if (member != p && member != q)
			{
				Line l2(q, member);
				float ang = l1.Angle(l2);
				if (ang < minAngle)
				{
					std::this_thread::sleep_for(std::chrono::milliseconds(150));
					DrawLine(q, nextPoint, RGB(255, 255, 255));

					minAngle = ang;
					nextPoint = member;
					std::this_thread::sleep_for(std::chrono::milliseconds(150));
					DrawLine(q, member, RGB(0, 255, 0));
				}
			}
		}
		DrawLine(q, nextPoint, RGB(255, 255, 255));
		p = q;
		q = nextPoint;
		selectedPoints.push_back(nextPoint);

		SelectObject(this->GetHDC(), brush1);
		Ellipse(this->GetHDC(), q.x - 5, q.y - 5, q.x+5, q.y+5);


		SelectObject(this->GetHDC(), brush2);
		Ellipse(this->GetHDC(), p.x - 5, p.y - 5, p.x+5, p.y+5);


		MoveToEx(this->GetHDC(), p.x, p.y, NULL);
		LineTo(this->GetHDC(), q.x, q.y);
		std::this_thread::sleep_for(std::chrono::seconds(1));

		//Draw All points again for better view
		for (auto const & member : points)
		{
			SelectObject(this->GetHDC(), brush3);
			Ellipse(this->GetHDC(), member.x - 5, member.y - 5, member.x + 5, member.y + 5);
		}

		//We redraw lines for better view.
		for (int i = 0; i < selectedPoints.size() - 1; i++)
		{
			MoveToEx(this->GetHDC(), selectedPoints[i].x, selectedPoints[i].y, NULL);
			LineTo(this->GetHDC(), selectedPoints[i + 1].x, selectedPoints[i + 1].y);
			SelectObject(this->GetHDC(), brush2);
			Ellipse(this->GetHDC(), selectedPoints[i].x - 5, selectedPoints[i].y - 5, selectedPoints[i].x + 5, selectedPoints[i].y + 5);
		}
		SelectObject(this->GetHDC(), brush2);
		Ellipse(this->GetHDC(),
			selectedPoints[selectedPoints.size() - 1].x - 5,
			selectedPoints[selectedPoints.size() - 1].y - 5,
			selectedPoints[selectedPoints.size() - 1].x + 5,
			selectedPoints[selectedPoints.size() - 1].y + 5);

	}

	
}