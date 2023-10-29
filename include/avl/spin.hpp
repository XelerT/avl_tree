#pragma once

#include <vector>
#include <iterator>
#include <algorithm>

namespace binary_trees
{
        template <typename T>
        class spin_t
        {
                private:
                        using vec_node = typename std::vector<T>;

                        vec_node spin;
                        size_t size = 0;

                public:
                        spin_t (size_t capacity_) : spin(capacity_) {};
                        spin_t () = default;

                        size_t insert (T &new_node_)
                        {
                                if (spin.size() < spin.capacity())
                                        spin[size] = new_node_;
                                else
                                        spin.push_back(new_node_);
                                
                                return ++size;
                        }

                        void erase (const size_t index_)
                        {
                                spin.erase(std::next(spin.begin(), index_));
                        }

                        size_t get_size     () const { return size; }
                        size_t get_capacity () const { return spin.capacity(); }

                        T& operator[] (const size_t index) { return spin[index]; }
        };
}