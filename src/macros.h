#ifndef MACROS_H
#define MACROS_H

/* do things both ways ... */
#define SAFE(x) \
  do {          \
    x           \
  } while (0)

#if defined(DEBUGMALLOC)
#define FREE(x) debugfree(x)
#define REALLOC(x, y) debugrealloc(x, y, 0, (char *)0)
#define CALLOC(x, y) debugcalloc(x, y, 0, (char *)0)
#define DMALLOC(x, t, d) debugmalloc(x, t, d)
#define DREALLOC(x, y, tag, desc) debugrealloc(x, y, tag, desc)
#define DCALLOC(x, y, tag, desc) debugcalloc(x, y, tag, desc)
#else
#define FREE(x) free(x)
#define REALLOC(x, y) realloc(x, y)
#define CALLOC(x, y) calloc(x, y)
#define DMALLOC(x, tag, desc) MALLOC(x)
#define DREALLOC(x, y, tag, desc) REALLOC(x, y)
#define DCALLOC(x, y, tag, desc) CALLOC(x, y)
#endif

#define ALLOCATE(type, tag, desc) ((type *)DMALLOC(sizeof(type), tag, desc))
#define CALLOCATE(num, type, tag, desc) ((type *)DCALLOC(sizeof(type[1]), num, tag, desc))
#define RESIZE(ptr, num, type, tag, desc) \
  ((type *)DREALLOC((void *)ptr, sizeof(type) * (num), tag, desc))

#ifdef DEBUG
#define IF_DEBUG(x) x
#define DEBUG_CHECK(x, y) \
  if (x) fatal(y)
#define DEBUG_CHECK1(x, y, a) \
  if (x) fatal(y, a)
#define DEBUG_CHECK2(x, y, a, b) \
  if (x) fatal(y, a, b)
#else
#define IF_DEBUG(x)
#define DEBUG_CHECK(x, y)
#define DEBUG_CHECK1(x, y, a)
#define DEBUG_CHECK2(x, y, a, b)
#endif

#if !defined(EDIT_SOURCE) && !defined(_FUNC_SPEC_)
#define COPY2(x, y)                    \
  ((char *)(x))[0] = ((char *)(y))[0]; \
  ((char *)(x))[1] = ((char *)(y))[1]
#define LOAD2(x, y)         \
  ((char *)&(x))[0] = *y++; \
  ((char *)&(x))[1] = *y++
#define STORE2(x, y)          \
  *x++ = ((char *)(&(y)))[0]; \
  *x++ = ((char *)(&(y)))[1]

#define COPY4(x, y)                    \
  ((char *)(x))[0] = ((char *)(y))[0]; \
  ((char *)(x))[1] = ((char *)(y))[1]; \
  ((char *)(x))[2] = ((char *)(y))[2]; \
  ((char *)(x))[3] = ((char *)(y))[3]
#define LOAD4(x, y)         \
  ((char *)&(x))[0] = *y++; \
  ((char *)&(x))[1] = *y++; \
  ((char *)&(x))[2] = *y++; \
  ((char *)&(x))[3] = *y++
#define STORE4(x, y)          \
  *x++ = ((char *)(&(y)))[0]; \
  *x++ = ((char *)(&(y)))[1]; \
  *x++ = ((char *)(&(y)))[2]; \
  *x++ = ((char *)(&(y)))[3]

#define COPY8(x, y)                    \
  ((char *)(x))[0] = ((char *)(y))[0]; \
  ((char *)(x))[1] = ((char *)(y))[1]; \
  ((char *)(x))[2] = ((char *)(y))[2]; \
  ((char *)(x))[3] = ((char *)(y))[3]; \
  ((char *)(x))[4] = ((char *)(y))[4]; \
  ((char *)(x))[5] = ((char *)(y))[5]; \
  ((char *)(x))[6] = ((char *)(y))[6]; \
  ((char *)(x))[7] = ((char *)(y))[7]
#define LOAD8(x, y)         \
  ((char *)&(x))[0] = *y++; \
  ((char *)&(x))[1] = *y++; \
  ((char *)&(x))[2] = *y++; \
  ((char *)&(x))[3] = *y++; \
  ((char *)&(x))[4] = *y++; \
  ((char *)&(x))[5] = *y++; \
  ((char *)&(x))[6] = *y++; \
  ((char *)&(x))[7] = *y++;
