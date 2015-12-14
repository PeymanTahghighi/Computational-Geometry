#include "GrahamConvexHulCalcl.h"
#include<algorithm>
#include<thread>

GrahamConvexHulCalcl * GCH = new GrahamConvexHulCalcl();

bool Comparer(Point A, Point B)
{
	return A.y > B.y;
}

GrahamConvexHulCalcl::GrahamConvexHulCalcl()
{
}


GrahamConvexHulCalcl::~GrahamConvexHulCalcl()
{
}

void GrahamConvexHulCalcl::CalculateConvexHullPoints()
{
	vector<Point> points = this->GetAllPoints();

	//We Use Selected Points For ReDrawing***
	vector<Point> selectedPoints;
	//***************************************

	//Create Brush For Drawing In Diffrenet Colors.***
	HBRUSH brush1 = CreateSolidBrush(RGB(0, 255, 0));
	HBRUSH brush3 = CreateSolidBrush(RGB(255, 255, 255));
	HBRUSH brush2 = CreateSolidBrush(RGB(255, 0, 0));
	//*************************************************

	//At First Sort Points By Y And Get The Max Y(Lowset Point).***
	std::sort(points.begin(), points.end(), Comparer);
	//*************************************************************

	//Set First Point As Lowset Point**
	Point p = points[0];
	//*********************************

	Point q;


	selectedPoints.push_back(p);

	while (q != points[0])//Check We Reched The End(Start Point) Or Not**
	{
		for (int i = 0; i < points.size(); i++)
		{
			bool canSelect = true;//We Use This To Identify Selected Points**

			int j = 0;
			
			if (points[i] == p || HaveMember<Point>(selectedPoints,points[i]))//Check This Point Is Selected Before Or Not.
			{

				continue;// Do Not Check Current Point.

			}

			//Simple Drawing**
			SelectObject(this->GetHDC(), brush1);
			Ellipse(this->GetHDC(), points[i].x - 5, points[i].y - 5, points[i].x + 5, points[i].y + 5);

			SelectObject(this->GetHDC(), brush2);
			Ellipse(this->GetHDC(), p.x - 5, p.y - 5, p.x + 5, p.y + 5);
			//****************

			//We Sleep This Thread For Easily Iterate Through Algorithm**
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
			//**********************************************************

			for (j = 0; j < points.size(); j++)
			{
				std::this_thread::sleep_for(std::chrono::milliseconds(100));

				if (i != j && points[i]!=p)
				{
					//Simple Waiting**
					std::this_thread::sleep_for(std::chrono::milliseconds(100));
					//***************
					
					//Draw Line From Current Point To Candidate Point**
					DrawLine(points[i], points[j], RGB(0, 255, 255));
					//***********************************************
					
					//Here We Calculate Points Orientation 
					//If This Selected Point Has A Right Turn When We Go From p->points[i]->points[j] Then We Discard It.
					if (CalculateTripletOrientation(p, points[j], points[i]) > 0)
					{
						//If The Point Is Discarded Then Wait A Moment And Draw A Red Line To Indicate That Its Discarded.
						std::this_thread::sleep_for(std::chrono::milliseconds(500));
						DrawLine(points[i], points[j], RGB(255, 0, 0));
						//***********************************************************************************************

						//This Point Cannot Be Selected So We Set This To False.
						canSelect = false;
						//******************************************************

						//We Can Break At This Point Because We Found A Point.
						break;
						//***************************************************

					}

					//Point[i] Has A Left Turn When We Got From p->points[i]->points[j]
					else
					{
						//Draw A Green Line For Left Turn
						std::this_thread::sleep_for(std::chrono::milliseconds(500));
						DrawLine(points[i], points[j], RGB(0, 255, 0));

						//*******************************
					}
				}
			}

			//Wait*****************************************************
			std::this_thread::sleep_for(std::chrono::milliseconds(300));
			//********************************************************

			//Delete All Drawed Line****************
			for (int k = j; k >= 0; k--)
			{
				if (k == points.size()) continue;//If We Draw All Lines.
				std::this_thread::sleep_for(std::chrono::milliseconds(100));
				DrawLine(points[i], points[k], RGB(255, 255, 255));
				
			}
			//**************************************

			
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
			SelectObject(this->GetHDC(), brush3);
			Ellipse(this->GetHDC(), points[i].x - 5, points[i].y - 5, points[i].x + 5, points[i].y + 5);
			
			//If We Found A Point That It Is In Convex Hull.
			if (canSelect)
			{
				q = points[i];
				
				//Simple Drawing**
				SelectObject(this->GetHDC(), brush1);
				Ellipse(this->GetHDC(), q.x - 5, q.y - 5, q.x + 5, q.y + 5);


				SelectObject(this->GetHDC(), brush2);
				Ellipse(this->GetHDC(), p.x - 5, p.y - 5, p.x + 5, p.y + 5);


				MoveToEx(this->GetHDC(), p.x, p.y, NULL);
				LineTo(this->GetHDC(), q.x, q.y);

				selectedPoints.push_back(q);

				//Draw All points.
				for (auto const & member : points)
				{
					SelectObject(this->GetHDC(), brush3);
					Ellipse(this->GetHDC(), member.x - 5, member.y - 5, member.x + 5, member.y + 5);
				}

				//We redraw lines for selected points again.
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


				//*********************************************************

				//We Set Next Point As Start Point.
				p = q;
				break;
			}
		}
	}
}