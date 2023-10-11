#pragma once

#include <cassert>

#include "Entity.hpp"

namespace Sub0Ent
{

    template< typename Component >
    constexpr bool has(const Entity& node)
    { return has<Component>(node.container(), node.id()); }

    template< typename Component >
    constexpr bool has( Container& container, EntityId nodeId)
    { return container.has<Component>(nodeId); }

    template< typename Component >
    Component* find( const Entity& node)
    { return find<Component>(node.container(), node.id()); }

    template< typename Component >
    constexpr Component* find( Container& container, EntityId nodeId)
    { return container.find<Component>(nodeId); }

    template< typename Component >
    constexpr Component& get( const Entity& node)
    { return get<Component>( node.container(), node.id() ); }

    template< typename Component >
    constexpr Component& get( Container& container, EntityId nodeId )
    { return container.get<Component>(nodeId); }

} //END: Sub0Ent