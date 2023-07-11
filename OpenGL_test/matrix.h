#pragma once

#include<math.h>
#include<stdlib.h>
#include<exception>
#include<string>
#include "vector4.h"



#define DEBUG

namespace gl_helper 
{
	class matrix
	{
	private:
		unsigned int* rows = nullptr;
		unsigned int* columns = nullptr;

		float* raw = nullptr;
		bool is_allocated = false;

		void allocate(unsigned int, unsigned int);
		void deallocate() noexcept;
	public:

       #ifdef DEBUG
		static unsigned int matrices_allocated;
		static unsigned int matrices_deallocated;
        #endif // DEBUG

		matrix() = default;
		matrix(unsigned int, unsigned int, float);
		matrix(unsigned int, unsigned int, float[], bool should_delete) noexcept;
		matrix(const matrix& m) { *this = m; }
		matrix(const vector3& v3);
		matrix(const vector4& v4);

		matrix(matrix&& m) noexcept { this->operator=(std::move(m)); }

		matrix& operator=(const matrix&);
		matrix& operator=(matrix&&) noexcept;

		inline unsigned int size() const noexcept { return (*rows) * (*columns); }
		inline unsigned int get_rows() const noexcept { return *rows; }
		inline unsigned int get_columns() const noexcept { return *columns; }

		~matrix() { deallocate(); }

		inline float* handle() noexcept { return raw; }
		inline float const* get_read_only_handle() const noexcept { return raw; }
		inline float& element_at(unsigned int row, unsigned int column) { return raw[row * (*columns) + column]; }
		inline float element_at_RO(unsigned int row, unsigned column) const { return raw[row * (*columns) + column]; }

		matrix take(unsigned int, unsigned int);
		matrix transpose();

		matrix operator*(const float) const;
		matrix operator+(const matrix&) const;
		matrix operator-(const matrix&) const;
		matrix operator*(const matrix&) const;

		matrix& operator*=(const float);
		matrix& operator*=(const matrix&);
		matrix& operator+=(const matrix&);
		matrix& operator-=(const matrix&);

		operator gl_helper::vector3();
		operator gl_helper::vector4();
	};
}


