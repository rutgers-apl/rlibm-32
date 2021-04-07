/* crlibm_config.h.  Generated from crlibm_config.h.in by configure.  */
/* crlibm_config.h.in.  Generated from configure.ac by autoheader.  */

/* Define if building universal (internal helper macro) */
/* #undef AC_APPLE_UNIVERSAL_BUILD */

/* Compile the filib-compatible interval functions */
/* #undef BUILD_INTERVAL_FUNCTIONS */

/* architecture- and system-specific FPU control header file */
#define CRLIBM_HAS_FPU_CONTROL 1

/* Processor type */
/* #undef CRLIBM_TYPECPU_ALPHA */

/* Processor type */
#define CRLIBM_TYPECPU_AMD64 1

/* Processor type */
/* #undef CRLIBM_TYPECPU_ITANIUM */

/* Processor type */
/* #undef CRLIBM_TYPECPU_POWERPC */

/* Processor type */
/* #undef CRLIBM_TYPECPU_SPARC */

/* Processor type */
/* #undef CRLIBM_TYPECPU_X86 */

/* OS type */
/* #undef CRLIBM_TYPEOS_BSD */

/* OS type */
/* #undef CRLIBM_TYPEOS_CYGWIN */

/* OS type */
/* #undef CRLIBM_TYPEOS_HPUX */

/* Use the sse2 operators */
/* #undef HAS_SSE2 */

/* Define to 1 if you have the <fenv.h> header file. */
#define HAVE_FENV_H 1

/* Define to 1 if you have the <float.h> header file. */
#define HAVE_FLOAT_H 1

/* Define to 1 if you have the <gmp.h> header file. */
/* #undef HAVE_GMP_H */

/* Define to 1 if you have the <inttypes.h> header file. */
#define HAVE_INTTYPES_H 1

/* Define to 1 if you have the `gmp' library (-lgmp). */
/* #undef HAVE_LIBGMP */

/* Define to 1 if you have the `m' library (-lm). */
#define HAVE_LIBM 1

/* Define to 1 if you have the `mcr' library (-lmcr). */
/* #undef HAVE_LIBMCR */

/* Define to 1 if you have the <libmcr.h> header file. */
/* #undef HAVE_LIBMCR_H */

/* Define to 1 if you have the `mpfr' library (-lmpfr). */
/* #undef HAVE_LIBMPFR */

/* Define to 1 if you have the `ultim' library (-lultim). */
/* #undef HAVE_LIBULTIM */

/* Define to 1 if the type `long double' works and has more range or precision
   than `double'. */
#define HAVE_LONG_DOUBLE 1

/* Define to 1 if the type `long double' works and has more range or precision
   than `double'. */
#define HAVE_LONG_DOUBLE_WIDER 1

/* Define to 1 if you have the <MathLib.h> header file. */
/* #undef HAVE_MATHLIB_H */

/* Define to 1 if you have the <memory.h> header file. */
#define HAVE_MEMORY_H 1

/* Define to 1 if you have the <mpfr.h> header file. */
/* #undef HAVE_MPFR_H */

/* Define to 1 if you have the `sqrt' function. */
/* #undef HAVE_SQRT */

/* Define to 1 if you have the <stdint.h> header file. */
#define HAVE_STDINT_H 1

/* Define to 1 if you have the <stdlib.h> header file. */
#define HAVE_STDLIB_H 1

/* Define to 1 if you have the <strings.h> header file. */
#define HAVE_STRINGS_H 1

/* Define to 1 if you have the <string.h> header file. */
#define HAVE_STRING_H 1

/* Define to 1 if you have the <sys/stat.h> header file. */
#define HAVE_SYS_STAT_H 1

/* Define to 1 if you have the <sys/types.h> header file. */
#define HAVE_SYS_TYPES_H 1

/* Define to 1 if you have the <unistd.h> header file. */
#define HAVE_UNISTD_H 1

/* Name of package */
#define PACKAGE "crlibm"

/* Define to the address where bug reports for this package should be sent. */
#define PACKAGE_BUGREPORT ""

/* Define to the full name of this package. */
#define PACKAGE_NAME ""

/* Define to the full name and version of this package. */
#define PACKAGE_STRING ""

/* Define to the one symbol short name of this package. */
#define PACKAGE_TARNAME ""

/* Define to the home page for this package. */
#define PACKAGE_URL ""

/* Define to the version of this package. */
#define PACKAGE_VERSION ""

/* Size of an SCS digit */
#define SCS_NB_BITS 30

/* Number of digits in the SCS structure */
#define SCS_NB_WORDS 8

/* The size of `int', as computed by sizeof. */
#define SIZEOF_INT 4

/* Define to 1 if you have the ANSI C header files. */
#define STDC_HEADERS 1

/* Version number of package */
#define VERSION "1.0beta5"

/* Define WORDS_BIGENDIAN to 1 if your processor stores words with the most
   significant byte first (like Motorola and SPARC, unlike Intel). */
#if defined AC_APPLE_UNIVERSAL_BUILD
# if defined __BIG_ENDIAN__
#  define WORDS_BIGENDIAN 1
# endif
#else
# ifndef WORDS_BIGENDIAN
/* #  undef WORDS_BIGENDIAN */
# endif
#endif

/* Define to empty if `const' does not conform to ANSI C. */
/* #undef const */

/* Define to `__inline__' or `__inline' if that's what the C compiler
   calls it, or to nothing if 'inline' is not supported under any name.  */
#ifndef __cplusplus
/* #undef inline */
#endif
