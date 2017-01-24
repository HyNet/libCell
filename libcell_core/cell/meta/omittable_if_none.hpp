/*!
 * @file omittable_if_none.hpp
 * @brief ��Ҫ˵��
 *
 *  ��ϸ˵��
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
 *   @return  ʹinspector ��annotationΪnoneʱ���Ժ���������
 */
constexpr omittable_if_none_t omittable_if_none()
{
	return{};
}

} // namespace cell
} // namespace cell

#endif /*CELL_OMITTABLE_IF_NONE_HPP*/