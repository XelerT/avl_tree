#include <iostream>

#include "avl.hpp"

using namespace std;

int main ()
{
        binary_trees::avl_t<int> tree{};
        tree.insert(5, 5);
        cout << tree.capacity() << " " << tree.size() << " " << tree.get_root_index() << endl;
        tree.insert(6, 6);
        tree.insert(7, 7);
        tree.insert(4, 4);
        tree.insert(10, 10);
        tree.insert(11, 11);
        tree.insert(1, 1);

        tree.graphviz_dump();
        cout << "Hello World!\n";
}