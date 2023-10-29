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

                        spin_t<node_t> &spin;

                        void insert_in_child (const node_t &node_, const size_t &child_index)
                        {
                                if (child_index != INVALID)
                                        spin[child_index].insert(node_);
                                else
                                        child_index = spin.insert(node_);
                        }

                        void create_insert_in_child (const T &elem_, const key_type &key_, 
                                                     const size_t &child_index)
                        {
                                if (child_index != INVALID)
                                        spin[child_index].insert(node_t(elem_, key_));
                                else
                                        child_index = spin.insert(node_t(elem_, key_));
                        }

                public:
                        node_t (const T &elem_, const key_type &key_, const spin_t<node_t> &spin_) 
                               :
                               elem(elem_), key(key_), spin(spin_) {};
                               
                        node_t () = default;

                        void insert (const node_t &node_)
                        {
                                if (node_.get_key() <= key)
                                        insert_in_child(node_, left_child_index);
                                else
                                        insert_in_child(node_, right_child_index);
                        }

                        void insert (const T &elem_, const key_type &key_)
                        {
                                if (key_ <= key)
                                        create_insert_in_child(elem_, key_, left_child_index);
                                else
                                        create_insert_in_child(elem_, key_, right_child_index);
                        }

                        size_t get_right_child_index () const { return right_child_index; }
                        size_t get_left_child_index  () const { return left_child_index;  }

                        T get_element    () { return elem; }
                        key_type get_key () { return key;  }
        };
}