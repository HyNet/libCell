/*!
 * @file load_callback.hpp
 * @brief ����һ��annotation����ʾ��inspector ִ��load ��������Ҫִ�еĶ���
 *
 *  ����һ��annotation����ʾ��inspector ִ��load ��������Ҫִ�еĶ���
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
 *   @param   f  ��Ҫ��load��ִ�е�function
 *   @return  ����һ��annotation ����inspector��ִ��load������ִ�иö���
 */
template<class Fun>
load_callback_t load_callback(Fun f)
{
	return{ std::move(f) };
}

} // namespace meta
} // namespace cell

#endif /*CELL_LOAD_CALLBACK_HPP*/