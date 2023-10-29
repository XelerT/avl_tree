#include "config.hpp"

using namespace binary_trees;

TEST (node, init)
{
        node_t node {42, 0};

        ASSERT_TRUE(node.get_right_child_index() == INVALID);
        ASSERT_TRUE(node.get_left_child_index()  == INVALID);

        ASSERT_TRUE(node.get_element() == 42);
        ASSERT_TRUE(node.get_key()     == 0);
}