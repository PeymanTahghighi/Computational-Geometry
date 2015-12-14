#pragma once
#include<vector>
#include<math.h>
#include<Windows.h>

using std::vector;

#define PI 3.14159265

struct Point
{
	float x, y;
	Point() : x(0.0f), y(0.0f) {}
	Point(float _x, float _y) : x(_x), y(_y) {}

	bool operator ==(const Point & rhs)
	{
		if (this->x == rhs.x && this->y == rhs.y) return true;
		return false;
	}
	bool operator !=(const Point & rhs)
	{
		if (this->x != rhs.x || this->y != rhs.y) return true;
		return false;
	}

	const bool operator ==(const Point & rhs) const
	{
		if (this->x == rhs.x && this->y == rhs.y) return true;
		return false;
	}
	Point &operator+(int i)
	{
		this->x += i;
		this->y += i;
		return *this;
	}
};

struct Line
{
	float x1, y1, x2, y2,x,y;
	Line(Point start, Point end) : x1(start.x), y1(start.y), x2(end.x), y2(end.y) 
	{
		x = end.x - start.x;
		y = end.y - start.y;
	}
	float Angle(const Line & rhs)
	{
		float dot = DotProduct(rhs);
		float mag1 = this->Magnitude();
		float mag2 = rhs.Magnitude();
		float cos= acosf(dot / (mag1*mag2));
		return static_cast<float>((cos * 180) / PI);
	}

	float Magnitude()
	{
		return sqrtf(pow((x2-x1), 2) + pow((y2-y1), 2));
	}

	const float Magnitude() const
	{
		return sqrtf(pow((x2 - x1), 2) + pow((y2 - y1), 2));
	}

	float DotProduct(const Line & that)
	{
		return this->x*that.x + this->y*that.y;
	}

};

class ConvexHullBase
{

public:

	ConvexHullBase() = default;

public:
	virtual void CalculateConvexHullPoints() = 0;

	virtual vector<Point> GetConvexHullPoints() { return this->m_convexHullPoints; }

	virtual void AddPoint(float x, float y)
	{
		Point p(x, y);
		this->m_allPoints.push_back(p);
	}

	virtual vector<Point> GetAllPoints() { return this->m_allPoints; }

	virtual void SetHDC(HDC h) { this->m_hdc = h; }



protected:

	virtual void SetAllPoints(vector<Point> &p) { this->m_allPoints = p; }

	virtual void AddConvexHullPoint(Point p) { this->m_convexHullPoints.push_back(p); }

	virtual int CalculateTripletOrientation(Point p, Point q, Point r)
	{
		int ret;
		ret = (q.y - p.y)*(r.x - q.x) - (q.x - p.x) * (r.y - q.y);
		return ret;
	}

	virtual HDC GetHDC() { return this->m_hdc; }

	virtual void DrawLine(Point p1, Point p2,COLORREF color)
	{
		float m = (p2.y - p1.y) / (p2.x - p1.x);
		float xmax = p1.x > p2.x ? p1.x : p2.x;
		for (float i = p1.x<p2.x ? p1.x : p2.x; i < xmax; i+=0.05f)
		{
			float y = m*(i - p1.x) + p1.y;;
			SetPixel(this->m_hdc, i, y, color);
		}
	}

	template<typename T>
	bool HaveMember(std::vector<T> vec, T data)
	{
		for (auto const & member : vec)
			if (member == data) return true;

		return false;
	}

private:
	vector<Point> m_allPoints;
	vector<Point> m_convexHullPoints;
	HDC m_hdc;
};