#pragma once

#include <tuple>
#include "Pool.hpp"

namespace Sub0Ent
{

	/** Helper for creating multiple Component pools with a single object 
	 * @tparam Components  List of Component types, a Pool<Compnent[X]> will be created for each typename 
	 */
	template< typename... Components >
	class Pools
	{
	public:
		//NOTE: C++11 std::make_tuple
		Pools( PoolRegistry& registry )
			: pools_( (sizeof( Components ), registry)... )
		{
		}

		//NOTE: C++14 std::get<>
		template< typename Component>
		Pool<Component>& get()
		{
			return std::get<Pool<Component>>( pools_ );
		}

	private:
		typedef std::tuple< Pool<Components>... > PoolTuple;
		PoolTuple pools_;
	};

} //END: Sub0Ent
