#pragma once

#include <functional>

template<class Signature>
struct function_type : public function_type<decltype(&Signature::operator())>
{
};

template<class Result, class Class, class... Args>
struct function_type<Result(Class::*)(Args...) const>
{
    typedef std::function<Result(Args...)> type;
};

template<class Result, class Class, class... Args>
struct function_type<Result(Class::*)(Args...)>
{
    typedef std::function<Result(Args...)> type;
};

template<class Result, class... Args>
struct function_type<Result(*)(Args...)>
{
    typedef std::function<Result(Args...)> type;
};

auto l = []{};

static_assert(std::is_same<std::function<void()>,
                           function_type<decltype(l)>::type
                          >::value, "");
