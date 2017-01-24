/*!
 * @file omittable_if_none.hpp
 * @brief 简要说明
 *
 *  详细说明
 *
 * @author
 * @date 2017/01/24
 * @version
 * @note
 */

#ifndef CELL_OMITTABLE_IF_NONE_HPP
#define CELL_OMITTABLE_IF_NONE_HPP

#include "cell/meta/annotation.hpp"

namespace cell {
namespace meta {

struct omittable_if_none_t : annotation
{
	constexpr omittable_if_none_t()
	{
		// nop
	}
};

/*!
 *   @param   void
 *   @return  使inspector 在annotation为none时可以忽略数据域
 */
constexpr omittable_if_none_t omittable_if_none()
{
	return{};
}

} // namespace cell
} // namespace cell

#endif /*CELL_OMITTABLE_IF_NONE_HPP*/