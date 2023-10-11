#include "Enti\Logical.h"

#include "Enti\Container.h" //<NOTE: Needed for majority of tests for component storage etc!
#include "Enti\Pools.h" //<NOTE: Needed for majority of tests for component storage etc!
#include "Enti\Has.h"

#include "TestTypes.h"
#include <gtest/gtest.h>

namespace Enti {
namespace Test 
{

TEST_CLASS(Logical_Test)
{
public:
	TEST_METHOD(LogicalQuery_Has)
	{
		Container container;
		Pools<Human> pools(container.poolRegistry());
		Node node = container.create(Human());

		ASSERT_TRUE( node % Has<Human>() );
		ASSERT_TRUE( query( node, Has<Human>() ) );
	}

	TEST_METHOD(LogicalQuery_AndHas)
	{
		Container container;
		Pools<Human,Health,Hat> pools(container.poolRegistry());
		Node node = container.create(Human(), Health(100), Hat());

		ASSERT_TRUE(node % (Has<Human>() && Has<Health>()) );
		ASSERT_TRUE(node % (Has<Health>() && Has<Human>()));
		ASSERT_TRUE(node % (Has<Human>() && Has<Health>() && Has<Hat>()) );
		ASSERT_TRUE(node % (Has<Health>() && Has<Hat>() && Has<Human>()) );

		ASSERT_FALSE(node % Has<Glasses>());
		ASSERT_FALSE(node % (Has<Glasses>() && Has<Human>()) );
		ASSERT_FALSE(node % (Has<Glasses>() && Has<Hat>() && Has<Human>()) );
	}

	TEST_METHOD(LogicalQuery_Object)
	{
		Container container;
		Pools<Human,Health,Hat> pools(container.poolRegistry());
		Node nodeA = container.create(Human(), Health(100), Hat());
		Node nodeB = container.create(Human(), Hat());

		auto hasCheck = (Has<Human>() && Has<Health>());
		ASSERT_TRUE(nodeA % hasCheck);
		ASSERT_TRUE( query(nodeA, hasCheck) );
		ASSERT_FALSE(nodeB % hasCheck);
		ASSERT_FALSE( query(nodeB, hasCheck) );
	}

	TEST_METHOD(LogicalQuery_AndGreater)
	{
		Container container;
		Pools<Human,Health,Hat> pools(container.poolRegistry());
		Node node = container.create(Human(), Health(100), Hat());

		ASSERT_TRUE(node % (Has<Human>() && (Has<Health>() > 99)) );
		ASSERT_FALSE(node % (Has<Human>() && (Has<Health>() > 100)) );
	}


	TEST_METHOD(LogicalQuery_AndGreaterEqual)
	{
		Container container;
		Pools<Human,Health,Hat> pools(container.poolRegistry());
		Node node = container.create(Human(), Health(100), Hat());

		ASSERT_TRUE(node % (Has<Human>() && (Has<Health>() >= 100)) );
		ASSERT_FALSE(node % (Has<Human>() && (Has<Health>() >= 101)) );
	}

	TEST_METHOD(LogicalQuery_AndLess)
	{
		Container container;
		Pools<Human,Health,Hat> pools(container.poolRegistry());
		Node node = container.create(Human(), Health(100), Hat());
		ASSERT_TRUE(node % (Has<Human>() && (Has<Health>() < 101)) );
		ASSERT_FALSE(node % (Has<Human>() && (Has<Health>() < 100)) );
	}

	TEST_METHOD(LogicalQuery_AndLessEqual)
	{
		Container container;
		Pools<Human,Health,Hat> pools(container.poolRegistry());
		Node node = container.create(Human(), Health(100), Hat());
		auto query = (Has<Human>() && (Has<Health>() <= 100));
		ASSERT_TRUE(node % query );
		auto queryFalse = (Has<Human>() && (Has<Health>() <= 99));
		ASSERT_FALSE(node % queryFalse );
	}

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

};

} //END: Test
} //END: Enti