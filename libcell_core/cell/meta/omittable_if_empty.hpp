/*!
 * @file omittable_if_empty.hpp
 * @brief 简要说明
 *
 *  详细说明
 *
 * @author
 * @date 2017/01/24
 * @version
 * @note
 */

#ifndef CELL_OMITTABLE_IF_EMPTY_HPP
#define CELL_OMITTABLE_IF_EMPTY_HPP

namespace cell {
namespace meta {

struct omittable_if_empty_t : annotation
{
	constexpr omittable_if_empty_t()
	{
		// nop
	}
};

/*!
 *   @param   void  
 *   @return  使inspector 在annotation为空时可以忽略数据域
 */
constexpr omittable_if_empty_t omittable_if_empty()
{
	return{};
}

}
} // namespace cell

#endif /*CELL_OMITTABLE_IF_EMPTY_HPP*/