/* * * * * * * * * * * * * * * * 
 * 	 /// MENTRANIUM \\\
 *
 *  - By Leystyku
 * * * * * * * * * * * * * * * */

#ifndef _IENGINECLEINT

#define _IENGINECLEINT

#include "../includes.h"


// ======================= TYPEDEFS ======================= //


typedef struct player_info_s
{
	DECLARE_BYTESWAP_DATADESC();
	// scoreboard information
	char			name[32];
	// local server user ID, unique while server is running
	int				userID;
	// global unique player identifer
	char			guid[32 + 1];
	// friends identification number
	int/*uint32*/			friendsID;
	// friends name
	char			friendsName[32];
	// true, if player is a bot controlled by game.dll
	bool			fakeplayer;
	// true if player is the HLTV proxy
	bool			ishltv;
	// custom files CRC for this player
	int /*CRC32_t*/			customFiles[4];
	// this counter increases each time the server downloaded a new file
	unsigned char	filesDownloaded;
} player_info_t;

typedef void ( __thiscall* ClientCmd_UnrestrictedFn )( void*, const char *szCmdString );
typedef int	( __thiscall* GetLocalPlayerFn )( void* );
typedef bool	( __thiscall* GetPlayerInfoFn )( void*, int ent_num, player_info_t *pinfo );
typedef int	( __thiscall* GetMaxClientsFn )( void* );
typedef bool	( __thiscall* IsInGameFn )( void* );
typedef bool	( __thiscall* IsDrawingLoadingImageFn )( void* );
typedef void	( __thiscall* SetViewAnglesFn )( void*, QAngle& va );

// ======================= INDICES ======================= //

#define INDEX_CLIENTENGINE_CLIENTCMD_UNRESTRICTED 1
#define INDEX_CLIENTENGINE_GETLOCALPLAYER 1
#define INDEX_CLIENTENGINE_GETPLAYERINFO 1
#define INDEX_CLIENTENGINE_GETMAXCLIENTS 1
#define INDEX_CLIENTENGINE_ISINGAME 1
#define INDEX_CLIENTENGINE_ISDRAWINGLOADINGIMAGE 1
#define INDEX_CLIENTENGINE_SETVIEWANGLES 1

// ======================= CLASS HEADER ======================= //

class IVEngineClient {
	
protected:

	PDWORD_PTR* base;
	template <typename T> T GetFunction( PDWORD_PTR*, UINT index );

public:

	PDWORD_PTR* GetBase();

	IVEngineClient( PDWORD_PTR* );   

	void ClientCmd_Unrestricted( const char *szCmdString );
	int GetLocalPlayer();
	bool GetPlayerInfo( int ent_num, player_info_t *pinfo );
	int GetMaxClients();
	bool IsInGame();
	bool IsDrawingLoadingImage();
	void SetViewAngles( QAngle& va );

};

#endif