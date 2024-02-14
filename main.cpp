#include <iostream>

#include "avl.hpp"
#include "ui.hpp"
#include "std_vector.hpp"

using namespace std;

int main ()
{
        std::vector<int> user_data = get_user_data<int>(std::cin);
        std::vector<int> output = parse_input_data<int>(user_data.begin(), user_data.end());

        print(output);
}