/*!
 * @file none.hpp
 * @brief nothing类型
 *
 *  用于表示空
 *
 * @author
 * @date 2017/01/24
 * @version
 * @note
 */

#ifndef CELL_NONE
#define CELL_NONE

#include <string>

#include "cell/detail/comparable.hpp"

namespace cell {

/*!
 * @class none_t
 *
 * @brief 表示nothing
 *
 * 例如可以通过none来赋值一个boost::optional变量，表示将该值设为未初始化的状态
 *
 * @author atom
 * @date 2017/01/24
 */
struct none_t : detail::comparable<none_t>
{
	/*
	 * A constexpr constructor must satisfy the following requirements :
	 *
	 * - each of its parameters must be LiteralType.
	 * - the class must have no virtual base classes
	 * - the constructor must not have a function - try - block
	*/
	
	constexpr none_t()
	{
		// nop
	}

	/*
	 * A constexpr function must satisfy the following requirements:
	 *
	 * - it must not be virtual
	 * - its return type must be LiteralType
	 * - each of its parameters must be LiteralType
	*/
	constexpr explicit operator bool() const 
	{
		return false;
	}


	static constexpr int compare(none_t) 
	{
		return 0;
	}

};

//! @relates none_t
static constexpr none_t none = none_t{};

inline std::string to_string(const none_t&)
{
	return "none";
}

} // namespace cell

#endif /*CELL_NONE*/