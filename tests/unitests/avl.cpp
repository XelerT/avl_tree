#include "config.hpp"

using namespace binary_trees;

TEST (avl, default_init)
{
        int invalid_val = 0xFFFFFF;
        avl_t<int> tree {invalid_val};

        EXPECT_EQ(tree.get_root_index(), DEFAULT_ROOT_INDEX);
        EXPECT_EQ(tree.capacity(), DEFAULT_SPINE_SIZE);
}

TEST (avl, init)
{
        int invalid_val = 0xFFFFFF;
        avl_t<int> tree {42, invalid_val};

        EXPECT_EQ(tree.get_root_index(), DEFAULT_ROOT_INDEX);
        EXPECT_EQ(tree.capacity(), 42);
}

// void insert (const T &data_, const key_type &key_);
TEST (avl, insert)
{
        int invalid_val = 0xFFFFFF;
        avl_t<int> tree {42, invalid_val};
        tree.insert(6, 6);
        tree.insert(7, 7);
        tree.insert(4, 4);

        int key1   = 6;
        int key2   = 7;
        int key420 = 420;

        EXPECT_EQ(tree.get_root_index(), 0);
        EXPECT_EQ(tree.size(), 3);
        EXPECT_EQ(tree.get_data(key1),   key1);
        EXPECT_EQ(tree.get_data(key2),   key2);
        EXPECT_EQ(tree.get_data(key420), invalid_val);
}