#include "Enti\Node.h"
#include "Enti\Container.h" //<NOTE: Needed for majority of tests for component storage etc!
#include "Enti\Pools.h" //<NOTE: Needed for majority of tests for component storage etc!
#include "Enti\Has.h"

#include "TestTypes.h"
#include <gtest/gtest.h>

namespace Enti {
namespace Test 
{
	TEST(Node,Null)
	{
		Node nullA;
		Node nullB( *(Container*)0, 0u );
		Node nullC( *(Container*)3, 0u );

		ASSERT_TRUE( nullA.isNull() );
		ASSERT_TRUE( nullB.isNull() );
		ASSERT_TRUE( nullC.isNull() );
		ASSERT_EQ( nullA, Node() );
		ASSERT_EQ( nullB, Node() );
		ASSERT_EQ( nullC, Node() );
		ASSERT_EQ( nullB, nullA );
		ASSERT_EQ( nullC, nullA );
		ASSERT_EQ( nullC, nullB );
	}

	TEST(Node,NotNull)
	{
		Node node( *(Container*)456, 123U );
		ASSERT_FALSE( node.isNull() );
	}

	TEST(Node,ConstructId)
	{
		Node node( *(Container*)456, 123U );
		ASSERT_EQ( 123U, node.id() );
	}

	TEST(Node,Equality)
	{
		Node node( *(Container*)456, 123U );
		ASSERT_EQ( Node(*(Container*)456, 123U), node );
		ASSERT_NE( Node(*(Container*)456, 124U), node );
		ASSERT_NE( Node(*(Container*)455, 123U), node );
	}

	TEST(Node,CopyConstruct)
	{
		Node node( *(Container*)456, 123U );
		Node nodeB( node ); //< Node handle - Has reference to container i.e. struct{ uint32_t, Container& }
		ASSERT_EQ(nodeB, node);
	}

	TEST(Node,CopyAssignment)
	{
		Node node( *(Container*)456, 123U );
		Node nodeC;
		nodeC = node;
		ASSERT_EQ(nodeC, node);
	}
	
	TEST(Node,Has)
	{
		Container container;
		Pools<Human,Health,Hat> pools(container);
		Node node = container.create(Human(), Health(100), Hat());

		//Member
		ASSERT_TRUE( node.has<Health>() );
		ASSERT_TRUE( node.has<Human>() );
		ASSERT_TRUE( node.has<Hat>() );
		ASSERT_FALSE( node.has<Shoes>() );

		//Global
		ASSERT_TRUE( has<Health>(node) );
		ASSERT_TRUE( has<Human>(node) );
		ASSERT_TRUE( has<Hat>(node) );
		ASSERT_FALSE( has<Shoes>(node) );

		//Global handle
		ASSERT_TRUE( has<Health>(container,node.id()) );
		ASSERT_TRUE( has<Human>(container,node.id()) );
		ASSERT_TRUE( has<Hat>(container,node.id()) );
		ASSERT_FALSE( has<Shoes>(container,node.id()) );
	}

	TEST(Node,Get)
	{
		Container container;
		Pools<Human,Health,Hat> pools(container);
		Node node = container.create(Human(), Health(100), Hat());

		//Member
		ASSERT_NE( nullptr, &node.get<Human>() );
		ASSERT_NE( nullptr, &node.get<Health>() );
		ASSERT_NE( nullptr, &node.get<Hat>() );

		//Global
		ASSERT_NE( nullptr, &get<Human>(node) );
		ASSERT_NE( nullptr, &get<Health>(node) );
		ASSERT_NE( nullptr, &get<Hat>(node) );

		//Global handle
		ASSERT_NE( nullptr, &get<Human>(container,node.id()) );
		ASSERT_NE( nullptr, &get<Health>(container,node.id()) );
		ASSERT_NE( nullptr, &get<Hat>(container,node.id()) );

		//Verify that the same objects returned on all interfaces
 		ASSERT_EQ( &get<Human>(node), &node.get<Human>() );
		ASSERT_EQ( &node.get<Human>(), &get<Human>(container,node.id()) );
	}

	TEST(Node,GetHasCorrectValue)
	{
		float cHealthPercent = rand() * (100.0f/float(RAND_MAX)); //< Random to ensure component memory initialised

		Container container;
		Pools<Health> pools(container.poolRegistry());
		Node node = container.create( Health(cHealthPercent) );

		ASSERT_EQ( cHealthPercent, node.get<Health>().percent );
	}

	TEST(Node,Find)
	{
		Container container;
		Pools<Human,Health,Hat> pools(container);
		Node node = container.create(Human(), Health(100), Hat());

		//Member
		ASSERT_NE( nullptr, node.find<Human>() );
		ASSERT_NE( nullptr, node.find<Health>() );
		ASSERT_NE( nullptr, node.find<Hat>() );
		ASSERT_EQ( nullptr, node.find<Shoes>() );

		//Global
		ASSERT_NE( nullptr, find<Human>(node) );
		ASSERT_NE( nullptr, find<Health>(node) );
		ASSERT_NE( nullptr, find<Hat>(node) );
		ASSERT_EQ( nullptr, find<Shoes>(node) );

		//Global handle
		ASSERT_NE( nullptr, find<Human>(container,node.id()) );
		ASSERT_NE( nullptr, find<Health>(container,node.id()) );
		ASSERT_NE( nullptr, find<Hat>(container,node.id()) );
		ASSERT_EQ( nullptr, find<Shoes>(container,node.id()) );

		//Verify that the same objects returned on all interfaces
		ASSERT_EQ( find<Human>(node), node.find<Human>() );
		ASSERT_EQ( node.find<Human>(), find<Human>(container,node.id()) );
	}

