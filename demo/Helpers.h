#pragma once

#include <stddef.h>

inline size_t alignBufferSize(size_t size, size_t alignment) {
    return (size + (alignment-1)) & ~(alignment-1);
}
