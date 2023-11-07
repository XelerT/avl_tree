#pragma once

#include <cstdint>

namespace binary_trees
{
        const size_t  INVALID                 = -1;
        const size_t  DEFAULT_ROOT_INDEX      = INVALID;
        const size_t  DEFAULT_SPINE_SIZE      = 64;
        const int     NODE_HEIGHT             = 1;
        const uint8_t CAPACITY_RESERVE_FACTOR = 2;
}

template <typename T>
T max (T &val1, T val2)
{
        return val1 > val2 ? val1 : val2;
}