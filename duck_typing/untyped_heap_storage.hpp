#pragma once

#include <functional>

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
        assert(pointer);
        return *static_cast<Type*>(pointer);
    }

    template<class Type>
    void copy_from(Type args)
    {
        pointer = new Type(args);
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
};

