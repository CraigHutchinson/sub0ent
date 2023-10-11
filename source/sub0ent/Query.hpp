#pragma once

#include <cassert>

#include "Entity.hpp"

namespace Sub0Ent
{
	/* Queriable object base type for operator overload resolution
	*/
	struct Query
	{};

	/* Is a type queryable */
	template<typename T>
	struct IsQuery
		: std::is_base_of<Query, T> 
	{};
	
	/* Query operator function
	*/
	template<class QueryObject >
	bool query( const Entity& node, const QueryObject& queryObject = QueryObject() )
	{ 
		static_assert(IsQuery<QueryObject>::value == true, "Not a Query type" );
		return queryObject(node); 
	}

	/* Query operator '%'
	*/
	template<class QueryObject>
	bool operator % (const Entity& node, const QueryObject& rhs)
	{
		return query( node, rhs );
	}

} //END: Sub0Ent