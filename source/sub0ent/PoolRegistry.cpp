#include "PoolRegistry.hpp"
#include "Pools.hpp"


namespace Sub0Ent
{	

	PoolRegistry::PoolRegistry() 
	: bufferListHead_(nullptr)
	{
		if ( registeryId_ >= cMaximumRegistryInstances )
			throw std::overflow_error( "Too many RegistryPool instances");
	}

	PoolRegistry::~PoolRegistry()
	{
		PoolInstancesBase* buffer = bufferListHead_;
		while( buffer )
		{
			buffer->clear( registeryId_ );
			buffer = buffer->next;
		}
	}
} //END: Sub0Ent



