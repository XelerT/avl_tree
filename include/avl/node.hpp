#pragma once

#include <memory>
// #include <format>

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
                        size_t parent_index      = INVALID;
                        int    branch_height     = 0;
                        int    size              = NODE_HEIGHT;

                        T        data {};
                        key_type key  {};

                        T max_elem {};

                        graph_node_atr_t atr {};

                        int insert_in_child (node_t &node_, size_t &child_index, spine_t<node_t> &spine_);

                        int create_insert_in_child (const T &data_, const key_type &key_, 
                                                    spine_t<node_t<T, key_type>> &spine_, 
                                                    size_t &child_index_);

                        void set_right_child_index (size_t index_) { right_child_index = index_; }
                        void set_left_child_index  (size_t index_) { left_child_index  = index_; }
                        void set_size              (int size_)     { size              = size_;  }

                        void set_rotated_branch_height (size_t &child_index, size_t second_child_index, 
                                                        size_t old_child_index, spine_t<node_t> &spine_);
                        void change_rotated_sizes      (size_t old_child_index, spine_t<node_t> &spine_);
                        
                        void update_height (spine_t<node_t> &spine_);
                        void change_rotated_heights (size_t old_child_index, 
                                                     size_t second_child_index, spine_t<node_t> &spine_);
                        size_t right_rotate (spine_t<node_t<T, key_type>> &spine_);
                        size_t left_rotate  (spine_t<node_t<T, key_type>> &spine_);

                        void calculate_branch_height (spine_t<node_t> &spine_);

                        int get_right_left_branches_delta_height (spine_t<node_t<T, key_type>> &spine_);

                        void set_branch_height (int branch_height_) { branch_height = branch_height_; } 
                        int count_elems_in_branch (spine_t<node_t> &spine_);

                        int calculate_rank_rec (spine_t<node_t> &spine_);
                public:
                        node_t (const T &data_, const key_type &key_, const size_t index_) 
                                :
                                index(index_), data(data_), key(key_) {};
                        node_t (const T &data_, const key_type &key_, const size_t index_, 
                                const size_t parent_index_) 
                                :
                                index(index_), parent_index(parent_index_), data(data_), key(key_) {};
                        node_t () = default;

                        size_t rebalance (spine_t<node_t<T, key_type>> &spine_);
                        size_t insert (node_t &node_, spine_t<node_t<T, key_type>> &spine_);
                        size_t insert (const T &data_, const key_type &key_, spine_t<node_t<T, key_type>> &spine_);

                        T get_data (const key_type &key_, const T &invalid_val, spine_t<node_t<T, key_type>> &spine_);
                        int count_elems_in_range (const key_type &low_key_, const key_type &high_key_, spine_t<node_t> &spine_);
                        int distance (const key_type &low_key_, const key_type &high_key_, spine_t<node_t> &spine_);

                        auto get_right_child_index () const { return right_child_index; }
                        auto get_left_child_index  () const { return left_child_index;  }
                        auto get_branch_height     () const { return branch_height;     }
                        auto get_size              () const { return size;              }

                        int calculate_rank (spine_t<node_t> &spine_);
  
                        size_t lower_bound (const key_type &bound_key_,  spine_t<node_t> &spine_);
                        size_t higher_bound (const key_type &bound_key_, spine_t<node_t> &spine_);

                        T get_data    () const { return data; }
                        key_type get_key () const { return key;  }

                        void graphviz_branch (std::ofstream &dot_file, spine_t<node_t<T, key_type>> &spine_);
                        void graphviz_tie_branch (std::ofstream &dot_file, spine_t<node_t<T, key_type>> &spine_);
        };

//===================================================~~~DECLARATIONS~~~====================================================================

