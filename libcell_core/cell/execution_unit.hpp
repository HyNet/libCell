/*!
 * @file execution_unit.hpp
 * @brief ��ִ�е�Ԫ��ʶ
 *
 *  ���ڳ��������һ����ִ�е�Ԫ
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
	 * @brief ִ�е�Ԫ�ı�ʶ(Identifies an execution unit)
	 *
	 * ���磺schedular�Ĺ����߳�, actor����ͨ����ȡ��execution unit ����������context information
	 *
	 * @author atom
	 * @date 2017/01/24
	 */
	class execution_unit
	{
	public:
		explicit execution_unit(actor_system *sys);

		// ��ֹ�������캯��
		execution_unit(const execution_unit&) = delete;
		execution_unit(execution_unit&&) = delete;
		virtual ~execution_unit();

		/*!
		 *   @param   ptr  ��ptr����execution unit�Ĺ�������
		 *   @return  void
		 *   @note    ��Ҫע�������
		 *   @warning ֻ�ܱ���ǰexecution unit����ִ�е�{@link resumable}����
		 */
		virtual void exec_later(resumable *ptr) = 0;

		/*!
		 *   @param   void
		 *   @return  ���ص�ǰexecution��enclosing actor system
		 *   @warning һ��Ҫ��actor ����resume֮ǰ����
		 */
		actor_system& system() const
		{
			CELL_ASSERT(system_ != nullptr);
			return *system_;
		}

		/*!
		 *   @param   void
		 *   @return  ���ص�ǰexecution unit������proxy factory
		 */
		proxy_registry* proxy_registry_ptr()
		{
			return proxies_;
		}

		/*!
		 *   @param   ptr  Ϊ��ǰexecution unit ����һ��proxy factory
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