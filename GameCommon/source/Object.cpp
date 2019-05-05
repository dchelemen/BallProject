#include "GameCommon/include/Object.h"

CObject::CObject( CObject* aParent )
{
	if ( !aParent )
		return;

	aParent->m_ChildVect.push_back( this );
}

CObject::~CObject()
{
	for ( auto child : m_ChildVect )
	{
		delete child;
	}
	m_ChildVect.clear();
}