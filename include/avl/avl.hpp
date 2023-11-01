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
                        size_t root_index = INVALID;

                public:
                        avl_t (size_t capacity_) : spine {capacity_} {};
                        avl_t () : spine {DEFAULT_SPINE_SIZE} {};

                        void insert (const T &elem_, const key_type &key_) 
                        {
                                if (root_index == INVALID) {
                                        root_index = spine.insert(node_t(elem_, key_, spine.get_size()));
                                        return;
                                }
                                spine[root_index].insert(elem_, key_, spine);
                        }

                        size_t get_root_index () const { return root_index; }
                        size_t capacity       () const { return spine.get_capacity(); }
                        size_t size           () const { return spine.get_size(); }

                        // void graphviz_dump (const std::string &tree_name) const;
                        void graphviz_dump (const std::string &tree_name = "tree")
                        {
                                std::ofstream dot_file(tree_name + ".dot");

                                digraph_t G {};
                                dot_file << dynamic_format(digraph_atr_sample, "G", G.dpi, G.splines);

                                spine[root_index].graphviz_family(dot_file, spine);
                                spine[root_index].graphviz_tie_family(dot_file, spine);

                                dot_file << "\n}";
                                
                                dot_file.close();
                        }
        };

        // inline void avl_t<T>::graphviz_dump (const std::string &tree_name) const
        // {
        //         std::ofstream dot_file(tree_name + ".dot");

        //         digraph_t G {};
        //         dot_file << std::format(digraph_atr_sample, "G", G.dpi, G.splines);
                
        //         spine[root_index].graphviz_family(dot_file, spine);
        //         spine[root_index].graphviz_tie_family(dot_file, spine);

        //         dot_file << "\n}";
                
        //         dot_file.close();
        // }
}