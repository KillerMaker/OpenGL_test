#pragma once

#include "matrix.h"
namespace gl_helper 
{
	class transform
	{
	public:
		void rotation_matrix_x(float, gl_helper::matrix&);
		void rotation_matrix_y(float, gl_helper::matrix&);
		void rotation_matrix_z(float, gl_helper::matrix&);
		void projection_matrix(gl_helper::matrix&, float, float, float, float, float);

		void rotate_x(float, gl_helper::matrix&);
		void rotate_y(float, gl_helper::matrix&);
		void rotate_z(float, gl_helper::matrix&);
		void translate(float, float, float, gl_helper::matrix&);
		void scale(float, float, float, gl_helper::matrix&);
		
		void scale_matrix(float, float, float, gl_helper::matrix&);

		void translation_matrix(float, float, float, gl_helper::matrix&);

		void identity_matrix(gl_helper::matrix&);
	};
}


