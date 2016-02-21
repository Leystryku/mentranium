#pragma once
#include "includes.h"

typedef void*	(__cdecl* CreateInterfaceFn)(const char*, unsigned long);
typedef void	(__cdecl* RandomSeed_t)	(int);
typedef float	(__cdecl* RandomFloat_t)(float, float);

template<typename Fn>
inline Fn GetVFunc(unsigned long** v, int i)
{
	return reinterpret_cast<Fn>((*v)[i]);
}

template<typename T>
inline T ReadPtr(void* base, unsigned long offset)
{
	return *(T*)((unsigned long)base + offset);
}

template<typename T>
inline void WritePtr(void* base, unsigned long offset, T value)
{
	*(T*)((unsigned long)base + offset) = value;
}

enum
{
	TEAM_UNASSIGNED,
	TEAM_SPECTATOR,
	TEAM_RED,
	TEAM_BLU,
};

enum
{
	MASK_SHOT	= 0x4600400B,
	MASK_WINDOW	= 0,
};

enum
{
	FLOW_OUTGOING = 0,
	FLOW_INCOMING
};

enum
{
	Class_None,
	Class_Scout,
	Class_Sniper,
	Class_Soldier,
	Class_Demoman,
	Class_Medic,
	Class_Heavy,
	Class_Pyro,
	Class_Spy,
	Class_Engineer,
};

enum
{
	PlayerCond_None = 0,
	PlayerCond_Slowed			= (1 << 0),
	PlayerCond_Zoomed			= (1 << 1),
	PlayerCond_Disguising		= (1 << 2),
	PlayerCond_Disguised		= (1 << 3),
	PlayerCond_Cloaked			= (1 << 4),
	PlayerCond_Ubercharged		= (1 << 5),
	PlayerCond_TeleportGlow		= (1 << 6),
	PlayerCond_Taunting			= (1 << 7),
	PlayerCond_UberchargeFade	= (1 << 8),
	PlayerCond_CloakFlicker		= (1 << 9),
	PlayerCond_Teleporting		= (1 << 10),
	PlayerCond_Kritzkreiged		= (1 << 11),
	PlayerCond_DeadRingered		= (1 << 13),
	PlayerCond_Bonked			= (1 << 14),
	PlayerCond_Dazed			= (1 << 15),
	PlayerCond_Buffed			= (1 << 16),
	PlayerCond_Charging			= (1 << 17),
	PlayerCond_DemoBuff			= (1 << 18),
	PlayerCond_CritCola			= (1 << 19),
	PlayerCond_InHealRadius		= (1 << 20),
	PlayerCond_Healing			= (1 << 21),
	PlayerCond_OnFire			= (1 << 22),
	PlayerCond_Overhealed		= (1 << 23),
	PlayerCond_Jarated			= (1 << 24),
	PlayerCond_Bleeding			= (1 << 25),
	PlayerCond_DefenseBuffed	= (1 << 26),
	PlayerCond_Milked			= (1 << 27),
	PlayerCond_MegaHeal			= (1 << 28),
	PlayerCond_RegenBuffed		= (1 << 29),
	PlayerCond_MarkedForDeath	= (1 << 30),
};

enum
{
	AC_IDLE = 0,
	AC_STATE_STARTFIRING,
    AC_STATE_FIRING,
    AC_STATE_SPINNING,
};

enum
{
	FL_ONGROUND		= (1 << 0),
	FL_DUCKING		= (1 << 1),
};

