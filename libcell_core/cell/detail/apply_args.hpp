/*!
 * @file apply_args.hpp
 * @brief 简要说明
 *
 *  详细说明
 *
 * @author
 * @date 2017/01/25
 * @version
 * @note
 */

#ifndef CELL_APPLY_ARGS_HPP
#define CELL_APPLY_ARGS_HPP

#include <utility>

#include "cell/detail/int_list.hpp"

namespace cell {
namespace detail {

// this utterly useless function works around a bug in Clang that causes
// the compiler to reject the trailing return type of apply_args because
// "get" is not defined (it's found during ADL)
template<long Pos, class... Ts>
typename tl_at<type_list<Ts...>, Pos>::type get(const type_list<Ts...>&);

template <class F, long... Is, class Tuple>
auto apply_args(F& f, detail::int_list<Is...>, Tuple& tup)
	-> decltype(f(get<Is>(tup)...)) 
{
	return f(get<Is>(tup)...);
}

template <class F, long... Is, class Tuple>
auto apply_moved_args(F& f, detail::int_list<Is...>, Tuple& tup)
	-> decltype(f(std::move(get<Is>(tup))...)) 
{
	return f(std::move(get<Is>(tup))...);
}

template <class F, class Tuple, class... Ts>
auto apply_args_prefixed(F& f, detail::int_list<>, Tuple&, Ts&&... xs)
	-> decltype(f(std::forward<Ts>(xs)...)) 
{
	return f(std::forward<Ts>(xs)...);
}

template <class F, long... Is, class Tuple, class... Ts>
auto apply_args_prefixed(F& f, detail::int_list<Is...>, Tuple& tup, Ts&&... xs)
	-> decltype(f(std::forward<Ts>(xs)..., get<Is>(tup)...)) 
{
	return f(std::forward<Ts>(xs)..., get<Is>(tup)...);
}

template <class F, class Tuple, class... Ts>
auto apply_moved_args_prefixed(F& f, detail::int_list<>, Tuple&, Ts&&... xs)
	-> decltype(f(std::forward<Ts>(xs)...)) 
{
	return f(std::forward<Ts>(xs)...);
}

template <class F, long... Is, class Tuple, class... Ts>
auto apply_moved_args_prefixed(F& f, detail::int_list<Is...>, Tuple& tup, Ts&&... xs)
	-> decltype(f(std::forward<Ts>(xs)..., std::move(get<Is>(tup))...)) 
{
	return f(std::forward<Ts>(xs)..., std::move(get<Is>(tup))...);
}

template <class F, long... Is, class Tuple, class... Ts>
auto apply_args_suffxied(F& f, detail::int_list<Is...>, Tuple& tup, Ts&&... xs)
	-> decltype(f(get<Is>(tup)..., std::forward<Ts>(xs)...)) 
{
	return f(get<Is>(tup)..., std::forward<Ts>(xs)...);
}


} // namespace detail
} // namespace cell

#endif /*CELL_APPLY_ARGS_HPP*/