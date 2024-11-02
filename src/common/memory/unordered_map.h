#pragma once

#include <unordered_map>
#include "nn_allocator.h"

namespace nn {
    template<typename K, typename T>
    using map = std::unordered_map<K, T, std::hash<K>, std::equal_to<K>, nn_allocator<std::pair<const K, T>>>;
}