enum
{
	IN_ATTACK		= (1 << 0),
	IN_JUMP			= (1 << 1),
	IN_DUCK			= (1 << 2),
	IN_FORWARD		= (1 << 3),
	IN_BACK			= (1 << 4),
	IN_USE			= (1 << 5),
	IN_CANCEL		= (1 << 6),
	IN_LEFT			= (1 << 7),
	IN_RIGHT		= (1 << 8),
	IN_MOVELEFT		= (1 << 9),
	IN_MOVERIGHT	= (1 << 10),
	IN_ATTACK2		= (1 << 11),
	IN_RUN			= (1 << 12),
	IN_RELOAD		= (1 << 13),
	IN_ALT1			= (1 << 14),
	IN_ALT2			= (1 << 15),
	IN_SCORE		= (1 << 16),
	IN_SPEED		= (1 << 17),
	IN_WALK			= (1 << 18),
	IN_ZOOM			= (1 << 19),
	IN_WEAPON1		= (1 << 20),
	IN_WEAPON2		= (1 << 21),
	IN_BULLRUSH		= (1 << 22),
};

enum
{
	MAT_DEBUG						= (1 << 0),
	MAT_NO_DEBUG_OVERRIDE			= (1 << 1),
	MAT_NODRAW						= (1 << 2),
	MAT_USE_IN_FILLRATE_MODE		= (1 << 3),
	MAT_VERTEXCOLOR					= (1 << 4),
	MAT_VERTEXALPHA					= (1 << 5),
	MAT_SELFILLUM					= (1 << 6),
	MAT_ADDITIVE					= (1 << 7),
	MAT_ALPHATEST					= (1 << 8),
	MAT_MULTIPASS					= (1 << 9),
	MAT_ZNEARER						= (1 << 10),
	MAT_MODEL						= (1 << 11),
	MAT_FLAT						= (1 << 12),
	MAT_NOCULL						= (1 << 13),
	MAT_NOFOG						= (1 << 14),
	MAT_IGNOREZ						= (1 << 15),
	MAT_DECAL						= (1 << 16),
	MAT_ENVMAPSPHERE				= (1 << 17),
	MAT_NOALPHAMOD					= (1 << 18),
	MAT_ENVMAPCAMERASPACE			= (1 << 19),
	MAT_BASEALPHAENVMAPMASK			= (1 << 20),
	MAT_TRANSLUCENT					= (1 << 21),
	MAT_NORMALMAPALPHAENVMAPMASK	= (1 << 22),
	MAT_NEEDS_SOFTWARE_SKINNING		= (1 << 23),
	MAT_OPAQUETEXTURE				= (1 << 24),
	MAT_ENVMAPMODE					= (1 << 25),
	MAT_SUPPRESS_DECALS				= (1 << 26),
	MAT_HALFLAMBERT					= (1 << 27),
	MAT_WIREFRAME					= (1 << 28),
	MAT_ALLOWALPHATOCOVERAGE		= (1 << 29)
};




#define	DECLFUNCA(I, RET, NAME, A, T, P, OBJ)	inline RET NAME A\
{\
	return GetVFunc<RET (__thiscall*) T>((pdword*)OBJ, I) P;\
}

struct GlobalVars
{
	float	RealTime;
	int		FrameCount;
	float	AbsoluteFrameTime;
	float	CurTime;
	float	FrameTime;
	int		MaxClients;
	int		TickCount;
	float	IntervalPerTick;
	float	InterpolationAmount;
	int		SimTicksThisFrame;
	int		NetworkProtocol;
	void*	SaveData;
	bool	Client;
	int		TimestampNetworkingBase;
	int		TimestampRandomizeWindow;
};

struct player_info
{
	char			name[32];
	int				userid;
	char			guid[33];
	unsigned int	friendsid;
	char			friendsname[32];
	bool			fakeplayer;
	bool			ishltv;
	unsigned long	customfiles[4];
	unsigned char	filesdownloaded;
};

struct CUserCmd
{
	int		header;
	int		command_number;
	int		tick_count;
	Vector	viewangles;
	Vector	move;
	int		buttons;
	char	impulse;
	int		weaponselect;
	int		weaponsubtype;
	int		random_seed;
	short	mousex;
	short	mousey;
	bool	hasbeenpredicted;

	inline char* mousewheel()
	{
		return (char*)((unsigned long)this + 0x59);
	}
};

