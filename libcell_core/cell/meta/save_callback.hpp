/*!
 * @file save_callback.hpp
 * @brief 构造一个annotation 用于inspector执行save操作后执行该动作
 *
 *  构造一个annotation 用于inspector执行save操作后执行该动作
 *
 * @author
 * @date 2017/01/24
 * @version
 * @note
 */

#ifndef CELL_SAVE_CALLBACK_HPP
#define CELL_SAVE_CALLBACK_HPP

#include "cell/meta/annotation.hpp"

namespace cell {
namespace meta {

template<class F>
struct save_callback_t : annotation 
{
	save_callback_t(F&& f) 
		:fun(f)
	{
		// nop
	}
	
	save_callback_t(save_callback_t&&) = default;
	F fun;
};

/*!
 *   @param   fun  需要在save后执行的function
 *   @return  返回一个annotation，使inspector在执行完save操作之后执行该function
 */
template<class F>
save_callback_t save_callback(F fun)
{
	return{ std::move(fun) };
}

} // namespace meta
} // namespace cell

#endif /*CELL_SAVE_CALLBACK_HPP*/