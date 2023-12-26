#ifndef FLSTRING_HH
# define FLSTRING_HH

# include "flmem.hh"
# include "flvector.hh"

namespace fl {

static inline vec<char *>
strSplit(const char *str, const i8 delim, i32 n, void *(*allocator)(u64)) {
	vec<char *> split;
	vec<char> span;
	char * tmp;

	for (i32 i = 0; i < n || str[i] != NULL; i++) {
		span += str[i];
		if (str[i] ==  delim) {
			tmp = (char *)allocator(span.size());
			int k = 0;
			for (; k < span.size(); k++) {
				tmp[k] = span[k];
			}
			tmp[k] = 0x00;
			span.clear();
			split.push_back(tmp); 
			i++;
		}
	}
	return (split);
}

};

#endif
