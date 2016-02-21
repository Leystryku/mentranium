
#define GAME_DLL
#define CLIENT_DLL

#define M_RADPI 57.295779513082f
#define PI 3.141592653589793238462643383279502884197169399375105820974944592307816406286

#define SQRTFAST( x ) ( (x) * Q_rsqrt( x ) 

#define NET_MESSAGE_BITS 6

#pragma comment (lib, "mathlib.lib")
#pragma comment (lib, "d3d9.lib")
#pragma comment (lib, "d3dx9.lib")
#pragma comment (lib, "Dwmapi.lib")
#pragma comment(lib, "Psapi.lib")
#pragma comment(lib, "wininet")
#pragma comment(lib, "shell32")
#pragma comment(lib, "urlmon.lib")
#pragma comment(lib, "ws2_32.lib")

#pragma comment (linker, "/NODEFAULTLIB:LIBCMT")

#include <windows.h>
#include <wininet.h>
#include <shellapi.h>
#include <stdio.h>
#include <string>
#include <sstream>
#include <d3d9.h>
#include <d3dx9.h>
#include <Dwmapi.h> 
#include <stdlib.h>
#include <iostream>
#include <Lmcons.h>
#include <math.h>
#include <Psapi.h>
#include <windowsx.h>

#include <cbase.h>
#include <checksum_md5.h>
#include <in_buttons.h>
#include <game/server/iplayerinfo.h>
#include <inetchannel.h>
#include <inetmsghandler.h>
#include <iclient.h>

#include <input.h>
#include <igamemovement.h>
#include <netadr.h>

#include "tools_detour.h"
#include "vhook.h"

using namespace std;

VHook * setcursorpos_Hook = 0;

enum tf_cond 
{ 
    TFCond_Slowed = (1 << 0), //Toggled when a player is slowed down. 
    TFCond_Zoomed = (1 << 1), //Toggled when a player is zoomed. 
    TFCond_Disguising = (1 << 2), //Toggled when a Spy is disguising.  
    TFCond_Disguised = (1 << 3), //Toggled when a Spy is disguised. 
    TFCond_Cloaked = (1 << 4), //Toggled when a Spy is invisible. 
    TFCond_Ubercharged = (1 << 5), //Toggled when a player is ÜberCharged. 
    TFCond_TeleportedGlow = (1 << 6), //Toggled when someone leaves a teleporter and has glow beneath their feet. 
    TFCond_Taunting = (1 << 7), //Toggled when a player is taunting. 
    TFCond_UberchargeFading = (1 << 8), //Toggled when the ÜberCharge is fading. 
    TFCond_CloakFlicker = (1 << 9), //Toggled when a Spy is visible during cloak. 
    TFCond_Teleporting = (1 << 10), //Only activates for a brief second when the player is being teleported; not very useful. 
    TFCond_Kritzkrieged = (1 << 11), //Toggled when a player is being crit buffed by the KritzKrieg. 
    TFCond_TmpDamageBonus = (1 << 12), //Unknown what this is for. Name taken from the AlliedModders SDK. 
    TFCond_DeadRingered = (1 << 13), //Toggled when a player is taking reduced damage from the Deadringer. 
    TFCond_Bonked = (1 << 14), //Toggled when a player is under the effects of The Bonk! Atomic Punch. 
    TFCond_Stunned = (1 << 15), //Toggled when a player's speed is reduced from airblast or a Sandman ball. 
    TFCond_Buffed = (1 << 16), //Toggled when a player is within range of an activated Buff Banner. 
    TFCond_Charging = (1 << 17), //Toggled when a Demoman charges with the shield. 
    TFCond_DemoBuff = (1 << 18), //Toggled when a Demoman has heads from the Eyelander. 
    TFCond_CritCola = (1 << 19), //Toggled when the player is under the effect of The Crit-a-Cola. 
    TFCond_InHealRadius = (1 << 20), //Unused condition, name taken from AlliedModders SDK. 
    TFCond_Healing = (1 << 21), //Toggled when someone is being healed by a medic or a dispenser. 
    TFCond_OnFire = (1 << 22), //Toggled when a player is on fire. 
    TFCond_Overhealed = (1 << 23), //Toggled when a player has >100% health. 
    TFCond_Jarated = (1 << 24), //Toggled when a player is hit with a Sniper's Jarate. 
    TFCond_Bleeding = (1 << 25), //Toggled when a player is taking bleeding damage. 
    TFCond_DefenseBuffed = (1 << 26), //Toggled when a player is within range of an activated Battalion's Backup. 
    TFCond_Milked = (1 << 27), //Player was hit with a jar of Mad Milk. 
    TFCond_MegaHeal = (1 << 28), //Player is under the effect of Quick-Fix charge. 
    TFCond_RegenBuffed = (1 << 29), //Toggled when a player is within a Concheror's range. 
    TFCond_MarkedForDeath = (1 << 30), //Player is marked for death by a Fan O'War hit. Effects are similar to TFCond_Jarated. 

