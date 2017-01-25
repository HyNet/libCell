/*!
 * @file annotation.hpp
 * @brief Cell �����е�meta annotaion��type tag
 *
 *  Cell �����е�meta annotaion��type tag
 *
 * @author atom
 * @date 2017/01/24
 * @version
 * @note
 */

#ifndef CELL_ANNOTATION
#define CELL_ANNOTATION

#include <type_traits>

namespace cell {
namespace meta {

/*!
 * @class annotation
 *
 * @brief annotation���ͱ�ʶ
 *
 * Cell �����е�meta annotaion��type tag
 *
 * @author T440
 * @date 2017/01/24
 */
struct annotation
{
	constexpr annotation()
	{
		// nop
	}
};

template<typename T>
struct is_annotation
{
	static constexpr bool value = std::is_base_of<annotation, T>::value;
};

template <class T>
struct is_annotation<T&> : is_annotation<T> {};

template <class T>
struct is_annotation<const T&> : is_annotation<T> {};

template <class T>
struct is_annotation<T&&> : is_annotation<T> {};

}

} // namespace cell

#endif /*CELL_ANNOTATION*/