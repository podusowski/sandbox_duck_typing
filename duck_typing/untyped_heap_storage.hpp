#pragma once

#include <functional>
#include <stdexcept>
#include <typeinfo>

struct untyped_heap_storage
{
    typedef std::function<void()> deleter_type;

    untyped_heap_storage()
    {
    }


    untyped_heap_storage(const untyped_heap_storage &) = delete;

    untyped_heap_storage & operator = (untyped_heap_storage && other)
    {
        pointer = other.pointer;
        other.pointer = nullptr;
        return *this;
    }

    untyped_heap_storage(untyped_heap_storage && other)
    {
        *this = std::move(other);
    }

    template<class Type>
    Type & get_as()
    {
        if (!pointer)
        {
            throw std::runtime_error("pointer is nullptr");
        }

        if (type != &typeid(Type))
        {
            throw std::runtime_error("wrong type");
        }

        return *static_cast<Type*>(pointer);
    }

    template<class Type>
    void copy_from(Type args)
    {
        pointer = new Type(args);
        type = &typeid(args);
        deleter = [this] { delete static_cast<Type*>(this->pointer); };
    }

    ~untyped_heap_storage()
    {
        if (pointer)
        {
            deleter();
        }
    }

private:
    deleter_type deleter;
    void * pointer = nullptr;
    std::type_info const * type = nullptr;
};

