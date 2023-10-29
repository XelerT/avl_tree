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
                        avl_t () : spin {DEFAULT_SPIN_SIZE} {};

                        void insert (const T &new_elem_, const key_type &key) 
                        {
                                spin[root_index].insert(new_elem_, key, spin);
                        }

                        size_t get_root_index () const { return root_index; }
                        size_t get_capacity   () const { return spin.get_capacity(); }
        };
}