//---------------------------------------------------~~~~~~Private~~~~~--------------------------------------------------------------------

        template <typename T, typename key_type>
        int node_t<T, key_type>::insert_in_child (node_t &node_, size_t &child_index, spine_t<node_t> &spine_)
        {
                node_.parent_index = index;
                if (child_index != INVALID)
                        spine_[child_index].insert(node_, spine_);
                else
                        child_index = spine_.insert(node_);
                return NODE_HEIGHT;
        }

        template <typename T, typename key_type>
        int node_t<T, key_type>::create_insert_in_child (const T &data_, const key_type &key_, 
                                                         spine_t<node_t> &spine_,
                                                         size_t &child_index_)
        {
                auto new_node = node_t(data_, key_, spine_.get_size(), index);
                if (child_index_ != INVALID)
                        spine_[child_index_].insert(new_node, spine_);
                else
                        child_index_ = spine_.insert(new_node);

                return NODE_HEIGHT;
        }

        template <typename T, typename key_type>
        void node_t<T, key_type>::set_rotated_branch_height (size_t &child_index, size_t second_child_index,
                                                             size_t old_child_index, spine_t<node_t> &spine_)
        {
                if (second_child_index != INVALID && child_index != INVALID &&
                    spine_[child_index].get_branch_height() >= spine_[second_child_index].get_branch_height()) {
                        branch_height = spine_[child_index].branch_height + NODE_HEIGHT;
                    }
                if (spine_[old_child_index].get_branch_height() <= branch_height) {
                        spine_[old_child_index].set_branch_height(branch_height);
                }
        }

        template <typename T, typename key_type>
        void node_t<T, key_type>::change_rotated_sizes (size_t old_child_index, spine_t<node_t> &spine_)
        {
                spine_[old_child_index].size = size;
                if (right_child_index != INVALID && left_child_index != INVALID)
                        size = spine_[right_child_index].size + spine_[left_child_index].size;
                else if (right_child_index != INVALID && left_child_index == INVALID)
                        size = spine_[right_child_index].size;
                else if (right_child_index == INVALID && left_child_index != INVALID)
                        size = spine_[left_child_index].size;
                else 
                        size = 0;
                size += NODE_HEIGHT;
        }

        template <typename T, typename key_type>
        void node_t<T, key_type>::update_height (spine_t<node_t> &spine_)
        {
                if (right_child_index != INVALID && left_child_index != INVALID)
                        branch_height = max(spine_[right_child_index].branch_height, 
                                            spine_[left_child_index].branch_height) + NODE_HEIGHT;
                else if (right_child_index != INVALID)
                        branch_height = spine_[right_child_index].branch_height + NODE_HEIGHT;
                else if (left_child_index != INVALID)
                        branch_height = spine_[left_child_index].branch_height + NODE_HEIGHT;
                else    
                        branch_height = 0;
        }

        template <typename T, typename key_type>
        void node_t<T, key_type>::change_rotated_heights (size_t old_child_index, 
                                                          size_t second_child_index, spine_t<node_t> &spine_)
        {
                update_height(spine_);
                spine_[second_child_index].update_height(spine_);
                spine_[old_child_index].update_height(spine_);
        }
        
        template <typename T, typename key_type>
        size_t node_t<T, key_type>::right_rotate (spine_t<node_t> &spine_)
        {
                auto old_left_child_index = left_child_index;
                
                left_child_index = spine_[left_child_index].get_right_child_index();
                spine_[old_left_child_index].set_right_child_index(index);

                spine_[old_left_child_index].parent_index = parent_index;
                parent_index = old_left_child_index;
                if (left_child_index != INVALID)
                        spine_[left_child_index].parent_index = index;

                change_rotated_sizes(old_left_child_index, spine_);
                change_rotated_heights(old_left_child_index, 
                                       spine_[old_left_child_index].right_child_index, spine_);
                
                return old_left_child_index; 
        }

        template <typename T, typename key_type>
        size_t node_t<T, key_type>::left_rotate (spine_t<node_t> &spine_)
        {
                auto old_right_child_index = right_child_index;

                right_child_index = spine_[right_child_index].get_left_child_index();
                spine_[old_right_child_index].set_left_child_index(index);
                
                spine_[old_right_child_index].parent_index = parent_index;
                parent_index = old_right_child_index;
                if (right_child_index != INVALID)
                        spine_[right_child_index].parent_index = index;

                change_rotated_sizes(old_right_child_index, spine_);
                change_rotated_heights(old_right_child_index,
                                       spine_[old_right_child_index].left_child_index, spine_);

                return old_right_child_index;
        }

        template <typename T, typename key_type>
        int node_t<T, key_type>::get_right_left_branches_delta_height (spine_t<node_t> &spine_)
        {                                
                if (right_child_index != INVALID && left_child_index != INVALID)
                        return spine_[right_child_index].get_branch_height() -
                               spine_[left_child_index].get_branch_height();
                else if (right_child_index == INVALID && left_child_index != INVALID)
                        return -spine_[left_child_index].get_branch_height() - NODE_HEIGHT;
                else if (right_child_index != INVALID)
                        return spine_[right_child_index].get_branch_height() + NODE_HEIGHT;
                                
                return NODE_HEIGHT;
        }

        template <typename T, typename key_type>
        void node_t<T, key_type>::calculate_branch_height (spine_t<node_t> &spine_)
        {
                if (right_child_index != INVALID && left_child_index != INVALID)
                        if (spine_[right_child_index].get_branch_height() < spine_[left_child_index].get_branch_height())
                                set_branch_height(spine_[left_child_index].get_branch_height() + NODE_HEIGHT);
                        else
                                set_branch_height(spine_[right_child_index].get_branch_height() + NODE_HEIGHT);
                else if (right_child_index != INVALID)
                        set_branch_height(spine_[right_child_index].get_branch_height() + NODE_HEIGHT);
                else if (left_child_index != INVALID)
                        set_branch_height(spine_[left_child_index].get_branch_height() + NODE_HEIGHT);
                else 
                        set_branch_height(0);
        }

        template <typename T, typename key_type>
        int node_t<T, key_type>::count_elems_in_branch (spine_t<node_t> &spine_)
        {
                int n_nodes = 0;
                
                if (left_child_index != INVALID)
                        n_nodes += spine_[left_child_index].count_elems_in_branch(spine_);
                if (right_child_index != INVALID)
                        n_nodes += spine_[right_child_index].count_elems_in_branch(spine_);
                
                return n_nodes;
        }

        template <typename T, typename key_type>
        int node_t<T, key_type>::calculate_rank_rec (spine_t<node_t> &spine_)
        {
                int rank = 0;

                if (parent_index != INVALID) {
                        auto parent_left  = spine_[parent_index].get_left_child_index();
                        auto parent_right = spine_[parent_index].get_right_child_index();

                        if (index == parent_right) {
                                if (parent_left != INVALID)
                                        rank += spine_[parent_left].get_size();
                                rank += NODE_HEIGHT;
                        } 
                        rank += spine_[parent_index].calculate_rank_rec(spine_);
                }
                return rank;
        }

