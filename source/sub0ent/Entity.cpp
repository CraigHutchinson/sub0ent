
#include "Entity.hpp"

#include "Container.hpp" //<NOTE: Needed for majority of tests for component storage etc!
#include "Pools.hpp" //<NOTE: Needed for majority of tests for component storage etc!
#include "Has.hpp"


namespace Sub0Ent 
{

	Entity::Entity() 
		: container_(nullptr)
		, id_(0)
	{}

	Entity::Entity(Container& container, EntityId id) 
		: container_(&container)
		, id_(id)
	{}

	
	Container& Entity::container() const
	{
		if ( container_ == nullptr )
			throw std::runtime_error( "Entity::container_ == nullptr" );
		return *container_;
	}


} //END: Sub0Ent