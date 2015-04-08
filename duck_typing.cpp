#include <string>
#include <map>
#include <iostream>
#include <functional>
#include <memory>
#include <cassert>

#include "function_traits.hpp"
#include "untyped_heap_storage.hpp"

struct function
{
    function(untyped_heap_storage & callable_storage)
        : callable_storage(callable_storage)
    {
    }

    template<class Functor>
    function & operator = (Functor f)
    {
        to_be_called = false;
        this->callable_storage.copy_from<typename function_type<Functor>::type>(f);
        return *this;
    }

    // called without args
    ~function()
    {
        if (to_be_called)
        {
            auto & f_without_args = callable_storage.get_as<std::function<void()>>();
            f_without_args();
        }
    }


    untyped_heap_storage & callable_storage;
    bool to_be_called = false;
};

struct object
{
    function operator / (std::string name)
    {
        function ret = members[name].function;
        ret.to_be_called = true; // FIXME
        return ret;
    }

private:
    struct member
    {
        member() : function(callable_storage)
        {
        }

        untyped_heap_storage callable_storage;
        function function;
    };

    std::map<std::string, member> members;
};

int main()
{
    object obj;
    obj / "hello" = [] { std::cout << "hello" << std::endl; };
    obj / "hello";

    //obj / "hello1" = [] (std::string name) { std::cout << "hello " << name << std::endl; };
    //obj / "hello1" / "Piotr";
}
