#pragma once

#include <vector>
#include <iterator>
#include <algorithm>

namespace binary_trees
{
        template <typename T>
        class spine_t
        {
                private:
                        using vec_node = typename std::vector<T>;

                        vec_node spine;
                        size_t size = 0;

                public:
                        spine_t (size_t capacity_) : spine(capacity_) {};
                        spine_t () : spine() {};

                        size_t insert (const T &new_node_);

                        void erase (const size_t index_);

                        size_t get_size     () const { return size; }
                        size_t get_capacity () const { return spine.capacity(); }

                        T& operator[] (const size_t index) { return spine[index]; }
        };

//===================================================~~~DECLARATIONS~~~====================================================================

        template <typename T>
        size_t spine_t<T>::insert (const T &new_node_)
        {
                if (size < spine.capacity())
                        spine[size] = new_node_;
                else
                        spine.push_back(new_node_);

                return size++;
        }

        template <typename T>
        void spine_t<T>::erase (const size_t index_)
        {
                spine.erase(std::next(spine.begin(), index_));
                size--;
        }
}