#pragma once

#include <map>

#include "Entity.hpp"
#include "CollectionRegistry.hpp"

namespace Sub0Ent
{
	class World
	{
	public:
		World()
		: nextEntityId_( cInvalid_EntityId + 1U /*@note 0u is invalid*/ )
		{}

		CollectionRegistry& collectionRegistry()
		{ return collections_; }

		const CollectionRegistry& collectionRegistry() const
		{ return collections_; }

		Entity create()
		{
			EntityId entityId = newEntityId();
			return Entity( *this, entityId );
		} 

#if CPP11
		template<typename... Components>
		Entity create(Components&&... items)
		{
			EntityId entityId = newEntityId();
			std::tuple<Components*...> comps( collections_.get<Components>().create(entityId, std::forward(items))... );
			return Entity( *this, entityId );
		}
#endif

		template<typename Component>
		void add( EntityId entityId, const Component& item )
		{
			collections_.get<Component>().create(entityId, item );
		}

#if CPP11
		template<typename Component>
		void add( EntityId entityId, Component&& item )
		{
			collections_.get<Component>().create(entityId, std::forward(item));
		}
#endif

		template<typename Component>
		bool has( EntityId entityId )
		{ 
			Collection<Component>* collection = collections_.find<Component>();
			return (collection != nullptr) && collection->has(entityId); 
		}

		template<typename Component>
		Component* find( EntityId entityId )
		{
			Collection<Component>* collection = collections_.find<Component>();
			return (collection != nullptr) ? collection->find(entityId) : nullptr; 
		}

		template<typename Component>
		Component& get( EntityId entityId )
		{ return collections_.get<Component>().get(entityId); }

		//TODO: fix as shoulnd't happen like this!
		operator CollectionRegistry&()
		{ return collections_; }

	private:

		EntityId newEntityId()
		{ return nextEntityId_++; }

	private:
		EntityId nextEntityId_; //< Id of the last created entity where (0 is invalid/null)
		CollectionRegistry collections_;
	};


	template< typename Component >
	bool add(World& world, const EntityId entityId, const Component& component)
	{
		return world.add(entityId, component);
	}

	template< typename Component >
	bool add(const Entity& entity, const Component& component)
	{
		return add(entity.world(), entity.id(), component);
	}

#if CPP11
	template< typename Component >
	void add(World& world, const EntityId entityId, Component&& component)
	{
		world.add(entityId, std::forward(component));
	}

	template< typename Component >
	void add(const Entity& entity, Component&& component)
	{
		add(entity.world(), entity.id(), std::forward(component));
	}
#endif

} //END: Sub0Ent
