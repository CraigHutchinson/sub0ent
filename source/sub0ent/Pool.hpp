#pragma once

#include <map>
#include <vector>

#include "PoolRegistry.hpp"
#include "EntityId.hpp"

namespace Sub0Ent {

	template< typename Component>
	class Pool
	{
	public: 
		typedef Component Component;
		
		typedef std::vector<EntityId> NodeIdVector;
		typedef std::vector<Component> ComponentVector;
		typedef typename NodeIdVector::iterator Iterator;

	public:
		Pool( PoolRegistry& registry )
			: registry_(registry)
		{ 
			registry_.set(this); 
		}

		~Pool()
		{ 
			registry_.clear(this);
		}

		Component* create(EntityId nodeId, Component&& component)
		{
			//TODO: THrow if already exists!
			//TODO: Very temp!
			return &components_.emplace( nodeId, std::move(component) ).first->second;
		}

		bool has(EntityId nodeId)
		{
			return components_.find(nodeId) != components_.end();			
		}


		/** Get pointer to a component of the specified nodeId
		@return Component instance of nullptr if no component exists for the node
		*/
		Component* find(EntityId nodeId)
		{
			NodeIdToComponentLookup::iterator iFind = components_.find(nodeId);
			return iFind != components_.end() ? &iFind->second : nullptr;			
		}

		/** Get reference to a component of the specified nodeId
		@warning Will throw exception if the nodeId was not found, use find() if component existance is unknown
		*/
		Component& get(EntityId nodeId)
		{
			NodeIdToComponentLookup::iterator iFind = components_.find(nodeId);
			if ( iFind == components_.end() )
				throw std::invalid_argument( "EntityId does not have this component type for call to Pool::get()");
			return iFind->second; //< Will throw if not valid itertor!
		}

		Component& at( const Iterator& iNode )
		{
			return iNode->second;
		}

		/** TODO */
		Iterator begin() 
		{ return components_.begin(); }

		/** TODO */
		Iterator end() 
		{ return components_.end(); }

	private:
		PoolRegistry& registry_; //< Registry the pool is attached to
		
		NodeIdVector ids_; //< Sub0Entty ids for lookup
		ComponentVector components_; //< Comoonent data
	};

} //END: Sub0Ent
