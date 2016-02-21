#include "sdk.h"

#include "util.h"
#include "pipe.h"

bool EInterface::Init(pdword* base)
{
	if (_vmt = base)
	{
		_hook = new VMT(_vmt);
		_size = _hook->GetVMTSize(*_vmt);
		
		pipe::Report("\t%i virtual members\n", _size);

		return true;
	}
	
	pipe::Report("\tunresolved");

	return false;
}

bool EInterface::Init(const char* dll, const char* name, int v)
{
	CreateInterfaceFn CreateInterface = (CreateInterfaceFn)IMPORT(dll, "CreateInterface");

	char test[128];
	sprintf(test, "%s%03i", name, v);

	if (!v)
		for (int i = 99; i && !v; i--)
		{
			sprintf(test, "%s%03i", name, i);

			if (CreateInterface(test, NULL))
				v = i;
		}

	pipe::Report("\n%s -> %s v%i", dll, name, v);

	return Init((pdword*)CreateInterface(test, NULL));
}

void EInterface::HookMethod(int m, void* hook, void* original)
{
	dword org = _hook->HookMethod((dword)hook, m);

	if (original)
		*(pdword)original = org;
}

dword EInterface::GetMethod(int m)
{
	return _hook->GetMethodAddress(m);
}

bool EInterface::SigCmp(const char* base, const char* sig)
{
	for (; *sig; ++base, ++sig)
		if (*sig != '?' && *sig != *base)
			return false;

	return *sig == 0;
}

bool EInterface::FindProc(int* mem, const char* sig, const char* dbg, int def)
{
	for (int i = *mem; i < _size; i++)
		if (SigCmp((const char*)GetMethod(i), sig))
		{
			if (dbg)
				pipe::Report("\t%s -> %i", dbg, i);

			*mem = i;
			return true;
		}

	if (dbg)
		pipe::Report("\t%s unresolved, using default %i", dbg, def);

	*mem = def;

	return false;
}

void IInput::ResolveInfo()
{
	pipe::Report("\tUsercommand data", MP_BACKUP);

	if (dword base = util::FindPattern(GetMethod(8), 0x100, "\x03?????\x33"))
	{
		BASE = *(pdword)(base + 2);
		pipe::Report("\t\t%X base", BASE);
	}

	if (SINGLEBASE = util::CalcStack(GetMethod(8)) == 1)
	{
		if (dword size = util::FindPattern(GetMethod(8), 0x100, "\x69\xC0"))
		{
			UCMD_SIZE = *(pdword)(size + 2);
			pipe::Report("\t\t%i bytes ", UCMD_SIZE);
		}
		else
		if (dword bits = util::FindPattern(GetMethod(8), 0x100, "\xC1\xE0"))
		{
			UCMD_SIZE = 1 << *(pbyte)(bits + 2);
			pipe::Report("\t\t%i bytes ", UCMD_SIZE);
		}

		if (dword slots = util::FindPattern(GetMethod(8), 0x100, "\x6B\xD2"))
		{
			MP_BACKUP = *(pbyte)(slots + 2);
			pipe::Report("\t\t%i reserved", MP_BACKUP);
		}
	}
	else
	{
		if (dword size = util::FindPattern(GetMethod(8), 0x100, "\x6B\xC0"))
		{
			UCMD_SIZE = *(pbyte)(size + 2);
			pipe::Report("\t\t%i bytes ", UCMD_SIZE);
		}
		else
		if (dword size2 = util::FindPattern(GetMethod(8), 0x100, "\x2B\xC2\x69\xC0"))
		{
			UCMD_SIZE = *(pdword)(size2 + 4);
			pipe::Report("\t\t%i bytes ", UCMD_SIZE);
		}

		if (dword slots = util::FindPattern(GetMethod(8), 0x100, "\x69\xD2"))
		{
			MP_BACKUP = *(pdword)(slots + 2);
			pipe::Report("\t\t%i reserved", MP_BACKUP);
		}
	}

	// BASE = 0xC4;

	//MP_BACKUP = 90;
	//UCMD_SIZE = 64;
}

const char* CBaseEntity::GetClassname()
{
	typedef const char* (__thiscall* GetClassnameFn)(void*);
	static GetClassnameFn get = (GetClassnameFn)util::FindPattern("client", "\x57\x8B\xF9\x8B\x87????\x85\xC0\x74\x0D\x50\xE8");

	return get(this);
}

mstudiohitboxset*	CBaseEntity::hboxset	= NULL;
matrix3x4			CBaseEntity::matrix[BONE_ARRAY];

bool CBaseEntity::UpdateBones()
{
	extern IModelInfo* mdlinfo;

	void* mdl = GetModel(), *stdhdr;

	if (!mdl)
		return false;

	stdhdr = mdlinfo->GetStudiomodel(mdl);

	if (!stdhdr)
		return false;

	if (SetupBones(matrix, BONE_ARRAY, 0x100, 0))
	{
		int boxset = ReadPtr<int>(stdhdr, 0xB0);
		if (hboxset = (mstudiohitboxset*)(((pbyte)stdhdr) + boxset))
			return true;
	}

	return false;
}