#define STORE8(x, y)          \
  *x++ = ((char *)(&(y)))[0]; \
  *x++ = ((char *)(&(y)))[1]; \
  *x++ = ((char *)(&(y)))[2]; \
  *x++ = ((char *)(&(y)))[3]; \
  *x++ = ((char *)(&(y)))[4]; \
  *x++ = ((char *)(&(y)))[5]; \
  *x++ = ((char *)(&(y)))[6]; \
  *x++ = ((char *)(&(y)))[7]

#define COPY_SHORT(x, y) COPY2(x, y)
#define LOAD_SHORT(x, y) LOAD2(x, y)
#define STORE_SHORT(x, y) STORE2(x, y)

/* LPC INT */
#define COPY_INT(x, y) COPY8(x, y)
#define LOAD_INT(x, y) LOAD8(x, y)
#define STORE_INT(x, y) STORE8(x, y)

/* LPC FLOAT */
#define COPY_FLOAT(x, y) COPY8(x, y)
#define LOAD_FLOAT(x, y) LOAD8(x, y)
#define STORE_FLOAT(x, y) STORE8(x, y)

#if SIZEOF_CHAR_P == 4
#define COPY_PTR(x, y) COPY4(x, y)
#define LOAD_PTR(x, y) LOAD4(x, y)
#define STORE_PTR(x, y) STORE4(x, y)

#define POINTER_INT intptr_t
#define INS_POINTER ins_pointer
#elif SIZEOF_CHAR_P == 8
#define COPY_PTR(x, y) COPY8(x, y)
#define LOAD_PTR(x, y) LOAD8(x, y)
#define STORE_PTR(x, y) STORE8(x, y)

#define POINTER_INT intptr_t
#define INS_POINTER ins_pointer
#else
#error pointers of size other than 4 or 8 not implemented
#endif
#endif /* !defined(EDIT_SOURCE) && !defined(_FUNC_SPEC_) */

#ifndef _FUNC_SPEC_
char *xalloc(int);
#ifdef DEBUGMALLOC
char *int_string_copy(const char *const, const char *);
char *int_string_unlink(const char *, const char *);
char *int_new_string(int, const char *);
char *int_alloc_cstring(const char *, const char *);
#else
char *int_string_copy(const char *const);
char *int_string_unlink(const char *);
char *int_new_string(int);
char *int_alloc_cstring(const char *);
#endif
#endif

#ifdef DEBUGMALLOC
#define string_copy(x, y) int_string_copy(x, y)
#define string_unlink(x, y) int_string_unlink(x, y)
#define new_string(x, y) int_new_string(x, y)
#define alloc_cstring(x, y) int_alloc_cstring(x, y)
#else
#define string_copy(x, y) int_string_copy(x)
#define string_unlink(x, y) int_string_unlink(x)
#define new_string(x, y) int_new_string(x)
#define alloc_cstring(x, y) int_alloc_cstring(x)
#endif

/* The ANSI versions must take an unsigned char, and must work on EOF.  These
 * versions take a (possibly signed) char, and do not work correctly on EOF.
 *
 * Note that calling isdigit(x) where x is a signed char with x < 0 (i.e.
 * high bit set) invokes undefined behavior.
 */
#define uisdigit(x) isdigit((unsigned char)x)
#define uislower(x) islower((unsigned char)x)
#define uisspace(x) isspace((unsigned char)x)
#define uisalnum(x) isalnum((unsigned char)x)
#define uisupper(x) isupper((unsigned char)x)
#define uisalpha(x) isalpha((unsigned char)x)
#define uisxdigit(x) isxdigit((unsigned char)x)
#define uisascii(x) isascii((unsigned char)x)
#define uisprint(x) isprint((unsigned char)x)

/* Compare two number */
#define COMPARE_NUMS(x, y) (((x) > (y) ? 1 : ((x) < (y) ? -1 : 0)))

/* FIXME: This is planned to become core functionaltiy set, remove this define
 * entirely. */
#ifndef DEBUG_MACRO
#define DEBUG_MACRO
#endif

#endif
