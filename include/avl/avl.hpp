#pragma once

#include <string>
#include <fstream>
#include <format>

#include "node.hpp"
#include "spin.hpp"

#include "graphviz.hpp"

namespace binary_trees
{
        using namespace graphviz;

        template <typename T, typename key_type = int>
        class avl_t
        {
                private:
                        spin_t<node_t<T>> spin;
                        size_t root_index = INVALID;

                public:
                        avl_t (size_t capacity_) : spin {capacity_} {};
                        avl_t () : spin {DEFAULT_SPIN_SIZE} {};

                        void insert (const T &elem_, const key_type &key_) 
                        {
                                if (root_index == INVALID) {
                                        root_index = spin.insert(node_t(elem_, key_));
                                        return;
                                }
                                spin[root_index].insert(elem_, key_, spin);
                        }

                        size_t get_root_index () const { return root_index; }
                        size_t capacity       () const { return spin.get_capacity(); }
                        size_t size           () const { return spin.get_size(); }

                        // void graphviz_dump (const std::string &tree_name) const;
                        void graphviz_dump (const std::string &tree_name = "tree")
                        {
                                std::ofstream dot_file(tree_name + ".dot");

                                digraph_t G {};
                                dot_file << dynamic_format(digraph_atr_sample, "G", G.dpi, G.splines);

                                spin[root_index].graphviz_family(dot_file, spin);
                                spin[root_index].graphviz_tie_family(dot_file, spin);

                                dot_file << "\n}";
                                
                                dot_file.close();
                        }
        };

        // inline void avl_t<T>::graphviz_dump (const std::string &tree_name) const
        // {
        //         std::ofstream dot_file(tree_name + ".dot");

        //         digraph_t G {};
        //         dot_file << std::format(digraph_atr_sample, "G", G.dpi, G.splines);
                
        //         spin[root_index].graphviz_family(dot_file, spin);
        //         spin[root_index].graphviz_tie_family(dot_file, spin);

        //         dot_file << "\n}";
                
        //         dot_file.close();
        // }
}