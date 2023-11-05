#pragma once

#include <format>

#include "spine.hpp"
#include "utils.hpp"

#include "graphviz/graphviz.hpp"

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

                        T        data {};
                        key_type key  {};

                        graph_node_atr_t atr {};

                        int insert_in_child (const node_t &node_, size_t &child_index, spine_t<node_t> &spine_);

                        int create_insert_in_child (const T &data_, const key_type &key_, 
                                                    spine_t<node_t<T, key_type>> &spine_, 
                                                    size_t &child_index_);

                        void set_right_child_index (size_t index_) { right_child_index = index_; }
                        void set_left_child_index  (size_t index_) { left_child_index  = index_; }

                        void set_rotated_branch_height (size_t &child_index, size_t second_child_index, 
                                                        size_t old_child_index, spine_t<node_t> &spine_);
                        size_t right_rotate (spine_t<node_t<T, key_type>> &spine_);
                        size_t left_rotate  (spine_t<node_t<T, key_type>> &spine_);

                        void calculate_branch_height (spine_t<node_t> &spine_);

                        int get_right_left_branches_delta_height (spine_t<node_t<T, key_type>> &spine_);

                        void set_branch_height (int branch_height_) { branch_height = branch_height_; } 

                public:
                        node_t (const T &data_, const key_type &key_, const size_t index_) 
                                :
                                index(index_), data(data_), key(key_) {};
                        node_t () = default;

                        size_t rebalance (spine_t<node_t<T, key_type>> &spine_);
                        size_t insert (const node_t &node_, spine_t<node_t<T, key_type>> &spine_);
                        size_t insert (const T &data_, const key_type &key_, spine_t<node_t<T, key_type>> &spine_);

                        T get_data (const key_type &key_, const T &invalid_val, spine_t<node_t<T, key_type>> &spine_);
                        int count_elems_in_range (const key_type &low_key_, const key_type &high_key_, spine_t<node_t> &spine_); 


                        auto get_right_child_index () const { return right_child_index; }
                        auto get_left_child_index  () const { return left_child_index;  }
                        auto get_branch_height     () const { return branch_height;     }

                        T get_data    () const { return data; }
                        key_type get_key () const { return key;  }

                        void graphviz_branch (std::ofstream &dot_file, spine_t<node_t<T, key_type>> &spine_);
                        void graphviz_tie_branch (std::ofstream &dot_file, spine_t<node_t<T, key_type>> &spine_);
        };

//===================================================~~~DECLARATIONS~~~====================================================================

