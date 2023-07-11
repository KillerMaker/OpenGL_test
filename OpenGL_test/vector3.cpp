#include "vector3.h"


gl_helper::vector3 gl_helper::vector3::cross_product(const vector3& vector)
{
	vector3 v(0, 0, 0);

	*v.x = *vector.y * *z - *vector.z * *y;
	*v.y = -(*vector.x * *z - *vector.z * *x);
	*v.z = *vector.y * *x - *vector.x * *y;

	return v;
}
