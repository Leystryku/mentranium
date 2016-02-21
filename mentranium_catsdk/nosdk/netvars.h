#pragma once
#include "main.h"

class RecvProp;
class RecvTable;

class NetvarValue
{
public:
	union
	{
		float	m_Float;
		long	m_Int;
		char*	m_pString;
		void*	m_pData;
		float	m_Vector[3];
	};

	int			m_Type;
};

class CRecvProxyData
{
public:
	const RecvProp*	m_pRecvProp;
	NetvarValue		m_Value;
	int				m_iElement;
	int				m_ObjectID;
};

typedef void (*RecvVarProxyFn)(const CRecvProxyData*, void*, void*);

class RecvProp
{
public:
	char*			m_pVarName;
	int				m_RecvType;
	int				m_Flags;
	int				m_StringBufferSize;
	bool			m_bInsideArray;
	void*			m_pExtraData;
	RecvProp*		m_pArrayProp;
	void*			m_ArrayLengthProxy;
	RecvVarProxyFn	m_ProxyFn;
	void*			m_DataTableProxyFn;
	RecvTable*		m_pDataTable;
	int				m_Offset;
	int				m_ElementStride;
	int				m_nElements;
	const char*		m_pParentArrayPropName;
};

class RecvTable
{
public:
	RecvProp*	m_pProps;
	int			m_nProps;
	void*		m_pDecoder;
	char*		m_pNetTableName;
	bool		m_bInitialized;
	bool		m_bInMainList;
};

class ClientClass
{
public:
	char			header[8];
	char*			m_pNetworkName;
	RecvTable*		m_pRecvTable;
	ClientClass*	m_pNext;
	int				m_ClassID;
};

namespace Netvars
{
	extern int m_hActiveWeapon;
	extern int m_iTeamNum;
	extern int m_lifeState;
	extern int m_vecOrigin;
	extern int m_fFlags;
	extern int m_nWaterLevel;
	extern int m_iHealth;
	extern int m_Local;
	extern int m_vecPunchAngle;
	extern int m_bPlayerSpotted;
	extern int m_flFlashMaxAlpha;
	extern int m_vecViewOffset0;
	extern int m_vecVelocity0;
	extern int m_angEyeAngles0;
	extern int m_nTickBase;
	extern int m_flNextPrimaryAttack;

	void Initialize();
	void ScanRecursively(RecvTable* recvTable);
	int GetHighestIndex();

	void Dump(_iobuf* o);
	void Dump(const char* o);
	bool HookNetvar(const char* dt, const char* m, RecvVarProxyFn hook = NULL);
	int GetNetvar(const char* dt, const char* m);
}