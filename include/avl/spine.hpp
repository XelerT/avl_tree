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
                        spine_t () = default;

                        size_t insert (const T &new_node_)
                        {
                                if (size < spine.capacity())
                                        spine[size] = new_node_;
                                else
                                        spine.push_back(new_node_);

                                return size++;
                        }

                        void erase (const size_t index_)
                        {
                                spine.erase(std::next(spine.begin(), index_));
                                size--;
                        }

                        size_t get_size     () const { return size; }
                        size_t get_capacity () const { return spine.capacity(); }

                        T& operator[] (const size_t index) { return spine[index]; }
        };
}