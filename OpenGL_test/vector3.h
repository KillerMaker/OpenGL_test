#pragma once

namespace gl_helper
{
	class vector3
	{
	private:
		float values[3] = {0,0,0};
	public:
		float * const x = values;
		float * const y = values+1;
		float * const z = values+2;

		vector3(float x, float y, float z)
		{
			*this->x = x;
			*this->y = y;
			*this->z = z;
		}

		vector3(const vector3& v) 
		{
			operator=(v);
		}

		vector3& operator=(const vector3& v)
		{
			*this->x = *v.x;
			*this->y = *v.y;
			*this->z = *v.z;

			return *this;
		}

		inline vector3 operator*(const float n) const noexcept
		{
			return vector3(*x * n, *y * n, *z * n);
		}

		inline friend vector3 operator*(const float n, const vector3& vector)
		{
			return vector3(*vector.x * n, *vector.y * n, *vector.z * n);
		}

		inline float operator*(const vector3& vector)
		{
			return (*x) * (*vector.x) + (*y) * (*vector.y) + (*z) * (*vector.z);
		}

		inline vector3 operator+(const vector3& vector)
		{
			return vector3(*x + *vector.x, *y + *vector.y, *z + *vector.z);
		}

		inline const float* get_raw_ptr() const { return values; }

		vector3 cross_product(const vector3& vector);

	};
}


