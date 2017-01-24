/*!
 * @file omitable.hpp
 * @brief 方便inspector 在生成hunman-friendly信息时,可以无条件的忽略(omit)数据域(data filed)
 *
 *  方便inspector 在生成hunman-friendly信息时,可以无条件的忽略(omit)数据域(data filed)
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
 *   @param   void  被测试变量
 *   @return  方便inspector 在生成hunman-friendly信息时,可以无条件的忽略(omit)数据域(data filed)
 */
constexpr omittable_t omittable()
{
	return{};
}

} // namespace meta
} // namespace cell

#endif /*CELL_OMITABLE_HPP*/