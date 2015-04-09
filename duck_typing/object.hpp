#pragma once

#include "untyped_heap_storage.hpp"
#include "function_traits.hpp"

#include <functional>

struct function
{
    function(untyped_heap_storage & callable_storage)
        : callable_storage(callable_storage)
    {
    }

    template<class Functor>
    function & operator = (Functor f)
    {
        this->callable_storage.copy_from<typename function_type<Functor>::type>(f);
        return *this;
    }

    template<class... Args>
    void operator () (Args... args)
    {
        auto & f= callable_storage.get_as<std::function<void(Args...)>>();
        f(args...);
    }

private:
    untyped_heap_storage & callable_storage;
};

struct object
{
    function operator / (std::string name)
    {
        return members[name].function;
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
