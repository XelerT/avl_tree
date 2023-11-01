#pragma once

#include <format>

#include "spin.hpp"
#include "utils.hpp"

#include "graphviz.hpp"

namespace binary_trees
{
        using namespace graphviz;
        
        template <typename T, typename key_type = int>
        class node_t 
        {
                private:
                        size_t right_child_index = INVALID;
                        size_t left_child_index  = INVALID;

                        T        elem {};
                        key_type key  {};

                        graph_node_atr_t atr {};

                        void insert_in_child (const node_t &node_, size_t &child_index, spin_t<node_t> &spin_)
                        {
                                if (child_index != INVALID)
                                        spin_[child_index].insert(node_, spin_);
                                else
                                        child_index = spin_.insert(node_);
                        }

                        void create_insert_in_child (const T &elem_, const key_type &key_, 
                                                     spin_t<node_t> &spin_, size_t &child_index_)
                        {
                                if (child_index_ != INVALID)
                                        spin_[child_index_].insert(node_t(elem_, key_), spin_);
                                else
                                        child_index_ = spin_.insert(node_t(elem_, key_));
                        }

                public:
                        node_t (const T &elem_, const key_type &key_) 
                                :
                                elem(elem_), key(key_) {};
                        node_t () = default;

                        void insert (const node_t &node_, spin_t<node_t> &spin_)
                        {
                                if (node_.get_key() <= key)
                                        insert_in_child(node_, left_child_index, spin_);
                                else
                                        insert_in_child(node_, right_child_index, spin_);
                        }

                        void insert (const T &elem_, const key_type &key_, spin_t<node_t> &spin_)
                        {
                                if (key_ <= key)
                                        create_insert_in_child(elem_, key_, spin_, left_child_index);
                                else
                                        create_insert_in_child(elem_, key_, spin_, right_child_index);
                        }

                        size_t get_right_child_index () const { return right_child_index; }
                        size_t get_left_child_index  () const { return left_child_index;  }

                        T get_element    () const { return elem; }
                        key_type get_key () const { return key;  }

                        // void graphviz_family     (std::ofstream &dot_file, spin_t<node_t> &spin_) const;
                        // void graphviz_tie_family (std::ofstream &dot_file, spin_t<node_t> &spin_) const;

                        void graphviz_family (std::ofstream &dot_file, spin_t<node_t> &spin_)
                        {
                                if (left_child_index != INVALID)
                                        spin_[left_child_index].graphviz_family(dot_file, spin_);
                                if (right_child_index != INVALID)
                                        spin_[right_child_index].graphviz_family(dot_file, spin_);

                                dot_file << dynamic_format(node_atr_sample, static_cast<void*>(this), atr.shape, atr.style, atr.height,
                                                        atr.width, atr.fixedsize, atr.fillcolor, atr.fontsize,
                                                        atr.penwidth);
                                dot_file << dynamic_format(node_elem_key_sample, static_cast<void*>(this), elem, key);
                        }

                        void graphviz_tie_family (std::ofstream &dot_file, spin_t<node_t> &spin_)
                        {
                                if (left_child_index != INVALID)
                                        spin_[left_child_index].graphviz_tie_family(dot_file, spin_);
                                if (right_child_index != INVALID)
                                        spin_[right_child_index].graphviz_tie_family(dot_file, spin_);

                                if (left_child_index != INVALID)
                                        dot_file << dynamic_format(nodes_tie_atr, static_cast<void*>(this), static_cast<void*>(&spin_[left_child_index]),
                                                                "black", atr.arrowsize, atr.penwidth);
                                if (right_child_index != INVALID)
                                        dot_file << dynamic_format(nodes_tie_atr, static_cast<void*>(this), static_cast<void*>(&spin_[right_child_index]),
                                                                "red", atr.arrowsize, atr.penwidth);
                        }
        };

        // inline void node_t<T>::graphviz_family (std::ofstream &dot_file, const spin_t<node_t<T>> &spin_) const
        // {
        //         if (left_child_index != INVALID)
        //                 spin_[left_child_index].graphviz_family(dot_file, spin_);
        //         if (right_child_index != INVALID)
        //                 spin_[right_child_index].graphviz_family(dot_file, spin_);

        //         dot_file << std::format(node_atr_sample, this, atr.shape, atr.style, atr.height,
        //                                 atr.width, atr.fixedsize, atr.fillcolor, atr.fontsize,
        //                                 atr.penwidth);

        //         dot_file << std::format(node_elem_key_sample, node, elem, key);
        // }

        // inline void node_t<T>::graphviz_tie_family (std::ofstream &dot_file, const spin_t<node_t<T>> &spin_) const
        // {
        //         if (left_child_index != INVALID)
        //                 spin_[left_child_index].graphviz_tie_family(dot_file, spin_);
        //         if (right_child_index != INVALID)
        //                 spin_[right_child_index].graphviz_tie_family(dot_file, spin_);

        //         if (left_child_index != INVALID)
        //                 dot_file << std::format(nodes_tie_atr, this, &spin_[left_child_index],
        //                                         "black", atr.arrowsize, atr.penwidth);
        //         if (right_child_index != INVALID)
        //                 dot_file << std::format(nodes_tie_atr, this, &spin_[right_child_index],
        //                                         "red", atr.arrowsize, atr.penwidth);
        // }
}