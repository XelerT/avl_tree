#include "config.hpp"

using namespace binary_trees;

TEST (node, init)
{
        node_t node {42, 0, 0};

        EXPECT_EQ(node.get_right_child_index(), INVALID);
        EXPECT_EQ(node.get_left_child_index(), INVALID);

        EXPECT_EQ(node.get_data(), 42);
        EXPECT_EQ(node.get_key(),      0);
}

// size_t insert (const node_t &node_, spine_t<node_t<T, key_type>> &spine_);
TEST (node, insert_node)
{
        node_t node             {42, 0, 0};
        node_t node_child_left  {42, -1, 1};
        node_t node_child_right {42,  1, 2};

        spine_t<node_t<int>> spine {};

        EXPECT_EQ(node.get_right_child_index(), INVALID);
        EXPECT_EQ(node.get_left_child_index(),  INVALID);

        EXPECT_EQ(node.get_data(), 42);
        EXPECT_EQ(node.get_key(),      0);

        spine.insert(node);
        node.insert(node_child_left,  spine);
        node.insert(node_child_right, spine);

        ASSERT_NE(node.get_right_child_index(), INVALID);
        EXPECT_NE(node.get_left_child_index(),  INVALID);

        EXPECT_EQ(spine[node.get_left_child_index()].get_data(), 42);
        EXPECT_EQ(spine[node.get_left_child_index()].get_key(),     -1);

        EXPECT_EQ(spine[node.get_right_child_index()].get_data(), 42);
        EXPECT_EQ(spine[node.get_right_child_index()].get_key(),      1);
}

// size_t insert (const T &data_, const key_type &key_, spine_t<node_t<T, key_type>> &spine_);
TEST (node, insert_datas)
{
        node_t node {42, 0, 0};
        spine_t<node_t<int>> spine {};

        EXPECT_EQ(node.get_right_child_index(), INVALID);
        EXPECT_EQ(node.get_left_child_index(),  INVALID);

        EXPECT_EQ(node.get_data(), 42);
        EXPECT_EQ(node.get_key(),   0);

        spine.insert(node);
        node.insert(42, -1,  spine);
        node.insert(42,  1, spine);

        ASSERT_NE(node.get_right_child_index(), INVALID);
        EXPECT_NE(node.get_left_child_index(),  INVALID);

        EXPECT_EQ(spine[node.get_left_child_index()].get_data(), 42);
        EXPECT_EQ(spine[node.get_left_child_index()].get_key(),  -1);

        EXPECT_EQ(spine[node.get_right_child_index()].get_data(), 42);
        EXPECT_EQ(spine[node.get_right_child_index()].get_key(),   1);
}