#ifndef __THODD_TUPLE_INDEXOF_HPP__
#  define __THODD_TUPLE_INDEXOF_HPP__

#  include <type_traits>

namespace 
thodd::tuple
{
    template<
        typename type_t,
        typename ... item_t>
    constexpr auto
    index_of(
        std::tuple<item_t...> const &)
    {
        auto __index = 0u ;
        auto __found = false ;

        ((!__found && std::is_same_v<type_t, item_t> ? 
            (__found = true, __index) : (__found ? __index : ++__index)), ...) ;

        return 
        __index ;
    }
}

#endif