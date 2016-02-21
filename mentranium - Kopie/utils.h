#include "includes.h"

LPD3DXFONT g_pFont;
LPD3DXFONT g_pFont2;
LPD3DXFONT g_pFont3;
LPD3DXSPRITE pSprite;
ID3DXLine *pLine;

class bacaFont
{
public:



	void FontManager (LPDIRECT3DDEVICE9 pDevice)
	{
		if (g_pFont && g_pFont2 && g_pFont3 && pLine && pSprite )
		{
			return;
		}

		D3DXCreateSprite( pDevice, &pSprite );
		D3DXCreateLine(  pDevice, &pLine );

		D3DXCreateFontA( pDevice, 12, 5, FW_THIN, 20, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY, DEFAULT_PITCH|FF_DONTCARE, "Tahoma",&g_pFont);
		D3DXCreateFontA( pDevice, 30, 15, FW_BOLD, 20, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY, DEFAULT_PITCH|FF_DONTCARE, "Arial",&g_pFont2);
		D3DXCreateFontA( pDevice, 12, 5, FW_THIN, 20, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY, DEFAULT_PITCH|FF_DONTCARE, "Tahoma",&g_pFont3);

	}

}zFont;

#include "d3d.cpp"
#include "Menu.h"

std::string formatString( PCHAR fmt, ... )
{
	char buf[1024];
	memset( buf, 0, 1024 );

	va_list va_alist;
	va_start( va_alist, fmt );
	_vsnprintf( buf + strlen( buf ), sizeof( buf ) - strlen( buf ), fmt, va_alist );
	va_end( va_alist );

	return buf;
}

bool bDickCompare(const BYTE* pData, const BYTE* bMask, const char* szMask)
{
	for(;*szMask;++szMask,++pData,++bMask)
		if(*szMask=='x' && *pData!=*bMask )
			return false;
	return (*szMask) == NULL;
}

DWORD dwFindPattern(DWORD dwAddress,const char *c_bMask,char * szMask)
{
	BYTE *bMask = (PBYTE)c_bMask;

	DWORD lolreturn = 0;
	for(DWORD i=0; i < (DWORD)(dwAddress - (DWORD)bMask); i++)
	{
		if( bDickCompare( (BYTE*)( dwAddress+i ),bMask,szMask) )
		{
			lolreturn = (DWORD)(dwAddress+i);
			break;
		}
	}

	return lolreturn;
}

DWORD GetFAGATOffset( PCHAR pClassName, PCHAR pVarName, RecvTable* pTable )
{
	DWORD dwPusseh = NULL;

	for( int i = 0; i < pTable->GetNumProps( ); i++ )
	{
		RecvProp* pProp = pTable->GetPropA( i );

		if( !pProp )
			continue;

		RecvTable* pChild = pProp->GetDataTable( );

		if( pChild && pChild->GetNumProps( ) )
			dwPusseh += GetFAGATOffset( pClassName, pVarName, pChild );

		if( !strcmp( pTable->GetName( ), pClassName ) && !strcmp( pProp->GetName( ), pVarName ) )
		{
			dwPusseh += pProp->GetOffset( );
			break;
		}
	}

	return dwPusseh;
}

DWORD GetNetvarOffset( PCHAR pClassName, PCHAR pVarName )
{
	ClientClass* peepeeClass = g_pClient->GetAllClasses( );

	if( !peepeeClass )
		return NULL;

	for( ; peepeeClass; peepeeClass = peepeeClass->m_pNext )
	{
		RecvTable* paseTable = peepeeClass->m_pRecvTable;

		if( !paseTable )
			continue;

		if( !paseTable->GetNumProps( ) )
			continue;

		if( !strstr( paseTable->GetName( ), "DT_" ) )
			continue;

		DWORD FagSet = GetFAGATOffset( pClassName, pVarName, paseTable );

		if( FagSet )
			return FagSet;
	}

	return NULL;
}

