#pragma once

#include "spin.hpp"
#include "utils.hpp"

namespace binary_trees
{
        template <typename T, typename key_type = int> 
        class node_t 
        {
                private:
                        size_t right_child_index = INVALID;
                        size_t left_child_index  = INVALID;

                        T        elem {};
                        key_type key  {};

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
        };
}