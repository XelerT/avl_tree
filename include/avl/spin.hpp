#include <vector>

class node_t {
        int a = 0;
};

namespace binary_trees
{
        class spin_t
        {
                private:
                        std::vector<node_t> spin;
                        size_t size = 0;
                public:
                        spin_t (size_t capacity_) : spin(capacity_) {};
                        spin_t () = default;

                        void insert (const node_t &new_node_)
                        {
                                if (spin.size() < spin.capacity())
                                        spin[size] = new_node_;
                                else
                                        spin.push_back(new_node_);
                                
                                size++;
                        }

                        size_t get_size     () const { return size; }
                        size_t get_capacity () const { return spin.capacity(); }

                        void erase (const size_t index_)
                        {
                                // spin.erase(index_);
                                
                        }
        };
}