#pragma once

#include <tuple>
#include "Pool.hpp"
#include "View.hpp"

namespace Sub0Ent
{
#if 0
	class ISystem
	{
	public:

		/** Update the system which wil call update(Sub0Ent::EntityId) for each entity in view
		 */
		virtual void update() = 0;
	
	protected:
		/** Update function called for each entity matching the system view
		 * @param[in]  nodeId  The entity node identifier for reference		 
		 */
		virtual void update( const Sub0Ent::EntityId nodeId ) = 0;
	};

	template< typename... Components >
	class System : public ISystem, protected View<Components...>
	{
	public:
		/** @note C++11 std::make_tuple
		*/
		System( PoolRegistry& registry )
			: View( registry )
		{
		}

		virtual void update() override
		{
			const auto iEnd = end();
			for ( auto iSub0Entty = begin(); iSub0Entty != iEnd; ++iSub0Entty) 
			{ 
				update( *iSub0Entty );
			} 
		}

	};
#endif

} //END: Sub0Ent
