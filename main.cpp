#include <iostream>

#include "avl.hpp"

using namespace std;

int main ()
{
        binary_trees::avl_t<int> tree{};
        tree.insert(5, 1);
        cout << "Hello World!\n";
}