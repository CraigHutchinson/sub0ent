#pragma once

#include <cassert>
#include <stdexcept>
#include "GlobalUniqueIndex.hpp"

namespace Sub0Ent {

template<typename Component>
class Pool;


/**  Holds registrations for Pool instances which can store a Component type
*/
class PoolRegistry
{
public:
	/** Defines the limit for the number of RegistryPools that can be instantiated
	@remark A table of this size is created for every component that is registred in any PoolRegistry instance
	*/
	static const size_t cMaximumRegistryInstances = 4; 

	PoolRegistry();

	~PoolRegistry();
	
	/** Find the pool instance for the specified component
	@return Pool instance or nullptr if no pool has been created for the Component type
	*/
	template< typename Component>
	Pool<Component>* find() /*const*/
	{ 
		return getPools<Component>().instances[registeryId_];
	}

	/** Get the pool instance for the specified component
	@warning Exception will be thrown if a pool instance does not exist
	@return Pool instance
	*/
	template< typename Component>
	Pool<Component>& get()
	{ 
		Pool<Component>* pool = getPools<Component>().instances[registeryId_];
		if ( pool == nullptr )
		{
			throw std::invalid_argument( 
				std::string("Pool not registered for Component of type ") + typeid(Component).name() );
		}

		return *pool;
	}
	
	/** Set the pool for a component 
	*/
	template< typename Component>
	void set( Pool<Component>* pool )
	{ 
		PoolInstances<Component>& pools = getPools<Component>();
		if ( pools.instances[registeryId_] != nullptr )
		{
			throw std::invalid_argument( 
				std::string("Pool already registered for Component of type ") + typeid(Component).name() );
		}

		///Update a list of pool-buffers so we can release instances at desrruction
		pools.next  = bufferListHead_;
		bufferListHead_ = &pools;

		pools.instances[registeryId_] = pool;
	}

	/** Clear the pool for a component 
	*/
	template< typename Component>
	void clear( Pool<Component>* pool )
	{ 
		PoolInstances<Component>& pools = getPools<Component>();

		assert( pools.instances[registeryId_] == pool ); //, Sanity check - to remove

		if ( bufferListHead_ == &pools )
		{
			bufferListHead_ = pools.next;
		}
		else
		{
			PoolInstancesBase* buffer = bufferListHead_;
			while( buffer->next != nullptr && buffer->next != &pools )
			{
				buffer = buffer->next;
			}

			if ( buffer->next == &pools )
			{
				buffer->next = pools.next;
			}
		}

		pools.instances[registeryId_] = nullptr;
	}
private:

	/** Each pool derives from an interface to allow clean up of references at destruction of RegistryPool 
	*/
	struct PoolInstancesBase
	{
		PoolInstancesBase* next; //< Next pool

		PoolInstancesBase()
		: next(nullptr) 
		{}

		virtual void clear( const size_t index ) = 0;
	};

	template < typename Component >
	struct PoolInstances : PoolInstancesBase
	{
		Pool<Component>* instances[cMaximumRegistryInstances];

		/** Make unpopulated instances buffer 
		*/
		PoolInstances() 
		: instances()
		{
		}

		/** Remove the isnatcne for a registry
		*/
		virtual void clear( const size_t registryId )
		{
			if ( registryId > cMaximumRegistryInstances )
				throw std::exception();
			
			instances[registryId] = nullptr;
		}
	};
	
	/** Pool instance buffer store for all PoolRegistry instances within the system
	@todo Document why this is static and try and remove?
	*/
	template < typename Component >
	PoolInstances<Component>& getPools()
	{
		static PoolInstances<Component> pools;
		return pools;
	}

private:
	PoolInstancesBase* bufferListHead_;
	const GlobalUniqueIndex registeryId_; //< Registry instance index
};


} //END: Sub0Ent
