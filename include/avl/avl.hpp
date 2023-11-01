#pragma once

#include <string>
#include <fstream>
#include <format>

#include "node.hpp"
#include "spine.hpp"

#include "graphviz.hpp"

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
                        avl_t (size_t capacity_, T &invalid_val_) : spine {capacity_}, invalid_val(invalid_val_) {};
                        avl_t (T &invalid_val_) : spine {DEFAULT_SPINE_SIZE}, invalid_val(invalid_val_) {};

                        void insert (const T &data_, const key_type &key_);
                        T get_data  (const key_type &key_) { return spine[root_index].get_data(key_, invalid_val, spine); }

                        size_t get_root_index () const { return root_index; }
                        size_t capacity       () const { return spine.get_capacity(); }
                        size_t size           () const { return spine.get_size(); }

                        void graphviz_dump (const std::string &tree_name = "tree");
        };

//===================================================~~~DECLARATIONS~~~====================================================================

        template <typename T, typename key_type>
        void avl_t<T, key_type>::insert (const T &data_, const key_type &key_)
        {
                if (root_index == INVALID) {
                        root_index = spine.insert(node_t(data_, key_, spine.get_size()));
                        return;
                }
                spine[root_index].insert(data_, key_, spine);
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