//---------------------------------------------------~~~~~~Public~~~~~~--------------------------------------------------------------------

        template <typename T, typename key_type>
        size_t node_t<T, key_type>::rebalance (spine_t<node_t> &spine_)
        {
                auto delta = get_right_left_branches_delta_height(spine_);

                if (delta > NODE_HEIGHT) {
                        if (spine_[right_child_index].get_right_left_branches_delta_height(spine_) < 0)
                                right_child_index = spine_[right_child_index].right_rotate(spine_);

                        return left_rotate(spine_);
                } else if (delta < -NODE_HEIGHT) {                
                        if (spine_[left_child_index].get_right_left_branches_delta_height(spine_) > 0)
                                left_child_index = spine_[left_child_index].left_rotate(spine_);

                        return right_rotate(spine_);
                }       
                calculate_branch_height(spine_);

                return index;
        }

        template <typename T, typename key_type>
        size_t node_t<T, key_type>::insert (node_t &node_, spine_t<node_t> &spine_)
        {
                if (node_.get_key() < key) {
                        branch_height = insert_in_child(node_, left_child_index, spine_) +
                                        NODE_HEIGHT;
                        left_child_index = spine_[left_child_index].rebalance(spine_);
                        size++;
                } else if (node_.get_key() != key) {
                        branch_height = insert_in_child(node_, right_child_index, spine_) +
                                        NODE_HEIGHT;
                        right_child_index = spine_[right_child_index].rebalance(spine_);
                        size++;
                } else if (node_.key == key) {
                        return 0;
                }

                return branch_height;
        }

        template <typename T, typename key_type>
        size_t node_t<T, key_type>::insert (const T &data_, const key_type &key_, spine_t<node_t> &spine_)
        {
                if (key_ < key) {
                        branch_height = create_insert_in_child(data_, key_, spine_, left_child_index) +
                                        NODE_HEIGHT;
                        left_child_index = spine_[left_child_index].rebalance(spine_);
                        size++;
                } else if (key_ != key) {
                        branch_height = create_insert_in_child(data_, key_, spine_, right_child_index) +
                                        NODE_HEIGHT;
                        right_child_index = spine_[right_child_index].rebalance(spine_);
                        size++;
                } else if (key_ == key) {
                        return 0;
                }
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
        int node_t<T, key_type>::calculate_rank (spine_t<node_t> &spine_)
        {
                int rank = NODE_HEIGHT;
                if (left_child_index != INVALID)
                        rank += spine_[left_child_index].get_size();

                return rank + calculate_rank_rec(spine_);
        }

        template <typename T, typename key_type>
        int node_t<T, key_type>::count_elems_in_range (const key_type &low_key_, 
                                                       const key_type &high_key_, spine_t<node_t> &spine_)
        {
                int n_nodes = 0;

                if (low_key_ > key && right_child_index != INVALID)
                        n_nodes += spine_[right_child_index].count_elems_in_range(low_key_, high_key_, spine_);
                else if (high_key_ < key && left_child_index != INVALID)
                        n_nodes += spine_[left_child_index].count_elems_in_range(low_key_, high_key_, spine_);
                else if (low_key_ < key && key < high_key_) {
                        if (right_child_index != INVALID)
                                n_nodes += spine_[right_child_index].count_elems_in_range(low_key_, high_key_, spine_);
                        if (left_child_index != INVALID)
                                n_nodes += spine_[left_child_index].count_elems_in_range(low_key_, high_key_, spine_);
                        n_nodes++;
                } else if (low_key_ == key) {
                        if (right_child_index != INVALID)
                                n_nodes += NODE_HEIGHT + spine_[right_child_index].count_elems_in_range(low_key_, 
                                                                                                        high_key_,
                                                                                                        spine_);
                } else if (high_key_ == key) {
                        if (left_child_index != INVALID)
                                n_nodes += NODE_HEIGHT + spine_[left_child_index].count_elems_in_range(low_key_,
                                                                                                       high_key_,
                                                                                                       spine_);
                }
                return n_nodes;
        }

        template <typename T, typename key_type>
        size_t node_t<T, key_type>::lower_bound (const key_type &bound_key_, spine_t<node_t> &spine_)
        {
                auto bound = index;
                if (key < bound_key_ && right_child_index != INVALID) {
                        bound = spine_[right_child_index].lower_bound(bound_key_, spine_);
                } else if (left_child_index != INVALID) {
                        if (key > bound_key_) {
                                bound = spine_[left_child_index].lower_bound(bound_key_, spine_);
                                if (bound != INVALID && spine_[bound].key < bound_key_)
                                        bound = index;
                        }
                }
                if (bound != INVALID && spine_[bound].key < bound_key_)
                        return INVALID;
                if (bound == INVALID && key > bound_key_)
                        return index;
                return bound;
        }

        template <typename T, typename key_type>
        size_t node_t<T, key_type>::higher_bound (const key_type &bound_key_, spine_t<node_t> &spine_)
        {
                auto bound = index;
                if (key > bound_key_ && left_child_index != INVALID) {
                        bound = spine_[left_child_index].higher_bound(bound_key_, spine_);
                } else if (right_child_index != INVALID) {
                        if (key < bound_key_) {
                                bound = spine_[right_child_index].higher_bound(bound_key_, spine_);
                                if (spine_[bound].key > bound_key_)
                                        bound = index;
                        }
                }
                return bound;
        }

        template <typename T, typename key_type>
        int node_t<T, key_type>::distance (const key_type &low_key_, 
                                           const key_type &high_key_, spine_t<node_t> &spine_)
        {
                auto lower_bound_index  = lower_bound(low_key_, spine_);
                auto higher_bound_index = higher_bound(high_key_, spine_);

                if (lower_bound_index == INVALID || higher_bound_index == INVALID)
                        return 0;

                auto lower_rank  = spine_[lower_bound_index].calculate_rank(spine_); 
                auto higher_rank = spine_[higher_bound_index].calculate_rank(spine_);

                if (lower_rank == higher_rank)
                        return NODE_HEIGHT;

                auto distance = higher_rank - lower_rank + 1; 

                return distance; 
        }        

        template <typename T, typename key_type>
        void node_t<T, key_type>::graphviz_branch (std::ofstream &dot_file, spine_t<node_t> &spine_)
        {
                if (left_child_index != INVALID)
                        spine_[left_child_index].graphviz_branch(dot_file, spine_);
                if (right_child_index != INVALID)
                        spine_[right_child_index].graphviz_branch(dot_file, spine_);

                dot_file << dynamic_format(node_atr_sample, static_cast<const void* const>(this), atr.shape, atr.style, atr.height,
                                           atr.width, atr.fixedsize, atr.fillcolor, atr.fontsize,
                                           atr.penwidth);
                dot_file << dynamic_format(node_data_key_sample, static_cast<const void* const>(this), data, key, parent_index, branch_height);
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