    TFCondEx_SpeedBuffAlly = (1 << 0), //Toggled when a player gets hit with the disciplinary action. 
    TFCondEx_HalloweenCritCandy = (1 << 1), //Only for Scream Fortress event maps that drop crit candy. 
    TFCondEx_CritCanteen = (1 << 2), //Player is getting a crit boost from a canteen.
    TFCondEx_CritHype = (1 << 4), //Soda Popper crits. 
    TFCondEx_CritOnFirstBlood = (1 << 5), //Arena first blood crit buff. 
    TFCondEx_CritOnWin = (1 << 6), //End of round crits. 
    TFCondEx_CritOnFlagCapture = (1 << 7), //CTF intelligence capture crits. 
    TFCondEx_CritOnKill = (1 << 8), //Unknown what this is for. 
    TFCondEx_RestrictToMelee = (1 << 9), //Unknown what this is for. 
    TFCondEx_Reprogrammed = (1 << 11), //MvM Bot has been reprogrammed.
    TFCondEx_PyroCrits = (1 << 12), //Player is getting crits from the Mmmph charge. 
    TFCondEx_PyroHeal = (1 << 13), //Player is being healed from the Mmmph charge. 
    TFCondEx_FocusBuff = (1 << 14), //Player is getting a focus buff.
    TFCondEx_DisguisedRemoved = (1 << 15), //Disguised remove from a bot.
    TFCondEx_MarkedForDeathSilent = (1 << 16), //MvM related.
    TFCondEx_DisguisedAsDispenser = (1 << 17), //Bot is disguised as dispenser.
    TFCondEx_Sapped = (1 << 18), //MvM bot is being sapped.
    TFCondEx_UberchargedHidden = (1 << 19), //MvM Related
    TFCondEx_UberchargedCanteen = (1 << 20), //Player is recieveing ubercharge from a canteen.
    TFCondEx_HalloweenBombHead = (1 << 21), //Player has a bomb on their head from Merasmus.
    TFCondEx_HalloweenThriller = (1 << 22), //Players are forced to dance from Merasmus.
};

class Prediction;

IBaseClientDLL *g_pClient				= NULL;
IVEngineClient *g_pEngine				= NULL;
IClientEntityList *g_pEntList			= NULL;
IEngineTrace *g_pEngineTrace			= NULL;
CGlobalVars *g_pGlobals					= NULL;
IPlayerInfoManager *g_pPlayerManager	= NULL;
IVModelInfoClient *g_pModelInfo			= NULL;
ICvar *g_pCVar							= NULL;
IGameMovement *g_pMovement				= NULL;
Prediction *g_pPrediction				= NULL;
CInput *g_pInput						= NULL;
IGameEventManager2 *g_pGameManager		= NULL;

//int* oldCmds;

typedef void ( __fastcall *OriginalShutdown )( void* thisptr, int edx,  const char* );

typedef void ( __fastcall *OriginalCreateMove )( void* thisptr, int edx, int sequence_number, float input_sample_frametime, bool active);
typedef void ( __stdcall *OriginalSetViewAngles )( QAngle &va );
typedef CUserCmd* ( __stdcall *OriginalGetUserCmd )( int sequence_number );

