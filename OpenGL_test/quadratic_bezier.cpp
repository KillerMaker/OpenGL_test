#include "quadratic_bezier.h"

void gl_helper::quadratic_bezier_curve::calculate(gl_helper::matrix& curve, int size, float presition)
{
	int index = 0;

	float m;
	float t2;
	float m2;

	for (float t = 0; t < 1; t += presition)
	{
		m = 1 - t;
		t2 = t * t;
		m2 = m * m;

		vector3 point_in_curve = (m2 * p0) + (2 * t * m * p1) + t2 * p2;

		curve.element_at(0,index++) = *point_in_curve.x;
		curve.element_at(0,index++) = *point_in_curve.y;
		curve.element_at(0,index++) = *point_in_curve.z;
	}
}
