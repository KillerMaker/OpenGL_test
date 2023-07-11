#include "transformation.h"
#include <iostream>
//using namespace gl_helper;

void gl_helper::transform::rotation_matrix_x(float angle, gl_helper::matrix& m)
{
	angle = angle * 3.14f / 180;
	m = gl_helper::matrix(4, 4, 0);

	m.element_at(0, 0) = 1.0f;
	m.element_at(1, 1) = cos(angle);
	m.element_at(1, 2) = -sin(angle);
	m.element_at(2, 1) = sin(angle);
	m.element_at(2, 2) = cos(angle);
	m.element_at(3, 3) = 1;
}

void gl_helper::transform::rotation_matrix_y(float angle, gl_helper::matrix& m)
{
	angle = angle * 3.14f / 180;
	m = gl_helper::matrix(4, 4, 0);
	
	m.element_at(0, 0) = cos(angle);
	m.element_at(0, 2) = -sin(angle);
	m.element_at(1, 1) = 1.0f;
	m.element_at(2, 0) = sin(angle);
	m.element_at(2, 2) = cos(angle);
	m.element_at(3, 3) = 1;
}

void gl_helper::transform::rotation_matrix_z(float angle, gl_helper::matrix& m)
{
	angle = angle * 3.14f / 180;
	m = gl_helper::matrix(4, 4, 0);
	
	m.element_at(0, 0) = cos(angle);
	m.element_at(0, 1) = -sin(angle);
	m.element_at(1, 0) = sin(angle);
	m.element_at(1, 1) = cos(angle);
	m.element_at(2, 2) = 1.0f;
	m.element_at(3, 3) = 1.0f;
}

void gl_helper::transform::projection_matrix(gl_helper::matrix& m, float fov, float width, float height, float near, float far)
{
	float aspect_ratio = height / width;
	float scale = 1 / tan(fov * 0.5 * 3.14f / 180);

	m = gl_helper::matrix(4, 4, 0);

	m.element_at(0, 0) = aspect_ratio * scale;
	m.element_at(1, 1) = scale;
	m.element_at(2, 2) = -(far+near) / (far - near);
	m.element_at(2, 3) = -2*(far * near) / (far - near);
	m.element_at(3, 2) = -1;
	m.element_at(3, 3) = 0;
	
}

void gl_helper::transform::rotate_x(float angle, gl_helper::matrix& m)
{
	angle = angle * 3.14f / 180;
	if (m.get_columns() == 4 && m.get_rows() == 4)
	{
		m.element_at(0, 0) = 1.0f;
		m.element_at(1, 1) = cos(angle);
		m.element_at(1, 2) = -sin(angle);
		m.element_at(2, 1) = sin(angle);
		m.element_at(2, 2) = cos(angle);
		m.element_at(3, 3) = 1;
	}
	
}

void gl_helper::transform::rotate_y(float angle, gl_helper::matrix& m)
{
	angle = angle * 3.14f / 180;
	if (m.get_columns() == 4 && m.get_rows() == 4)
	{
		m.element_at(0, 0) = cos(angle);
		m.element_at(0, 2) = -sin(angle);
		m.element_at(1, 1) = 1.0f;
		m.element_at(2, 0) = sin(angle);
		m.element_at(2, 2) = cos(angle);
		m.element_at(3, 3) = 1;
	}
}

void gl_helper::transform::rotate_z(float angle, gl_helper::matrix&m)
{
	angle = angle * 3.14f / 180;
	if (m.get_columns() == 4 && m.get_rows() == 4)
	{
		m.element_at(0, 0) = cos(angle);
		m.element_at(0, 1) = -sin(angle);
		m.element_at(1, 0) = sin(angle);
		m.element_at(1, 1) = cos(angle);
		m.element_at(2, 2) = 1.0f;
		m.element_at(3, 3) = 1.0f;
	}
}

void gl_helper::transform::translate(float x, float y, float z, gl_helper::matrix& m)
{
	gl_helper::matrix translation;
	translation_matrix(x, y, z, translation);

	m = translation * m;
}

void gl_helper::transform::scale(float, float, float, gl_helper::matrix&)
{
}


void gl_helper::transform::scale_matrix(float x, float y, float z, gl_helper::matrix& m)
{
	m = gl_helper::matrix(4, 4, 0);

	m.element_at(0, 0) = x;
	m.element_at(1, 1) = y;
	m.element_at(2, 2) = z;
	m.element_at(3, 3) = 1.0f;
}


void gl_helper::transform::translation_matrix(float x, float y, float z, gl_helper::matrix& m)
{
	identity_matrix(m);

	m.element_at(0, 3) = x;
	m.element_at(1, 3) = y;
	m.element_at(2, 3) = z;
	m.element_at(3, 3) = 1.0f;
}

void gl_helper::transform::identity_matrix(gl_helper::matrix& m)
{
	m = gl_helper::matrix(4, 4, 0.0f);
	m.element_at(0, 0) = 1;
	m.element_at(1, 1) = 1;
	m.element_at(2, 2) = 1;
	m.element_at(3, 3) = 1;
}

