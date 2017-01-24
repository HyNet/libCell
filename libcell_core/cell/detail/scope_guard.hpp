/*!
 * @file scope_guard.hpp
 * @brief scope guard ʵ��
 *
 *  scope guard�ļ���ʵ��
 *
 * @author atom
 * @date 2017/01/24
 * @version 0.1.0
 * @note
 */

#ifndef CELL_SCOPE_GUARD_HPP
#define CELL_SCOPE_GUARD_HPP

#include <utility>

namespace cell {
namespace detail {

template<class Fun>
class scope_guard
{
	scope_guard() = delete;
	scope_guard(const scope_guard&) = delete;
	scope_guard& operator=(const scope_guard&) = delete;

public:
	scope_guard(Fun f)
		:fun_(std::move(f))
		,enable_(true)
	{
		//nop
	}

	scope_guard(scope_guard&& other)
		:fun_(std::move(other.fun_))
		,enable_(other.enable_)
	{
		other.enable_ = false;
	}

	~scope_guard()
	{
		if (enable_)
		{
			fun_();
		}
	}
	
	/*!
	 *   @param   void 
	 *   @return  ʹ�˳�ʱ��������Դ������
	 */
	inline disable() { enable_ == false;  }

private:
	Fun fun_;
	bool enable_;
};


/*!
 *   @param   f  scope guard�˳�ʱִ�еĶ���
 *   @return  ����һ��scope guard�����˳�scope��ʱ��ִ��f
 *   @relates scope_guard
 */
template<class Fun>
scope_guard<Fun> make_scope_guard(Fun f)
{
	return{ std::move(f) };
}

} // namespace detail
} // namespace cell

#endif /*CELL_SCOPE_GUARD_HPP*/