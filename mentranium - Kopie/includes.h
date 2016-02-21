
#define GAME_DLL
#define CLIENT_DLL
#define M_RADPI 57.295779513082f
#define PI 3.141592653589793238462643383279502884197169399375105820974944592307816406286
#define CalcRandomSeed(cn)(MD5_PseudoRandom(cn) & 255)


#pragma comment (lib, "mathlib.lib")
#pragma comment (lib, "psapi.lib" )
#pragma comment (lib, "User32.lib")
#pragma comment (lib, "d3d9.lib")
#pragma comment (lib, "d3dx9.lib")
#pragma comment (lib, "Dwmapi.lib")

#pragma comment (linker, "/NODEFAULTLIB:LIBCMT")
#pragma warning (disable : 4099 4075 4996)

#include <windows.h>
#include <string>
#include <sstream>
#include <fstream>
#include <stdio.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <Dwmapi.h> 
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <Color.h>
#include <tlhelp32.h>
#include <psapi.h>
#include <shlwapi.h>
#include <Lmcons.h>

using namespace std;

#include <cbase.h>
#include <engine/ivdebugoverlay.h>
#include <Input.h>
#include <in_buttons.h>
#include <icvar.h>
#include <inetchannel.h>
#include <igameevents.h>
#include <checksum_md5.h>
#include <game/server/iplayerinfo.h>

bool bNeedsFlush = false;

#include "tools_detour.cpp"

IGameEventManager2 *g_pGameManager		= NULL;
IBaseClientDLL *g_pClient				= NULL;
IVEngineClient *g_pEngine				= NULL;
IClientEntityList *g_pEntList			= NULL;
IEngineTrace *g_pEngineTrace			= NULL;
CGlobalVars *g_pGlobals					= NULL;
IPlayerInfoManager *g_pPlayerManager	= NULL;
IVModelInfoClient *g_pModelInfo			= NULL;
IVDebugOverlay *g_pDebugOverlay		= NULL;
CInput *g_pInput						= NULL;


void __fastcall newShutdown( void* thisptr, int edx, const char *dc_string );


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

VMatrix worldToScreen;
bool DoRenderOnce = false;

DWORD   dwThreadIdArray[90];