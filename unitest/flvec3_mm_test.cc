#include "test.hh"

using namespace fl;

void flvec3test_mm(void) {
	vec3_mm_t test1 = {.vec3 = {1, 1, 1}};
	vec3_mm_t test2 = {.vec3 = {3, 3, 3}};
	vec3_mm_t test3 = {.vec3 = {2, 2, 2}};

	vec3_mm_t ret1 = vec3_mm_add(test1, test2);
	vec3_mm_t ret2 = vec3_mm_sub(test1, test3);
	vec3_mm_t ret3 = vec3_mm_mul(test2, test3);
	vec3_mm_t ret4 = vec3_mm_div(test2, test3);

	vec3_mm_t vectest_mm = {.vec3 = {1, 2, 3}};

	std::cout << "add:" << ret1.vec3.x << ret1.vec3.y << ret1.vec3.z << '\n';
	std::cout << "sub:" << ret2.vec3.x << ret2.vec3.y << ret2.vec3.z << '\n';
	std::cout << "mul:" << ret3.vec3.x << ret3.vec3.y << ret3.vec3.z << '\n';
	std::cout << "div:" << ret4.vec3.x << ret4.vec3.y << ret4.vec3.z << '\n';
	for (int i = 0; i < 4; i++) {
		std::cout << "_m128 data at " << i << " :" << vectest_mm.mm_data[i] << "\n";
	}
}