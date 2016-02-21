#ifndef __VMTHOOK_H__
#define __VMTHOOK_H__

class CVMTHook
{
public:
	CVMTHook(void* instance);

	size_t m_iNumIndices;
	void** m_pOriginalVTable;
	void** m_pNewVTable;
	void*** m_pInstance;

	void* hookFunction(size_t iIndex, void* pfnHook);
	void* unhookFunction(size_t iIndex);
	void* callFunction(size_t iIndex, int n, ...);

	int tellCount( );

};


#include "tools_detour.cpp"

#endif //__VMTHOOK_H__