#ifndef FLLOGGER_HH
# define FLLOGGER_HH

#include <fstream>
#include <fltype.h>

static inline i8
initLogger(const char *filepath) {
	std::ofstream file(filepath);

	if (!file.is_open()) {
		return (FL_ERROR);
	};

	return (FL_GOOD);
}

#endif
