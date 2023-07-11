#include "cubic_bezier.h"

void gl_helper::cubic_bezier::calculate(gl_helper::matrix& curve, int size, float presition)
{
	float m,m2,m3,t2,t3;

	int index = 0;

	vector3 point_in_curve(0,0,0);

	for (float t = 0; t < 1; t += presition)
	{
		m = 1 - t;
		m2 = m * m;
		m3 = m2 * m;
		t2 = t * t;
		t3 = t2 * t;

		point_in_curve = (m3 * p0) + (3 * t * m2 * p1) + (3 * t2 * m * p2) + (t3 * p3);

		curve.element_at(0,index++) = *point_in_curve.x;
		curve.element_at(0,index++) = *point_in_curve.y;
		curve.element_at(0,index++) = *point_in_curve.z;
	}
}
