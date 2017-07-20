#ifndef __THODD_TUPLE_ALGORITHM_HPP__
#  define __THODD_TUPLE_ALGORITHM_HPP__

#  include <tuple>
#  include <type_traits>
#  include <utility>

namespace 
thodd::tuple
{
    template<
        size_t index_c>
    constexpr auto 
    __accumulate_if (
        auto&& __func,
        auto&& __accumulator, 
        auto&& __predicate,
        auto&& __state, 
        auto&& __tuple)
    -> decltype(auto)
    {
        if constexpr (index_c < std::tuple_size<std::decay_t<decltype(__tuple)>>::value)
        {    
            if(std::forward<decltype(__predicate)>(__predicate) (std::forward<decltype(__state)>(__state)))                
                return 
                __accumulate_if<index_c + 1> (
                    std::forward<decltype(__func)>(__func), 
                    std::forward<decltype(__accumulator)>(__accumulator),
                    std::forward<decltype(__predicate)>(__predicate), 
                    std::forward<decltype(__accumulator)>(__accumulator)(
                        std::forward<decltype(__state)>(__state), 
                        __func(std::get<index_c>(__tuple))), 
                    std::forward<decltype(__tuple)>(__tuple)) ;
            else 
                return 
                __accumulate_if<index_c + 2> (
                    std::forward<decltype(__func)>(__func), 
                    std::forward<decltype(__accumulator)>(__accumulator), 
                    std::forward<decltype(__predicate)>(__predicate),
                    std::forward<decltype(__accumulator)>(__accumulator)(
                        std::forward<decltype(__state)>(__state), 
                        __func(std::get<index_c>(__tuple))), 
                    std::forward<decltype(__tuple)>(__tuple)) ;
        }
        else
            return 
            __state ;
    }

    constexpr auto 
    accumulate_if (
        auto&& __func, 
        auto&& __accumulator, 
        auto&& __predicate, 
        auto&& __state, 
        auto&& __tuple)
    -> decltype(auto)
    {
        return 
        __accumulate_if<0u>(
            std::forward<decltype(__func)>(__func),
            std::forward<decltype(__accumulator)>(__accumulator), 
            std::forward<decltype(__predicate)>(__predicate),
            std::forward<decltype(__state)>(__state), 
            std::forward<decltype(__tuple)>(__tuple)) ;
    }

    constexpr auto 
    accumulate (
        auto&& __func,
        auto&& __accumulator, 
        auto&& __state, 
        auto&& __tuple)
    -> decltype(auto)
    {
        return 
        __accumulate_if<0u> ( 
            std::forward<decltype(__func)>(__func),
            std::forward<decltype(__accumulator)>(__accumulator), 
            [] (auto&&... __args) { return true; },
            std::forward<decltype(__state)>(__state), 
            std::forward<decltype(__tuple)>(__tuple)) ;
    }

    constexpr auto
    iterate_if (
        auto&& __func, 
        auto&& __predicate, 
        auto&& __tuple)
    -> decltype(auto)
    {
        return 
        accumulate_if (
            std::forward<decltype(__func)>(__func), 
            [&__tuple] (auto&& __state, auto&& __res) { return std::forward<decltype(__tuple)>(__tuple) ; }, 
            std::forward<decltype(__predicate)>(__predicate), 
            std::forward<decltype(__tuple)>(__tuple), 
            std::forward<decltype(__tuple)>(__tuple)) ;
    }


    constexpr auto
    iterate (
        auto&& __func, 
        auto&& __tuple)
    -> decltype(auto)
    {
        return 
        iterate_if (
            std::forward<decltype(__func)>(__func), 
            [] (auto&&... __args) { return true; }, 
            std::forward<decltype(__tuple)>(__tuple)) ;
    }
}

#endif