bool ScreenTransform( Vector& point, Vector& screen )
{

	if ( !g_pEngine )
		return true;

	if ( !dwEngineDLLHandle )
		return true;

	DWORD dwWorldToSreenAddr = dwEngineDLLHandle+0x5D1DC0;

	if ( !dwWorldToSreenAddr || !(dwWorldToSreenAddr) )
	{
		dwWorldToSreenAddr = dwEngineDLLHandle+0x5CBAD4;

		if ( !dwWorldToSreenAddr || !(dwWorldToSreenAddr) )
		{

			dwWorldToSreenAddr = dwEngineDLLHandle+0x5D15D8;

			if ( !dwWorldToSreenAddr || !(dwWorldToSreenAddr) )
				return true;
		}

	}

	if ( !&point )
	{
		point[0] = 0;
		point[1] = 0;
		point[2] = 0;
	}

	if ( !point[0] )
		point[0] = 0;

	if ( !point[1] )
		point[1] = 0;

	if ( !point[2] )
		point[2] = 0;

	/*
	if ( !&worldToScreen || ResetMatrix )
	{
		worldToScreen = *(VMatrix*)(dwWorldToSreenAddr); //g_pEngine->WorldToScreenMatrix();
		ResetMatrix = false;
		return true;
	}*/

	const VMatrix &worldToScreen = *(VMatrix*)(dwWorldToSreenAddr); //g_pEngine->WorldToScreenMatrix();

	if ( !&worldToScreen )
		return true;

	float w;

	screen.x = worldToScreen[0][0] * point[0] + worldToScreen[0][1] * point[1] + worldToScreen[0][2] * point[2] + worldToScreen[0][3];
	screen.y = worldToScreen[1][0] * point[0] + worldToScreen[1][1] * point[1] + worldToScreen[1][2] * point[2] + worldToScreen[1][3];
	w		 = worldToScreen[3][0] * point[0] + worldToScreen[3][1] * point[1] + worldToScreen[3][2] * point[2] + worldToScreen[3][3];

	// Just so we have something valid here
	screen.z = 0.0f;

	bool behind;
	if( w < 0.001f )
	{
		behind = true;
		screen.x *= 100000;
		screen.y *= 100000;
	}
	else
	{
		behind = false;
		float invw = 1.0f / w;
		screen.x *= invw;
		screen.y *= invw;
	}

	return behind;
}

int W = 0;
int H = 0;
bool WorldToScreen( Vector v, Vector &s )
{
	if ( !g_pClient )
		return false;

	if( ScreenTransform( v, s ) != false )
		return false;

	if ( W == 0 || H == 0 )
	{
		W = ScrW;
		H = ScrH;
	}

	float x = W / 2;
	float y = H / 2;

	x += 0.5 * s.x * W + 0.5;
	y -= 0.5 * s.y * H + 0.5;

	s.x = x;
	s.y = y;

	return true;
}

//Netvar Stuff

Vector& GetOrigin( C_BaseEntity *pEntity )
{
	if ( !pEntity || !m_fVecOrigin )
		return Vector(0,0,0);

	return *(Vector*)((DWORD)pEntity + m_fVecOrigin);
}


Vector& GetViewOffset( C_BaseEntity* pEntity )
{
	if ( !pEntity || !m_fVecViewOffset )
		return Vector(0,0,0);

	return *(Vector*)((DWORD)pEntity + m_fVecViewOffset);
}

Vector& GetEyePosition( C_BaseEntity* pEntity )
{

	if ( !pEntity || !(DWORD)pEntity || !m_fVecOrigin || !m_fVecViewOffset )
		return Vector(0,0,0);

	Vector m_vecOrigin = Vector(0,0,0);
	m_vecOrigin += *(Vector*)((DWORD)pEntity + m_fVecOrigin);

	Vector m_vecViewOffset = Vector(0,0,0);
	m_vecOrigin += *(Vector*)((DWORD)pEntity + m_fVecViewOffset);

	if ( !&(m_vecOrigin + m_vecViewOffset) )
		return Vector(0,0,0);

	return m_vecOrigin + m_vecViewOffset;
}

int GetTeam( C_BaseEntity *pEntity )
{
	if ( !pEntity )
		return 0;

	if ( !m_iTeamNum )
		return 0;

	return *(int*)((DWORD)pEntity + m_iTeamNum);
}