//---------------------------------------------------~~~~~~Private~~~~~--------------------------------------------------------------------

        template <typename T, typename key_type>
        int node_t<T, key_type>::insert_in_child (const node_t &node_, size_t &child_index, spine_t<node_t> &spine_)
        {
                if (child_index != INVALID) {
                        // std::cout << "key1=" << key << "\n";
                        std::cout << spine_.get_size() << "\n"; 
                        spine_[child_index].insert(node_, spine_);
                }
                else {
                        // std::cout << "here\n";
                        // std::cout << static_cast<void*>(this)<<"=this\n";
                        child_index = spine_.insert(node_);
                        // std::cout << static_cast<void*>(this)<<"=this\n";
                        // std::cout << "child_index" << " " << child_index << "\n";
                }
                // std::cout << "key2=" << key << "\n";

                return NODE_HEIGHT;
        }

        template <typename T, typename key_type>
        int node_t<T, key_type>::create_insert_in_child (const T &data_, const key_type &key_, 
                                                         spine_t<node_t> &spine_,
                                                         size_t &child_index_)
        {
                if (child_index_ != INVALID) {
                        // std::cout << "create_insert_in_child0\n";
                        spine_[child_index_].insert(node_t(data_, key_, spine_.get_size()), spine_);
                        // std::cout << "create_insert_in_child1\n";
                } else
                        child_index_ = spine_.insert(node_t(data_, key_, spine_.get_size()));
                // std::cout << "create_insert_in_child2\n";

                return NODE_HEIGHT;
        }

        template <typename T, typename key_type>
        void node_t<T, key_type>::set_rotated_branch_height (size_t &child_index, size_t second_child_index,
                                                             size_t old_child_index, spine_t<node_t> &spine_)
        {
                if (second_child_index != INVALID && child_index != INVALID &&
                    spine_[child_index].get_branch_height() >= spine_[second_child_index].get_branch_height())
                        branch_height = spine_[child_index].branch_height + NODE_HEIGHT;
                if (spine_[old_child_index].get_branch_height() <= branch_height)
                        spine_[old_child_index].set_branch_height(branch_height + NODE_HEIGHT);
        }

        template <typename T, typename key_type>
        size_t node_t<T, key_type>::right_rotate (spine_t<node_t> &spine_)
        {
                auto old_left_child_index = left_child_index;
                
                // std::cout << left_child_index << "\n";
                left_child_index = spine_[left_child_index].get_right_child_index();
                set_rotated_branch_height(left_child_index, right_child_index, old_left_child_index, spine_);
                spine_[old_left_child_index].set_right_child_index(index);

                if (right_child_index == left_child_index)
                        set_branch_height(0);

                return old_left_child_index; 
        }

        template <typename T, typename key_type>
        size_t node_t<T, key_type>::left_rotate (spine_t<node_t> &spine_)
        {
                auto old_right_child_index = right_child_index;
                                
                right_child_index = spine_[right_child_index].get_left_child_index();
                set_rotated_branch_height(right_child_index, left_child_index, old_right_child_index, spine_);
                spine_[old_right_child_index].set_left_child_index(index);

                if (right_child_index == left_child_index)
                        set_branch_height(0);

                return old_right_child_index;
        }

        template <typename T, typename key_type>
        int node_t<T, key_type>::get_right_left_branches_delta_height (spine_t<node_t> &spine_)
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

        template <typename T, typename key_type>
        void node_t<T, key_type>::calculate_branch_height (spine_t<node_t> &spine_)
        {
                if (right_child_index != INVALID && left_child_index != INVALID)
                        if (spine_[right_child_index].get_branch_height() < spine_[left_child_index].get_branch_height())
                                set_branch_height(spine_[left_child_index].get_branch_height() + 1);
                        else
                                set_branch_height(spine_[right_child_index].get_branch_height() + 1);
                else if (right_child_index != INVALID)
                        set_branch_height(spine_[right_child_index].get_branch_height() + 1);
                else if (left_child_index != INVALID)
                        set_branch_height(spine_[left_child_index].get_branch_height() + 1);
        }

