#pragma once

#include <tuple>
#include "Pool.hpp"

template <typename T, typename... Ts> struct get_index;

template <typename T, typename... Ts>
struct get_index<T, T, Ts...> : std::integral_constant<std::size_t, 0U> {};

template <typename T, typename Tail, typename... Ts>
struct get_index<T, Tail, Ts...> :
	std::integral_constant<std::size_t, 1U + get_index<T, Ts...>::value> {};
 
template <typename T>
struct get_index<T>
{
	// condition is always false, but should be dependant of T
	static_assert(sizeof(T) == 0U, "type not found");
};
template<typename T>
using Bare = typename std::remove_cv<typename std::remove_reference<T>::type>::type;

namespace Sub0Ent
{
	/** Creates a union view for Sub0Entties with the selected components 
	 * @tparam Components  The components that will be iterated over to findSub0Entties containign all
						   Each type can  define required access pattern using standard C++ language as follows:
						   * Type - Required component with no acces (TBD: Could be same as Type&)
						   * Type& - Required component for read & write by reference
						   * Type* - Optional component for read & write could be nullptr
						   * const Type& - Required component for read-only
						   * const Type* - Optional component for read-only could be nullptr

	*/
	template< typename... Components >
	class View
	{
	public: 
		static const uint32_t cComponentCount = sizeof...(Components); ///< number of components

		typedef std::tuple< Pool<Components>&... > Pools; ///< All component pools

#if 0
		typedef std::tuple< typename Pool<Components>::Iterator... > PoolIterators; ///< All omcponent iterators
#else
		/// @temp Detect all iterators of same type and use std::array automatically
		typedef std::array< typename Pool<void>::Iterator, cComponentCount > PoolIterators;
#endif

		class Iterator
		{
		public:
			Iterator( Pools& pools, PoolIterators&& iterators )
			   : pools_(pools)
				, iterators_( std::move(iterators) )
			{
			}

			template< typename Component>
			Component& get()
			{
				static const uint32_t cComponentIndex = get_index<Component,Components...>::value; 
				return std::get<cComponentIndex>(pools_).at( 
					std::get<cComponentIndex>(iterators_) );
			}

			Iterator& operator++()
			{
				auto& interA = std::get<0U>(iterators_);
				++interA;
				//auto& interB = std::tuple_element<1U>(iterators_);

				return *this;
			}

			bool operator != ( const Iterator& rhs ) const
			{ 
				return iterators_ != rhs.iterators_; 
			}

			bool operator == ( const Iterator& rhs ) const
			{ 
				return iterators_ == rhs.iterators_; 
			}

			operator EntityId() const
			{ 
				auto iSub0Entty = std::get<0U>(iterators_);
				auto iEnd = std::get<0U>(pools_).end();
				return (iSub0Entty != iEnd) ? iSub0Entty->first 
										 : cInvalid_NodeId; 
			}

			Iterator& operator*()
			{
				return *this;
			}

		private:
			Pools pools_; ////< Pools from the view
			PoolIterators iterators_;
		};

	public:
		/** @note C++11 std::make_tuple
		*/
		View( PoolRegistry& registry )
			: pools_( (sizeof( Components ), registry.get<Components>() )... )
		{
		}

		/** @note Uses C++14 std::get<>
		*/
		template< typename Component>
		Pool<Component>& getPool()
		{
			static const uint32_t cComponentIndex = get_index<Component,Components...>::value;
			return std::get<cComponentIndex>(pools_);
		}

		/** TODO */
		Iterator begin() 
		{ return Iterator( pools_, PoolIterators( getPool<Components>().begin()...) ); }
		
		/** TODO */
		Iterator end() 
		{ return Iterator( pools_, PoolIterators( getPool<Components>().end()... )  ); }
	private:
		Pools pools_;
	};

} //END: Sub0Ent