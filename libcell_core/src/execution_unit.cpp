

#include "cell/execution_unit.hpp"

cell::execution_unit::execution_unit(actor_system *sys)
	:system_(sys)
	, proxies_(nullptr)
{
	// nop
}

cell::execution_unit::~execution_unit()
{
	// nop
}
