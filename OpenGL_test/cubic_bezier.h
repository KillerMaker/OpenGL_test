#pragma once
#include "vector3.h"
#include "matrix.h"

namespace gl_helper 
{
	class cubic_bezier
	{
	private:
		vector3 p0;
		vector3 p1;
		vector3 p2;
		vector3 p3;

	public:
		cubic_bezier(const vector3& p0, const vector3& p1, const vector3& p2, const vector3& p3) 
			:p0{ p0 }, p1{ p1 }, p2{ p2 }, p3{ p3 } {}

		void calculate(gl_helper::matrix& curve, int size, float presition);
	};

}

