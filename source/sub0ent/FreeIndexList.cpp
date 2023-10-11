
#include "FreeIndexList.hpp"

namespace Sub0Ent 
{

	FreeIndexList::FreeIndexList() 
	: mask_( Mask::cAll )
	{}

	FreeIndexList::Index FreeIndexList::alloc()
	{ 
		if ( mask_ == Mask::cNone )
			throw AllocFailed( "Exceeds limit of UniqueIndex instances");
		return mask_.clearFirstSet();
	}

	void FreeIndexList::free( Index index )
	{
		mask_.set(index); 
	}

	bool FreeIndexList::isEmpty()
	{ 
		return mask_ == Mask::cAll; 
	}

	bool FreeIndexList::isFull()
	{ 
		return mask_ == Mask::cNone; 
	}

} //END: Sub0Ent