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
	int tellCount( );

};


#endif //__VMTHOOK_H__