/*!
 * @file save_callback.hpp
 * @brief ����һ��annotation ����inspectorִ��save������ִ�иö���
 *
 *  ����һ��annotation ����inspectorִ��save������ִ�иö���
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
 *   @param   fun  ��Ҫ��save��ִ�е�function
 *   @return  ����һ��annotation��ʹinspector��ִ����save����֮��ִ�и�function
 */
template<class F>
save_callback_t save_callback(F fun)
{
	return{ std::move(fun) };
}

} // namespace meta
} // namespace cell

#endif /*CELL_SAVE_CALLBACK_HPP*/