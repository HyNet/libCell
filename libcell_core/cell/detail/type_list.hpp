/*!
 * @file type_list.hpp
 * @brief 类型操作容器 type list
 *
 *  提供操作一组类型的容器
 *
 * @author
 * @date 2017/01/25
 * @version
 * @note
 */


#ifndef CELL_TYPE_LIST_HPP
#define CELL_TYPE_LIST_HPP

#include <cstddef>
#include <typeinfo>
#include <type_traits>

#include "cell/unit.hpp"
#include "cell/none.hpp"

#include "cell/detail/tbind.hpp"
#include "cell/detail/type_pair.hpp"

namespace cell {
namespace detail {


/*!
 * @class type_list
 *
 * @brief a list of types
 *
 * @author atom
 * @date 2017/01/25
 */
template<class ... Ts>
struct type_list
{
	constexpr type_list()
	{
		// nop
	}
};

/// empty type list
using empty_type_list = type_list<>;

template<class T>
struct is_type_list
{
	static constexpr bool value = false;
};

template<class ... Ts>
struct is_type_list< type_list<Ts> >
{
	static constexpr bool value = true;
};


/*!
 *   @param   type_list  a list of types
 *   @return  the first type in the type list
 *   @note    模板函数原型: T head(type_list)
 */

/// get the first element type of type `List`
template <class List>
struct tl_head;

template<>
struct tl_head< type_list<> >
{
	using type = void;
};

template<typename T0, class... Ts>
struct tl_head<type_list<T0, Ts...> >
{
	using type = T0;
};

/*!
 *   @param   type_list  a list of types
 *   @return  the types in the type list *except the head type*
 *   @note    T tail(type_list)
 */

template<class List>
struct tl_tail;

template<>
struct tl_tail<type_list<>>
{
	using type = void;
};

template<typename T0, class... Ts>
struct tl_tail<type_list<T0, Ts...> >
{
	using type = type_list<Ts...>;
};

/*!
 *   @param   type_list
 *   @return  返回template parameters的数量
 *   @note    size_t size(type_list)
 */

template<class List>
struct tl_size;

template<class... Ts>
struct tl_size<type_list<Ts...> >
{
	static constexpr size_t value = sizeof...(Ts);
};

template<class... Ts>
constexpr size_t tl_size<type_list<Ts...> >::value;

/*!
 *   @param   type_list  被测试变量
 *   @return  return the last element of type `List`
 *   @note    T back(type_list)
 */

template<class List>
struct tl_back;

template<>
struct tl_back<type_list<> >
{
	using type = unit_t;
};

template<typename T0>
struct tl_back<type_list<T0>>
{
	using type = T0;
};

template<typename T0, typename T1, class... Ts>
struct tl_back<type_list<T0, T1, Ts...> >
{
	using type = typename tl_back<type_list<T1, Ts...> >::type;
};

/*!
 *   @param   type_list
 *   @return  type_list是否为空
 *   @note    bool empty(type_list)
 */

template<class List>
struct tl_empty
{
	static constexpr bool value = std::is_same<empty_type_list, List>::value;
};

/*!
 *   @param   from  size_t: the begin index of the type slice in the type_list 
 *   @param   to    size_t: the end index of the type slice in the type_list
 *   @return  a slice of type_list
 *   @note    list slice(size_t, size_t)
 */

template<size_t LeftOffset, size_t Remaining,
		 typename PadType, class List, class... Ts>
struct tl_slice_impl
{
	using type
		= typename tl_slice_impl<
		LeftOffset - 1,
		Remaining,
		PadType,
		typename tl_tail<List>::type,
		Ts...
		>::type;
};

template<size_t Remaining, typename PadType, class List, class... Ts>
struct tl_slice_impl<0, Remaining, PadType, List, Ts...>
{
	using type
		= typename tl_slice_impl<
		0,
		Remaining - 1,
		PadType,
		typename tl_tail<List>::type,
		Ts...
		typename tl_head<List>::type
		>::type;
};

template<size_t Remaining, typename PadType, class... Ts>
struct tl_slice_impl<0, Remaining, PadType, empty_type_list, Ts...>
{
	using type
		= typename tl_slice_impl<
		0,
		Remaining - 1,
		PadType,
		empty_type_list,
		Ts...,
		PadType
		>::type;
};

template<typename PadType, class List, class... Ts>
struct tl_slice_impl<0, 0, PadType, List, Ts...>
{
	using type = type_list<Ts...>;
};

template<class List, size_t ListSize, size_t First, size_t Last, 
		typename PadType = unit_t>
struct tl_slice_
{
	using type =
		typename tl_slice_impl<
		First,
		(Last - First),
		PadType,
		List
		>::type;
};

template<class List, size_t ListSize, typename PadType>
struct tl_slice_<List, ListSize, 0, 0, PadType>
{
	using type = List;
};

/// Creates a new list from range (First, Last].
template<class List, size_t First, size_t Last >
struct tl_slice
{
	using type
		= typename tl_slice_<
		List,
		tl_size<List>::value,
		(First > Last ? Last : First),
		Last
		>::type;
};

/// Create a new list that containing the last `N` elements
template<class List, size_t NewSize, size_t OldSize = tl_size<List>::value>
struct tl_right
{
	static constexpr size_t first_idx = OldSize > NewSize ? OldSize - NewSize : 0;
	using type = typename tl_slice_<List, first_idx, OldSize>::type;
};

template<class List, size_t N>
struct tl_right<List, N, N>
{
	using type = List;
};

template<size_t N>
struct tl_right<empty_type_list, N, 0>
{
	using type = empty_type_list;
};

template<>
struct tl_right<empty_type_list, 0, 0>
{
	using type = empty_type_list;
};


/*!
 *   @param   ListA  需要被zip的type list
 *   @param   ListB  需要被zip的type list
 *   @param   Fun    zip动作
 *   @return  
 *   @note    需要满足sizeof(ListA) == sizeof(ListB)
 *           e.g. tl_zip< type_list<int, double>, type_list<float, string> >::type
 *                is type_list<type_pair<int, float>, type_pair<double, string> >
 */

template<class ListA, class ListB,
			template<class, typename> class Fun = to_type_pair>
struct tl_zip_impl;

template<class... LhsElements, class... RhsElements,
			template<class, typename> class Fun>
struct tl_zip_impl<type_list<LhsElements...>, type_list<RhsElements...>, Fun>
{
	static_assert(sizeof...(LhsElements) == sizeof...(RhsElements),
		"List have different size");
	using type = type_list<typename Fun<LhsElements, RhsElements>::type...>;
};

template<class ListA, class ListB, template<class, class> class Fun>
struct tl_zip
{
	static constexpr size_t sizea = tl_size<ListA>::value;
	static constexpr size_t sizeb = tl_size<ListB>::value;
	static constexpr size_t result_size = (sizea < sizeb) ? sizea : sizeb;
	using type =
		typename tl_zip_impl<
			typename tl_slice<ListA, 0, result_size>::type,
			typename tl_slice<ListB, 0, result_size>::type,
			Fun
		>::type;
};

/// Equal to `tl_zip(tl_right(ListA, N), tl_right(rightB, N), Fun)`
template<class ListA, class ListB, template<class, class> class Fun, size_t N>
struct tl_zip_right
{
	using type =
		typename tl_zip_impl<
			typename tl_right<ListA, N>::type,
			typename tl_right<ListB, N>::type,
			Fun
		>::type;
};

template<class ListA, class ListB,
			typename PadA = unit_t, typename PadB = unit_t,
		template<class, typename> class Fun = to_type_pair>
struct tl_zip_all
{
	static constexpr size_t result_size =
		(tl_size<ListA>::value > tl_size<ListB>) ? tl_size<ListA>::value 
												 : tl_size<ListB>::value;
	using type =
		typename tl_zip_impl<
			typename tl_slice_<ListA, tl_size<ListA>::value, 0, result_size>::type,
			typename tl_slice_<ListB, tl_size<ListB>::value, 0, result_size>::type,
			Fun
		>::type;
};

template<class ListA>
struct tl_unzip;

template <class... Elements>
struct tl_unzip<type_list<Elements...> >
{
	using first = type_list<typename Elements::first...>;
	using second = type_list<typename Elements::second...>;
};


/*!
 *   @param   list  要查询的type list
 *   @param   type  要查询的type
 *   @return  返回type在list中的索引值
 *   @note    int index_of(list, type)
 */

template<int Pos, class X, class... Ts>
struct tl_index_of_impl;

template<int Pos, class X>
struct tl_index_of_impl<Pos, X>
{
	static constexpr int value = -1;
};

template<int Pos, class X, class... Ts>
struct tl_index_of_impl<Pos, X, X, Ts...>
{
	static constexpr int value = Pos;
};

template<int Pos, class X, class T, class... Ts>
struct tl_index_of_impl<Pos, X, T, Ts...>
{
	static constexpr int value = tl_index_of_impl<Pos + 1, X, Ts...>::value;
};

template<class List, class T>
struct tl_index_of;

template<class... Ts, class T>
struct tl_index_of<type_list<Ts...>, T>
{
	static constexpr int value = tl_index_of_impl<0, T, Ts...>::value;
};

/*!
 *   @param   list  查询所在的type list
 *   @param   predicate  谓词，表示一个判断条件
 *   @return  返回符合predicate的索引值
 *   @note    int index_where(list, predicate)
 */
template<int Pos, template<class> class Pred, class... Ts>
struct tl_index_where_impl;

template<int Pos, template<class> class Pred>
struct tl_index_where_impl<Pos, Pred>
{
	static constexpr int value = -1;
};

template<int Pos, template<class> class Pred, class T, class... Ts>
struct tl_index_where_impl<Pos, Pred, T, Ts...>
{
	static constexpr int value =
		Pred<T>::value ? Pos : tl_index_where_impl<Pos + 1, Pred, Ts...>::value;
};

template<class List, template<class> class Pred>
struct tl_index_where;

template<class... Ts, template<class> class Pred>
struct tl_index_where<type_list<Ts...>, Pred>
{
	static constexpr int value = tl_index_where_impl<0, Pred, Ts...>::value;
};

/*!
 *   @param   list  需要被reverse的type list
 *   @return  返回一个新的type list, 反转了原type list的顺序
 *   @note    list reverse(list)
 */
template <class From, class... Elements>
struct tl_reverse_impl;

template <class T0, class... T, class... E>
struct tl_reverse_impl<type_list<T0, T...>, E...> 
{
	using type = typename tl_reverse_impl<type_list<T...>, T0, E...>::type;
};

template <class... E>
struct tl_reverse_impl<empty_type_list, E...> 
{
	using type = type_list<E...>;
};

/// Creates a new list with elements in reversed order.
template <class List>
struct tl_reverse 
{
	using type = typename tl_reverse_impl<List>::type;
};


/*!
 *   @param   list  被查找的type list
 *   @param   type  需要查找的type
 *   @return  返回type list中是否存在type
 *   @note    bool find(list, type)
 */
// bool find(list, type)

/// Finds the first element of type `What` beginning at index `Pos`.
template <template <class> class Pred, class... Ts>
struct tl_find_impl;

template <template <class> class Pred>
struct tl_find_impl<Pred> 
{
	using type = none_t;
};

template <template <class> class Pred, class T, class... Ts>
struct tl_find_impl<Pred, T, Ts...> 
{
	using type =
		typename std::conditional<
		Pred<T>::value,
		T,
		typename tl_find_impl<Pred, Ts...>::type
		>::type;
};

/// Finds the first element satisfying `Pred` beginning at index `Pos`.
template <class List, template <class> class Pred>
struct tl_find;

template <class... Ts, template <class> class Pred>
struct tl_find<type_list<Ts...>, Pred> 
{
	using type = typename tl_find_impl<Pred, Ts...>::type;
};

/*!
 *   @param   list		被检查的type list
 *   @param   predicate 谓词，表示一个判断条件
 *   @return  返回是否list中所有类型全部满足predicate
 *   @note    bool forall(List, predicate)
 */

/// Tests whether a predicate holds for all elements of a list.
template <class List, template <class> class Pred>
struct tl_forall 
{
	static constexpr bool value =
		Pred<typename tl_head<List>::type>::value
		&& tl_forall<typename tl_tail<List>::type, Pred>::value;
};

template <template <class> class Pred>
struct tl_forall<empty_type_list, Pred> 
{
	static constexpr bool value = true;
};

template <class ListA, class ListB, template <class, class> class Pred>
struct tl_forall2_impl 
{
	static constexpr bool value =
		Pred<typename tl_head<ListA>::type,
		typename tl_head<ListB>::type>::value
		&& tl_forall2_impl<typename tl_tail<ListA>::type,
		typename tl_tail<ListB>::type, Pred>::value;
};

template <template <class, typename> class Pred>
struct tl_forall2_impl<empty_type_list, empty_type_list, Pred> 
{
	static constexpr bool value = true;
};

/// Tests whether a binary predicate holds for all
///    corresponding elements of `ListA` and `ListB`.
template <class ListA, class ListB, template <class, class> class Pred>
struct tl_binary_forall 
{
	static constexpr bool value =
		tl_size<ListA>::value == tl_size<ListB>::value
		&& tl_forall2_impl<ListA, ListB, Pred>::value;
};

/*!
 *   @param   list 被检查的type list
 *   @param   predicate 谓词，通常指一个判断条件
 *   @return  返回list是否存在满足predicate的type
 *   @note    bool tl_exists(list, predicate)
 */

