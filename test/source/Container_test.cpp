#include "Sub0Ent/World.hpp"
#include "Sub0Ent/Collection.hpp"
#include "Sub0Ent/Has.hpp"
#include "Sub0Ent/Query.hpp"
#include "Sub0Ent/Logical.hpp"

#include "TestTypes.hpp"
#include <gtest/gtest.h>


namespace Sub0Ent {	
namespace Test {
		
	TEST( World, CreateEntity)
	{
		World world;
		Entity entity = world.create();
		Entity entityB = world.create();
		ASSERT_FALSE( entity.isNull() );
		ASSERT_NE( Entity(), entity );
		ASSERT_NE( entity, entityB );
	}

	/*
	TEST( World, Has)
	{

	World world;
	Collection<Human,Health,Hat> collections(world.collectionRegistry());
	(void)world.create(Human(), Health(cHealthPercent), Hat());

	ASSERT_TRUE( has<Health>(world) );
	ASSERT_TRUE( has<Human>(world) );
	ASSERT_TRUE( has<Hat>(world) );
	ASSERT_FALSE( has<Shoes>(world) );
	}*/

} //END: Test
} //END: Sub0Ent