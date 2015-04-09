#include "duck_typing/function_traits.hpp"

auto l = []{};

static_assert(std::is_same<std::function<void()>,
                           function_type<decltype(l)>::type
                          >::value, "");

static_assert(std::is_same<std::function<void()>,
                           function_type<decltype(l)>::type
                          >::value, "");
