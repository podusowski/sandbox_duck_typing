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
    obj / "hello" = [] { std::cout << "hello" << std::endl; };
    obj / "hello1" = [] (std::string name) { std::cout << "hello " << name << std::endl; };

    obj / "hello";
    //obj / "hello1" / "Piotr";
}
