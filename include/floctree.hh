#ifndef FLOCTREE_HH
# define FLOCTREE_HH

#include "flmath.hh"
#include "fldata.hh"

namespace fl {

template <typename Type>
class OctreeNode {
	private:
		i32 depth;
		Type label;
		i32 child_number;

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

		f32 getSize(i32 exponent) {
			return (pow(2, exponent - depth));
		}

		void clear(void) {
			for (i32 i = 0; i < child_number; i++) {
				children[i]->clear();
				delete children[i];
				children[i] = nullptr;
			}
		}

		void createChild() {
			if (child_number < 8) {
				children[child_number] = new OctreeNode<Type>(depth + 1, Type {});
				child_number++;
			}
		}

		OctreeNode(i32 depth, Type label)
		: depth(depth), label(label) {
			for (i32 i = 0; i < 8; i++) {
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
		f32 size;
		size_t depth;
		i32 exponent;
		i32 max_depth;

	public:

		i32 root_size(void) {
			return (size);
		}

		// Encode 3D coordinates i32o Morton code
		u64 mortonEncode(u32 x, u32 y, u32 z) {
			u64 morton = 0;
			for (i32 i = 0; i < 21; i++) {
				morton |= ((x & 1U << i) << 2 * i) | ((y & 1U << i) << (2 * i + 1)) | ((z & 1U << i) << (2 * i + 2));
			}
			return morton;
		}

		// Decode Morton code i32o 3D coordinates
		void mortonDecode(u64 morton, u32& x, u32& y, u32& z) {
			x = y = z = 0;
			for (i32 i = 0; i < 21; i++) {
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
			u64 morton = mortonEncode(
				static_cast<u32>(target_pos.x),
				static_cast<u32>(target_pos.y),
				static_cast<u32>(target_pos.z)
			);
			OctreeNode<Type>* currentNode = *root;
			for (i32 i = max_depth - 1; i >= 0; i--) {
				i32 childIndex = (morton >> 3 * i) & 0x7;
				if (currentNode->children[childIndex] == nullptr) {
					return (currentNode->getData());
				}
				currentNode = currentNode->children[childIndex];
			}
			return currentNode->getData();
		}

		Octree(vec3 pos, f32 root_size, i32 max_depth, Type root_label): size(root_size), max_depth(max_depth) {
			*root = new OctreeNode<Type>(0, root_label);//can have an error here if i get segfault it come from here
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
        for (i32 i = 0; i < 8; i++) {
            if (node->children[i] != nullptr) {
                linearQuery(node->children[i]);
            }
        }
    }
}

};

#endif
