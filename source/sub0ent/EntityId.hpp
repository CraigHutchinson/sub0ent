#pragma once

#include <cstdint>

namespace Sub0Ent
{
	/* Entity unique world Id
	@remarks May be uint16_t to reduce memory usage with trade off for Entity entity count
	*/
	typedef std::uint32_t EntityId;

	const EntityId cInvalid_EntityId = 0U;

	/** Returns whether the entity id is a null-ent where entityId == cInvalid_EntityId */
	constexpr inline bool isNull( EntityId entityId )
	{ return entityId == cInvalid_EntityId; }

} //END: Sub0Ent

