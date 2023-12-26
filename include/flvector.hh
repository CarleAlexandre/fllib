#ifndef flvecTOR_HH
# define flvecTOR_HH

#include "flmem.hh"

namespace fl {

template <typename Type> class vec {
	protected:
		Type	*array;
		Type	*first_elem;
	public:
		u64	capacity;
		u64	used;

	Type
	&operator[](const u64 idx) {
		return(first_elem[idx]);
	};

	Type
	&at(const u64 idx) {
		return (first_elem[idx]);
	}

	void
	operator+=(Type data) {
		push_back(data);
	};

	template <u64 N>
	void
	operator+=(Type (&data)[N]) {
		push_back(data);
	};

	Type
	last(void) {
		return (first_elem[used]);
	}

	Type
	first(void) {
		return (first_elem[0]);
	}

	bool
	copy(vec<Type> *to, u64 n) {
		if (to == NULLPTR) {
			return (0);
		}
		u64 i = 0;
		for (; i < n || i < used; i++) {
			*to += first_elem[i];
		}
		return (i);
	}

	void
	expand(void) {
		Type *tmp = new Type[ 2 * capacity];
		for (u64 i = 0; i < used; ++i) {
            tmp[i] = first_elem[i];
        }
		delete [] array;
		capacity *= 2;
		array = tmp;
		first_elem = array;
	}

	void
	reduce(void) {
		Type *tmp = new Type[capacity - (u64)(capacity * 0.5)];
		for (u64 i = 0; i < used; ++i) {
            tmp[i] = first_elem[i];
        }
		delete [] array;
		capacity *= 0.5;
		array = tmp;
		first_elem = array;
	}

	void
	push_back(Type element) {
		if (used >= capacity -1 || used == 0) {
			expand();
		}
		first_elem[used] = element;
		used++;
	}

	template <u64 N>
	void
	push_back(Type	(&element)[N]) {
		while (used + N >= capacity) {
			expand();
		}
		for (u64 i = 0; i < N; i++) {
			first_elem[used + i] = element[i];
		}
		used += N;
	}

	const u64
	size(void) {
		return ((const u64)used);
	}

	void
	pop_back(void) {
		used--;
		if (used < capacity * 0.5) {
			reduce();
		}
	}

	void
	pop_back(u64 n) {
		used -= n;
		if (used < capacity * 0.5) {
			reduce();
		}
	}

	void
	pop_first(void) {
		first_elem = &array[1];
		used--;
		if (used < capacity * 0.5) {
			reduce();
		}
	}

	void
	pop_first(u64 n) {
		first_elem = &array[n - 1];
		used -= n;
		if (used < capacity * 0.5) {
			reduce();
		}
	}

	//array index start from 0
	void
	erase(u64 index) {
		for (i32 i = 0; i < used - index - 1; i ++) {
			first_elem[index + i] =  first_elem[index + i + 1];
		}
		used--;
		if (used < capacity * 0.5) {
			reduce();
		}
	}

	void
	clear(void) {
		delete [] array;
		array = new Type[1];
		first_elem = array;
		capacity = 1;
		used = 0;
	}

	void
	putNullLast() {
		push_back(0x00);
	}

	const i8
	*c_str(void) {
		putNullLast();
		return ((const i8 *)first_elem);
	}

	vec() {
		array = new Type[1];
		first_elem = array;
		capacity = 1;
		used = 0;
	}
	~vec() {
		delete [] array;
	}
};

};

#endif
