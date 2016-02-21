#include "netvars.h"

int Netvars::m_hActiveWeapon;
int Netvars::m_iTeamNum;
int Netvars::m_lifeState;
int Netvars::m_vecOrigin;
int Netvars::m_fFlags;
int Netvars::m_nWaterLevel;
int Netvars::m_iHealth;
int Netvars::m_Local;
int Netvars::m_vecPunchAngle;
int Netvars::m_bPlayerSpotted;
int Netvars::m_flFlashMaxAlpha;
int Netvars::m_vecViewOffset0;
int Netvars::m_vecVelocity0;
int Netvars::m_angEyeAngles0;
int Netvars::m_nTickBase;
int Netvars::m_flNextPrimaryAttack;

RecvTable* recvTables[8192];

void Netvars::Dump(const char* f)
{
	FILE* o = pipe::OpenFile(f);

	if (!o)
		return;

	Dump(o);
	fclose(o);
}

extern IClient* client;

void Netvars::Dump(_iobuf* o)
{
	const char* region = "< unknown origin >";
	const char* lprev = NULL;

	for (int i = 0; i < GetHighestIndex(); i++)
	{
		for (ClientClass* CC = client->GetAllClasses(); CC; CC = CC->m_pNext)
			if (CC->m_pRecvTable == recvTables[i])
			{
				region = CC->m_pNetworkName;
				break;
			}

		if (region != lprev)
		{
			fprintf(o, "%s:\n", region);
			lprev = region;
		}
		
		fprintf(o, "\t%s:\n", recvTables[i]->m_pNetTableName);

		for (int x = 0; x < recvTables[i]->m_nProps; x++)
			if (recvTables[i]->m_pProps[x].m_pDataTable)
				fprintf(o, "\t\t0x%04X -> %s : %s\n",
					recvTables[i]->m_pProps[x].m_Offset,
					recvTables[i]->m_pProps[x].m_pVarName,
					recvTables[i]->m_pProps[x].m_pDataTable->m_pNetTableName);
			else
				fprintf(o, "\t\t0x%04X -> %s\n",
					recvTables[i]->m_pProps[x].m_Offset,
					recvTables[i]->m_pProps[x].m_pVarName);

		fputc('\n', o);
		fflush(o);
	}
}

int Netvars::GetHighestIndex()
{
	for (int i = 0; i < (sizeof(recvTables) / 4); i++)
		if (!recvTables[i])
			return i;

	return 0;
}

void Netvars::ScanRecursively(RecvTable* recvTable)
{
	recvTables[GetHighestIndex()] = recvTable;

	for (int i = 0; i < recvTable->m_nProps; i++)
	{
		RecvProp* prop = &recvTable->m_pProps[i];

		if (prop->m_pDataTable)
		{
			bool hasvalue = false;
			for (int x = 0; x < GetHighestIndex(); x++)
				if (recvTables[x] == prop->m_pDataTable)
					hasvalue = true;

			if (!hasvalue)
				ScanRecursively(prop->m_pDataTable);
		}
	}
}

int Netvars::GetNetvar(const char* dt, const char* m)
{
	bool any = dt[0] == '*';

	for (int i = 0; i < GetHighestIndex(); i++)
		if (any || !strcmp(recvTables[i]->m_pNetTableName, dt))
			for (int x = 0; x < recvTables[i]->m_nProps; x++)
				if (!strcmp(recvTables[i]->m_pProps[x].m_pVarName, m))
					return recvTables[i]->m_pProps[x].m_Offset;
	
	util::Message("Failed to get %s -> %s", dt, m);

	return 0;
}

bool Netvars::HookNetvar(const char* dt, const char* m, RecvVarProxyFn fn)
{
	bool any = dt[0] == '*';

	for (int i = 0; i < GetHighestIndex(); i++)
		if (any || !strcmp(recvTables[i]->m_pNetTableName, dt))
			for (int x = 0; x < recvTables[i]->m_nProps; x++)
				if (!strcmp(recvTables[i]->m_pProps[x].m_pVarName, m))
					recvTables[i]->m_pProps[x].m_ProxyFn = fn;

	return true;
}



#define RESOLVE(DT, VAR)		VAR = GetNetvar(#DT, #VAR);
#define RESOLVE2(DT, VAR, VAR2)	VAR = GetNetvar(DT, VAR2);

void Netvars::Initialize()
{
	memset(recvTables, 0, sizeof(recvTables));

	for (ClientClass* CC = client->GetAllClasses(); CC; CC = CC->m_pNext)
		ScanRecursively(CC->m_pRecvTable);

	RESOLVE(DT_BaseCombatCharacter, m_hActiveWeapon)
	RESOLVE(DT_BaseEntity, m_iTeamNum)
	RESOLVE(DT_BaseEntity, m_vecOrigin)
	RESOLVE(DT_BasePlayer, m_lifeState)
	RESOLVE(DT_BasePlayer, m_fFlags)
	RESOLVE(DT_BasePlayer, m_iHealth)
	RESOLVE(DT_LocalPlayerExclusive, m_Local)
	RESOLVE(DT_LocalPlayerExclusive, m_nTickBase)
	RESOLVE(DT_LocalActiveWeaponData, m_flNextPrimaryAttack)

	if (insurgency())	RESOLVE2("DT_Local", m_vecPunchAngle, "m_viewPunchAngle")
	else				RESOLVE(DT_Local, m_vecPunchAngle)

	if (css())
	{
		RESOLVE(DT_CSPlayer, m_flFlashMaxAlpha)
		RESOLVE(DT_CSPlayerResource, m_bPlayerSpotted)
	}

	RESOLVE2("*", m_nWaterLevel, "m_nWaterLevel")
	RESOLVE2("*", m_angEyeAngles0, "m_angEyeAngles[0]")
	RESOLVE2("*", m_vecViewOffset0, "m_vecViewOffset[0]")
	RESOLVE2("DT_LocalPlayerExclusive", m_vecVelocity0, "m_vecVelocity[0]")
}