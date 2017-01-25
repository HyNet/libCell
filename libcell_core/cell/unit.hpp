/*!
 * @file unit.hpp
 * @brief 简要说明
 *
 *  详细说明
 *
 * @author
 * @date 2017/01/25
 * @version
 * @note
 */

#ifndef CELL_UNIT_HPP
#define CELL_UNIT_HPP

#include <string>
#include "cell/detail/comparable.hpp"

namespace cell {

/*!
 * @class unit_t
 *
 * @brief unit_t是void的安全版本
 *
 * unit_t 可以被用来替代void，以便于安全的作为返回值返回，或者保存，这样在使用时就不必处理void产生的异常情况
 *
 * @author T440
 * @date 2017/01/25
 */
struct unit_t : detail::comparable<unit_t>
{
	constexpr unit_t() noexcept
	{
		// nop
	}

	constexpr unit_t(const unit_t&) noexcept
	{
		// nop
	}

	template<class T>
	explicit constexpr unit_t(T&&) noexcept
	{
		// nop
	}

	static constexpr int compare(const unit_t&) noexcept
	{
		return 0;
	}

	template<class ... Ts>
	constexpr unit_t operator()(Ts&...) const noexcept
	{
		return{};
	}
};

static constexpr unit_t unit = unit_t{};

/// @relates unit_t
template<class Processor>
void serialize(Processor&, const unit_t&, unsigned int)
{
	// nop
}

/// @relates unit_t
inline std::string to_string(const unit_t&)
{
	return "unit";
}

template<class T>
struct lift_void
{
	using type = T;
};

template<>
struct lift_void<void>
{
	using type = unit_t;
};

template<class T>
struct unlift_void
{
	using type = T;
};

template<>
struct unlift_void<unit_t>
{
	using type = void;
};

} // namespace cell

#endif /*CELL_UNIT_HPP*/