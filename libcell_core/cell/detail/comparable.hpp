/*!
 * @file comparable.hpp
 * @brief Barton�CNackman trick
 *
 *  �ο����ӣ�https://en.wikipedia.org/wiki/Barton%E2%80%93Nackman_trick
 *
 * @author atom
 * @date 2017/01/24
 * @version 0.1.0
 * @note
 */

#ifndef CELL_COMPARABLE
#define CELL_COMPARABLE

namespace cell {
namespace detail {

/*!
 * @class comparable
 *
 * @brief Barton�CNackman trick implementation
 *
 * `Subclass` �����г�Ա����compare��T���жԱȣ�
 * �ԱȽ��Ϊinteger x��
 * - `x < 0` : `*this < other`
 * - `x > 0` : `*this > other`
 * - `x = 0` : `*this == other`
 *
 * @author atom
 * @date 2017/01/24
 */

template <class Subclass, class T = Subclass>
class comparable
{
	friend bool operator==(const Subclass& lhs, const T& rhs) noexcept
	{
		return lhs.compare(rhs) == 0;
	}

	friend bool operator==(const T& lhs, const Subclass& rhs) noexcept
	{
		return lhs.compare(rhs) == 0;
	}

	friend bool operator!=(const Subclass& lhs, const T& rhs) noexcept
	{
		return lhs.compare(rhs) != 0;
	}

	friend bool operator!=(const T& lhs, const Subclass& rhs) noexcept
	{
		return lhs.compare(rhs) != 0;
	}

	friend bool operator<(const Subclass& lhs, const T& rhs) noexcept
	{
		return lhs.compare(rhs) < 0;
	}

	friend bool operator>(const Subclass& lhs, const T& rhs) noexcept
	{
		return lhs.compare(rhs) > 0;
	}

	friend bool operator<(const T& lhs, const Subclass& rhs) noexcept
	{
		return lhs < rhs;
	}

	friend bool operator>(const T& lhs, const Subclass& rhs) noexcept
	{
		return lhs > rhs;
	}

	friend bool operator<=(const Subclass& lhs, const T& rhs) noexcept
	{
		return lhs.compare(rhs) <= 0;
	}

	friend bool operator>=(const Subclass& lhs, const T& rhs) noexcept
	{
		return lhs.compare(rhs) >= 0;
	}

	friend bool operator<=(const T& lhs, const Subclass& rhs) noexcept {
		return lhs <= rhs;
	}

	friend bool operator>=(const T& lhs, const Subclass& rhs) noexcept {
		return lhs >= rhs;
	}

};

template <class Subclass>
class comparable<Subclass, Subclass> {
	friend bool operator==(const Subclass& lhs, const Subclass& rhs) noexcept 
	{
		return lhs.compare(rhs) == 0;
	}

	friend bool operator!=(const Subclass& lhs, const Subclass& rhs) noexcept 
	{
		return lhs.compare(rhs) != 0;
	}

	friend bool operator<(const Subclass& lhs, const Subclass& rhs) noexcept 
	{
		return lhs.compare(rhs) < 0;
	}

	friend bool operator<=(const Subclass& lhs, const Subclass& rhs) noexcept 
	{
		return lhs.compare(rhs) <= 0;
	}

	friend bool operator>(const Subclass& lhs, const Subclass& rhs) noexcept 
	{
		return lhs.compare(rhs) > 0;
	}

	friend bool operator>=(const Subclass& lhs, const Subclass& rhs) noexcept 
	{
		return lhs.compare(rhs) >= 0;
	}
};

} // namespace detail
} // namespace cell

#endif /*CELL_COMPARABLE*/