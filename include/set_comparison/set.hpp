#pragma once

#include <vector>
#include <set>
#include <utility>
#include <iostream>

#include "ui/ui.hpp"

template<typename T>
long int find_n_elems_in_range (std::set<T> &tree, T lower_bound, T upper_bound)
{
        auto upper_bound_it = tree.upper_bound(upper_bound);
        auto lower_bound_it = tree.lower_bound(lower_bound);

        return distance(lower_bound_it, upper_bound_it);
}

template<typename T, typename key_type>
std::vector<T> parse_input_data4set (std::vector<std::pair<char, std::pair<T, key_type>>> &input)
{
        std::set<int> tree{};
        std::vector<T> output_data {};

        for (auto &elem : input) {
                if (elem.first == 'k') {
                        tree.insert(elem.second.first);
                } else if (elem.first == 'q') {
                        output_data.push_back(find_n_elems_in_range(tree, elem.second.first, elem.second.second));
                } else {
                        throw std::runtime_error("Unknown command.");
                }
        }

        return output_data;
}