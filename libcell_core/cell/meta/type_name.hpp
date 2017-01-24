/*!
 * @file type_name.hpp
 * @brief type name annotation
 *
 *  获得一个type name annotation
 *
 * @author
 * @date 2017/01/24
 * @version
 * @note
 */

#ifndef CELL_TYPE_NAME_HPP
#define CELL_TYPE_NAME_HPP

#include "cell/meta/annotation.hpp"

namespace cell {

namespace meta {

struct type_name_t : annotation
{
	constexpr type_name_t(const char* cstr)
		:value(cstr)
	{
		//nop
	}
	const char *value;
};

/*!
 *   @param   cstr  类型名
 *   @return  type name annotation
 */
type_name_t constexpr type_name(const char *cstr)
{
	return{ cstr };
}

}

} // namespace cell

#endif /*CELL_TYPE_NAME_HPP*/