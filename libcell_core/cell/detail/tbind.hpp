/*!
 * @file tbind.hpp
 * @brief 简要说明
 *
 *  详细说明
 *
 * @author
 * @date 2017/01/25
 * @version
 * @note
 */

#ifndef CELL_TBIND_HPP
#define CELL_TBIND_HPP

namespace cell {

namespace detail {

template<template <class, typename> class Tpl, typename Arg1>
struct tbind
{
	template<class Arg2>
	struct type
	{
		static constexpr bool value = Tpl<Arg1, Arg2>::value;
	};
};


} // namespace detail

} // namespace cell

#endif /*CELL_TBIND_HPP*/