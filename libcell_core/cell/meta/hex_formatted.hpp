/*!
 * @file hex_formatted.hpp
 * @brief hex fomatted
 *
 *  hex fomatted
 *
 * @author atom
 * @date 2017/01/24
 * @version
 * @note
 */

#ifndef CELL_HEX_FORMATTED_HPP
#define CELL_HEX_FORMATTED_HPP

#include "cell/meta/annotation.hpp"

namespace cell {

namespace meta {

struct hex_formatted_t : annotation {
	constexpr hex_formatted_t()
	{
		// nop
	}
};

/*!
 *   @param   void 
 *   @return  
 *   @note    应该由inspector将data field format 为hex
 */
constexpr hex_formatted_t hex_formatted()
{
	return{};
}

}


} // namespace cell

#endif /*CELL_HEX_FORMATTED_HPP*/