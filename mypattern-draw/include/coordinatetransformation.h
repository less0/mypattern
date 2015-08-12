#ifndef COORDINATETRANSFORMATION_H
#define COORDINATETRANSFORMATION_H

#include <point.h>
#include <bezier.h>
#include <beziercomplex.h>

using namespace MyPattern::Base;

namespace MyPattern
{
	namespace Draw
	{
		class CoordinateTransformation
		{
			public:
				CoordinateTransformation(double offsetX, double offsetY, double scaleX, double scaleY);
				
				Point Transform(Point);
				BezierComplex Transform(BezierComplex);
				Bezier Transform(Bezier);
				Point TransformInverse(Point);
				BezierComplex TransformInverse(BezierComplex);
				Bezier TransformInverse(Bezier);
			private:
				double m_offsetX;
				double m_offsetY;
				double m_scaleX;
				double m_scaleY;
		};
	}
}

#endif //COORDINATETRANSFORMATION_H