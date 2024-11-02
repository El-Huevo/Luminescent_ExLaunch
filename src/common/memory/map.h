#pragma once

#include <map>
#include "nn_allocator.h"

namespace nn {
    template<typename K, typename T>
    using map = std::map<K, T, std::less<K>, nn_allocator<std::pair<const K, T>>>;
}