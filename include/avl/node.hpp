#pragma once

#include <format>

#include "spine.hpp"
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
                        size_t index             = INVALID;
                        int    branch_height     = 0;

                        T        elem {};
                        key_type key  {};

                        graph_node_atr_t atr {};

                        int insert_in_child (const node_t &node_, size_t &child_index, spine_t<node_t> &spine_)
                        {
                                if (child_index != INVALID)
                                        spine_[child_index].insert(node_, spine_);
                                else
                                        child_index = spine_.insert(node_);

                                return NODE_HEIGHT;
                        }

                        int create_insert_in_child (const T &elem_, const key_type &key_, 
                                                    spine_t<node_t> &spine_, size_t &child_index_)
                        {
                                if (child_index_ != INVALID)
                                        spine_[child_index_].insert(node_t(elem_, key_, spine_.get_size()), spine_);
                                else
                                        child_index_ = spine_.insert(node_t(elem_, key_, spine_.get_size()));

                                return NODE_HEIGHT;
                        }

                        void set_right_child_index (size_t index_) { right_child_index = index_; }
                        void set_left_child_index  (size_t index_) { left_child_index  = index_; }

                        size_t right_rotate (spine_t<node_t> &spine_)
                        {
                                auto old_left_child_index = left_child_index;
                                
                                left_child_index = spine_[left_child_index].get_right_child_index();
                                spine_[old_left_child_index].set_right_child_index(index);

                                return old_left_child_index; 
                        }

                        size_t left_rotate (spine_t<node_t> &spine_)
                        {
                                auto old_right_child_index = right_child_index;
                                
                                right_child_index = spine_[right_child_index].get_left_child_index();
                                spine_[old_right_child_index].set_left_child_index(index);

                                return old_right_child_index;
                        }

                        int get_right_left_branches_delta_height (spine_t<node_t> &spine_)
                        {                                
                                if (right_child_index != INVALID && left_child_index != INVALID)       
                                        return spine_[right_child_index].get_branch_height() -
                                               spine_[left_child_index].get_branch_height();
                                else if (right_child_index == INVALID && left_child_index != INVALID)
                                        return -spine_[left_child_index].get_branch_height();
                                else if (left_child_index == INVALID && right_child_index != INVALID)
                                        return spine_[right_child_index].get_branch_height();
                                
                                return NODE_HEIGHT;
                        }

                        size_t rebalance (spine_t<node_t> &spine_)
                        {
                                auto delta = get_right_left_branches_delta_height(spine_);
                                
                                if (delta > NODE_HEIGHT) {
                                        auto right_right_child_index = spine_[right_child_index].get_right_child_index();
                                        if (right_right_child_index == INVALID ||
                                            spine_[right_right_child_index].get_branch_height()) {
                                               right_child_index = spine_[right_child_index].right_rotate(spine_);
                                        }

                                        return left_rotate(spine_);
                                } else if (delta < -NODE_HEIGHT) {
                                        auto left_left_child_index = spine_[left_child_index].get_left_child_index();
                                        if (left_left_child_index == INVALID ||
                                            spine_[left_left_child_index].get_branch_height()) {
                                               left_child_index = spine_[left_child_index].left_rotate(spine_);
                                        }
                                        
                                        return right_rotate(spine_);
                                }
                                
                                return index;
                        }

                public:
                        node_t (const T &elem_, const key_type &key_, const size_t index_) 
                                :
                                index(index_), elem(elem_), key(key_) {};
                        node_t () = default;

                        size_t insert (const node_t &node_, spine_t<node_t> &spine_)
                        {
                                if (node_.get_key() <= key) {
                                        branch_height = insert_in_child(node_, left_child_index, spine_) +
                                                        NODE_HEIGHT;
                                        left_child_index = spine_[left_child_index].rebalance(spine_);
                                } else {
                                        branch_height = insert_in_child(node_, right_child_index, spine_) +
                                                        NODE_HEIGHT;
                                        right_child_index = spine_[right_child_index].rebalance(spine_);
                                }
                                
                                return branch_height;
                        }

                        size_t insert (const T &elem_, const key_type &key_, spine_t<node_t> &spine_)
                        {
                                if (key_ <= key) {
                                        branch_height = create_insert_in_child(elem_, key_, spine_, left_child_index) +
                                                        NODE_HEIGHT;
                                        left_child_index = spine_[left_child_index].rebalance(spine_);
                                } else {
                                        branch_height = create_insert_in_child(elem_, key_, spine_, right_child_index) +
                                                        NODE_HEIGHT;
                                        right_child_index = spine_[right_child_index].rebalance(spine_);
                                }

                                return branch_height;
                        }

                        auto get_right_child_index () const { return right_child_index; }
                        auto get_left_child_index  () const { return left_child_index;  }
                        auto get_branch_height     () const { return branch_height;     }

                        T get_element    () const { return elem; }
                        key_type get_key () const { return key;  }

                        // void graphviz_family     (std::ofstream &dot_file, spine_t<node_t> &spine_) const;
                        // void graphviz_tie_family (std::ofstream &dot_file, spine_t<node_t> &spine_) const;

                        void graphviz_family (std::ofstream &dot_file, spine_t<node_t> &spine_)
                        {
                                if (left_child_index != INVALID)
                                        spine_[left_child_index].graphviz_family(dot_file, spine_);
                                if (right_child_index != INVALID)
                                        spine_[right_child_index].graphviz_family(dot_file, spine_);

                                dot_file << dynamic_format(node_atr_sample, static_cast<void*>(this), atr.shape, atr.style, atr.height,
                                                           atr.width, atr.fixedsize, atr.fillcolor, atr.fontsize,
                                                           atr.penwidth);
                                dot_file << dynamic_format(node_elem_key_sample, static_cast<void*>(this), elem, key);
                        }

                        void graphviz_tie_family (std::ofstream &dot_file, spine_t<node_t> &spine_)
                        {
                                if (left_child_index != INVALID)
                                        spine_[left_child_index].graphviz_tie_family(dot_file, spine_);
                                if (right_child_index != INVALID)
                                        spine_[right_child_index].graphviz_tie_family(dot_file, spine_);

                                if (left_child_index != INVALID)
                                        dot_file << dynamic_format(nodes_tie_atr, static_cast<void*>(this), static_cast<void*>(&spine_[left_child_index]),
                                                                "black", atr.arrowsize, atr.penwidth);
                                if (right_child_index != INVALID)
                                        dot_file << dynamic_format(nodes_tie_atr, static_cast<void*>(this), static_cast<void*>(&spine_[right_child_index]),
                                                                "red", atr.arrowsize, atr.penwidth);
                        }
        };

        // inline void node_t<T>::graphviz_family (std::ofstream &dot_file, const spine_t<node_t<T>> &spine_) const
        // {
        //         if (left_child_index != INVALID)
        //                 spine_[left_child_index].graphviz_family(dot_file, spine_);
        //         if (right_child_index != INVALID)
        //                 spine_[right_child_index].graphviz_family(dot_file, spine_);

        //         dot_file << std::format(node_atr_sample, this, atr.shape, atr.style, atr.height,
        //                                 atr.width, atr.fixedsize, atr.fillcolor, atr.fontsize,
        //                                 atr.penwidth);

        //         dot_file << std::format(node_elem_key_sample, node, elem, key);
        // }

        // inline void node_t<T>::graphviz_tie_family (std::ofstream &dot_file, const spine_t<node_t<T>> &spine_) const
        // {
        //         if (left_child_index != INVALID)
        //                 spine_[left_child_index].graphviz_tie_family(dot_file, spine_);
        //         if (right_child_index != INVALID)
        //                 spine_[right_child_index].graphviz_tie_family(dot_file, spine_);

        //         if (left_child_index != INVALID)
        //                 dot_file << std::format(nodes_tie_atr, this, &spine_[left_child_index],
        //                                         "black", atr.arrowsize, atr.penwidth);
        //         if (right_child_index != INVALID)
        //                 dot_file << std::format(nodes_tie_atr, this, &spine_[right_child_index],
        //                                         "red", atr.arrowsize, atr.penwidth);
        // }
}