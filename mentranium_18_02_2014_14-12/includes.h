
#define GAME_DLL
#define CLIENT_DLL
#define M_RADPI 57.295779513082f
#define PI 3.14159265 //Defining what PI is. PI is a Circle


#pragma comment (lib, "mathlib.lib")
#pragma comment (lib, "psapi.lib" )
#pragma comment (lib, "User32.lib")
#pragma comment (lib, "d3d9.lib")
#pragma comment (lib, "d3dx9.lib")

#pragma comment (linker, "/NODEFAULTLIB:LIBCMT")
#pragma warning (disable : 4099 4075 4996)

#include <windows.h>
#include <string>
#include <sstream>
#include <fstream>
#include <stdio.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <Color.h>
#include <tlhelp32.h>
#include <psapi.h>

#include <cbase.h>
#include <mathlib/Vector.h>
#include <globalvars_base.h>
#include <engine/ivdebugoverlay.h>
#include <IInput.h>
#include <Input.h>
#include <vgui/IPanel.h>
#include <vgui/ISurface.h>
#include <in_buttons.h>
#include <engine/IEngineTrace.h>
#include <C_BaseAnimating.h>
#include <icvar.h>
#include <tier1/tier1.h>
#include <tier2/tier2.h>
#include <tier3/tier3.h>
#include <vstdlib/cvar.h>
#include <inetchannel.h>
#include <inetmsghandler.h>
#include <ienginevgui.h>
#include <takedamageinfo.h>
#include <iviewrender_beams.h>
#include <igameevents.h>
#include <checksum_md5.h>
#include <shot_manipulator.h>
#include <game/server/iplayerinfo.h>

#include <boost/filesystem.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <boost/crc.hpp>

LPDIRECT3DDEVICE9 m_pDevice;
bool bNeedsFlush = false;

#include "tools_ade32.cpp"
#include "tools_detour.cpp"
#include "newbitbuf.cpp"

IGameEventManager2 *g_pGameManager		= NULL;
ICvar *g_pCVar							= NULL;
IBaseClientDLL *g_pClient				= NULL;
IVEngineClient *g_pEngine				= NULL;
IClientEntityList *g_pEntList			= NULL;
CInput *g_pInput						= NULL;
IEngineTrace *g_pEngineTrace			= NULL;
CGlobalVars *g_pGlobals					= NULL;
IPlayerInfoManager *g_pPlayerManager	= NULL;
IVModelInfoClient *g_pModelInfo			= NULL;
IVDebugOverlay *g_pDebugOverlay			= NULL;
IUniformRandomStream *random			= NULL;
CBaseEntityList*   g_pEntityList		= NULL;


static int(__stdcall*_SetCursorPos)(int X, int Y);
 
typedef void (__cdecl* OriginalWriteUserCmd)(void*, CUserCmd*, CUserCmd*);
typedef const char *( __fastcall *OriginalC_BaseEnt_Classname )( void* thisptr, int edx );
typedef void ( __cdecl *OriginalCL_QueueDownload )( const char *pszFileName );
typedef void ( __fastcall *OriginalCreateMove )( void* thisptr, int edx,  int, float, bool );
typedef bool ( __fastcall *OriginalWriteUsercmdDeltaToBuffer )( void* thisptr, int edx, void* buf, int from, int to, bool isnew);
typedef void ( __fastcall *OriginalShutdown )( void* thisptr, int edx,  const char* );
typedef int  (__fastcall  *OriginalInKeyEvent)( void* thisptr, int edx, int code, ButtonCode_t num, const char* bind );
typedef HRESULT (__fastcall* OriginalPresent)( void* thisptr, int edx, LPDIRECT3DDEVICE9 device, const RECT* rect_source, const RECT* rect_dest, HWND dest_hwnd, const RGNDATA* pDirtyRegion);

OriginalWriteUserCmd WriteUserCmd;
OriginalC_BaseEnt_Classname C_BaseEnt_Classname;
OriginalCL_QueueDownload CL_QueueDownloadFn;
OriginalCreateMove CreateMoveFn;
OriginalShutdown ShutdownFn;
OriginalInKeyEvent InKeyEventFn;
OriginalWriteUsercmdDeltaToBuffer WriteUsercmdDeltaToBufferFn;
OriginalPresent PresentFn;



int m_fFlags = 0;
int m_iHealth = 0;
int m_iTeamNum = 0;
int m_fVecViewOffset = 0;
int m_angEyeAngles = 0;
int m_fVecPunchAngle = 0;
int m_fLocal = 0;
int m_bAlive = 0;
int m_fVecOrigin = 0;
int m_iObserverMode = 0;
int m_flNextPrimaryAttack = 0;
int m_flNextSecondaryAttack = 0;
int m_iClip1 = 0;
int m_hActiveWeapon = 0;
int m_nTickBase = 0;

int CenterX = 0;
int CenterY = 0;
int ScrW	= 0;
int ScrH	= 0;
int HighestEntityIndex = 0;
int	MaximumClients = 0;

bool shouldShoot = false;
int writeCount = 0;
bool shouldReload = false;
bool menu_isopen = false;

Vector pAimVec = Vector(0,0,0);
QAngle aimAngles;
QAngle viewAng = QAngle(0,0,0);

C_BasePlayer* pLocalEntity = NULL;
C_BaseEntity* pAimEntity = NULL;
IClientEntity* pLocalWeapon = NULL;

PDWORD CL_Move = NULL;

#define NET_MESSAGE_BITS 6



CreateInterfaceFn CvarFactory		= NULL;
CreateInterfaceFn clientFactory		= NULL;
CreateInterfaceFn engineFactory		= NULL;
CreateInterfaceFn serverFactory		= NULL;

HMODULE ClientDLLHandle = NULL;
HMODULE EngineDLLHandle = NULL;
HMODULE ServerDLLHandle = NULL;
HMODULE GameOverlayDLLHandle = NULL;


DWORD dwClientDLLHandle = NULL;
DWORD dwEngineDLLHandle = NULL;
DWORD dwServerDLLHandle = NULL;
DWORD dwGameOverlayDLLHandle = NULL;

//bool LogText( const char* txt  );