float CBaseEntity::GetNextPrimaryFire()
{
	return ReadPtr<float>((void*)this, Netvars::m_flNextPrimaryAttack);
}

int CBaseEntity::GetTickBase()
{
	return ReadPtr<int>((void*)this, Netvars::m_nTickBase);
}

CBaseEntity* CBaseEntity::GetActiveWeapon()
{
	extern IEntities* ents;
	extern IEngine* engine;

	return ents->GetClientEntityHandle(ReadPtr<unsigned long>((void*)this, Netvars::m_hActiveWeapon));
}

int CBaseEntity::GetTeam()
{
	return ReadPtr<int>((void*)this, Netvars::m_iTeamNum);
}

int CBaseEntity::GetHealth()
{
	return ReadPtr<int>((void*)this, Netvars::m_iHealth);
}

bool CBaseEntity::IsAlive()
{
	return !ReadPtr<bool>((void*)this, Netvars::m_lifeState);
}

dword CBaseEntity::GetHPColor()
{
	extern IEntities* ents;
	extern IEngine* engine;

	float p = GetHealthPercentage();

	if (p < 0.33f)
		return CC_RED;

	if (p < 0.66f)
		return CC_YELLOW;

	return CC_GREEN;
}

dword CBaseEntity::GetESPColor()
{
	extern IEntities* ents;
	extern IEngine* engine;

	if (gmod())
	{
		CBaseEntity* lp = LocalPlayer();

		if (lp->GetTeam() == this->GetTeam())
			return CC_LIGHTBLUE;
		else
			return CC_LIGHTRED;
	}
	else
	{
		int team = GetTeam();

		if (team == TEAM_RED)
			return CC_LIGHTRED;

		if (team == TEAM_BLU)
			return CC_LIGHTBLUE;
	}

	return CC_WHITE;
}

const char* CBaseEntity::GetNick()
{
	extern IEngine* engine;
	static player_info info;

	engine->GetPlayerInfo(this->EntIndex(), &info);

	return info.name;
}

const char* CBaseEntity::GetNickSafe()
{
	extern IEngine* engine;
	static player_info info;

	engine->GetPlayerInfo(this->EntIndex(), &info);
	util::SafeFormat(info.name);

	return info.name;
}

int CBaseEntity::GetFlags()
{
	return ReadPtr<int>((void*)this, Netvars::m_fFlags);
}

char CBaseEntity::GetWaterLevel()
{
	return ReadPtr<char>((void*)this, Netvars::m_nWaterLevel);
}

bool CBaseEntity::CSS_IsSemiAuto()
{
	const char* cclass = GetClientClass()->m_pNetworkName;

	return !strcmp(cclass, "CWeaponGlock")	||
		!strcmp(cclass, "CWeaponUSP")		||
		!strcmp(cclass, "CWeaponP228")		|| 
		!strcmp(cclass, "CDEagle")			|| 
		!strcmp(cclass, "CWeaponFiveSeven")	||
		!strcmp(cclass, "CWeaponElite")		||
		!strcmp(cclass, "CWeaponAWP")		||
		!strcmp(cclass, "CWeaponScout");
}

bool CBaseEntity::ShouldIgnore()
{
	const char* cclass = GetClientClass()->m_pNetworkName;
	
	if (css())
	return !strcmp(cclass, "CC4")			||
		!strcmp(cclass, "CKnife")			||
		!strcmp(cclass, "CBaseCSGrenade")	||
		!strcmp(cclass, "CHEGrenade")		|| 
		!strcmp(cclass, "CSmokeGrenade")	||
		!strcmp(cclass, "CFlashbang");

	if (gmod())
	return !strcmp(cclass, "CWeaponPhysGun");

	return false;
}

Vector CBaseEntity::GetEyeAngles()
{
	return ReadPtr<Vector>((void*)this, Netvars::m_angEyeAngles0);
}

Vector CBaseEntity::GetOrigin()
{
	return ReadPtr<Vector>((void*)this, Netvars::m_vecOrigin);
}

Vector CBaseEntity::GetCenter()
{
	Vector mins, maxs, ctr;
	GetRenderBounds(mins, maxs);

	ctr = GetOrigin();
	ctr.z += (mins.z + maxs.z) * 0.5f;

	return ctr;
}

Vector CBaseEntity::GetAbsCenter()
{
	Vector mins, maxs, ctr;
	GetRenderBounds(mins, maxs);

	ctr = GetAbsOrigin();
	ctr.z += (mins.z + maxs.z) * 0.5f;

	return ctr;
}

Vector CBaseEntity::GetVelocity()
{
	return ReadPtr<Vector>((void*)this, Netvars::m_vecVelocity0);
}

Vector CBaseEntity::GetShootPos()
{
	return GetAbsOrigin() + ReadPtr<Vector>((void*)this, Netvars::m_vecViewOffset0);
}

Vector CBaseEntity::GetServersideShootPos()
{
	return GetOrigin() + ReadPtr<Vector>((void*)this, Netvars::m_vecViewOffset0);
}

Vector CBaseEntity::GetViewPunch()
{
	return ReadPtr<Vector>((void*)this, Netvars::m_Local + Netvars::m_vecPunchAngle);
}