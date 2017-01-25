/*!
 * @file atom.hpp
 * @brief 简要说明
 *
 *  详细说明
 *
 * @author
 * @date 2017/01/25
 * @version
 * @note
 */

#ifndef CELL_ATOM_HPP
#define CELL_ATOM_HPP

#include <string>
#include <functional>
#include <type_traits>

#include "cell/detail/atom_val.hpp"

namespace cell {

/*!
 * @class atom_value
 *
 * @brief 定义atom的值类型
 *
 * 关于enum class 参考链接:https://zhuanlan.zhihu.com/p/21722362
 *
 * @author atom
 * @date 2017/01/25
 */
enum class atom_value : uint64_t
{
	/// @cond PRIVATE
	dirty_little_hack = 31337
	/// @endcond
};


/*!
 *   @param   what  atom_value
 *   @return  atom_value对应的字符串
 *   @relates atom_value
 *   @note    返回字符串的size == 11
 */
std::string to_string(const atom_value& what);

/*!
 *   @param   x  需要转换成atom_value的字符串
 *   @return  参数x对应的atom_value;
 *   @note    x限制在10个字符内
 */
atom_value atom_from_string(const std::string& x);

/*!
 *   @param   str  需要转换的字符串字面值
 *   @param   Size 字符串数组的大小（包含NULL terminator）
 *   @return  将给定的字符串字面值转化为atom_value
 *   @note    str需要有NULL terminator
 */
template<size_t Size>
constexpr atom_value atom(char const (&str)[Size])
{
	static_assert(Size <= 11, "only 10 characters are allowed");
	return static_cast<atom_value>(detail::atom_val(str));
}


/*!
 * @class atom_constant
 *
 * @brief 将atom_value转化为编译时的常量
 *
 * 通过将atom_value转化为编译时的常量可以利用元编程在编译时计算结果
 *
 * @author T440
 * @date 2017/01/25
 */
template<atom_value V>
struct atom_constant
{
	constexpr atom_constant()
	{
		// nop
	}

	/*!
	 *   @param   void  被测试变量
	 *   @param   V  特化的atom_value
	 *   @return  返回包装后的值
	 */
	constexpr operator atom_value() const
	{
		return V;
	}

	static constexpr uint64_t uint_value()
	{
		return static_cast<uint64_t>(V);
	}

	/// Returns an instance *of this constant* (*not* an `atom_value`).
	static const atom_constant value;
};

template<class T>
struct is_atom_constant
{
	static constexpr bool value = false;
};

template<atom_value X>
struct is_atom_constant< atom_constant<X> >
{
	static constexpr bool value = true;
};

template<atom_value V>
std::string to_string(const atom_constant<V>&)
{
	return to_string(V);
}

template<atom_value V>
const atom_constant<V> atom_constant<V>::value = atom_constant<V>{}

/// atom used for add operation
using add_atom = atom_constant<atom("add")>;

/// atom used for get operation
using get_atom = atom_constant<atom("get")>;

/// atom used for put operation
using put_atom = atom_constant<atom("put")>;

/// atom used for signalizing update, e.g., in a key-value store
using update_atom = atom_constant<atom("update")>;

/// atom used for delete operation
using delete_atom = atom_constant<atom("delete")>;

/// atom used for response message
using ok_atom = atom_constant<atom("ok")>;

/// atom used for triggering system-level message handling
using sys_atom = atom_constant<atom("sys")>;

/// atom used for signaling group subscriptions
using join_atom = atom_constant<atom("join")>;

/// atom used for signaling group unsubscriptions
using leave_atom = atom_constant<atom("leave")>;

/// atom used for signaling forwarding paths
using forward_atom = atom_constant<atom("forward")>;

/// atom used for buffer management
using flush_atom = atom_constant<atom("flush")>;

/// atom used for I/O redirection
using redirect_atom = atom_constant<atom("redirect")>;

/// atom used for link request over network
using link_atom = atom_constant<atom("link")>;

/// atom used for unlink network request
using unlink_atom = atom_constant<atom("unlink")>;

/// atom used for publish actor at a given port
using publish_atom = atom_constant<atom("publish")>;

/// atom used for remove an actor/port mapping
using unpublish_atom = atom_constant<atom("unpublish")>;

/// Used for signalizing group membership.
using subscribe_atom = atom_constant<atom("subscribe")>;

/// Used for withdrawing group membership.
using unsubscribe_atom = atom_constant<atom("unsubscrib")>;

/// Used for establishing network connections.
using connect_atom = atom_constant<atom("connect")>;

/// Used for opening ports or files.
using open_atom = atom_constant<atom("open")>;

/// Used for closing ports or files.
using close_atom = atom_constant<atom("close")>;

/// Used for spawning remote actors.
using spawn_atom = atom_constant<atom("spawn")>;

/// Used for migrating actors to other nodes.
using migrate_atom = atom_constant<atom("migrate")>;

/// Used for triggering periodic operations.
using tick_atom = atom_constant<atom("tick")>;

/// Used as config parameter for the `logger`.
using trace_log_lvl_atom = atom_constant<atom("TRACE")>;

/// Used as config parameter for the `logger`.
using debug_log_lvl_atom = atom_constant<atom("DEBUG")>;

/// Used as config parameter for the `logger`.
using info_log_lvl_atom = atom_constant<atom("INFO")>;

/// Used as config parameter for the `logger`.
using warning_log_lvl_atom = atom_constant<atom("WARNING")>;

/// Used as config parameter for the `logger`.
using error_log_lvl_atom = atom_constant<atom("ERROR")>;

/// Used as config parameter for the `logger`.
using quiet_log_lvl_atom = atom_constant<atom("QUIET")>;

} // namespace cell

namespace std {

/*!
 *   @param   x  cell::atom_value
 *   @return  返回对cell::atom_value的hash值
 *   @note    对模板std::hash进行cell::atom特例化
 */
template<>
struct hash<cell::atom_value>
{
	size_t operator()(cell::atom_value x) const
	{
		hash<uint64_t> f;
		return f(static_cast<uint64_t>(x));
	}
};

}

#endif /*CELL_ATOM_HPP*/