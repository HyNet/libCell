/*!
 * @file load_callback.hpp
 * @brief 构造一个annotation，表示在inspector 执行load 操作后需要执行的动作
 *
 *  构造一个annotation，表示在inspector 执行load 操作后需要执行的动作
 *
 * @author atom
 * @date 2017/01/24
 * @version 0.1.0
 * @note
 */

#ifndef CELL_LOAD_CALLBACK_HPP
#define CELL_LOAD_CALLBACK_HPP

#include "cell/meta/annotation.hpp"

namespace cell {
namespace meta {

template<class Fun>
struct load_callback_t :annotation
{
	load_callback_t(Fun&& f)
		:fun(f)
	{
		// nop
	}

	load_callback_t(load_callback_t&&) = default;
	Fun fun;
};

/*!
 *   @param   f  需要在load后执行的function
 *   @return  返回一个annotation 用于inspector在执行load操作后执行该动作
 */
template<class Fun>
load_callback_t load_callback(Fun f)
{
	return{ std::move(f) };
}

} // namespace meta
} // namespace cell

#endif /*CELL_LOAD_CALLBACK_HPP*/