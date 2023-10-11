#pragma once

#include <cassert>
#include <cstdint>
#include <stdexcept>

#include "EntityId.hpp"
#define CPP11 1

namespace Sub0Ent
{
	//Forward declaration
	class Container;

	class Entity
	{
	public:
		/* Default consturctor initialises a null hnode reference */
		Entity();

		/* Create anode for the specified container and Id */
		Entity(Container& container, EntityId id) ;
		
		/** Get nodes container */
		Container& container() const;

		/** Get node handle */
		constexpr EntityId id() const {
			return id_;
		}	

		/** Returns whether the node id is a null-ent where id()==0 */
		constexpr bool isNull() const { 
			return Sub0Ent::isNull( id_ ); 
		}
		
		template< typename Component >
		constexpr bool has() const { 
			return container.has<Component>(id()); 
		}

		template< typename Component >
		constexpr Component& get() const {
			return container.get<Component>(id()); 
		}

		template< typename Component >
		constexpr Component* find() const {
            return container.find<Component>(id()); 
		}

		template< typename Component >
		constexpr void add( const Component& component ) const {
            container.add(id(), component ); 
		}

#if CPP11
		template< typename Component >
		constexpr void add( Component&& component ) const { 
            container.add(id(), std::forward(component) ); 
		}
#endif

	private:
		/** Throws if this is null-ent */
		void throwIfIsNull()
		{
			if ( isNull() )
				throw std::runtime_error( "add() on null-ent" );
		}

	protected:
		Container* container_;
		EntityId id_;
	};


	template< typename Component >
	bool add( Container& container, const EntityId nodeId, const Component& component )
	{ 
		return container.add( nodeId, component ); 
	}

	template< typename Component >
	bool add( const Entity& node, const Component& component )
	{ 
		return add( node.container(), node.id(), component ); 
	}

#if CPP11
	template< typename Component >
	void add( Container& container, const EntityId nodeId, Component&& component )
	{ 
		container.add( nodeId, std::forward(component) ); 
	}

	template< typename Component >
	void add( const Entity& node, Component&& component )
	{ 
		add( node.container(), node.id(), std::forward(component) ); 
	}
#endif

	/** Equality to test nodeId and container are equal
	@returns True if (id()==0 && rhs.id()==0) || id()==rhs.id() && (&container()==&rhs.container())
	*/
	inline bool operator ==( const Entity& lhs, const Entity& rhs)
	{
		return (lhs.id() == rhs.id()) 
			&& ((lhs.id() == 0U) || (&lhs.container() == &rhs.container()));
	}

	/** @see operator==(const Entity&,const Entity&)
	*/
	inline bool operator !=( const Entity& lhs, const Entity& rhs)
	{
		return !(lhs == rhs);
	}

} //END: Sub0Ent
