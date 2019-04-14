#ifndef D_DEBUG
#define D_DEBUG

#include <iostream>

#define PRINT_VAR(x) std::cout << __PRETTY_FUNCTION__ << ": " << \
        __LINE__ << ": " << #x << " = " << (x) << std::endl;

#endif
