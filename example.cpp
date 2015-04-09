#include <string>
#include <map>
#include <iostream>
#include <functional>
#include <memory>
#include <cassert>

#include "duck_typing/object.hpp"

int main()
{
    object obj;

    obj / "hello" = []
    {
        std::cout << "hello" << std::endl;
    };

    obj / "hello1" = [] (int i)
    {
        std::cout << "hello " << i << std::endl;
    };

    obj / "hello_with_string" = [] (std::string s)
    {
        std::cout << "hello " << s << std::endl;
    };

    obj / "hello_with_int_and_string" = [] (int i, std::string s)
    {
        std::cout << "hello " << i << " " << s << std::endl;
    };

    obj["hello"]();
    obj["hello1"](1);
    obj["hello_with_string"](std::string("Piotr"));
    obj["hello_with_int_and_string"](2, std::string("Piotr"));
}
