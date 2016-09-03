#include "BoundingBox.h"
#include "Vector.h"
class Point
{
	Point(const float& x, const float& y);
	Point();
	float x, y;
	static bool pointToBox(const Point& point, const BoundingBox& box);
	static bool pointToVector(const Point& point, const Vector& vector);
};