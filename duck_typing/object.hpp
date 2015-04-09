#pragma once

#include "untyped_heap_storage.hpp"
#include "function_traits.hpp"

#include <functional>

template<class Param>
struct function_with_param_caller
{
    function_with_param_caller(untyped_heap_storage & callable_storage, Param param)
        : callable_storage(callable_storage),
          param(param)
    {
    }

    template<class Argument>
    function_with_param_caller<Argument> operator / (Argument arg)
    {
        return function_with_param_caller<Argument>(callable_storage, arg);
    }

    ~function_with_param_caller()
    {
        auto & f = callable_storage.get_as<std::function<void(Param)>>();
        f(param);
    }

private:
    Param param;
    untyped_heap_storage & callable_storage;
};

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

    template<class Argument>
    function_with_param_caller<Argument> operator / (Argument arg)
    {
        to_be_called = false;
        return function_with_param_caller<Argument>(callable_storage, arg);
    }

    // called without args
    ~function()
    {
        //if (to_be_called)
        //{
        //    auto & f_without_args = callable_storage.get_as<std::function<void()>>();
        //    f_without_args();
        //}
    }

    template<class... Args>
    void operator () (Args... args)
    {
        auto & f= callable_storage.get_as<std::function<void(Args...)>>();
        f(args...);
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

