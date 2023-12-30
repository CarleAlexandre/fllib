#ifndef FLTYPE_H
# define FLTYPE_H

/* typedef*/

typedef const void *constptr;
typedef void *ptr;

typedef char i8;
typedef short i16;
typedef int i32;
typedef long long i64;

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;
typedef float f32;
typedef double f64;

/* define*/

# ifndef NULL
#  define NULL 0x00
# endif

# ifndef NULLPTR
#  define NULLPTR 0x00
# endif

# ifndef NIL
#  define NIL 0x00
# endif

# ifndef endl
#  define endl '\n'
# endif

/**
	Critical Error
*/
# ifndef FL_ERROR
#  define FL_ERROR -1
# endif

/**
	Intended Behavior
*/
# ifndef FL_GOOD
#  define FL_GOOD 0
# endif

/**
	Not Critical but could be better
*/
# ifndef FL_BAD
#  define FL_BAD 1
# endif

#endif
