/*!
 * @file type_pair.hpp
 * @brief 简要说明
 *
 *  详细说明
 *
 * @author
 * @date 2017/01/25
 * @version
 * @note
 */

#ifndef CELL_TYPE_PAIR_HPP
#define CELL_TYPE_PAIR_HPP

namespace cell {
namespace detail {

template<class First, typename Second>
struct type_pair
{
	using first = First;
	using second = Second;
};

template<class First, typename Second>
struct to_type_pair
{
	using type = type_pair<First, Second>
};

template<class What>
struct is_type_pair
{
	static constexpr bool value = false;
};

template<class First, typename Second>
struct is_type_pair<type_pair<First, Second> >
{
	static constexpr bool value = true;
};

} // namespace detail
} // namespace cell

#endif /*CELL_TYPE_PAIR_HPP*/