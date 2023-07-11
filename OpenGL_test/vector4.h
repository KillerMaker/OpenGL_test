#pragma once
#include"vector3.h"

namespace gl_helper 
{
	class vector4
	{
	private:
		float values[4] = { 0,0,0,0 };
	public:
		float* const x = values;
		float* const y = values + 1;
		float* const z = values + 2;
		float* const w = values + 3;

		vector4(float x, float y, float z, float w = 1.0f) 
		{
			*this->x = x;
			*this->y = y;
			*this->z = z;
			*this->w = w;

		}
		vector4(vector3 v, float w = 1.0f) 
		{
			*this->x = *v.x;
			*this->y = *v.y;
			*this->z = *v.z;
			*this->w = w;
		}

		vector4(const vector4& v) 
		{
			operator=(v);
		}

		vector4& operator=(const vector4& v)
		{
			*this->x = *v.x;
			*this->y = *v.y;
			*this->z = *v.z;
			*this->w = *v.w;
		}

	    inline vector4 operator*(const float n)
		{
			return vector4(*x * n, *y * n, *z * n, *w * n);
		}

		inline friend vector4 operator*(const float n, vector4& vector)
		{
			return vector4(*vector.x * n, *vector.y * n, *vector.z * n, *vector.w * n);
		}

		inline vector4 operator+(const vector4& vector)
		{
			return vector4(*x + *vector.x, *y + *vector.y, *z + *vector.z, *w + *vector.w);
		}

		inline operator vector3() const
		{
			return vector3(*x, *y, *z);
		}

		inline const float* get_raw_ptr() const { return values; }

	};
}


