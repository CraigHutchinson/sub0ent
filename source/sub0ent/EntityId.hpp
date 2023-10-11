#pragma once

#include <cstdint>

namespace Sub0Ent
{
	/* Entity unique container Id
	@remarks May be uint16_t to reduce memory usage with trade off for Entity entity count
	*/
	typedef std::uint32_t EntityId;

	const EntityId cInvalid_NodeId = 0U;

	/** Returns whether the node id is a null-ent where nodeId == cInvalid_NodeId */
	constexpr inline bool isNull( EntityId nodeId )
	{ return nodeId == cInvalid_NodeId; }

} //END: Sub0Ent

