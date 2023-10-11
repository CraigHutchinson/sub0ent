#include "Enti\PoolRegistry.h"
#include "Enti\Pools.h"

#include "TestTypes.h"
#include <gtest/gtest.h>

namespace Enti {
	namespace Test 
	{

		TEST(Pool,Create)
		{
			PoolRegistry poolRegistry;
			Pool<Human> humanPool(poolRegistry);
			ASSERT_NE( nullptr, humanPool.create( 0U, Human() ) );
		}


	} //END: Test
} //END: Enti



