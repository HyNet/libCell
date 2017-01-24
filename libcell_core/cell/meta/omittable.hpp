/*!
 * @file omitable.hpp
 * @brief ����inspector ������hunman-friendly��Ϣʱ,�����������ĺ���(omit)������(data filed)
 *
 *  ����inspector ������hunman-friendly��Ϣʱ,�����������ĺ���(omit)������(data filed)
 *
 * @author
 * @date 2017/01/24
 * @version
 * @note
 */

#ifndef CELL_OMITABLE_HPP
#define CELL_OMITABLE_HPP

#include "cell/meta/annotation.hpp"

namespace cell {
namespace meta {

struct omittable_t : annotation
{
	constexpr omittable_t()
	{
		// nop
	}
};


/*!
 *   @param   void  �����Ա���
 *   @return  ����inspector ������hunman-friendly��Ϣʱ,�����������ĺ���(omit)������(data filed)
 */
constexpr omittable_t omittable()
{
	return{};
}

} // namespace meta
} // namespace cell

#endif /*CELL_OMITABLE_HPP*/