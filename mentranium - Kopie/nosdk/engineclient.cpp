/* * * * * * * * * * * * * * * * 
 * 	 /// MENTRANIUM \\\
 *
 *  - By Leystyku
 * * * * * * * * * * * * * * * */

#include "baseclientengine.h"

IVEngineClient::IVEngineClient( PDWORD_PTR* pdwClass )
{

	this->base = pdwClass;

}

template <typename T> T IVEngineClient::GetFunction( PDWORD_PTR* pdwClass, unsigned int uiIndex ){

	PDWORD_PTR pdwVMT = *pdwClass;

	return (T)pdwVMT[ uiIndex ];

}

PDWORD_PTR* IVEngineClient::GetBase( ){

	return this->base;

}

/* ========================================
	Name : IVEngineClient::ClientCmd_Unrestricted
	Returns : void
=========================================== */

void IVEngineClient::ClientCmd_Unrestricted( const char *szCmdString )
{

	return this->GetFunction< ClientCmd_UnrestrictedFn >( this->base, INDEX_CLIENTENGINE_CLIENTCMD_UNRESTRICTED )( this->base );

}

/* ========================================
	Name : IVEngineClient::GetLocalPlayer
	Returns : void
=========================================== */

int IVEngineClient::GetLocalPlayer()
{

	return this->GetFunction< GetLocalPlayerFn >( this->base, INDEX_CLIENTENGINE_GETLOCALPLAYER )( this->base );

}

/* ========================================
	Name : IVEngineClient::GetPlayerInfo
	Returns : void
=========================================== */

bool IVEngineClient::GetPlayerInfo( int ent_num, player_info_t *pinfo )
{

	return this->GetFunction< GetPlayerInfoFn >( this->base, INDEX_CLIENTENGINE_GETPLAYERINFO )( this->base );

}

/* ========================================
	Name : IVEngineClient::GetMaxClients
	Returns : void
=========================================== */

int IVEngineClient::GetMaxClients( )
{

	return this->GetFunction< GetMaxClientsFn >( this->base, INDEX_CLIENTENGINE_GETMAXCLIENTS )( this->base );

}

/* ========================================
	Name : IVEngineClient::IsInGame
	Returns : void
=========================================== */

bool IVEngineClient::IsInGame()
{

	return this->GetFunction< IsInGameFn >( this->base, INDEX_CLIENTENGINE_ISINGAME )( this->base );

}

/* ========================================
	Name : IVEngineClient::IsDrawingLoadingImageFn
	Returns : void
=========================================== */

bool IVEngineClient::IsDrawingLoadingImage( )
{

	return this->GetFunction< IsDrawingLoadingImageFn >( this->base, INDEX_CLIENTENGINE_ISDRAWINGLOADINGIMAGE )( this->base );

}

/* ========================================
	Name : IVEngineClient::SetViewAnglesFn
	Returns : void
=========================================== */

void IVEngineClient::SetViewAngles( QAngle &va )
{

	return this->GetFunction< SetViewAnglesFn >( this->base, INDEX_CLIENTENGINE_SETVIEWANGLES )( this->base );

}