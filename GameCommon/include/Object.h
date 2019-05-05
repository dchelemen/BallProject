#pragma once
#pragma warning(disable:4251)

#include "GameCommon/include/Export.h"

#include <vector>

class GAMECOMMON_API CObject
{
public:
	CObject() = delete;
	CObject( CObject* aParent );
	virtual ~CObject();

protected:

private:
	std::vector< CObject* > m_ChildVect;
};