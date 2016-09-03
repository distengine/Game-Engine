#include "Point.h"

Point::Point(const float& x, const float& y)
{
	this->x = x;
	this->y = y;
}

Point::Point()
{
	x = 0;
	y = 0;
}

bool Point::pointToBox(const Point& point, const BoundingBox& box)
{
	// If point is within the box, Do Blah
	return 0;
}

bool Point::pointToVector(const Point& point, const Vector& vector)
{
	// If a point is within a vector, Do Blah
	return 0;
}