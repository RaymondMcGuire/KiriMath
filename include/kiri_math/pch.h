#include <kiri_math/logging.h>
#include <kiri_math/platform.h>

#ifdef BBR_MATH_WINDOWS

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#define NOMINMAX
#include <objbase.h>
#endif

#include <kiri_math/private_helpers.h>