	TEST(Node,FindHasCorrectValue)
	{
		const float cHealthPercent = rand() * (100.0f/float(RAND_MAX)); //< Random to ensure component memory initialised
		const float cHealthPercentB = rand() * (100.0f/float(RAND_MAX));
		const float cShoeSize = rand() / 100.0F;
		const float cShoeSizeB = rand() / 100.0F;

		Container container;
		Pools<Health,Shoes> pools(container);
		Node node = container.create( Health(cHealthPercent), Shoes(cShoeSize) );
		Node nodeB = container.create( Health(cHealthPercentB), Shoes(cShoeSizeB) );

		ASSERT_EQ( cHealthPercent, node.find<Health>()->percent);
		ASSERT_EQ( cShoeSize, node.find<Shoes>()->size);

		ASSERT_EQ( cHealthPercentB, nodeB.find<Health>()->percent);
		ASSERT_EQ( cShoeSizeB, nodeB.find<Shoes>()->size);
	}

	TEST(Node,GetInvalid_Throws)
	{
		Container container;
		Node node = container.create();

		//Member
		ASSERT_THROW( node.get<Shoes>(), std::invalid_argument );

		//Global
		ASSERT_THROW( get<Health>(node), std::invalid_argument );

		//Global handle
		ASSERT_THROW( get<Hat>(container,node.id()), std::invalid_argument );
	}

	TEST(Node,Add)
	{
		Container container;
		Pools<Human,Health,Hat,Shoes> pools(container.poolRegistry());
		Node node = container.create(Human());

		ASSERT_TRUE( has<Human>(node) );
		ASSERT_FALSE( has<Health>(node) );
		ASSERT_FALSE( has<Hat>(node) );
		ASSERT_FALSE( has<Shoes>(node) );

		node.add( Health(100) );
		ASSERT_TRUE( has<Human>(node) );
		ASSERT_TRUE( has<Health>(node) );
		ASSERT_FALSE( has<Hat>(node) );
		ASSERT_FALSE( has<Shoes>(node) );

		add( node, Hat() );
		ASSERT_TRUE( has<Human>(node) );
		ASSERT_TRUE( has<Health>(node) );
		ASSERT_TRUE( has<Hat>(node) );
		ASSERT_FALSE( has<Shoes>(node) );

		add( container, node.id(), Shoes(9) );
		ASSERT_TRUE( has<Human>(node) );
		ASSERT_TRUE( has<Health>(node) );
		ASSERT_TRUE( has<Hat>(node) );
		ASSERT_TRUE( has<Shoes>(node) );
	}


	TEST(Node,AddHasCorrectValue)
	{
		float cHealthPercent = rand() * (100.0f/float(RAND_MAX)); //< Random to ensure component memory initialised
		float cHealthShoeSize = rand() * (12.0f/float(RAND_MAX)); //< Random to ensure component memory initialised

		Container container;
		Pools<Health,Shoes> pools(container.poolRegistry());
		Node node = container.create();

		node.add( Health(cHealthPercent) );
		ASSERT_EQ( cHealthPercent, get<Health>(node).percent );

		add( container, node.id(), Shoes(cHealthShoeSize) );
		ASSERT_EQ( cHealthShoeSize, get<Shoes>(node).size );
	}

	/*
	TEST(Node,GetMore)
	{
	Container container;
	Pools<Human,Health,Hat> pools(container.poolRegistry());
	Node node = container.create(Human(), Health(cHealthPercent), Hat());

	std::tuple<Human,Health,Hat> hhh = get<Human,Health,Hat>(node);
	}*/
	/*
	TEST_METHOD(Container_Get)
	{
	const float cHealthPercent = cHealthPercent;

	Container container;
	Pools<Human,Health,Hat> pools(container.poolRegistry());
	(void)container.create(Human(), Health(cHealthPercent), Hat());
	(void)container.create(Human(), Health(cHealthPercent) );
	(void)container.create(Human());

	ASSERT_EQ( get<Human>(container).size(), 3u );
	ASSERT_EQ( get<Health>(container).size(), 2u );
	ASSERT_EQ( get<Hat>(container).size(), 1 );
	ASSERT_EQ( get<Shoes>(container).size(), 0u );


	ASSERT_EQ( get<Health>(container)[0].percent, cHealthPercent );
	}
	*/

	/*
	TEST_METHOD(ContainerHasSingle)
	{
	Container container;
	Pools<Human,Health,Hat> pools(container.poolRegistry());
	Node node = container.create(Human(), Health(cHealthPercent), Hat());

	using Has;

	auto result = (container % has<Glasses>());
	ASSERT_TRUE(result);
	ASSERT_TRUE(result.size() == 1u);
	ASSERT_TRUE(result[0] == node);
	}*/


} //END: Test
} //END: Enti