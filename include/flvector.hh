#ifndef flvecTOR_HH
# define flvecTOR_HH

#include "flmem.h"

namespace fl {

template <typename Type> class vec {
	Type	*array;
	Type	*first_elem;

	public:
	unsigned long long	capacity;
	unsigned long long	used;

	Type &operator[](const unsigned long long idx) {
		return(first_elem[idx]);
	};

	Type &at(const unsigned long long idx) {
		return (first_elem[idx]);
	}

	void operator+=(Type data) {
		push_back(data);
	};

	template <unsigned long long N>
	void operator+=(Type (&data)[N]) {
		push_back(data);
	};

	Type last(void) {
		return (first_elem[used]);
	}

	Type first(void) {
		return (first_elem[0]);
	}

	void expand(void) {
		Type *tmp = new Type[ 2 * capacity];
		for (unsigned long long i = 0; i < used; ++i) {
            tmp[i] = first_elem[i];
        }
		delete [] array;
		capacity *= 2;
		array = tmp;
		first_elem = array;
	}

	void reduce(void) {
		Type *tmp = new Type[capacity - (unsigned long long)(capacity * 0.5)];
		for (unsigned long long i = 0; i < used; ++i) {
            tmp[i] = first_elem[i];
        }
		delete [] array;
		capacity *= 0.5;
		array = tmp;
		first_elem = array;
	}

	void push_back(Type element) {
		if (used >= capacity -1 || used == 0) {
			expand();
		}
		array[used] = element;
		used++;
	}

	template <unsigned long long N>
	void push_back(Type	(&element)[N]) {
		while (used + N >= capacity) {
			expand();
		}
		for (unsigned long long i = 0; i < N; i++) {
			array[used + i] = element[i];
		}
		used += N;
	}

	unsigned long long const size(void) {
		return (used);
	}

	void pop_back(void) {
		used--;
		if (used < capacity * 0.5) {
			reduce();
		}
	}

	void pop_back(unsigned long long n) {
		used -= n;
		if (used < capacity * 0.5) {
			reduce();
		}
	}

	void pop_first(void) {
		first_elem = &array[1];
		used--;
		if (used < capacity * 0.5) {
			reduce();
		}
	}

	void pop_first(unsigned long long n) {
		first_elem = &array[n - 1];
		used -= n;
		if (used < capacity * 0.5) {
			reduce();
		}
	}

	//array index start from 0
	void erase(unsigned long long index) {
		for (int i = 0; i < used - index - 1; i ++) {
			first_elem[index + i] =  first_elem[index + i + 1];
		}
		used--;
		if (used < capacity * 0.5) {
			reduce();
		}
	}

	void clear(void) {
		delete [] array;
		array = new Type[1];
		first_elem = array;
		capacity = 1;
		used = 0;
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
