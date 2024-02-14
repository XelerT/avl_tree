#pragma once

#include <string>
#include <fstream>
// #include <format>
#include <memory>

#include "node.hpp"
#include "spine.hpp"
#include "utils.hpp"

#include "graphviz/graphviz.hpp"

namespace binary_trees
{
        using namespace graphviz;

        template <typename T, typename key_type = int>
        class avl_t
        {
                private:
                        spine_t<node_t<T>> spine;
                        size_t root_index = DEFAULT_ROOT_INDEX;
                        T invalid_val;

                public:
                        avl_t (T &invalid_val_) : spine {}, invalid_val(invalid_val_) {};

                        void insert (const T &data_, const key_type &key_);
                        
                        T get_data  (const key_type &key_) 
                        { return spine[root_index].get_data(key_, invalid_val, spine); }
                        
                        int count_elems_in_range (const key_type &low_key_, const key_type &high_key_) 
                        { return spine[root_index].count_elems_in_range(low_key_, high_key_, spine); }

                        size_t get_root_index () const { return root_index; }
                        size_t capacity       () const { return spine.get_capacity(); }
                        size_t size           () const { return spine.get_size(); }

                        void graphviz_dump (const std::string &tree_name = "tree");

                        int distance (const key_type &low_key_, 
                                      const key_type &high_key_)
                        { 
                                if (root_index != INVALID && low_key_ < high_key_)
                                        return spine[root_index].distance(low_key_, high_key_, spine);
                                else
                                        return 0;
                        }
        };

//===================================================~~~DECLARATIONS~~~====================================================================

        template <typename T, typename key_type>
        void avl_t<T, key_type>::insert (const T &data_, const key_type &key_)
        {
                if (root_index == INVALID) {
                        // root_index = spine.insert(node_t(data_, key_, spine.get_size(), spine));
                        root_index = spine.insert(node_t(data_, key_, spine.get_size()));
                        return;
                }
                if (spine.get_size() >= spine.get_capacity() - 1) {
                        spine.reserve(spine.get_capacity() * CAPACITY_RESERVE_FACTOR);
                }
                spine[root_index].insert(data_, key_, spine);
                root_index = spine[root_index].rebalance(spine);
        }

        template <typename T, typename key_type>
        void avl_t<T, key_type>::graphviz_dump (const std::string &tree_name)
        {
                std::ofstream dot_file(tree_name + ".dot");

                digraph_t G {};
                dot_file << dynamic_format(digraph_atr_sample, "G", G.dpi, G.splines);

                spine[root_index].graphviz_branch(dot_file, spine);
                spine[root_index].graphviz_tie_branch(dot_file, spine);

                dot_file << "\n}";
                                
                dot_file.close();
        }
}