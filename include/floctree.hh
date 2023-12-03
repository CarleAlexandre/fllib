#include "flmath.h"
#include "fldata.hh"

namespace fl {

template <typename Type>
class OctreeNode {
	private:
		int depth;
		Type label;
		int child_number;

	public:
		OctreeNode *children[8];

		bool isLeaf() {
			return (child_number == 0);
		}

		float getSize(int exponent) {
			return (flPow(2, exponent- depth));
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

		OctreeNode(int depth, Type label, int root_size)
		: depth(depth), label(label) {
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
		float length;
		size_t depth;
		int exponent;
		int max_depth;

	public:

		int size(void) {
			return (length);
		}

		Octree(vec3 pos, float size, int max_depth, Type root_label): length(size), max_depth(max_depth) {
			root = new OctreeNode<Type>(0, root_label, size);
			depth = 0;
			exponent = pow(2, size);
		}

		~Octree() {
			(*root)->clear();
			delete root;
		}
};

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

template <typename type>
inline
void setPlayerOffset(Octree<type> *octree) {
	vec3 offset = (octree->size() * octree->size() / 2);
}

};
