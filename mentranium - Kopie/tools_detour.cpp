#include "tools_detour.h"
 
CVMTHook::CVMTHook(void* instance)
{
	HANDLE hProcessHeap;
 
	if( !instance)
		return;

	m_pInstance = (void***) instance;
	m_pOriginalVTable = *m_pInstance;
 
	//Count number of Pointers in the table
 
	m_iNumIndices = 0;
 
	//TODO: check if pointer into .text section
	while(m_pOriginalVTable[m_iNumIndices])
	{
		m_iNumIndices++;
	}

	//Allocate memory on the heap for our own copy of the table
 
	hProcessHeap = GetProcessHeap();
 
	if ( !hProcessHeap )
		return;

	m_pNewVTable = (void**) HeapAlloc(hProcessHeap, 0, sizeof(void*) * m_iNumIndices);

	if ( !m_pNewVTable )
		return;
	
	memcpy(m_pNewVTable, m_pOriginalVTable, sizeof(void*) * m_iNumIndices);
	*m_pInstance=m_pNewVTable;

}

int CVMTHook::tellCount( )
{

	int m_iNumIndices = 0;
 
	//TODO: check if pointer into .text section
	while(m_pOriginalVTable[m_iNumIndices])
	{
		m_iNumIndices++;
	}

	return m_iNumIndices;
}

void* CVMTHook::hookFunction(size_t iIndex, void* pfnHook)
{
	//Valid index?
	if(iIndex >= m_iNumIndices)
		return NULL;
 
	//Write new pointer
	m_pNewVTable[iIndex] = pfnHook;
 
	//And return pointer to original function
	return m_pOriginalVTable[iIndex];
}