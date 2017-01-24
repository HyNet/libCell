/*!
 * @file execution_unit.hpp
 * @brief 可执行单元标识
 *
 *  用于抽象的描述一个可执行单元
 *
 * @author atom
 * @date 2017/01/24
 * @version 0.1.0
 * @note
 */

#ifndef CELL_EXECUTION_UNIT
#define CELL_EXECUTION_UNIT

#include "cell/fwd.hpp"

#include "cell/config.hpp"

namespace cell {

	/*!
	 * @class execution_unit
	 *
	 * @brief 执行单元的标识(Identifies an execution unit)
	 *
	 * 例如：schedular的工作线程, actor可以通过获取其execution unit 来访问其他context information
	 *
	 * @author atom
	 * @date 2017/01/24
	 */
	class execution_unit
	{
	public:
		explicit execution_unit(actor_system *sys);

		// 禁止拷贝构造函数
		execution_unit(const execution_unit&) = delete;
		execution_unit(execution_unit&&) = delete;
		virtual ~execution_unit();

		/*!
		 *   @param   ptr  将ptr加入execution unit的工作队列
		 *   @return  void
		 *   @note    需要注意的问题
		 *   @warning 只能被当前execution unit正在执行的{@link resumable}调用
		 */
		virtual void exec_later(resumable *ptr) = 0;

		/*!
		 *   @param   void
		 *   @return  返回当前execution的enclosing actor system
		 *   @warning 一定要在actor 调用resume之前设置
		 */
		actor_system& system() const
		{
			CELL_ASSERT(system_ != nullptr);
			return *system_;
		}

		/*!
		 *   @param   void
		 *   @return  返回当前execution unit关联的proxy factory
		 */
		proxy_registry* proxy_registry_ptr()
		{
			return proxies_;
		}

		/*!
		 *   @param   ptr  为当前execution unit 关联一个proxy factory
		 *   @return  void
		 */
		void proxy_registry_ptr(proxy_registry *ptr)
		{
			proxies_ = ptr;
		}

	protected:
		actor_system *system_;
		proxy_registry *proxies_;

	};

} // namespace cell

#endif /*CELL_EXECUTION_UNIT*/