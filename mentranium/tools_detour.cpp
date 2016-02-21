
int calls = 0; // dum'

CVMTHook::CVMTHook(void* instance)
{

	calls++;

	if( !instance)
		return;

	m_pInstance = (void***) instance;

	if ( !m_pInstance )
		return;

	m_pOriginalVTable = *m_pInstance;

	if ( !m_pOriginalVTable )
		return;

	//Count number of Pointers in the table
 
	int num = 0;
 
	while(m_pOriginalVTable[num])
	{
		num++;
	}

	m_iNumIndices = num;

	if ( m_iNumIndices == 0 )
		return;

	//Allocate memory on the heap for our own copy of the table
	int size = sizeof(void*) * m_iNumIndices;

	m_pNewVTable = (void**) malloc(size);

	if ( !m_pNewVTable )
		return;
	
	memcpy(m_pNewVTable, m_pOriginalVTable, size);
	*m_pInstance=m_pNewVTable;

}

int CVMTHook::tellCount( )
{
	calls++;

	/*
	int m_iNumIndices = 0;
 
	while(m_pOriginalVTable[m_iNumIndices])
	{
		m_iNumIndices++;
	}*/

	return m_iNumIndices;
}

void* CVMTHook::hookFunction(size_t iIndex, void* pfnHook)
{
	calls++;

	//Valid index?
	if(iIndex >= m_iNumIndices)
		return NULL;

	if ( !m_pOriginalVTable[iIndex] )
		return NULL;

	//Write new pointer
	m_pNewVTable[iIndex] = pfnHook;
 
	//And return pointer to original function
	return m_pOriginalVTable[iIndex];
}

void* CVMTHook::unhookFunction(size_t iIndex)
{
	calls++;

	//Valid index?
	if(iIndex >= m_iNumIndices)
		return NULL;

	if ( !m_pOriginalVTable[iIndex] )
		return NULL;

	//Rewrite old pointer
	m_pNewVTable[iIndex] = m_pOriginalVTable[iIndex];
	//m_pInstance[iIndex] = &m_pOriginalVTable[iIndex];
	
	//And return pointer to original function
	return m_pOriginalVTable[iIndex];
}

void* CVMTHook::callFunction(size_t iIndex, int n, ...)
{

	//Valid index?
	if(iIndex >= m_iNumIndices)
		return NULL;

	if ( !m_pInstance )
		return NULL;

	if ( !m_pOriginalVTable[iIndex] )
		return NULL;

	void *org =  m_pOriginalVTable[iIndex];
	void *inst = m_pInstance;

	va_list v;
	va_start(v, n);

	v += n * 4 + 4;

	for (int i = 0; i < n; i++)
	{
		void* a = *(void**)((v -= 4) - 4);
		__asm PUSH a
	}

	void* r;
	
	__asm MOV ECX, inst

	__asm
	{
		CALL org
		MOV r, EAX
	}

	va_end(v);

	if ( r )
		MessageBox( NULL, "got return", "LOL", MB_OK );

	return r;
}

