/*!
 * @file omittable_if_empty.hpp
 * @brief ��Ҫ˵��
 *
 *  ��ϸ˵��
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
 *   @return  ʹinspector ��annotationΪ��ʱ���Ժ���������
 */
constexpr omittable_if_empty_t omittable_if_empty()
{
	return{};
}

}
} // namespace cell

#endif /*CELL_OMITTABLE_IF_EMPTY_HPP*/