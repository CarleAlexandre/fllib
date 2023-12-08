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

		bool isLeaf(void) {
			return (child_number == 0);
		}

		Type getData(void) {
			return (label);
		}

		void setData(Type data) {
			label = data;
		}

		float getSize(int exponent) {
			return (flPow(2, exponent - depth));
		}

		void clear(void) {
			for (int i = 0; i < child_number; i++) {
				children[i]->clear();
				delete children[i];
				children[i] = nullptr;
			}
		}

		void createChild() {
			if (child_number < 8) {
				children[child_number] = new OctreeNode<Type>;
				child_number++;
			}
		}

		OctreeNode(int depth, Type label, int root_size)
		: depth(depth), label(label) {
			for (int i = 0; i < 8; i++) {
				children[i] = nullptr;
			}
		}

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
		int exponent;
		int max_depth;

	public:

		int root_size(void) {
			return (size);
		}

		// Encode 3D coordinates into Morton code
		unsigned long long mortonEncode(unsigned int x, unsigned int y, unsigned int z) {
			unsigned long long morton = 0;
			for (int i = 0; i < 21; i++) {
				morton |= ((x & 1U << i) << 2 * i) | ((y & 1U << i) << (2 * i + 1)) | ((z & 1U << i) << (2 * i + 2));
			}
			return morton;
		}

		// Decode Morton code into 3D coordinates
		void mortonDecode(unsigned long long morton, unsigned int& x, unsigned int& y, unsigned int& z) {
			x = y = z = 0;
			for (int i = 0; i < 21; i++) {
				x |= ((morton >> 3 * i) & 1U) << i;
				y |= ((morton >> (3 * i + 1)) & 1U) << i;
				z |= ((morton >> (3 * i + 2)) & 1U) << i;
			}
		}

		OctreeNode<Type> *getRoot(void) {
			return (*root);
		}

		// Linear data query algorithm
		Type query(const vec3& target_pos) {
			unsigned long long morton = mortonEncode(
				static_cast<unsigned int>(target_pos.x),
				static_cast<unsigned int>(target_pos.y),
				static_cast<unsigned int>(target_pos.z)
			);
			OctreeNode<Type>* currentNode = *root;
			for (int i = max_depth - 1; i >= 0; i--) {
				int childIndex = (morton >> 3 * i) & 0x7;
				if (currentNode->children[childIndex] == nullptr) {
					return (currentNode->getData());
				}
				currentNode = currentNode->children[childIndex];
			}
			return currentNode->getData();
		}

		Octree(vec3 pos, float root_size, int max_depth, Type root_label): size(root_size), max_depth(max_depth) {
			root = new OctreeNode<Type>(0, root_label, root_size);//can have an error here if i get segfault it come from here
			depth = 0;
			exponent = log2(size);
		}
		~Octree() {
			(*root)->clear();
			delete *root;
			*root = nullptr;
		}

};




template <typename Type>
void linearQuery(OctreeNode<Type>* node) {
    // Perform operations on the node (e.g., check if it contains relevant data)

    if (!node->isLeaf()) {
        for (int i = 0; i < 8; i++) {
            if (node->children[i] != nullptr) {
                linearQuery(node->children[i]);
            }
        }
    }
}

};
