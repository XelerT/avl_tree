#pragma once

#include <vector>
#include <utility>
#include <iterator>

#include "avl/avl.hpp"
#include "utils/std.hpp"

template <typename T>
std::vector<T> get_user_data (std::istream &in)
{
        T val1 = 0;
        T val2 = 0;

        std::vector<T> input {};
        unsigned char cmd = 0;

        while (!in.eof()) {
                in >> cmd;
                if (cmd == 'k') {            
                        in >> val1;

                        input.push_back('k');
                        input.push_back(val1);
                } else if (cmd == 'q') {
                        in >> val1;
                        in >> val2;

                        input.push_back('q');
                        input.push_back(val1);
                        input.push_back(val2);
                }
                cmd = '\0';
        }

        if (in.fail() && !in.eof())
                throw std::runtime_error("You need to enter \"k\" to add data and \"q\" to enter range.");

        return input;
}

template <typename T, typename It>
std::vector<T> 
parse_input_data (It start, It fin)
{        
        T invalid_val = 0xFFFFFFFF;
        binary_trees::avl_t<T> tree {invalid_val};

        std::vector<T> output_data {};

        T val1 {};
        T val2 {};
        for (auto it = start; it != fin; ++it) {
                if (*it == 'k') {
                        val1 = *(++it);
                        tree.insert(val1, val1);
                } else if (*it == 'q') {
                        val1 = *(++it);
                        val2 = *(++it);
                        output_data.push_back(tree.distance(val1, val2));
                } else {
                        std::cout << *it << "\n";
                        throw std::runtime_error("Unknown command.");
                }
        }
        // tree.graphviz_dump();

        return output_data;
}