struct ray
{
	VectorAligned m_Start;
	VectorAligned m_Delta;
	VectorAligned m_StartOffset;
	VectorAligned m_Extents;
	// int pad0;
	bool m_IsRay;
	bool m_IsSwept;

	ray(Vector start, Vector end)
	{
		Init(start, end);
	}

	void Init(Vector start, Vector end)
	{
		m_Delta.x = end.x - start.x;
		m_Delta.y = end.y - start.y;
		m_Delta.z = end.z - start.z;
		m_IsSwept = m_Delta.LengthSqr() != 0;
		m_Extents.x = m_Extents.y = m_Extents.z = 0;
		m_IsRay = true;
		m_StartOffset.x = m_StartOffset.y = m_StartOffset.z = 0;
		m_Start.x = start.x;
		m_Start.y = start.y;
		m_Start.z = start.z;
	}
};

class CBaseEntity;
struct rt
{
	Vector			startpos;
	Vector			endpos;
	Vector			normal;
	float			distance;
	char			type;
	char			signbits;
	short			unknown;
	float			fraction;
	int				contents;
	unsigned short	dispflags;
	bool			allsolid;
	bool			startsolid;
	float			fractionleftsolid;
	const char*		name;
	short			surfaceprops;
	unsigned short	flags;
	int				hitgroup;
	short			physicsbone;
	CBaseEntity*	ent;
	int				hitbox;
};

struct mstudiobbox
{
	int		bone;
	int		group;
	Vector	bbmin;
	Vector	bbmax;
	int		szhitboxnameindex;
	int		unused[8];

	inline char* pszHitboxName()
	{
		if (!szhitboxnameindex)
			return "";

		return (char*)(((dword)this) + szhitboxnameindex);
	}
};

struct mstudiohitboxset
{
	int					sznameindex;
	inline char* const	name(void) const	{ return (char*)(((dword)this) + sznameindex); }
	int					numhitboxes;
	int					hitboxindex;
	inline mstudiobbox* hitbox(int i) const { return (mstudiobbox*)(((byte*)this) + hitboxindex) + i; };
};

struct ModelRenderInfo
{
	Vector			origin;
	QAngle			angles; 
	CBaseEntity*	entity;
	void*			model;
	void*			world;
	void*			lighting;
	Vector*			lighting_origin;
	int				flags;
	int				entity_index;
	int				skin;
	int				body;
	int				hitboxset;
};





#define	BONE_ARRAY	128

class ClientClass;
class ILuaObject;

class CBaseEntity
{
public:
	DECLFUNCA(183, ILuaObject*,	GMOD_GetLuaTable,	(), (void*), (this), (this));
	DECLFUNCA(187, bool,		GMOD_HasLuaTable,	(), (void*), (this), (this));

	DECLFUNCA(2, ClientClass*,	GetClientClass,	(), (void*), ((void*)(this + 0x8)), (void*)(this + 0x8));
	DECLFUNCA(8, bool,			IsDormant,		(), (void*), ((void*)(this + 0x8)), (void*)(this + 0x8));
	DECLFUNCA(9, int,			EntIndex,		(), (void*), ((void*)(this + 0x8)), (void*)(this + 0x8));
	DECLFUNCA(9, void*,			GetModel,		(), (void*), ((void*)(this + 0x4)), (void*)(this + 0x4));
	DECLFUNCA(9, Vector&,		GetAbsOrigin,	(), (void*), (this), (this));
	DECLFUNCA(10, Vector&,		GetAbsAngles,	(), (void*), (this), (this));
	DECLFUNCA(20, void,			GetRenderBounds,
		(Vector &mins, Vector &maxs),
		(void*, Vector&, Vector&),
		((void*)(this + 0x4), mins, maxs),
		(void*)(this + 0x4)
		);

	DECLFUNCA(16, bool,			SetupBones,
		(matrix3x4* matrix, int bones, int msk, float time),
		(void*, matrix3x4*, int, int, float),
		((void*)(this + 0x4), matrix, bones, msk, time),
		(void*)(this + 0x4)
		);

