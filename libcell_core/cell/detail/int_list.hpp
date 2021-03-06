/*!
 * @file int_list.hpp
 * @brief 简要说明
 *
 *  详细说明
 *
 * @author
 * @date 2017/01/25
 * @version
 * @note
 */

#ifndef CELL_INT_LIST_HPP
#define CELL_INT_LIST_HPP

#include "cell/detail/type_list.hpp"

namespace cell {
namespace detail {

template<long... Is>
struct int_list{};

template<size_t N, size_t Size, long... Is>
struct il_right_impl;

template<size_t N, size_t Size>
struct il_right_impl<N, Size>
{
	using type = int_list<>;
};

template<size_t N, size_t Size, long I, long... Is>
struct il_right_impl<N, Size, I, Is...> : il_right_impl<N, Size - 1, Is...> {};

template<size_t N, long I, long... Is>
struct il_right_impl<N, N, I, Is...>
{
	using type = int_list<I, Is...>;
};

template<class List, size_t N>
struct il_right;

template<long... Is, size_t N>
struct il_right<int_list<Is...>, N>
{
	using type = typename il_right_impl<(N > sizeof...(Is) ? sizeof...(Is) : N)
											, sizeof...(Is), Is...>::type;
};

template <bool Done, size_t Num, class List, long... Is>
struct il_take_impl;

template <class List, long... Is>
struct il_take_impl<true, 0, List, Is...> 
{
	using type = List;
};

template <size_t Num, long... Rs, long I, long... Is>
struct il_take_impl<false, Num, int_list<Rs...>, I, Is...> 
{
	using type = typename il_take_impl<Num == 1, Num - 1, int_list<Rs..., I>, Is...>::type;
};

template <class List, size_t N>
struct il_take;

template <long... Is, size_t N>
struct il_take<int_list<Is...>, N> 
{
	using type = typename il_take_impl<N == 0, N, int_list<>, Is...>::type;
};


/// Creates indices for `List` beginning at `Pos`.
template <class List, long Pos = 0, typename Indices = int_list<>>
struct il_indices;

template <template <class...> class List, long... Is, long Pos>
struct il_indices<List<>, Pos, int_list<Is...>> 
{
	using type = int_list<Is...>;
};

template <template <class...> class List,
	typename T0,
	class... Ts,
	long Pos,
	long... Is>
	struct il_indices<List<T0, Ts...>, Pos, int_list<Is...>> 
{
	// always use type_list to forward remaining Ts... arguments
	using type =
		typename il_indices<
		type_list<Ts...>,
		Pos + 1,
		int_list<Is..., Pos>
		>::type;
};

template <class T>
typename il_indices<T>::type get_indices(const T&) 
{
	return{};
}

template <size_t Num, class T>
typename il_right<typename il_indices<T>::type, Num>::type
get_right_indices(const T&) 
{
	return{};
}

template <long First, long Last, long... Is>
struct il_range : il_range<First + 1, Last, Is..., First> {};

template <long Last, long... Is>
struct il_range<Last, Last, Is...> 
{
	using type = int_list<Is...>;
};

} // namespace detail
} // namespace cell

#endif /*CELL_INT_LIST_HPP*/