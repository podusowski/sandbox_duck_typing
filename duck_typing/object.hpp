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

    function as_called_on_destruct()
    {
        function ret(callable_storage);
        ret.to_be_called = true;
        return ret;
    }

private:
    untyped_heap_storage & callable_storage;
    bool to_be_called = false;
};

struct object
{
    function operator / (std::string name)
    {
        return members[name].function.as_called_on_destruct();
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