	static mstudiohitboxset*	hboxset;
	static matrix3x4			matrix[BONE_ARRAY];

	const char* GetClassname();
	bool		UpdateBones();
	inline int	Hitboxes() { return hboxset->numhitboxes; };
	inline mstudiobbox* GetHitbox(int i) { return hboxset->hitbox(i); }
	inline Vector		GetBoxCtr(int i)
	{
		mstudiobbox* box = GetHitbox(i);

		Vector mins, maxs;
		VectorTransform(box->bbmin, matrix[box->bone], mins);
		VectorTransform(box->bbmax, matrix[box->bone], maxs);

		return (mins + maxs) * 0.5f;
	}

	CBaseEntity*	GetActiveWeapon();
	int				GetTeam();
	int				GetHealth();
	inline int		GetMaxHealth() { return 100; };
	bool			IsAlive();

	inline float	GetHealthPercentage()	{ return clamp((float)GetHealth() / (float)GetMaxHealth(), 0.0f, 1.0f); }

	Vector	GetEyeAngles();
	Vector	GetOrigin();
	Vector	GetCenter();
	Vector	GetAbsCenter();
	Vector	GetViewPunch();
	Vector	GetVelocity();
	Vector	GetShootPos();
	Vector	GetServersideShootPos();

	dword	GetMDLColor();
	dword	GetESPColor();
	dword	GetHPColor();

	const char*	GetNick();
	const char* GetNickSafe();
	
	float	GetNextPrimaryFire();
	int		GetTickBase();
	int		GetShotsFired();
	int		GetFlags();
	char	GetWaterLevel();
	bool	ShouldIgnore();

	inline bool HasFlag(int flag)	{ return chk(GetFlags(), flag); }
	inline bool IsDucked()			{ return HasFlag(FL_DUCKING); }
	inline bool IsOnGround()		{ return HasFlag(FL_ONGROUND); }
	


	bool CSS_IsSemiAuto();
};

class GameEvent
{
public:
	DECLFUNCA(1, const char*,	GetName,	(),											(void*),							(this),					this);
	DECLFUNCA(8, const char*,	GetString,	(const char* key, const char* default = ""),(void*, const char*, const char*),	(this, key, default),	this);
	DECLFUNCA(5, bool,			GetBool,	(const char* key, bool default	= NULL),	(void*, const char*, bool),			(this, key, default),	this);
	DECLFUNCA(6, int,			GetInt,		(const char* key, int default	= NULL),	(void*, const char*, int),			(this, key, default),	this);
	DECLFUNCA(7, float,			GetFloat,	(const char* key, float default	= NULL),	(void*, const char*, float),		(this, key, default),	this);
};

class NetChannel
{
public:
	DECLFUNCA(9, float,	GetLatency,	(int flow = 0), (void*, int), (this, flow), (this));
	DECLFUNCA(36, void,	Shutdown,	(const char* reason), (void*, const char*), (this, reason), (this));
};

class Material
{
public:
	DECLFUNCA(29, void,			SetMaterialFlag, (int flag, bool on), (void*, int, bool), (this, flag, on), this);
};

class ConVar
{
public:
	DECLFUNCA(2, void, SetValue, (const char* v), (void*, const char*), (this + 0x18, v), (this + 0x18));

	inline void SetValue(int v)
	{
		*(int*)((unsigned long)(this) + 0x30) = v;
	}

	inline void SetValue(float v)
	{
		*(float*)((unsigned long)(this) + 0x2C) = v;
	}

	inline char* GetString()
	{
		return *(char**)((unsigned long)(this) + 0x24);
	}

	inline float GetFloat()
	{
		return *(float*)((unsigned long)(this) + 0x2C);
	}

	inline int GetInt()
	{
		return *(int*)((unsigned long)(this) + 0x30);
	}

	inline void SetFlags(int v)
	{
		*(int*)(*(unsigned long*)((unsigned long)(this) + 0x1C) + 0x14) = v;
	}

