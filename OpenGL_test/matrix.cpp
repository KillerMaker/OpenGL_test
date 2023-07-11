#include "matrix.h"
#include <cassert>
#include <iostream>

using namespace gl_helper;


#ifdef DEBUG
unsigned int matrix::matrices_allocated = 0;
unsigned int matrix::matrices_deallocated = 0;
#endif // DEBUG

matrix::matrix(unsigned int rows, unsigned int columns, float init = 0.0f)
{
	allocate(rows, columns);

	for (int i = 0; i < rows * columns; i++)
		raw[i] = init;
}

matrix::matrix(unsigned int rows, unsigned int columns, float init[], bool should_delete) noexcept
{
	this->rows = new unsigned int(rows);
	this->columns = new unsigned int(columns);

	is_allocated = should_delete;

	raw = init;
}

gl_helper::matrix::matrix(const vector3& v3)
{
	raw = (float*)v3.get_raw_ptr();
	rows = new unsigned int(3);
	columns = new unsigned int(1);
}

gl_helper::matrix::matrix(const vector4& v4)
{
	raw = (float*) v4.get_raw_ptr();
	rows = new unsigned int(4);
	columns = new unsigned int(1);
}

matrix& matrix::operator=(const matrix& m)
{
	if (&m == this) return *this;

	if (is_allocated) deallocate();

	allocate(*m.rows, *m.columns);

	for (int i = 0; i < (*rows) * (*columns); i++)
		raw[i] = m.raw[i];

	return *this;
}

matrix& matrix::operator=(matrix&& m) noexcept
{
	if (&m == this) return *this;

	if (is_allocated) deallocate();

	is_allocated = m.is_allocated;
	m.is_allocated = false;

	raw = m.raw;
	rows = m.rows;
	columns = m.columns;

	m.raw = nullptr;
	m.rows = nullptr;
	m.columns = nullptr;
}

void matrix::allocate(unsigned int rows, unsigned int columns)
{
	if (is_allocated) deallocate();

	raw = new float[rows * columns];

	this->rows = new unsigned int(rows);
	this->columns = new unsigned int(columns);

	is_allocated = true;

    #ifdef DEBUG
	matrices_allocated++;
     #endif // DEBUG

}

void matrix::deallocate() noexcept
{
	if (!is_allocated) return;

	delete[] raw;

	delete rows;
	delete columns;

	is_allocated = false;

#ifdef DEBUG
	matrices_deallocated++;
#endif // DEBUG

}

matrix gl_helper::matrix::take(unsigned int rows, unsigned int columns)
{
	if (rows > *this->rows || columns > *this->columns)
		throw;

	matrix result;

	result.allocate(rows, columns);

	for (int i = 0; i < rows; i++)
		for (int j = 0; j < columns; j++)
			result.element_at(i, j) = element_at(i, j);

	return result;
}

matrix gl_helper::matrix::transpose()
{
	matrix transposed = *this;

	*transposed.rows = *this->columns;
	*transposed.columns = *this->rows;

	return transposed;
}

matrix matrix::operator*(const float scalar) const
{
	matrix result = *this;

	for (int i = 0; i < (*rows) * (*columns); i++)
		result.raw[i] *= scalar;

	return result;
}

matrix matrix::operator+(const matrix& m) const
{
	matrix result = *this;

	if (rows == m.rows && columns == m.columns)
	{
		for (int i = 0; i < (*rows) * (*columns); i++)
			result.raw[i] += m.raw[i];

		return result;
	}
		
	throw std::exception("Imposible to sum matrices of different order");
}

matrix matrix::operator-(const matrix& m) const
{
	matrix result = *this;

	if (rows == m.rows && columns == m.columns)
	{
		for (int i = 0; i < (*rows) * (*columns); i++)
			result.raw[i] -= m.raw[i];

		return result;
	}

	throw std::exception("Imposible to sum matrices of different order");
}

matrix matrix::operator*(const matrix& m) const
{
	if (*this->columns != *m.rows)
		throw std::exception("Imposible to multiply matrices");

	matrix result(*this->rows, *m.columns);

	for (int row = 0; row < *result.rows; row++)
	{
		for (int col = 0; col < *result.columns; col++)
		{
			double temp = 0;

			for (int it = 0; it < *this->columns; it++)
				temp += this->element_at_RO(row, it) * m.element_at_RO(it, col);

			result.element_at(row,col) = temp;
		}
	}

	return result;

}

matrix& gl_helper::matrix::operator*=(const float scalar)
{
	matrix temp = *this * scalar;
	*this = std::move(temp);

	return *this;
}

matrix& gl_helper::matrix::operator*=(const matrix& m)
{
	matrix temp = *this * m;
	*this = std::move(temp);

	return *this;
}

matrix& gl_helper::matrix::operator+=(const matrix& m)
{
	matrix temp = *this + m;
	*this = std::move(temp);

	return *this;
}

matrix& gl_helper::matrix::operator-=(const matrix& m)
{
	matrix temp = *this - m;
	*this = std::move(temp);

	return *this;
}

matrix::operator gl_helper::vector3()
{
	if (*rows == 1 && *columns == 3)
		return { element_at(0,0), element_at(0,1), element_at(0,2) };
	else if (*rows == 3 && *columns == 1)
		return { element_at(0,0), element_at(1,0), element_at(2,0) };
	else throw;
}

gl_helper::matrix::operator gl_helper::vector4()
{
	if (*rows == 1 && *columns == 4)
		return { element_at(0,0), element_at(0,1), element_at(0,2), element_at(0,3) };
	else if (*rows == 4 && *columns == 1)
		return { element_at(0,0), element_at(1,0), element_at(2,0), element_at(3,0) };
	else throw;
}



