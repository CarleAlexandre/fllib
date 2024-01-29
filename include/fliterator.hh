#ifndef FLITERATOR_HH
# define FLITERATOR_HH

namespace fl {

template <typename Type>
class iterator {
	private:
		Type iter;
	public:

	void operator++() {

	}
	void operator--() {

	}

	Type data() {

	}

	iterator() {
	}
	~iterator() {
	}
};

template <typename Type>
class const_iterator : public iterator<Type> {

};

};

#endif