	inline int GetFlags()
	{
		return *(int*)(*(unsigned long*)((unsigned long)(this) + 0x1C) + 0x14);
	}

	inline char* GetName()
	{
		return *(char**)(*(unsigned long*)((unsigned long)(this) + 0x1C) + 0xC);
	}

	inline unsigned long* GetCallback()
	{
		return (unsigned long*)((unsigned long)this + 0x44);
	}
};

class EHANDLE
{
public:
	DECLFUNCA(2, unsigned long&, GetRef, (), (void*), (this), this);
};



#undef INTERFACE
#undef THIS
#define	INTERFACE(NAME)			class I##NAME : public EInterface
#define	FINDFUNC(I, SIG, D, M)	I = M; FindProc(&I, SIG, #I, D);
#define	THIS					_vmt
#define	DECLFUNC(I, RET, NAME, A, T, P)	inline RET NAME A\
{\
	return GetVFunc<RET (__thiscall*) T>(THIS, I) P;\
}


class EInterface
{
protected:
	pdword*	_vmt;
	int		_size;

	bool	SigCmp(const char* base, const char* sig);
	bool	FindProc(int* mem, const char* sig, const char* dbg = 0, int def = 0);

public:
	bool	Init(pdword* base);
	bool	Init(const char* dll, const char* name, int ver = 0);
	void	HookMethod(int m, void* hook, void* original);
	dword	GetMethod(int m);

	inline void Destruct()
	{

	};

	inline dword GetBase()
	{
		return (dword)_vmt;
	};
};

INTERFACE(ConVar)
{
public:
	IConVar()
	{
		if (Init("vstdlib", "VEngineCvar"))
		{

		}
	}

	DECLFUNC(12, ConVar*, FindVar, (char* name), (void*, char*), (THIS, name));
};

INTERFACE(Trace)
{
public:
	int m_TraceRay;

	ITrace()
	{
		if (Init("engine", "EngineTraceClient"))
		{
			FINDFUNC(m_TraceRay, "\x53\x8B\xDC\x83\xEC\x08\x83\xE4\xF0\x83\xC4\x04\x55\x8B\x6B\x04\x89\x6C\x24\x04\x8B\xEC\xB8", 5, 0);
		}
	}

	DECLFUNC(m_TraceRay, void, TraceRay,
		(const ray &r, int msk, void* flt, rt* tr),
		(void*, const ray&, int, void*, rt*),
		(THIS, r, msk, flt, tr));
};

INTERFACE(ModelInfo)
{
public:
	IModelInfo()
	{
		if (Init("engine", "VModelInfoClient"))
		{

		}
	}

	DECLFUNC(3,		const char*,	GetModelName,	(const void* model), (void*, const void*), (THIS, model));
	DECLFUNC(28,	void*,			GetStudiomodel,	(const void* model), (void*, const void*), (THIS, model));
	DECLFUNC(16,	void,			GetMaterial,
		(const void* model, int size, Material** table),
		(void*, const void*, int, Material**),
		(THIS, model, size, table)
	);
};

INTERFACE(GameEventManager)
{
public:
	IGameEventManager()
	{
		if (Init("engine", "GAMEEVENTSMANAGER", 2))
		{

		}
	};

	DECLFUNC(3, bool,	AddListener,	(void* listener, const char* name),	(void*, void*, const char*, bool),	(THIS, listener, name, false));
	DECLFUNC(5, void,	DelListener,	(void* listener),					(void*, void*),						(THIS, listener));
};

INTERFACE(DebugOverlay)
{
public:
	IDebugOverlay()
	{
		if (Init("engine", "VDebugOverlay"))
		{

		}
	}

	DECLFUNC(10, void, ToScreen, (const Vector& world, Vector& scr), (void*, const Vector&, Vector&), (THIS, world, scr));
};

