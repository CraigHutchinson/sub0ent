#include "Enti/Container.h"
#include "Enti/Pool.h"
#include "Enti/Has.h"
#include "Enti/Query.h"
#include "Enti/Logical.h"

#include "TestTypes.h"
#include <gtest/gtest.h>


namespace Enti {	
namespace Test {
		
	TEST( Container, CreateNode)
	{
		Container container;
		Node node = container.create();
		Node nodeB = container.create();
		ASSERT_FALSE( node.isNull() );
		ASSERT_NE( Node(), node );
		ASSERT_NE( node, nodeB );
	}

	/*
	TEST( Container, Has)
	{

	Container container;
	Pools<Human,Health,Hat> pools(container.poolRegistry());
	(void)container.create(Human(), Health(cHealthPercent), Hat());

	ASSERT_TRUE( has<Health>(container) );
	ASSERT_TRUE( has<Human>(container) );
	ASSERT_TRUE( has<Hat>(container) );
	ASSERT_FALSE( has<Shoes>(container) );
	}*/

} //END: Test
} //END: Enti