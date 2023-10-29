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

                        void insert_in_child (node_t &node_, size_t &child_index)
                        {
                                if (child_index != INVALID)
                                        spin[child_index].insert(node_);
                                else
                                        child_index = spin.insert(node_);
                        }

                        void create_insert_in_child (const T &elem_, const key_type &key_, 
                                                     spin_t<node_t> &spin_, size_t &child_index_)
                        {
                                auto node = node_t(elem_, key_, spin_);
                                if (child_index_ != INVALID)
                                        spin[child_index_].insert(node);
                                else
                                        child_index_ = spin.insert(node);
                        }

                        spin_t<node_t>& get_spin () { return spin; }

                public:
                        node_t (const T &elem_, const key_type &key_, spin_t<node_t> &spin_) 
                                :
                                elem(elem_), key(key_), spin(spin_) {};

                        node_t (node_t &node_)
                                : right_child_index(node_.get_right_child_index()),
                                  left_child_index(node_.get_left_child_index()),
                                  elem(node_.get_element()),
                                  key(node_.get_element()),
                                  spin(node_.get_spin())
                                {}; 

                        node_t () = default;

                        ~node_t () {};
                        node_t& operator= (node_t &node_)
                        {
                                return *this = node_t(node_);
                        };

                        node_t& operator= (node_t &&node_)
                        {
                                right_child_index = node_.get_right_child_index();
                                left_child_index  = node_.get_left_child_index();
                                elem              = node_.get_element();
                                key               = node_.get_element();
                                spin              = node_.get_spin();

                                return *this;
                        };
                        // node_t            (node_t &&node_) = default;

                        void insert (node_t &node_)
                        {
                                if (node_.get_key() <= key)
                                        insert_in_child(node_, left_child_index);
                                else
                                        insert_in_child(node_, right_child_index);
                        }

                        void insert (const T &elem_, const key_type &key_)
                        {
                                if (key_ <= key)
                                        create_insert_in_child(elem_, key_, spin, left_child_index);
                                else
                                        create_insert_in_child(elem_, key_, spin, right_child_index);
                        }

                        size_t get_right_child_index () const { return right_child_index; }
                        size_t get_left_child_index  () const { return left_child_index;  }

                        T get_element    () const { return elem; }
                        key_type get_key () const { return key;  }
        };
}