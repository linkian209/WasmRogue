// substdio.h
/// @file
/// @brief Workaround for systems without a proper stdio implementation
///
/// stdio.h replacement/wrapper, since some target platforms have I/O not quite
/// rising to the level of "standard".
///
/// For platforms with working stdio, this header should just include the
/// real stdio.h. For other platforms, this should prototype a custom
/// implementation.
#ifndef SUBSTDIO_H
#define SUBSTDIO_H

#include <stdio.h>
#include <stdarg.h>

#endif

