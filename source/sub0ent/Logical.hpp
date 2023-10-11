#pragma once

#include "Query.hpp"

namespace Sub0Ent
{
	/** Has Operator
	*/
	template<class Component>
	struct Has : Query
	{
		typedef Component Component_t;
		constexpr bool operator() (const Entity& Entity) const
		{ return has<Component>(Entity); }
	};

	/** Find Operator similar to Has but obtains a pointer to the component
	@remark GreaterOp, LessOp etc require the component value so Has is converted to a Find operation in these cases
	*/
	template<class Component>
	struct Find : Query
	{
		typedef Component Component_t;
		constexpr Component* operator() (const Entity& Entity) const
		{ return find<Component>(Entity); }
	};
	
	/* Logical-and operation '&&'
	*/
	template<class Lhs, class Rhs>
	struct AndOp : Query
	{
		AndOp( const Lhs& lhs, const Rhs& rhs ) : lhs_(lhs), rhs_(rhs) {}
		constexpr bool operator() (const Entity& node) const
		{ return lhs_(node) && rhs_(node); }
	private:
		const Lhs lhs_;
		const Rhs rhs_;
	};

	/* Logical-and query object '&&'
	*/
	template<class Lhs, class Rhs>
	typename std::enable_if<IsQuery<Lhs>::value && IsQuery<Rhs>::value,
		AndOp<Lhs, Rhs> >::type operator &&(const Lhs& lhs, const Rhs& rhs)
	{
		return AndOp<Lhs, Rhs>( lhs, rhs );
	}

	template<class Lhs, class Value>
	struct QueryValueOp : Query
	{
		QueryValueOp( const Lhs& lhs, const Value& value ) : lhs_(lhs), value_(value) {}
	protected:
		const Lhs lhs_;
		const Value value_;
	};

	/* Logical-greater operation '>'
	*/
	template<class Lhs, class Value>
	struct GreaterOp : QueryValueOp<Lhs,Value>
	{
		GreaterOp( const Lhs& lhs, const Value& value ) : QueryValueOp(lhs,value) {}
		constexpr bool operator() (const Entity& node) const
		{ return false; }//lhs_(node) > value_; }
	};

	/* Logical-greater query object '>'
	*/
	template<class Lhs, class Value>
	typename std::enable_if<IsQuery<Lhs>::value && !IsQuery<Value>::value,
		GreaterOp<Lhs, Value> >::type operator >(const Lhs& lhs, const Value& value)
	{
		return GreaterOp<Lhs, Value>( lhs, value);
	}


	/* Logical-and operation '>='
	*/
	template<class Lhs, class Value>
	struct GreaterEqualOp : QueryValueOp<Lhs,Value>
	{
		GreaterEqualOp( const Lhs& lhs, const Value& value ) : QueryValueOp(lhs,value) {}
		constexpr bool operator() (const Entity& node) const
		{ return lhs_(node) >= value_; }
	};

	/* Logical-greater query object '>='
	*/
	template<class Lhs, class Value>
	typename std::enable_if<IsQuery<Lhs>::value && !IsQuery<Value>::value,
		GreaterEqualOp<Lhs, Value> >::type operator >=(const Lhs& lhs, const Value& value)
	{
		return GreaterEqualOp<Lhs, Value>( lhs, value );
	}

	/* Logical-and operation '<'
	*/
	template<class Lhs, class Value>
	struct LessOp : QueryValueOp<Lhs,Value>
	{
		LessOp( const Lhs& lhs, const Value& value ) : QueryValueOp(lhs,value) {}
		constexpr bool operator() (const Entity& node) const
		{ return lhs_(node) < value_; }
	};

	/* Logical-greater query object '<'
	*/
	template<class Lhs, class Value>
	typename std::enable_if<IsQuery<Lhs>::value && !IsQuery<Value>::value,
		LessOp<Lhs, Value> >::type operator <(const Lhs& lhs, const Value& value)
	{
		return LessOp<Lhs, Value>( lhs, value );
	}


	/* Logical-and operation '<='
	*/
	template<class Lhs, class Value>
	struct LessEqualOp : QueryValueOp<Lhs,Value>
	{
		LessEqualOp( const Lhs& lhs, const Value& value ) : QueryValueOp(lhs,value) {}
		constexpr bool operator() (const Entity& node) const
		{ return lhs_(node) <= value_; }
	};

	/* Logical-greater query object '<='
	*/
	template<class Lhs, class Value>
	typename std::enable_if<IsQuery<Lhs>::value && !IsQuery<Value>::value,
		LessEqualOp<Lhs, Value> >::type operator <=(const Lhs& lhs, const Value& value)
	{
		return LessEqualOp<Lhs, Value>( lhs, value );
	}

} //END: Sub0Ent