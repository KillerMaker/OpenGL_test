#pragma once
#include"vector3.h"
#include <corecrt_math.h>
#include "matrix.h"

namespace gl_helper 
{
	
	class quadratic_bezier_curve
	{
	private:
		vector3 p0;
		vector3 p1;
		vector3 p2;

	public:
		quadratic_bezier_curve(const vector3& p0, const vector3& p1, const vector3& p2 ) :p0{ p0 }, p1{ p1 }, p2{ p2 } {}
		void calculate(gl_helper::matrix& curve, int size, float presition);
	};

}