typedef void* ( __fastcall* OriginalFrameStageNotify )( void*, int edx, ClientFrameStage_t );

VMatrix worldToScreen;
OriginalShutdown ShutdownFn;
OriginalGetUserCmd GetUserCmdFn;

OriginalSetViewAngles SetViewAnglesFn;
OriginalCreateMove CreateMoveFn;
OriginalFrameStageNotify FrameStageNotifyFn;

CVMTHook *clientHook;
CVMTHook *engineHook;
CVMTHook *inputHook;
CVMTHook *channelHook;

DWORD m_fFlags = 0;
DWORD m_iHealth = 0;
DWORD m_iTeamNum = 0;
DWORD m_fVecViewOffset = 0;
DWORD m_vecPunchAngle = 0;
DWORD m_vecPunchAngleVel = 0;
DWORD m_fLocal = 0;
DWORD m_fVecOrigin = 0;
DWORD m_flNextPrimaryAttack = 0;
DWORD m_flNextSecondaryAttack = 0;
DWORD m_iClip1 = 0;
DWORD m_hActiveWeapon = 0;
DWORD m_nTickBase = 0;
DWORD m_lifeState = 0;
DWORD m_vVelocity = 0;
DWORD m_angEyeAngles = 0;
DWORD m_flSimulationTime = 0;

DWORD TF2_m_bReadyToBackstab = 0;
DWORD TF2_m_Shared = 0;
DWORD TF2_m_nPlayerCond = 0;
DWORD TF2_m_i_objHealth = 0;


DWORD CreateMove_EBP = 0;

int h_iLocalTeam = 0;
int CenterX = 0;
int CenterY = 0;
int ScrW	= 0;
int ScrH	= 0;

float flCurTime = 0;


int highSeedNum = 0;
int lastTickCount = 0;

int HighestEntityIndex = 0;
int	MaximumClients = 0;
int g_LocalPlayerNum = 0;


int g_AppID = 0;
bool bIsReady = false;
bool* bSendPacket = false;

const char *viewESP_Classname = 0;

int oldSidemove = 0;
int oldForwardmove = 0;
int oldUpmove = 0;

Vector currentSpread = Vector(0,0,0);

LPDIRECT3D9EX D3D;
IDirect3DDevice9* m_pDevice;

bool shouldShoot = false;
bool menu_opened = false;

INetChannel *g_NetChan;

Vector pAimVec = Vector(0,0,0);

QAngle aimAngles = QAngle(0,0,0);
QAngle oldView = QAngle(0,0,0);


C_BasePlayer* pLocalEntity = NULL;
C_BaseEntity* pAimEntity = NULL;
C_BaseEntity* forceTarget = NULL;
C_BaseEntity* pLocalWeapon = NULL;

CreateInterfaceFn clientFactory		= NULL;
CreateInterfaceFn engineFactory		= NULL;
CreateInterfaceFn serverFactory		= NULL;
CreateInterfaceFn vstdLibFactory	= NULL;
CreateInterfaceFn vguiLibFactory	= NULL;

HMODULE ClientDLLHandle = NULL;
HMODULE EngineDLLHandle = NULL;
HMODULE ServerDLLHandle = NULL;
HMODULE VstdLibDLLHandle= NULL;
HMODULE LuaSharedDLLHandle = NULL;
HMODULE VguiDLLHandle	= NULL;

HMODULE hInstDLLHandle = NULL;

HANDLE Thread1, Thread2, Thread3, Thread4;

DWORD dwClientDLLHandle		= NULL;
DWORD dwEngineDLLHandle		= NULL;
DWORD dwServerDLLHandle		= NULL;
DWORD dwVstdLibDLLHandle	= NULL;
DWORD dwLuaSharedDLLHandle  = NULL;
DWORD dwVguiDLLHandle		= NULL;

HWND game_HWND;
WNDCLASSEX wClass;
bool registered_OurWND = false;

DWORD dw_WorldToScreenMatrix;

DWORD   dwThreadIdArray[90];