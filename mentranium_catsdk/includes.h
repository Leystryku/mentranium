#pragma once
#define GAME_DLL
#define CLIENT_DLL
#define M_RADPI 57.295779513082f
#define PI 3.141592653589793238462643383279502884197169399375105820974944592307816406286
#define CalcRandomSeed(cn)(MD5_PseudoRandom(cn) & 255)
#define dword DWORD
#define pdword PDWORD
#define	clamp(_v, _min, _max) ((_v > _max) ? _max : ((_v < _min) ? _min : _v))
#define	add(dst, flag)((dst) |= (flag))
#define	del(dst, flag)((dst) &=~(flag))
#define	not(dst, flag)((dst) & ~(flag))
#define	chk(dst, flag)((dst) &  (flag))

#define	LocalPlayer()(ents->GetClientEntity(engine->GetLocalPlayer()))


#pragma comment (lib, "mathlib.lib")
#pragma comment (lib, "d3d9.lib")
#pragma comment (lib, "d3dx9.lib")
#pragma comment (lib, "Dwmapi.lib")

#pragma comment (linker, "/NODEFAULTLIB:LIBCMT")

#include <windows.h>
#include <string>
#include <sstream>
#include <d3d9.h>

#include <Dwmapi.h> 
#include <stdlib.h>
#include <iostream>
#include <Lmcons.h>

#include "vector.h"
#include "sdk.h"

#include "tools_detour.cpp"

using namespace std;


typedef CBaseEntity C_BaseEntity;
typedef CBaseEntity C_BasePlayer;
typedef CBaseEntity IClientEntity;


IEngine* engine = NULL;


//typedef int ( __cdecl *OriginalCRender_WorldToScreenMatrix )( );
typedef const char *( __fastcall *OriginalC_BaseEnt_Classname )( void* thisptr, int edx );
typedef void ( __stdcall *OriginalSetViewAngles )( QAngle &va );
typedef void ( __fastcall *OriginalShutdown )( void* thisptr, int edx,  const char* );


OriginalShutdown ShutdownFn;
OriginalSetViewAngles SetViewAnglesFn;


OriginalC_BaseEnt_Classname C_BaseEnt_Classname;
//OriginalCRender_WorldToScreenMatrix CRender_WorldToScreenMatrix;

DWORD m_fFlags = 0;
DWORD m_iHealth = 0;
DWORD m_iTeamNum = 0;
DWORD m_fVecViewOffset = 0;
DWORD m_angEyeAngles = 0;
DWORD m_vecPunchAngle = 0;
DWORD m_vecPunchAngleVel = 0;
DWORD m_fLocal = 0;
DWORD m_fVecOrigin = 0;
DWORD m_flNextPrimaryAttack = 0;
DWORD m_flNextSecondaryAttack = 0;
DWORD m_iClip1 = 0;
DWORD m_hActiveWeapon = 0;
DWORD m_nTickBase = 0;

int CenterX = 0;
int CenterY = 0;
int ScrW	= 0;
int ScrH	= 0;
int HighestEntityIndex = 0;
int	MaximumClients = 0;

LPDIRECT3D9EX D3D;
IDirect3DDevice9Ex* m_pDevice;

bool shouldShoot = false;
bool menu_opened = false;

Vector pAimVec = Vector(0,0,0);

QAngle aimAngles = QAngle(0,0,0);
QAngle viewAng = QAngle(0,0,0);

C_BasePlayer* pLocalEntity = NULL;
C_BaseEntity* pAimEntity = NULL;
IClientEntity* pLocalWeapon = NULL;

#define NET_MESSAGE_BITS 6


CreateInterfaceFn clientFactory		= NULL;
CreateInterfaceFn engineFactory		= NULL;
CreateInterfaceFn serverFactory		= NULL;

HMODULE ClientDLLHandle = NULL;
HMODULE EngineDLLHandle = NULL;
HMODULE ServerDLLHandle = NULL;

HANDLE Thread1, Thread2, Thread3;

DWORD dwClientDLLHandle = NULL;
DWORD dwEngineDLLHandle = NULL;
DWORD dwServerDLLHandle = NULL;

HWND game_HWND;
WNDCLASSEX wClass;
bool registered_OurWND = false;

float worldToScreen[4][4];
bool DoRenderOnce = false;

DWORD   dwThreadIdArray[90];