INTERFACE(Client)
{
public:
	int m_CreateMove;
	int m_GetAllClasses;
	
	IClient()
	{
		if (Init("client", "VClient"))
		{
			FINDFUNC(m_CreateMove,		"\x55\x8B\xEC\x51\x56\x6A?\x6A\x01\x8D\x4D\xFF", 21, 16);
			FINDFUNC(m_GetAllClasses,	"\xA1????\xC3\xCC", 8, 0);
		}
	}

	DECLFUNC(m_GetAllClasses, ClientClass*, GetAllClasses, (), (void*), (THIS));
};

INTERFACE(Input)
{
public:
	int MP_BACKUP;
	int UCMD_SIZE;
	int BASE;
	bool SINGLEBASE;

	IInput(dword base)
	{
		if (Init((pdword*)*(pdword)*(pdword)base))
			ResolveInfo();
	}

	void ResolveInfo();
};

INTERFACE(Entities)
{
public:
	int m_GetClientEntity;
	int m_GetClientEntityHandle;
	int m_GetHighestEntityIndex;

	IEntities()
	{
		if (Init("client", "VClientEntityList"))
		{
			FINDFUNC(m_GetClientEntity,			"\x55\x8B\xEC\x8B\x45\x08\x85\xC0\x78", 3, 0);
			FINDFUNC(m_GetClientEntityHandle,	"\x55\x8B\xEC\x8B\x55\x08\x51\x8B\xC4\x89\x10\x8B\x01\x8B\x50\x08\xFF\xD2\x85\xC0\x74", 4, 2);
			FINDFUNC(m_GetHighestEntityIndex,	"\x8B\x41\x24\xC3\xCC", 6, 0);
		}
	}

	DECLFUNC(3, CBaseEntity*,	GetClientEntity,		(int entid),			(void*, int),			(THIS, entid))
	DECLFUNC(4, CBaseEntity*,	GetClientEntityHandle,	(unsigned long handle), (void*, unsigned long), (THIS, handle))
	DECLFUNC(6, int,			GetHighestEntityIndex,	(),						(void*),				(THIS))
};

INTERFACE(Engine)
{
public:
	IEngine()
	{
		if (Init("engine", "VEngineClient"))
		{

		}
	}
	
	DECLFUNC(5, void,	GetScreenSize,		(int &w, int &h), (void*, int&, int&), (THIS, w, h))
	DECLFUNC(8, bool,	GetPlayerInfo,		(int entindex, player_info* info), (void*, int, player_info*), (THIS, entindex, info))
	DECLFUNC(12, int,	GetLocalPlayer,		(), (void*), (THIS))
	DECLFUNC(21, int,	GetMaxClients,		(),	(void*), (THIS))
	DECLFUNC(26, bool,	IsInGame,			(), (void*), (THIS))
	DECLFUNC(72, NetChannel*, GetNetChannel,(), (void*), (THIS))
	DECLFUNC(85, bool,	IsTakingScreenshot, (), (void*), (THIS))
	DECLFUNC(19, void,	GetViewAngles,		(Vector &a), (void*, Vector&), (THIS, a));
	DECLFUNC(20, void,	SetViewAngles,		(Vector &a), (void*, Vector&), (THIS, a));
};

INTERFACE(Panel)
{
public:
	int m_PaintTraverse;
	int m_GetName;

	IPanel()
	{
		if (Init("vgui2", "VGUI_Panel"))
		{
			FINDFUNC(m_PaintTraverse,
				"\x55\x8B\xEC\x8B\x01\x8B\x55\x08\x8B\x80????"
				"\x52\xFF\xD0\x8B\x4D\x10\x8B\x10\x8B\x52\x0C"
				"\x51\x8B\x4D\x0C\x51\x8B\xC8\xFF\xD2\x5D\xC2"
				, 41, 35);

			FINDFUNC(m_GetName, "\x55\x8B\xEC\x8B\x4D?\x8B\x01\x8B\x90????\xFF\xD2\x5D\xC2\x04", 36, 35);
		}
	}
	
	DECLFUNC(m_GetName, const char*, GetName, (unsigned int p), (void*, unsigned int), (THIS, p));
};
