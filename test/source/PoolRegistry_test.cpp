#include "Enti\PoolRegistry.h"

#include "Enti\Pools.h"

#include "TestTypes.h"
#include <gtest/gtest.h>

namespace Enti {
namespace Test 
{

	TEST(PoolRegistry,Pool_Register)
	{
		PoolRegistry poolRegistry;
		Pool<Human> humanPool(poolRegistry);
		Pool<Health> healthPool(poolRegistry);
		Pool<Hat> hatPool(poolRegistry);

		ASSERT_EQ( &poolRegistry.get<Hat>(), &hatPool );
		ASSERT_EQ( &poolRegistry.get<Human>(), &humanPool );
		ASSERT_EQ( &poolRegistry.get<Health>(), &healthPool );
	}

	TEST(PoolRegistry,Pools_Register)
	{
		PoolRegistry poolRegistry;
		Pools<Human,Health,Hat> pools(poolRegistry);

		ASSERT_EQ( &poolRegistry.get<Hat>(), &pools.get<Hat>() );
		ASSERT_EQ( &poolRegistry.get<Human>(), &pools.get<Human>() );
		ASSERT_EQ( &poolRegistry.get<Health>(), &pools.get<Health>() );
	}

	TEST(PoolRegistry,GetInvalid_Throws)
	{
		PoolRegistry poolRegistry;

		ASSERT_EQ( nullptr, poolRegistry.find<Shoes>() );
		ASSERT_EQ( nullptr, poolRegistry.find<Hat>() );
		ASSERT_EQ( nullptr, poolRegistry.find<Health>() );

		//Get should throw
		ASSERT_THROW( poolRegistry.get<Shoes>(), std::invalid_argument );
		ASSERT_THROW( poolRegistry.get<Hat>(), std::invalid_argument );
		ASSERT_THROW( poolRegistry.get<Health>(), std::invalid_argument );
	}

	/** Pool will unregister when out of scope
	*/
	TEST(PoolRegistry,Unregister)
	{
		PoolRegistry poolRegistry;
		{
			Pool<Human> instance( poolRegistry );
			// Note: Pool de-registers when desctructed
		}
		ASSERT_EQ( nullptr, poolRegistry.find<Human>() );
	}

	TEST(PoolRegistry,DuplicateType_Throws)
	{
		PoolRegistry poolRegistry;
		Pool<Human> instanceA( poolRegistry );
		ASSERT_THROW( Pool<Human> instanceB( poolRegistry ), std::invalid_argument );
	}

	TEST(PoolRegistry,ReRegisterType)
	{
		PoolRegistry poolRegistry;
		{
			Pool<Human> instanceA( poolRegistry ); // Note: Pool de-registers when desctructed
		}

		Pool<Human> instanceB( poolRegistry ); // Second Pool
		ASSERT_EQ( &instanceB, poolRegistry.find<Human>() );
	}
/*
	TEST(PoolRegistry,StackPoolsRegistration )
	{
		PoolRegistry poolRegistry;
		Pools<Human,Health,Hat> pools(poolRegistry);
	}
	*/

} //END: Test
} //END: Enti



