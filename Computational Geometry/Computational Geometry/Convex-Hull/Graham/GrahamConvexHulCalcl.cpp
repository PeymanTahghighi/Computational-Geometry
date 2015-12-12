#include "GrahamConvexHulCalcl.h"
#include<algorithm>
#include<thread>

GrahamConvexHulCalcl * GCH = new GrahamConvexHulCalcl();

bool Comparer(Point A, Point B)
{
	return A.y > B.y;
}

//bool PointComparer(Point p1, Point p2)
//{
//	if (p1.y == 0 && p1.x>0) return true; //angle of p1 is 0, thus p2>p1
//	if (p2.y == 0 && p2.x>0) return false; //angle of p2 is 0 , thus p1>p2
//	if (p1.y>0 && p2.y<0) return true; //p1 is between 0 and 180, p2 between 180 and 360
//	if (p1.y<0 && p2.y>0) return false;
//	return (p1^p2)>0; //return true if p1 is clockwise from p2
//	
//}

GrahamConvexHulCalcl::GrahamConvexHulCalcl()
{
}


GrahamConvexHulCalcl::~GrahamConvexHulCalcl()
{
}

void GrahamConvexHulCalcl::CalculateConvexHullPoints()
{
	vector<Point> points = this->GetAllPoints();
	vector<Point> selectedPoints;
	HBRUSH brush1 = CreateSolidBrush(RGB(0, 255, 0));
	HBRUSH brush3 = CreateSolidBrush(RGB(255, 255, 255));
	HBRUSH brush2 = CreateSolidBrush(RGB(255, 0, 0));
	std::sort(points.begin(), points.end(), Comparer);
	Point p = points[0];
	Point q;
	selectedPoints.push_back(p);

	while (q != points[0])
	{
		for (int i = 0; i < points.size(); i++)
		{
			bool canSelect = true;
			int checkedPoints = 0;
			int j = 0;
			if (points[i] == p) continue;
			SelectObject(this->GetHDC(), brush1);
			Ellipse(this->GetHDC(), points[i].x - 5, points[i].y - 5, points[i].x + 5, points[i].y + 5);


			SelectObject(this->GetHDC(), brush2);
			Ellipse(this->GetHDC(), p.x - 5, p.y - 5, p.x + 5, p.y + 5);

			std::this_thread::sleep_for(std::chrono::milliseconds(100));
			//DrawLine(p, points[i], RGB(0, 0, 255));
			for (j = 0; j < points.size(); j++)
			{
				std::this_thread::sleep_for(std::chrono::milliseconds(100));
				if (i != j && points[i]!=p)
				{
					std::this_thread::sleep_for(std::chrono::milliseconds(100));
					DrawLine(points[i], points[j], RGB(0, 255, 255));
					checkedPoints++;
					if (CalculateTripletOrientation(p, points[j], points[i]) > 0)
					{
						std::this_thread::sleep_for(std::chrono::milliseconds(500));
						DrawLine(points[i], points[j], RGB(255, 0, 0));
						canSelect = false;
						break;
					}
					else
					{
						std::this_thread::sleep_for(std::chrono::milliseconds(500));
						DrawLine(points[i], points[j], RGB(0, 255, 0));
					}
				}
			}
			std::this_thread::sleep_for(std::chrono::milliseconds(300));
			for (int k = j; k >= 0; k--)
			{
				if (k == points.size()) continue;
				std::this_thread::sleep_for(std::chrono::milliseconds(100));
				DrawLine(points[i], points[k], RGB(255, 255, 255));
			}
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
			SelectObject(this->GetHDC(), brush3);
			Ellipse(this->GetHDC(), points[i].x - 5, points[i].y - 5, points[i].x + 5, points[i].y + 5);
			DrawLine(p, points[i], RGB(255, 255, 255));
			if (canSelect && checkedPoints!=0)
			{
				q = points[i];
				
				SelectObject(this->GetHDC(), brush1);
				Ellipse(this->GetHDC(), q.x - 5, q.y - 5, q.x + 5, q.y + 5);


				SelectObject(this->GetHDC(), brush2);
				Ellipse(this->GetHDC(), p.x - 5, p.y - 5, p.x + 5, p.y + 5);


				MoveToEx(this->GetHDC(), p.x, p.y, NULL);
				LineTo(this->GetHDC(), q.x, q.y);

				selectedPoints.push_back(q);

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
					LineTo(this->GetHDC(), selectedPoints[i + 1].x, selectedPoints[i+1].y);
					SelectObject(this->GetHDC(), brush2);
					Ellipse(this->GetHDC(), selectedPoints[i].x - 5, selectedPoints[i].y - 5, selectedPoints[i].x + 5, selectedPoints[i].y + 5);
				}
				SelectObject(this->GetHDC(), brush2);
				Ellipse(this->GetHDC(), 
					selectedPoints[selectedPoints.size() - 1].x - 5, 
					selectedPoints[selectedPoints.size() - 1].y - 5, 
					selectedPoints[selectedPoints.size() - 1].x + 5, 
					selectedPoints[selectedPoints.size() - 1].y + 5);

				
				
					

				p = q;
				break;
			}
		}
	}
	
	

	std::this_thread::sleep_for(std::chrono::seconds(1));

	
}

