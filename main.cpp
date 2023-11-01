#include <iostream>

#include "avl.hpp"

using namespace std;

int main ()
{
        int invalid_val = 0xFFFFFF;
        binary_trees::avl_t<int> tree{invalid_val};
        tree.insert(5, 5);
        tree.insert(6, 6);
        tree.insert(7, 7);
        tree.insert(4, 4);
        tree.insert(10, 10);
        tree.insert(11, 11);
        tree.insert(1, 1);

        tree.graphviz_dump();
}