#include "flmath.h"
#include "fldata.hh"

namespace fl {

inline short getMortonId(const float x, const float y, const float z) {
	short ret;
	ret &= (int)x;
	ret &= (int)y;
	ret &= (int)z;
	return (ret);
}

inline vec3 getChildPosFromIndex(int idx, vec3 center) {
	vec3 ret;

	return (ret);
}

template <typename Type>
class OctreeNode {
	private:
		vec3 pos;
		int depth;
		Type label;
		int root_size;
		int child_number;
	
	public:
		OctreeNode *children[8];

		bool isLeaf() {
			return (child_number == 0);
		}

		float getSize(void) {
			return (flPow(2, flpow(2, root_size) - depth));
		}

		void clear(void) {
			for (int i = 0; i < child_number; i++) {
				children[i]->clear();
				delete children[i];
			}
		}

		void createChild() {
			if (child_number < 8) {
				children[child_number] = new OctreeNode<Type>;
			}
		}

		OctreeNode(float x, float y, float z, int depth, Type label, int root_size)
		: depth(depth), label(label), root_size(root_size) {
			pos.x = x;
			pos.y = y;
			pos.z = z;
			for (int i = 0; i < 8; i++) {
				children[i] == 0x00;
			}
		};

		~OctreeNode() {
			clear();
		}
};

template <typename Type>
class Octree {

	private:
		vec3 pos;
		OctreeNode<Type> **root;
		float size;
		size_t depth;
		int max_depth;

	public:

		Octree(vec3 pos, float size, int max_depth, Type root_label): size(size), max_depth(max_depth) {
			root = new OctreeNode<Type>(0, 0, 0, 0, root_label, size);
			depth = 0;
		}

		~Octree() {
			(*root)->clear();
			delete root;
		}
};

};