//---------------------------------------------------~~~~~~Public~~~~~~--------------------------------------------------------------------

        template <typename T, typename key_type>
        size_t node_t<T, key_type>::rebalance (spine_t<node_t> &spine_)
        {
                auto delta = get_right_left_branches_delta_height(spine_);

                if (delta > NODE_HEIGHT) {
                        if (spine_[right_child_index].get_right_left_branches_delta_height(spine_) < 0) {
                                right_child_index = spine_[right_child_index].right_rotate(spine_);
                        }
                        return left_rotate(spine_);
                } else if (delta < -NODE_HEIGHT) {                
                        if (spine_[left_child_index].get_right_left_branches_delta_height(spine_) > 0) {
                                left_child_index = spine_[left_child_index].left_rotate(spine_);
                        }                        
                        return right_rotate(spine_);
                }       
                calculate_branch_height(spine_);

                return index;
        }

        template <typename T, typename key_type>
        size_t node_t<T, key_type>::insert (const node_t &node_, spine_t<node_t> &spine_)
        {
                // std::cout << node_.get_key() << " insert data1\n";
                if (node_.get_key() < key) {
                        branch_height = insert_in_child(node_, left_child_index, spine_) +
                                        NODE_HEIGHT;
                        left_child_index = spine_[left_child_index].rebalance(spine_);
                } else if (node_.get_key() != key) {
                        branch_height = insert_in_child(node_, right_child_index, spine_) +
                                        NODE_HEIGHT;
                        right_child_index = spine_[right_child_index].rebalance(spine_);
                }
                return branch_height;
        }

        template <typename T, typename key_type>
        size_t node_t<T, key_type>::insert (const T &data_, const key_type &key_, spine_t<node_t> &spine_)
        {
                if (key_ < key) {
                        branch_height = create_insert_in_child(data_, key_, spine_, left_child_index) +
                                        NODE_HEIGHT;
                        // std::cout << "insert data2\n";
                        left_child_index = spine_[left_child_index].rebalance(spine_);
                } else if (key_ != key) {
                        branch_height = create_insert_in_child(data_, key_, spine_, right_child_index) +
                                        NODE_HEIGHT;
                        // std::cout << "insert data3\n";
                        right_child_index = spine_[right_child_index].rebalance(spine_);
                }
// std::cout << "insert data4\n";
                return branch_height;
        }

        template <typename T, typename key_type>
        T node_t<T, key_type>::get_data (const key_type &key_, const T &invalid_val_,
                                         spine_t<node_t> &spine_)
        {
                if (key == key_) {
                        return data;
                } else {
                        T found_data {invalid_val_};
                        if (key_ < key && left_child_index != INVALID)
                                found_data = spine_[left_child_index].get_data(key_, invalid_val_, spine_);

                        if (found_data != invalid_val_) 
                                return found_data;
                        
                        if (key_ > key && right_child_index != INVALID)
                                return spine_[right_child_index].get_data(key_, invalid_val_, spine_);
                }
                return invalid_val_;
        }

        template <typename T, typename key_type>
        int node_t<T, key_type>::count_elems_in_range (const key_type &low_key_, 
                                                       const key_type &high_key_, spine_t<node_t> &spine_)
        {
                int n_nodes = 0;

                if (key >= low_key_  && right_child_index != INVALID &&
                    key <= high_key_ && left_child_index != INVALID)
                        n_nodes += spine_[left_child_index].count_elems_in_range(low_key_, high_key_, spine_)
                                +  spine_[right_child_index].count_elems_in_range(low_key_, high_key_, spine_); 
                else if (key < low_key_ && right_child_index != INVALID)
                        n_nodes += spine_[right_child_index].count_elems_in_range(low_key_, high_key_, spine_);
                else if (left_child_index != INVALID) {
                        // std::cout << n_nodes << " here1\n";
                        n_nodes += spine_[left_child_index].count_elems_in_range(low_key_, high_key_, spine_);
                }
                // std::cout << n_nodes << " here2\n";
                
                if (key > low_key_ && key < high_key_)
                        n_nodes += NODE_HEIGHT;
                if (key == low_key_ && key == high_key_)
                        n_nodes += NODE_HEIGHT;
                
                // std::cout << n_nodes << " here3\n";
                return n_nodes;
        }

        template <typename T, typename key_type>
        void node_t<T, key_type>::graphviz_branch (std::ofstream &dot_file, spine_t<node_t> &spine_)
        {
                if (left_child_index != INVALID)
                        spine_[left_child_index].graphviz_branch(dot_file, spine_);
                if (right_child_index != INVALID)
                        spine_[right_child_index].graphviz_branch(dot_file, spine_);

                dot_file << dynamic_format(node_atr_sample, static_cast<void*>(this), atr.shape, atr.style, atr.height,
                                           atr.width, atr.fixedsize, atr.fillcolor, atr.fontsize,
                                           atr.penwidth);
                dot_file << dynamic_format(node_data_key_sample, static_cast<void*>(this), data, key, branch_height);
        }

        template <typename T, typename key_type>
        void node_t<T, key_type>::graphviz_tie_branch (std::ofstream &dot_file, spine_t<node_t> &spine_)
        {
                if (left_child_index != INVALID)
                        spine_[left_child_index].graphviz_tie_branch(dot_file, spine_);
                if (right_child_index != INVALID)
                        spine_[right_child_index].graphviz_tie_branch(dot_file, spine_);

                if (left_child_index != INVALID)
                        dot_file << dynamic_format(nodes_tie_atr, static_cast<void*>(this),
                                                   static_cast<void*>(&spine_[left_child_index]),
                                                   "black", atr.arrowsize, atr.penwidth);
                if (right_child_index != INVALID)
                        dot_file << dynamic_format(nodes_tie_atr, static_cast<void*>(this),
                                                   static_cast<void*>(&spine_[right_child_index]),
                                                   "red", atr.arrowsize, atr.penwidth);
        }
}