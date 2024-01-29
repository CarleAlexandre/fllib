#ifndef FLLINKEDLIST_H
# define FLLINKEDLIST_H

#include "fltype.h"
#include "flmem.h"

typedef struct lnode_s lnode_t;

typedef struct lnode_s {
	void *elem;
	lnode_t *next;
} lnode_t;

inline lnode_t *list_last(lnode_t **list) {
	lnode_t *span = *list;
	while (span->next != NULLPTR) {
		span = span->next;
	}
	return (span);
}

inline void list_add(lnode_t *newnode, lnode_t **list) {
	lnode_t *span = list_last(list);

	span->next = newnode;
}

inline bool list_is(void *data, lnode_t **list, u64 datasize) {
	lnode_t *span = *list;

	while (span->next != NULLPTR || memCmp(span->elem, data, datasize) != 0) {
		span = span->next;
	}
	if (span->next == NULLPTR && memCmp(span->elem, data, datasize) != 0) {
		return (false);
	}
	return (true);
}

inline lnode_t *list_get(void *data, lnode_t **list, u64 datasize) {
	lnode_t *span = *list;

	while (span->next != NULLPTR || memCmp(span->elem, data, datasize) != 0) {
		span = span->next;
	}
	if (span->next == NULLPTR && memCmp(span->elem, data, datasize) != 0) {
		return (NULLPTR);
	}
	return (span);
}

inline u64 list_idx(void *data, lnode_t **list, u64 datasize) {
	lnode_t *span = *list;

	u64 i = 0;
	while (span->next != NULLPTR || memCmp(span->elem, data, datasize) != 0) {
		span = span->next;
		i++;
	}
	if (span->next == NULLPTR && memCmp(span->elem, data, datasize) != 0) {
		return (-1);
	}
	return (i);
}

inline void list_foreach(lnode_t **list, void (*fun)(void *)){
	lnode_t *span = *list;

	while (span->next != NULLPTR) {
		fun(span->elem);
	}
}

//need to free the pointer returned or else it leak
inline lnode_t *list_del(lnode_t **list, u32 idx) {
	lnode_t *span = *list;

	for (u64 i = 0; i < idx; i++) {
		span = span->next;
	}
	lnode_t *tmp = span->next;
	span->next = tmp->next;
	return (tmp);
}

#endif
