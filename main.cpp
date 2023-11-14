#include <iostream>

#include "avl.hpp"
#include "ui.hpp"
#include "std_vector.hpp"

using namespace std;

int main ()
{
        auto user_data = get_user_data();
        println(parse_input_data(user_data));
}