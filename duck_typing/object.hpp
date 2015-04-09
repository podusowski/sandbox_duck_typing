#pragma once

#include "untyped_heap_storage.hpp"
#include "function_traits.hpp"

#include <map>
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
        auto & f = callable_storage.get_as<std::function<void(Args...)>>();
        f(args...);
    }

private:
    untyped_heap_storage & callable_storage;
};

struct object
{
    object() = default;

    template<class T>
    object(T value)
    {
        *this = value;
    }

    object & operator = (const object & other) = delete;

    template<class T>
    object & operator = (T value)
    {
        storage.copy_from(value);
        return *this;
    }

    function operator [] (std::string name)
    {
        return members[name].function;
    }

    template<class T>
    T as()
    {
        return storage.get_as<T>();
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
    untyped_heap_storage storage;
};
