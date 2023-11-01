#include "config.hpp"

using namespace binary_trees;

TEST (avl, default_init)
{
        avl_t<int> tree {};

        ASSERT_TRUE(tree.get_root_index() == DEFAULT_ROOT_INDEX);
        ASSERT_TRUE(tree.get_capacity()   == DEFAULT_SPINE_SIZE);
}

TEST (avl, init)
{
        avl_t<int> tree {42};

        ASSERT_TRUE(tree.get_root_index() == DEFAULT_ROOT_INDEX);
        ASSERT_TRUE(tree.get_capacity()   == 42);
}