#include "Enti/Container.h"
#include "Enti/Pool.h"
#include "Enti/Pools.h"
#include "Enti/View.h"

#include "TestTypes.h"
#include <gtest/gtest.h>


namespace Enti {	
	namespace Test {

		TEST( View, GetPool )
		{
			PoolRegistry registry;
			Pool<Human> humanPool(registry);
			Pool<Health> healthPool(registry);
			Pool<Hat> hatPool(registry);

			View<Health, Human, Hat> humanHealthHatView(registry);
			ASSERT_EQ( &humanHealthHatView.getPool<Human>(), &humanPool );
			ASSERT_EQ( &humanHealthHatView.getPool<Health>(), &healthPool );
			ASSERT_EQ( &humanHealthHatView.getPool<Hat>(), &hatPool );
		}

		TEST(View,GetPool_Throws)
		{
			PoolRegistry registry;
			ASSERT_THROW( View<Human> humanView(registry), std::invalid_argument );
		}


		TEST( View, Begin_Empty )
		{
			Container registry;
			Pools<Human,Health,Hat> pools(registry);
			View<Health, Human, Hat> view(registry);
			ASSERT_EQ( view.begin(), view.end() );
		}

		TEST( View, Begin_NotEmpty )
		{
			Container registry;
			Pools<Human,Health,Hat> pools(registry);
			(void)registry.create( Human(), Health(100.0F), Hat() );

			View<Health, Human, Hat> view(registry);
			ASSERT_NE( view.begin(), view.end() );
		}

		TEST( View, Begin_HasPartial )
		{
			Container registry;
			Pools<Human,Health,Hat> pools(registry);
			View<Health, Human, Hat> view(registry);
			(void)registry.create( Human(), Health(100.0F)/* , Hat() -- Missing hat! */ );
			ASSERT_EQ( view.begin(), view.end() );
		}

		TEST( View, Begin_NotCompleteOptional )
		{
			Container registry;
			Pools<Human,Health,Hat> pools(registry);
			View<Health, Human, Hat*> view(registry); //< Hat is optional with '*'
			(void)registry.create( Human(), Health(100.0F)/* , Hat() -- Missing hat! */ );
			ASSERT_EQ( view.begin(), view.end() );
		}

		TEST( View, Intersect2 )
		{
			Container container;
			Pools<Human,Hat> pools(container);
			View<Human,Hat> view(container); 

			for ( NodeId humanId : { 1, 2, 3, 4, 5, 8, 9 } ) container.add( humanId, Human() );
			for ( NodeId hatId   : { 1, 5, 6, 7, 8, 9 } ) container.add( hatId, Hat() );
			
			auto iEntity = view.begin();
			for ( NodeId nodeId : { 1, 5, 8, 9 } )
			{
				EXPECT_EQ( nodeId, *iEntity );
				++iEntity;
			}
			EXPECT_EQ( view.end(), ++iEntity );
		}

		TEST( View, Intersect3 )
		{
			Container container;
			Pools<Human,Hat,Health> pools(container);
			View<Human,Hat,Health> view(container); 

			for ( NodeId humanId  : { 1, 2, 3, 4, 5, 8 } ) container.add( humanId, Human() );
			for ( NodeId hatId    : { 3, 5, 6, 7, 8, 9, 10 } ) container.add( hatId, Hat() );
			for ( NodeId healthId : { 1, 3, 5, 8, 9 } ) container.add( healthId, Health(100.0F) );

			auto iEntity = view.begin();
			for ( NodeId nodeId : {  3, 5, 8 } )
			{
				EXPECT_EQ( nodeId, *iEntity );
				++iEntity;
			}
			EXPECT_EQ( view.end(), ++iEntity );
		}

		TEST( View, Intersect4 )
		{
			Container container;
			Pools<Human,Hat,Health,Glasses> pools(container);
			View<Human,Hat,Health,Glasses> view(container); 

			for ( NodeId humanId  : { 1, 2, 3, 4, 5, 7, 9 } ) container.add( humanId, Human() );
			for ( NodeId hatId    : { 3, 5, 6, 7, 8, 9 } ) container.add( hatId, Hat() );
			for ( NodeId healthId : { 1, 3, 7, 9, 10 } ) container.add( healthId, Health(100.0F) );
			for ( NodeId glassId  : { 3, 4, 6, 7, 8, 9, 11 } ) container.add( glassId, Glasses() );

			auto iEntity = view.begin();
			for ( NodeId nodeId : {  3, 7, 9 } )
			{
				EXPECT_EQ( nodeId, *iEntity );
				++iEntity;
			}
			EXPECT_EQ( view.end(), ++iEntity );
		}

	} //END: Test
} //END: Enti