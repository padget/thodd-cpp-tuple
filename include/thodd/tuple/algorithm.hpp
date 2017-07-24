#ifndef __THODD_TUPLE_ALGORITHM_HPP__
#  define __THODD_TUPLE_ALGORITHM_HPP__

#  include <tuple>
#  include <type_traits>
#  include <utility>

namespace 
thodd::tuple
{
    constexpr auto 
    accumulate_if (
        auto&& __predicate,
        auto&& __func, 
        auto&& __accumulator,
        auto&& __initial, 
        auto&& __tuple)
    -> decltype(auto)
    {
        return
        std::apply (
            [&] (auto && ... __item) 
            {
                std::decay_t<decltype(__initial)> __tmp = std::forward<decltype(__initial)>(__initial) ;
                ((__tmp = std::forward<decltype(__predicate)>(__predicate)(__tmp, __item) ? 
                            std::forward<decltype(__accumulator)>(__accumulator)(
                                __tmp, 
                                std::forward<decltype(__func)>(__func)(__item)) : 
                            __tmp), ...) ;

                return 
                __tmp ;
            },
            std::forward<decltype(__tuple)>(__tuple)) ;

    }


    constexpr auto 
    accumulate (
        auto&& __func, 
        auto&& __accumulator,
        auto&& __initial, 
        auto&& __tuple)
    -> decltype(auto)
    {
        return
        accumulate_if(
            [](auto&& ... __args) { return true ; },
            std::forward<decltype(__func)>(__func),
            std::forward<decltype(__accumulator)>(__accumulator),
            std::forward<decltype(__initial)>(__initial),
            std::forward<decltype(__tuple)>(__tuple)) ;
    }


    
    constexpr void
    iterate_if (
        auto&& __pred,
        auto&& __func, 
        auto&& __tuple)
    {
        std::apply(
            [&__func, &__pred] (auto&& ... __item) 
            { 
                auto __each = 
                [&__func, &__pred] (auto&& ___item) 
                { 
                    if(std::forward<decltype(__pred)>(__pred)(___item))
                        std::forward<decltype(__func)>(__func)(std::forward<decltype(___item)>(___item)) ;
                } ;
              
                (__each (std::forward<decltype(__item)>(__item)), ... ) ;
            }, 
            std::forward<decltype(__tuple)>(__tuple)) ;
    }

    constexpr auto 
    iterate (
        auto&& __func, 
        auto&& __tuple)
    {
        std::apply(
            [&__func] (auto&& ... __item) 
            { (std::forward<decltype(__func)>(__func)(std::forward<decltype(__item)>(__item)), ...) ; }, 
            std::forward<decltype(__tuple)>(__tuple)) ;
    }
}

#endif