#pragma once

#include <map>

#include "Entity.hpp"
#include "PoolRegistry.hpp"

namespace Sub0Ent
{
	//forward dclarations
	class IComponent;


	class Container
	{
	public:
		Container()
		: nextNodeId_( cInvalid_NodeId + 1U /*@note 0u is invalid*/ )
		{}

		PoolRegistry& poolRegistry()
		{ return pools_; }

		const PoolRegistry& poolRegistry() const
		{ return pools_; }

		Entity create()
		{
			EntityId nodeId = newNodeId();
			return Entity( *this, nodeId );
		} 

#if CPP11
		template<typename... Components>
		Entity create(Components&&... items)
		{
			EntityId nodeId = newNodeId();
			std::tuple<Components*...> comps( pools_.get<Components>().create(nodeId, std::move(items))... );
			return Entity( *this, nodeId );
		}
#endif

		template<typename Component>
		void add( EntityId nodeId, const Component& item )
		{
			pools_.get<Component>().create(nodeId, item );
		}

#if CPP11
		template<typename Component>
		void add( EntityId nodeId, Component&& item )
		{
			pools_.get<Component>().create(nodeId, std::move(item));
		}
#endif

		template<typename Component>
		bool has( EntityId nodeId )
		{ 
			Pool<Component>* pool = pools_.find<Component>();
			return (pool != nullptr) && pool->has(nodeId); 
		}

		template<typename Component>
		Component* find( EntityId nodeId )
		{
			Pool<Component>* pool = pools_.find<Component>();
			return (pool != nullptr) ? pool->find(nodeId) : nullptr; 
		}

		template<typename Component>
		Component& get( EntityId nodeId )
		{ return pools_.get<Component>().get(nodeId); }

		//TODO: fix as shoulnd't happen like this!
		operator PoolRegistry&()
		{ return pools_; }

	private:

		EntityId newNodeId()
		{ return nextNodeId_++; }

	private:
		EntityId nextNodeId_; //< Id of the last created node where (0 is invalid/null)
		PoolRegistry pools_;
	};


} //END: Sub0Ent
