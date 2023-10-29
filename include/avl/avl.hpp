#pragma once

#include "node.hpp"
#include "spin.hpp"

namespace binary_trees
{
        template <typename T, typename key_type = int>
        class avl_t
        {
                private:
                        spin_t<node_t<T>> spin;
                        size_t root_index = DEFAULT_ROOT_INDEX;

                public:
                        avl_t (size_t capacity_) : spin {capacity_} {};
                        avl_t () = default;

                        void add_element (const T &new_elem_, const key_type &key) 
                        {
                                spin[root_index].insert(new_elem_, key);
                        }
        };
}