/*
 * Copyright (c) 2026 Anaconda, Inc. All rights reserved.
 *
 * Compile/link smoke test for the libcuest-dev package.
 *
 * Including <cuest.h> verifies that the public headers are installed and
 * self-contained. Taking the address of cuestGetMathMode forces the linker to
 * resolve a symbol from libcuest.so, which validates the unversioned development
 * symlink and the library's link-time interface. The function is not called
 * because that would require a live CUDA context/GPU; for a binary repack, the
 * useful check is that a consumer can compile and link against the package.
 * The pointer is volatile so the symbol reference is retained at all
 * optimization levels.
 */

#include <cuest.h>

int main(void) {
    cuestStatus_t (*volatile get_math_mode)(cuestHandle_t, cuestMathMode_t *) = cuestGetMathMode;
    return get_math_mode == 0;
}
