#include <iostream>
#include <chrono>

#include "ui.hpp"
#include "avl/avl.hpp"
#include "utils/std.hpp"

using namespace std;
using namespace std::chrono;

namespace
{
        int get_number (const std::string &str, int &val)
        {
                val = stoi(str);
                return length(val);
        }
} // anonymous namespace

vector<pair<char, pair<int, int>>>
get_user_data ()
{
        int val1 = 0;
        int val2 = 0;

        vector<pair<char, pair<int, int>>> input {};
        char cmd = 0;

        while (!cin.eof()) {
                cin >> cmd;
                if (cmd == 'k') {
                        cin >> val1;
                        
                        input.push_back({'k', {val1, 0}});
                } else if (cmd == 'q') {
                        cin >> val1;
                        cin >> val2;

                        input.push_back({'q', {val1, val2}});
                }
                cmd = '\0';
        }

        if (std::cin.fail() && !std::cin.eof())
                throw std::runtime_error("You need to enter \"k\" to add data and \"q\" to enter range.");

        return input;
}

vector<int> parse_input_data (vector<pair<char, pair<int, int>>> &input)
{
        int invalid_val = 0xFFFFFFFF;
        binary_trees::avl_t<int> tree{invalid_val};

        vector<int> output_data {};

        for (auto &elem : input) {
                if (elem.first == 'k') {
                        tree.insert(elem.second.first, elem.second.first);
                } else if (elem.first == 'q') {
                        if (elem.second.first >= elem.second.second)
                                output_data.push_back(0);
                        else
                                output_data.push_back(tree.distance(elem.second.first, elem.second.second));
                } else {
                        throw std::runtime_error("Unknown command.");
                }
        }
        // tree.graphviz_dump();

        return output_data;
}