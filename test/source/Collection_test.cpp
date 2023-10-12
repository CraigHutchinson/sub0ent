#include "sub0ent/CollectionRegistry.hpp"
#include "sub0ent/Collection.hpp"

#include "TestTypes.hpp"
#include <gtest/gtest.h>

namespace Sub0Ent {
	namespace Test 
	{

		TEST(Collection,Create)
		{
			CollectionRegistry collectionRegistry;
			Collection<Human> humanCollection(collectionRegistry);
			ASSERT_NE( nullptr, humanCollection.create( 0U, Human() ) );
		}


	} //END: Test
} //END: Sub0Ent



