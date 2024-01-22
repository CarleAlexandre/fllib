#ifndef FLSTRING_HH
# define FLSTRING_HH

# include <flvector.hh>

namespace fl {

static inline vec<char *>
strSplit(const char *str, const i8 delim, u64 n, void *(*allocator)(u64)) {
	vec<char *> split;
	vec<char> span;
	char * tmp;

	for (u64 i = 0; i < n || str[i] != '\0'; i++) {
		span += str[i];
		if (str[i] ==  delim) {
			tmp = (char *)allocator(span.size());
			for (u64 k = 0; k <= span.size(); k++) {
				if (k == span.size()) {
					tmp[k] = 0x00;
					break;
				}
				tmp[k] = span[k];
			}
			span.clear();
			split.push_back(tmp);
			i++;
		}
	}
	return (split);
}

};

#endif