bool isFriendlyTeam( C_BaseEntity *pEntity )
{

	int teamnum = GetTeam(pEntity);
	int localteamnum = GetTeam(pLocalEntity);

	if ( teamnum == localteamnum )
	{
		return true; // Friendly color
	}
	
	return false; // Enemy Color

}

int GetFlags( C_BaseEntity *pEntity )
{
	if ( !pEntity )
		return 0;

	if ( !m_fFlags )
		return 0;

	if ( !((DWORD)pEntity + m_fFlags) )
		return 0;

	return *(int*)((DWORD)pEntity + m_fFlags);
}


int GetHealth( C_BaseEntity *pEntity )
{
	if ( !pEntity )
		return 0;

	if ( !m_iHealth )
		return 0;

	if ( !((DWORD)pEntity + m_iHealth) )
		return 0;

	return *(int*)((DWORD)pEntity + m_iHealth);
}

D3DCOLOR GetTeamCol( C_BaseEntity *pEntity )
{

	if ( !pLocalEntity )
		return D3DCOLOR_RGBA(255, 255, 255, 255 );

	if ( !pEntity )
		return D3DCOLOR_RGBA(255, 255, 255, 255 );

	if ( !m_iTeamNum )
		return D3DCOLOR_RGBA(255, 255, 255, 255 );

	if ( isFriendlyTeam(pEntity) )
	{
		return D3DCOLOR_RGBA( 16, 255, 16, 255 ); // Friendly color
	}else{
		return D3DCOLOR_RGBA( 255, 16, 16, 255 ); // Enemy Color
	}

	return D3DCOLOR_RGBA(255, 255, 255, 255 );
}

bool bIsFagBadIndax( int iPenis ) 
{
    player_info_s Info; 

    if( iPenis == g_pEngine->GetLocalPlayer( ) ) 
        return true; 

    if( g_pEngine->GetPlayerInfo( iPenis, &Info ) == false ) 
        return true; 

    if ( Info.fakeplayer || Info.friendsID == 0 ) 
        return true;

    return false; 
} 


void Mentranium_Name( const char *name )
{

	if ( !g_pEngine->IsConnected() )
		return;

	INetChannel *ch = (INetChannel*)g_pEngine->GetNetChannelInfo();

	if ( !ch )
		return;

	char pckBuf[256];
	bf_write pck( pckBuf, sizeof( pckBuf ) );
	

	pck.WriteUBitLong( 5, NET_MESSAGE_BITS );
	pck.WriteByte( 0x01 );
	pck.WriteString( "name" );
	pck.WriteString( name );
	
	ch->SendData( pck );

}

void* getEnterprise( CreateInterfaceFn* fn, PCHAR name )
{

	for( int i = 100; i > 1; --i )
	{
		PCHAR fmt = ( i < 10 ) ? "%s00%d" : "%s0%d";

		string swag = formatString( fmt, name, i );
		void *ptr = ( *fn )( swag.c_str(), 0 );
		if( ptr )
		{
			Msg(swag.c_str());
			Msg("\n");

			return ptr;
		}

		if ( i == 0 || i < 0 )
			break;

	}

	return 0;
}

inline void**& getvtable( void* inst, size_t offset = 0 )
{
    return *reinterpret_cast<void***>( (size_t)inst + offset );
}
inline const void** getvtable( const void* inst, size_t offset = 0 )
{
    return *reinterpret_cast<const void***>( (size_t)inst + offset );
}

template< typename Fn >
inline Fn getvfunc( const void* inst, long index, long offset = 0 )
{
	return (*reinterpret_cast<Fn**>( (uintptr_t)inst + offset ))[ index ];
}

/*
bool prediction__PerformPrediction( bool received_new_world_update, C_BasePlayer *localPlayer, int incoming_acknowledged, int outgoing_command )
{
	typedef bool ( __thiscall* OriginalFn )( CPrediction*, bool, C_BasePlayer *, int, int );
	
	return getvfunc<OriginalFn>( g_pPredictionSystem, 21 )( g_pPredictionSystem, received_new_world_update, localPlayer, incoming_acknowledged, outgoing_command );
}
*/

bool IsGameOverlayOpen()
{
	return (GetCursorPos(NULL) == TRUE);
}

#include "Menu.cpp"