 /// Tests whether a predicate holds for some of the elements of a list.
template <class List, template <class> class Pred>
struct tl_exists 
{
	static constexpr bool value =
		Pred<typename tl_head<List>::type>::value
		|| tl_exists<typename tl_tail<List>::type, Pred>::value;
};

template <template <class> class Pred>
struct tl_exists<empty_type_list, Pred> 
{
	static constexpr bool value = false;

};

/*!
 *   @param   list  被检查的变量
 *   @param   predicate  谓词，作为判断条件
 *   @return  返回List中满足predicate的数目
 *   @note    size_t count(list, predicate)
 */

/// Counts the number of elements in the list which satisfy a predicate.
template <class List, template <class> class Pred>
struct tl_count 
{
	static constexpr size_t value =
		(Pred<typename tl_head<List>::type>::value ? 1 : 0)
		+ tl_count<typename tl_tail<List>::type, Pred>::value;
};

template <template <class> class Pred>
struct tl_count<empty_type_list, Pred> 
{
	static constexpr size_t value = 0;
};

template <class List, template <class> class Pred>
constexpr size_t tl_count<List, Pred>::value;

/*!
 *   @param   list  被检查的type list
 *   @param   type  需要检查的type
 *   @return  返回list中type的个数
 *   @note    size_t count_type(list, type)
 */

/// Counts the number of elements in the list which are equal to `T`.
template <class List, class T>
struct tl_count_type 
{
	static constexpr size_t value =
		(std::is_same<typename tl_head<List>::type, T>::value ? 1 : 0)
		+ tl_count_type<typename tl_tail<List>::type, T>::value;
};

template <class T>
struct tl_count_type<empty_type_list, T> 
{
	static constexpr size_t value = 0;
};

template <class List, class T>
constexpr size_t tl_count_type<List, T>::value;

/*!
 *   @param   list  被检查的List
 *   @param   predicate 谓词，作为判断条件
 *   @return  返回list中不满足predicate的个数
 *   @note    size_t count_not(list, predicate)
 */

/// Counts the number of elements in the list which satisfy a predicate.
template <class List, template <class> class Pred>
struct tl_count_not 
{
	static constexpr size_t value =
		(Pred<typename tl_head<List>::type>::value ? 0 : 1) +
		tl_count_not<typename tl_tail<List>::type, Pred>::value;

};

template <template <class> class Pred>
struct tl_count_not<empty_type_list, Pred> 
{
	static constexpr size_t value = 0;

};


/*!
 *   @param   lista  需要concate的list
 *   @param   listb  需要concate的list
 *   @return  返回一个concate lista, listb, ...之后的list
 *   @note    list tl_concat(list, list, ...)
 */

template <class ListA, class ListB>
struct tl_concat_impl;

/// Concatenates two lists.
template <class... LhsTs, class... RhsTs>
struct tl_concat_impl<type_list<LhsTs...>, type_list<RhsTs...>> 
{
	using type = type_list<LhsTs..., RhsTs...>;
};

/// Concatenates lists.
template <class... Lists>
struct tl_concat;

template <class List0>
struct tl_concat<List0> 
{
	using type = List0;
};

template <class List0, class List1, class... Lists>
struct tl_concat<List0, List1, Lists...> 
{
	using type =
		typename tl_concat<
		typename tl_concat_impl<List0, List1>::type,
		Lists...
		>::type;
};

/*!
 *   @param   list  被push的list
 *   @param   type  需要push的type
 *   @return  将type push_back到list
 *   @note    list push_back(list, type)
 */

template <class List, class What>
struct tl_push_back;

/// Appends `What` to given list.
template <class... ListTs, class What>
struct tl_push_back<type_list<ListTs...>, What> 
{
	using type = type_list<ListTs..., What>;

};

/*!
 *   @param   list  被push_front的list
 *   @param   type  需要push的type
 *   @return  将type push_front到List
 *   @note    list push_front(list, type)
 */

template <class List, class What>
struct tl_push_front;

/// Appends `What` to given list.
template <class... ListTs, class What>
struct tl_push_front<type_list<ListTs...>, What> 
{
	using type = type_list<What, ListTs...>;
};

/// Alias for `tl_push_front<List, What>`.
template <class What, class List>
struct tl_cons : tl_push_front<List, What> 
{
	// nop
};

/*!
 *   @param   list  需要被操作的type list
 *   @param   trait 对list中每个元素进行的操作
 *   @return  对List中进行trait后得到新的type list
 *   @note    list tl_map(list, trait)
 */

template <class T, template <class> class... Funs>
struct tl_apply_all;

template <class T>
struct tl_apply_all<T> 
{
	using type = T;
};

template <class T, template <class> class Fun0, template <class> class... Funs>
struct tl_apply_all<T, Fun0, Funs...> 
{
	using type = typename tl_apply_all<typename Fun0<T>::type, Funs...>::type;
};

/// Creates a new list by applying a "template function" to each element.
template <class List, template <class> class... Funs>
struct tl_map;

template <class... Ts, template <class> class... Funs>
struct tl_map<type_list<Ts...>, Funs...> 
{
	using type = type_list<typename tl_apply_all<Ts, Funs...>::type...>;
};

/*!
 *   @param   list  被检查的type lsit
 *   @param   trait 条件
 *   @param   result list返回每个元素的执行结果
 *   @param   fun   执行的动作
 *   @return  返回执行fun之后的新的list
 *   @note    list tl_map_condition(list, trait, fun)
 */
/// Creates a new list by applying a `Fun` to each element which
///    returns `TraitResult` for `Trait`.
template <class List, template <class> class Trait, bool TRes,
	template <class> class... Funs>
struct tl_map_conditional 
{
	using type =
		typename tl_concat<
		type_list<
		typename std::conditional<
		Trait<typename tl_head<List>::type>::value == TRes,
		typename tl_apply_all<typename tl_head<List>::type, Funs...>::type,
		typename tl_head<List>::type
		>::type
		>,
		typename tl_map_conditional<
		typename tl_tail<List>::type,
		Trait, TRes, Funs...
		>::type
		>::type;
};

template <template <class> class Trait, bool TraitResult,
	template <class> class... Funs>
struct tl_map_conditional<empty_type_list, Trait, TraitResult, Funs...> 
{
	using type = empty_type_list;
};


/*!
 *   @param   list  被pop的list
 *   @return  返回执行了pop_back后的新list，
 *   @note    list pop_back(list)
 */
// list pop_back()

/// Creates a new list with all but the last element of `List`.
template <class List>
struct tl_pop_back 
{
	using type = typename tl_slice<List, 0, tl_size<List>::value - 1>::type;
};

template <>
struct tl_pop_back<empty_type_list> 
{
	using type = empty_type_list;
};


/*!
 *   @param   list 
 *   @param   back  要替换到list最后的变量
 *   @return  返回一个替换了list最后一个变量的新list
 *   @note    list replace_back()
 */

/// Creates a new list with all but the last element of `List`
/// and append `T` to the new list.
template <class List, class Back, class Intermediate = type_list<>>
struct tl_replace_back;

template <class T0, class T1, class... Ts, class Back, class... Us>
struct tl_replace_back<type_list<T0, T1, Ts...>, Back, type_list<Us...>>
	: tl_replace_back<type_list<T1, Ts...>, Back, type_list<Us..., T0>> {};

template <class T, class Back, class... Us>
struct tl_replace_back<type_list<T>, Back, type_list<Us...>> 
{
	using type = type_list<Us..., Back>;
};

/*!
 *   @param   list
 *   @param   size_t  查找的索引值
 *   @return  如果找到，则返回type, 否则返回unit_t
 *   @note    type at(list, size_t)
 */

template <size_t N, class... E>
struct tl_at_impl;

template <size_t N, typename E0, class... E>
struct tl_at_impl<N, E0, E...> 
{
	using type = typename tl_at_impl<N - 1, E...>::type;
};

template <class E0, class... E>
struct tl_at_impl<0, E0, E...> 
{
	using type = E0;
};

template <size_t N>
struct tl_at_impl<N> 
{
	using type = unit_t; // no such element
};

template <class List, size_t N>
struct tl_at;

/// Gets element at index `N` of `List`.
template <size_t N, class... E>
struct tl_at<type_list<E...>, N> 
{
	using type = typename tl_at_impl<N, E...>::type;
};

/*!
 *   @param   list 
 *   @param   type  要prepend的类型
 *   @return  返回对list prepend type之后的新list
 *   @note    list prepend(list, type)
 */
// list prepend(type)

template <class List, class What>
struct tl_prepend;

/// Creates a new list with `What` prepended to `List`.
template <class What, class... T>
struct tl_prepend<type_list<T...>, What> 
{
	using type = type_list<What, T...>;
};

// list filter(predicate)
// list filter_not(predicate)

template <class List, bool... Selected>
struct tl_filter_impl;

template <>
struct tl_filter_impl<empty_type_list>
{
	using type = empty_type_list;
};

template <class T0, class... T, bool... S>
struct tl_filter_impl<type_list<T0, T...>, false, S...> 
{
	using type = typename tl_filter_impl<type_list<T...>, S...>::type;
};

template <class T0, class... T, bool... S>
struct tl_filter_impl<type_list<T0, T...>, true, S...> 
{
	using type =
		typename tl_prepend<
		typename tl_filter_impl<
		type_list<T...>,
		S...
		>::type,
		T0
		>::type;
};

template <class List, template <class> class Pred>
struct tl_filter;

/// Create a new list containing all elements which satisfy `Pred`.
template <template <class> class Pred, class... T>
struct tl_filter<type_list<T...>, Pred> 
{
	using type =
		typename tl_filter_impl<
		type_list<T...>,
		Pred<T>::value...
		>::type;
};

/// Creates a new list containing all elements which
///    do not satisfy `Pred`.
template <class List, template <class> class Pred>
struct tl_filter_not;

template <template <class> class Pred>
struct tl_filter_not<empty_type_list, Pred> 
{
	using type = empty_type_list;
};

template <template <class> class Pred, class... T>
struct tl_filter_not<type_list<T...>, Pred> 
{
	using type =
		typename tl_filter_impl<
		type_list<T...>,
		!Pred<T>::value...
		>::type;
};

/// Creates a new list containing all elements which
///    are equal to `Type`.
template <class List, class Type>
struct tl_filter_type;

template <class Type, class... T>
struct tl_filter_type<type_list<T...>, Type> 
{
	using type =
		typename tl_filter_impl<
		type_list<T...>,
		!std::is_same<T, Type>::value...
		>::type;
};

/// Creates a new list containing all elements which
///    are not equal to `Type`.
template <class List, class Type>
struct tl_filter_not_type;

template <class Type, class... T>
struct tl_filter_not_type<type_list<T...>, Type> 
{
	using type =
		typename tl_filter_impl<
		type_list<T...>,
		(!std::is_same<T, Type>::value)...
		>::type;
};

// list distinct(list)

/// Creates a new list from `List` without any duplicate elements.
template <class List>
struct tl_distinct;

template <>
struct tl_distinct<empty_type_list> 
{
	using type = empty_type_list;
};

template <class T0, class... Ts>
struct tl_distinct<type_list<T0, Ts...>> 
{
	using type =
		typename tl_concat<
		type_list<T0>,
		typename tl_distinct<
		typename tl_filter_type<
		type_list<Ts...>,
		T0
		>::type
		>::type
		>::type;
};

// bool is_distinct

/// Tests whether a list is distinct.
template <class L>
struct tl_is_distinct 
{
	static constexpr bool value =
		tl_size<L>::value == tl_size<typename tl_distinct<L>::type>::value;
};

// list resize(list, size, fill_type)

template <class List, bool OldSizeLessNewSize, size_t OldSize, size_t NewSize,
	class FillType>
	struct tl_pad_right_impl;

template <class List, size_t OldSize, size_t NewSize, class FillType>
struct tl_pad_right_impl<List, false, OldSize, NewSize, FillType> 
{
	using type = typename tl_slice<List, 0, NewSize>::type;
};

template <class List, size_t Size, class FillType>
struct tl_pad_right_impl<List, false, Size, Size, FillType> 
{
	using type = List;
};

template <class List, size_t OldSize, size_t NewSize, class FillType>
struct tl_pad_right_impl<List, true, OldSize, NewSize, FillType> 
{
	using type =
		typename tl_pad_right_impl<
		typename tl_push_back<List, FillType>::type,
		OldSize + 1 < NewSize,
		OldSize + 1,
		NewSize,
		FillType
		> ::type;
};

/// Resizes the list to contain `NewSize` elements and uses
///    `FillType` to initialize the new elements with.
template <class List, size_t NewSize, class FillType = unit_t>
struct tl_pad_right 
{
	using type =
		typename tl_pad_right_impl<
		List,
		(tl_size<List>::value < NewSize),
		tl_size<List>::value,
		NewSize,
		FillType
		>::type;
};

// bool pad_left(list, N)

template <class List, size_t OldSize, size_t NewSize, class FillType>
struct tl_pad_left_impl 
{
	using type =
		typename tl_pad_left_impl<
		typename tl_push_front<
		List,
		FillType
		>::type,
		OldSize + 1,
		NewSize,
		FillType
		>::type;
};

template <class List, size_t Size, class FillType>
struct tl_pad_left_impl<List, Size, Size, FillType> 
{
	using type = List;
};

/// Resizes the list to contain `NewSize` elements and uses
///    `FillType` to initialize prepended elements with.
template <class List, size_t NewSize, class FillType = unit_t>
struct tl_pad_left 
{
	static constexpr size_t list_size = tl_size<List>::value;
	using type =
		typename tl_pad_left_impl<
		List,
		list_size,
		(list_size > NewSize) ? list_size : NewSize,
		FillType
		>::type;
};

// bool is_zipped(list)

template <class List>
struct tl_is_zipped 
{
	static constexpr bool value = tl_forall<List, is_type_pair>::value;
};

/// Removes trailing `What` elements from the end.
template <class List, class What = unit_t>
struct tl_trim 
{
	using type =
		typename std::conditional<
		std::is_same<typename tl_back<List>::type, What>::value,
		typename tl_trim<typename tl_pop_back<List>::type, What>::type,
		List
		>::type;
};

template <class What>
struct tl_trim<empty_type_list, What> 
{
	using type = empty_type_list;
};

// list union(list1, list2)

template <class... Xs>
struct tl_union 
{
	using type = typename tl_distinct<typename tl_concat<Xs...>::type>::type;
};

// list intersect(list1, list2)

template <class List,
	bool HeadIsUnique =
	tl_count_type<List, typename tl_head<List>::type>::value == 1>
	struct tl_intersect_impl;

template <>
struct tl_intersect_impl<empty_type_list, false>
{
	using type = empty_type_list;
};

template <class T0, class... Ts>
struct tl_intersect_impl<type_list<T0, Ts...>, true>
{
	using type = typename tl_intersect_impl<type_list<Ts...>>::type;
};

template <class T0, class... Ts>
struct tl_intersect_impl<type_list<T0, Ts...>, false> 
{
	using type =
		typename tl_concat<
		type_list<T0>,
		typename tl_intersect_impl<
		typename tl_filter_type<
		type_list<Ts...>,
		T0
		>::type
		>::type
		>::type;
};

template <class... Ts>
struct tl_intersect 
{
	using type =
		typename tl_intersect_impl<
		typename tl_concat<Ts...>::type
		>::type;
};

// list group_by(list, predicate)

template <bool Append, class What, class Where>
struct tl_group_by_impl_step;

template <class What, class... Ts>
struct tl_group_by_impl_step<true, What, type_list<Ts...>> 
{
	using type = type_list<type_list<Ts..., What>>;
};

template <class What, class List>
struct tl_group_by_impl_step<false, What, List> 
{
	using type = type_list<List, type_list<What>>;
};

template <class In, class Out, template <class, typename> class Pred>
struct tl_group_by_impl 
{
	using last_group = typename tl_back<Out>::type;
	using suffix =
		typename tl_group_by_impl_step<
		Pred<
		typename tl_head<In>::type,
		typename tl_back<last_group>::type
		>::value,
		typename tl_head<In>::type,
		last_group
		>::type;
	using prefix = typename tl_pop_back<Out>::type;
	using new_out = typename tl_concat<prefix, suffix>::type;
	using type =
		typename tl_group_by_impl<
		typename tl_tail<In>::type,
		new_out,
		Pred
		>::type;
};

template <template <class, class> class Pred, class T0, class... Ts>
struct tl_group_by_impl<type_list<T0, Ts...>, empty_type_list, Pred> 
{
	using type =
		typename tl_group_by_impl<
		type_list<Ts...>,
		type_list<type_list<T0>>,
		Pred
		>::type;
};

template <class Out, template <class, typename> class Pred>
struct tl_group_by_impl<empty_type_list, Out, Pred> 
{
	using type = Out;
};

template <class List, template <class, typename> class Pred>
struct tl_group_by 
{
	using type =
		typename tl_group_by_impl<
		List,
		empty_type_list,
		Pred
		>::type;
};

/// Applies the types of the list to `VarArgTemplate`.
template <class List, template <class...> class VarArgTemplate>
struct tl_apply;

template <class... Ts, template <class...> class VarArgTemplate>
struct tl_apply<type_list<Ts...>, VarArgTemplate> 
{
	using type = VarArgTemplate<Ts...>;
};

// bool contains(list, x)

template <class List, class X>
struct tl_contains;

template <class X>
struct tl_contains<type_list<>, X> : std::false_type {};

template <class... Ts, class X>
struct tl_contains<type_list<X, Ts...>, X> : std::true_type {};

template <class T, class... Ts, class X>
struct tl_contains<type_list<T, Ts...>, X> : tl_contains<type_list<Ts...>, X> {};

// subset_of(list, list)

template <class ListA, class ListB, bool Fwd = true>
struct tl_subset_of;

template <class List>
struct tl_subset_of<type_list<>, List, true> : std::true_type {};

template <class ListA, class ListB>
struct tl_subset_of<ListA, ListB, false> : std::false_type {};

template <class T, class... Ts, class List>
struct tl_subset_of<type_list<T, Ts...>, List>
	: tl_subset_of<type_list<Ts...>, List, tl_contains<List, T>::value> {};

/// Tests whether ListA contains the same elements as ListB
/// and vice versa. This comparison ignores element positions.
template <class ListA, class ListB>
struct tl_equal 
{
	static constexpr bool value = tl_subset_of<ListA, ListB>::value
		&& tl_subset_of<ListB, ListA>::value;
};

template <size_t N, class T>
struct tl_replicate 
{
	using type = typename tl_cons<T, typename tl_replicate<N - 1, T>::type>::type;
};

template <class T>
struct tl_replicate<0, T> 
{
	using type = type_list<>;
};


} // namespace detail
} // namespace cell

#endif /*CELL_TYPE_LIST_HPP*/