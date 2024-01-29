#ifndef FLLLIST_HH
# define FLLLIST_HH

#include <fltype.h>
#include <flmem.h>

namespace fl {

template <typename T>
struct lnode_t {
	T elem;
	lnode_t *next;
	lnode_t *prev;
};

template <typename T>
class llist {
	protected:

	lnode_t<T> **list;
	lnode_t<T> *iterator;
	lnode_t<T> *last;
	u64 length;

	public:

	T operator[](const u64 idx) {
		lnode_t<T> *span = *list;

		for (u64 i = 0; i < idx; i++) {
			span = span->next;
			if (span == NULL) {
				abort();
			}
		}
		return (span->elem);
	}

	void incr() {
		if (iterator->next) {
			iterator = iterator->next;
		}
	}

	void decr() {
		if (iterator->prev) {
			iterator = iterator->next;
		}
	}

	lnode_t<T> *iter(void) {
		return (iterator);
	}

	const lnode_t<T> *const_iter(void) {
		return ((const lnode_t<T> *)iterator);
	}

	const u64 size(void) {
		return ((const u64)length);
	}

	lnode_t<T> *list_last(void) {
		if (length == 0) {
			return (*list);
		}
		lnode_t<T> *span = *list;
		while (span->next != NULLPTR) {
			span = span->next;
		}
		return (span);
	}

	void list_add(T data) {
		lnode_t<T> *span = last;

		lnode_t<T> *newnode = new (lnode_t<T>);
		if (!newnode) {
			abort();
		}

		newnode->elem = data;
		newnode->next = NULLPTR;
		newnode->prev = NULLPTR;
		if (length == 0) {
			*list = newnode;
			iterator = *list;
		} else {
			span->next = newnode;
			newnode->prev = span;
		}
		last = newnode;
		length++;
	}

	u64 list_find(T data) {
		lnode_t<T> *span = *list;

		u64 idx = 0;
		while (span->next != NULLPTR || memCmp(span->elem, data, sizeof(T)) != 0) {
			span = span->next;
			idx++;
		}
		if (span->next == NULLPTR && memCmp(span->elem, data, sizeof(T)) != 0) {
			return (false);
		}
		return (idx);
	}

	template <typename argT>
	void list_foreach(void (*fun)(T *, argT *), argT *arg){
		lnode_t<T> *span = *list;
		while (span->next != NULLPTR) {
			fun(&span->elem, arg);
		}
		span = *list;
	}

	//need to free the data returned or else it leak
	T list_del(u32 idx) {
		lnode_t<T> *span = *list;

		for (u64 i = 0; i < idx; i++) {
			span = span->next;
		}

		T ret = span->elem;
		if (span->prev != NULLPTR) {
			span->prev->next = NULLPTR;
		}
		if (span->next != NULLPTR) {
			lnode_t<T> *tmp = span->next;
			tmp->prev = span->prev;
		}
		delete span;
		return (ret);
	}

	llist() {
		list = new (lnode_t<T> *);
		iterator = *list;
		last = *list;
		length = 0;
	}

	~llist() {
	}
};

};

#endif