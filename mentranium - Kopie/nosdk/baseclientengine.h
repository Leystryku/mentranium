/* * * * * * * * * * * * * * * * 
 * 	 /// MENTRANIUM \\\
 *
 *  - By Leystyku
 * * * * * * * * * * * * * * * */

#ifndef _IBASEENGINECLEINT

#define _IBASEENGINECLEINT

#include "../includes.h"


// ======================= TYPEDEFS ======================= //

class RecvTable;

class ClientClass
{
public:
	ClientClass( char *pNetworkName/*, CreateClientClassFn createFn, CreateEventFn createEventFn, RecvTable *pRecvTable*/ )
	{
		/*m_pNetworkName	= pNetworkName;
		m_pCreateFn		= createFn;
		m_pCreateEventFn= createEventFn;
		m_pRecvTable	= pRecvTable;
		
		// Link it in
		m_pNext				= g_pClientClassHead;
		g_pClientClassHead	= this;*/
	}

	const char* GetName()
	{
		return m_pNetworkName;
	}

public:
	void*					m_pCreateFn;//LOL
	void*					m_pCreateEventFn;	// LOL Only called for event objects.
	char					*m_pNetworkName;
	RecvTable				*m_pRecvTable;
	ClientClass				*m_pNext;
	int						m_ClassID;	// Managed by the engine.

};

class RecvProp
{
// This info comes from the receive data table.
public:
							RecvProp();

	void					InitArray( int nElements, int elementStride );

	int						GetNumElements() const;
	void					SetNumElements( int nElements );

	int						GetElementStride() const;
	void					SetElementStride( int stride );

	int						GetFlags() const;

	const char*				GetName() const;
	void*					GetType() const;

	RecvTable*				GetDataTable() const;
	void					SetDataTable( /*RecvTable *pTable*/ );

	void*					GetProxyFn() const;
	void					SetProxyFn( /*RecvVarProxyFn fn*/ );

	void*					GetDataTableProxyFn() const;
	void					SetDataTableProxyFn( /*DataTableRecvVarProxyFn fn*/ );

	int						GetOffset() const;
};


class RecvTable
{
public:

	typedef RecvProp	PropType;

				RecvTable();
				RecvTable( RecvProp *pProps, int nProps, char *pNetTableName );
				~RecvTable();

	void		Construct( RecvProp *pProps, int nProps, char *pNetTableName );

	int			GetNumProps();
	RecvProp*	GetProp( int i );

	const char*	GetName();

	// Used by the engine while initializing array props.
	void		SetInitialized( bool bInitialized );
	bool		IsInitialized() const;

	// Used by the engine.
	void		SetInMainList( bool bInList );
	bool		IsInMainList() const;


public:

	// Properties described in a table.
	RecvProp		*m_pProps;
	int				m_nProps;
};

class ClientClass;

typedef ClientClass*	( __thiscall* GetAllClassesFn )( void* );
typedef int	( __thiscall* GetScreenWidthFn )( void* );
typedef int	( __thiscall* GetScreenHeightFn )( void* );

// ======================= INDICES ======================= //

#define INDEX_BASECLIENTENGINE_GETALLCLASSES			1
#define INDEX_BASECLIENTENGINE_GETSCREENWIDTH			1
#define INDEX_BASECLIENTENGINE_GETSCREENHEIGHT			1

// ======================= CLASS HEADER ======================= //

class IBaseClientEngine {
	
protected:

	PDWORD_PTR* base;
	template <typename T> T GetFunction( PDWORD_PTR*, UINT index );

public:

	PDWORD_PTR* GetBase();

	IBaseClientEngine( PDWORD_PTR* );   

	ClientClass* GetAllClasses();
	int GetScreenWidth();
	int GetScreenHeight();

};

#endif