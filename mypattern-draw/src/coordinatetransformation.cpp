#include <coordinatetransformation.h>

using namespace MyPattern::Draw;

CoordinateTransformation::CoordinateTransformation(double offsetX, double offsetY, double scaleX, double scaleY)
{
	m_offsetX = offsetX;
	m_offsetY = offsetY;
	m_scaleX = scaleX;
	m_scaleY = scaleY;
}

Point CoordinateTransformation::Transform(Point p)
{
	Point result = Point(m_offsetX + p.get_x() * m_scaleX,m_offsetY + p.get_y() * m_scaleY);
	result.set_landmark_name(p.get_landmark_name());
	return result;
}

BezierComplex CoordinateTransformation::Transform(BezierComplex b)
{
	list<Bezier> resultingBeziers;
	list<Bezier> originalBeziers = b.get_beziers();
	
	for(list<Bezier>::iterator it = originalBeziers.begin(); it != originalBeziers.end(); it++)
	{
		resultingBeziers.push_back(Transform(*it));
	}
	
	return BezierComplex(resultingBeziers, b.get_name());
}

Bezier CoordinateTransformation::Transform(Bezier b)
{
	array<Point,4> resultingPoints;
	array<Point,4> originalPoints = b.get_points();
	
	for(int index = 0; index < 4; index++)
	{
		resultingPoints[index] = Transform(originalPoints[index]);
	}
	
	return Bezier(resultingPoints);
}

Point CoordinateTransformation::TransformInverse(Point p)
{
	Point result =  Point((p.get_y() - m_offsetX) / m_scaleX,(p.get_y() - m_offsetY) / m_scaleY);
	result.set_landmark_name(p.get_landmark_name());
	return result;
}