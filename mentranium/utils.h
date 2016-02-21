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


std::string formatString( string fmt, ... )
{
	int n, size = 100;
    std::string text;
    va_list marker;
    bool b = false;
    while (!b)
    {
        text.resize(size);
        va_start(marker, fmt);
        n = vsnprintf((char*)text.data(), size, fmt.c_str(), marker);
        va_end(marker);
        if ((n > 0) && ((b = (n < size)) == true)) text.resize(n); else size*=2;
    }

	return text.c_str();
}

bool bDickCompare(const BYTE* pData, const BYTE* bMask, const char* szMask)
{
	for(;*szMask;++szMask,++pData,++bMask)
		if(*szMask=='x' && *pData!=*bMask )
			return false;
	return (*szMask) == NULL;
}

DWORD dwFindPattern(DWORD dwAddress,const char *c_bMask,char * szMask, int skip=0)
{
	BYTE *bMask = (PBYTE)c_bMask;
	DWORD dwMask = (DWORD)bMask;

	if ( !dwMask )
		return 0;

	if ( !bMask )
		return 0;

	DWORD dwFind = (DWORD)(dwAddress - dwMask);

	if ( !dwFind )
		return 0;

	DWORD lolreturn = 0;
	for(DWORD i=0; i < dwFind; i++)
	{
		if( bDickCompare( (BYTE*)( dwAddress+i ),bMask,szMask) )
		{
			if ( skip )
				skip--;
			else
				return (DWORD)(dwAddress+i);
		}
	}

	return 0;
}

DWORD GetNetOffset( PCHAR pClassName, PCHAR pVarName, RecvTable* pTable )
{
	DWORD dwPusseh = NULL;

	for( int i = 0; i < pTable->GetNumProps( ); i++ )
	{
		RecvProp* pProp = pTable->GetPropA( i );

		if( !pProp )
			continue;

		RecvTable* pChild = pProp->GetDataTable( );

		if( pChild && pChild->GetNumProps( ) )
			dwPusseh += GetNetOffset( pClassName, pVarName, pChild );

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

		DWORD FagSet = GetNetOffset( pClassName, pVarName, paseTable );

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

	int shit = 0;

	if ( ScreenTransform( v, s ) ) // gotta be false
		return false;

	shit = 1;

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

void NormalizeAngles( QAngle &angle )
{
	int tries = 0;
	for ( int axis = 0; axis < 3; ++axis )
	{
		while ( angle[axis] > 180.f )
		{
			angle[axis] -= 360.f;
		}

		while ( angle[axis] < -180.f )
		{
			angle[axis] += 360.f;
		}

		tries++;

		if ( tries > 100 )
			break;
	}
}


void NormalizeVectors( Vector &vec )
{
	int tries = 0;
	for ( int axis = 0; axis < 3; ++axis )
	{
		while ( vec[axis] > 180.f )
		{
			vec[axis] -= 0.01f;
		}

		while ( vec[axis] < -180.f )
		{
			vec[axis] += 0.01f;
		}

		tries++;

		if ( tries > 100 )
			break;

	}
}

//Netvar Stuff

Vector& GetVelocity( C_BaseEntity *pEntity )
{
	if ( !pEntity || !m_vVelocity )
		return Vector(0,0,0);

	return *(Vector*)((DWORD)pEntity + m_vVelocity);
}

Vector& GetAbsOrigin( C_BaseEntity *pEntity )
{
	if ( !pEntity || !m_fVecOrigin )
		return Vector(0,0,0);

	Vector shit = pEntity->GetAbsOrigin();
	return Vector(shit.x,shit.y,shit.z);//*(Vector*)((DWORD)pEntity + m_fVecOrigin);
}


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

QAngle& GetEyeAngles( C_BaseEntity* pEntity )
{

	if ( !pEntity || !(DWORD)pEntity || !m_angEyeAngles )
		return QAngle(0,0,0);


	return *(QAngle*)((DWORD)pEntity + m_angEyeAngles);
}

float __fastcall flGetDistance( Vector vecOriginx,Vector vecOriginy )
{
	double x = vecOriginx[0] - vecOriginy[0];
	double y = vecOriginx[1] - vecOriginy[1];
	double z = vecOriginx[2] - vecOriginy[2];
 
	return sqrtf( x*x + y*y + z*z);
}

inline float NormalizeAngle( float angle )
{
	if ( angle < 0.0 )
		angle += 360.0;
	else if ( angle >= 360.0 )
		angle -= 360.0;
	return angle;
}


int GetHealth( C_BaseEntity *pEntity )
{
	if ( !pEntity )
		return 0;

	if ( !m_iHealth )
		return 0;

	int ret = 0;

	if ( ((DWORD)pEntity + m_iHealth) )
		ret =  *(int*)((DWORD)pEntity + m_iHealth);

	if ( ret < 1 && g_AppID == 440 && TF2_m_i_objHealth && ((DWORD)pEntity + TF2_m_i_objHealth) )
		ret = *(int*)((DWORD)pEntity + TF2_m_i_objHealth);
	
	return ret;
}

int GetActiveWepIndex( C_BaseEntity *pEntity )
{
	if ( !pEntity )
		return 0;

	if ( !m_hActiveWeapon )
		return 0;

	if ( !((DWORD)pEntity + m_hActiveWeapon) )
		return 0;

	int Index = 0;

	DWORD hActiveWep = *(DWORD*)( ( DWORD )pEntity + m_hActiveWeapon );
	
	Index = hActiveWep & 0xFFF;

	return Index;
}

float AimbotRate(C_BaseEntity* pl, bool npc, int mode)
{

	if ( !bIsReady )
		return 0.f;

	float rate = 0.f;

	Vector myorg = GetAbsOrigin(pLocalEntity);
	Vector plorg = GetAbsOrigin(pl);

	if ( mode == 0 )
	{
		rate = myorg.DistTo( plorg );
	}
	
	if ( mode == 1 )
	{
		rate = GetHealth(pl);
	}

	if ( mode == 2 )
	{
		Vector path = (plorg - myorg);
		QAngle angeyes = GetEyeAngles(pLocalEntity);
		Vector vecEyes = Vector(angeyes.x, angeyes.y, angeyes.z);

		NormalizeVectors(vecEyes);

		rate = path.DistTo(vecEyes);
	}

	if ( mode == 3 )
	{
		Vector path = (myorg - plorg);
		QAngle angeyes = GetEyeAngles(pl);
		Vector vecEyes = Vector(angeyes.x, angeyes.y, angeyes.z);

		NormalizeVectors(vecEyes);

		rate = path.DistTo(vecEyes);

		if ( npc )
			rate *= 10.f;

		if ( g_AppID == 240 && !npc )
		{
			int weaponIndex = GetActiveWepIndex( pl );
			
			if ( weaponIndex )
			{
				C_BaseEntity *pWeapon = dynamic_cast<C_BaseEntity*>(g_pEntList->GetClientEntity( weaponIndex ));

				if ( pWeapon )
				{
					const char *classname = pWeapon->GetClassname();

					if ( classname )
					{
						if ( strstr(classname, "awp") || strstr(classname, "deagle") || strstr(classname, "scout") )
						{
							rate *= 0.01f;
						}
					}
				}
			}

		}

	}


	return rate;
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
	int localteamnum = h_iLocalTeam;

	if ( teamnum == localteamnum )
	{
		return true; // Friendly color
	}
	
	return false; // Enemy Color

}


typedef const char* (__thiscall* GetClassnameFn)(void*);
GetClassnameFn getclass;

const char* C_BaseEntity::GetClassname()
{
	//MessageBox( NULL, "getclassname", "k", MB_OK );
	if ( !this )
		return NULL;

	return getclass(this);
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

int GetTickBase( C_BaseEntity *pEntity )
{
	if ( !pEntity )
		return 0;

	if ( !m_nTickBase )
		return 0;

	if ( !((DWORD)pEntity + m_nTickBase) )
		return 0;

	int time = 0;
	time += *(int*)((DWORD)pEntity + m_nTickBase);

	return time;
}

float GetCurTime( )
{
	if ( !g_pGlobals || !g_pGlobals->interval_per_tick )
		return 0.0f;

	if ( pLocalEntity == NULL )
		return 0.0f;

	int tick_base = GetTickBase(pLocalEntity);

	if ( tick_base == 0 )
		return 0.0f;

	return tick_base * g_pGlobals->interval_per_tick;
}

bool IsReadyToBackstab( IClientEntity *pEntity )
{
	if ( !pEntity )
		return 0;

	if ( !TF2_m_bReadyToBackstab )
		return 0;

	if ( !((DWORD)pEntity + TF2_m_bReadyToBackstab) )
		return 0;

	return *(bool*)((DWORD)pEntity + TF2_m_bReadyToBackstab);
}

char GetLifeState( C_BaseEntity *pEntity )
{
	if ( !pEntity )
		return 0;

	if ( !m_lifeState )
		return 0;

	if ( !((DWORD)pEntity + m_lifeState) )
		return 0;

	return *(char*)((DWORD)pEntity + m_lifeState);
}

bool IsAlive( C_BaseEntity *pEntity )
{
	if ( !pEntity )
		return false;

	if ( GetLifeState( pEntity ) != 0 )
		return false;

	if ( pEntity->GetMoveType() == MOVETYPE_OBSERVER )
		return false;


	return true;
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

bool bIsBadIndex( int iPenis ) 
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

#include "d3d.cpp"
#include "menu.h"

cuntMena *menu = NULL;

void Mentranium_StringCmd( const char *stringcmd )
{

	if ( !g_pEngine->IsConnected() )
		return;
	
	INetChannel *ch = (INetChannel*)g_pEngine->GetNetChannelInfo();

	if ( !ch )
		return;

	char pckBuf[256];
	bf_write pck( pckBuf, sizeof( pckBuf ) );
	

	pck.WriteUBitLong( 4, NET_MESSAGE_BITS );

	pck.WriteString( stringcmd );
	
	ch->SendData( pck );

	return;

	typedef void (__fastcall* SendStringCmdFn)(void* thisptr, int edx, const char*);

	static DWORD sig = dwFindPattern(dwEngineDLLHandle, "\x55\x8B\xEC\x81\xEC\x00\x00\x00\x00\x83\x79\x10\x00\x74\x3C", "xxxxx????xxxxxx");
	static SendStringCmdFn SendStringCmd = (SendStringCmdFn)sig;

	return SendStringCmd( ch, NULL, stringcmd );
}

static unsigned long ReadDWord(FILE * fp) 
{
	unsigned long ret;  
	fread( &ret, 4, 1, fp );
	return ret;
}

static unsigned short ReadWord(FILE * fp) 
{
	unsigned short ret; 
	fread( &ret, 2, 1, fp );
	return ret;
}


bool ReadWaveFile(
	const char *pFilename,
	char *&pData,
	int &nDataBytes,
	int &wBitsPerSample,
	int &nChannels,
	int &nSamplesPerSec)
{
	FILE * fp = fopen(pFilename, "rb");
	if(!fp)
		return false;

	fseek( fp, 22, SEEK_SET );
	
	nChannels = ReadWord(fp);
	nSamplesPerSec = ReadDWord(fp);

	fseek(fp, 34, SEEK_SET);
	wBitsPerSample = ReadWord(fp);

	fseek(fp, 40, SEEK_SET);
	nDataBytes = ReadDWord(fp);
	ReadDWord(fp);
	pData = new char[nDataBytes];
	if(!pData)
	{
		fclose(fp);
		return false;
	}
	fread(pData, nDataBytes, 1, fp);
	fclose( fp );
	return true;
}

void Mentranium_SendVoice( void *data, int bits )
{

	if ( !g_pEngine->IsConnected() )
		return;

	INetChannel *ch = (INetChannel*)g_pEngine->GetNetChannelInfo();

	if ( !ch )
		return;

	char pckBuf[256];
	bf_write pck( pckBuf, sizeof( pckBuf ) );
	

	pck.WriteUBitLong( 10, NET_MESSAGE_BITS ); // 15 = svc_VoiceData

	pck.WriteWord( bits ); // bits
	pck.WriteBits( data, bits ); // voicedata
	ch->SendData( pck );

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

void Mentranium_Say( const char *tosay )
{
	string penis = string( "say " ) + string( tosay );

	const char *sex = penis.c_str();

	Mentranium_StringCmd( sex );

}

void Mentranium_TeamSay( const char *tosay )
{
	string penis = string( "say_team " ) + string( tosay );

	const char *sex = penis.c_str();

	Mentranium_StringCmd( sex );

}

void MakeVector( QAngle angle, QAngle& vector ) 
{ 
	float pitch; 
	float yaw; 
	float tmp;           

	pitch	= (float)(angle[0] * M_PI/180); 
	yaw		= (float)(angle[1] * M_PI/180); 
	tmp		= (float) cos(pitch);

	vector[0] = (float) (-tmp * -cos(yaw)); 
	vector[1] = (float) (sin(yaw)*tmp);
	vector[2] = (float) -sin(pitch);
}

QAngle m_angle;
void CalcAngle( Vector &src, Vector &dst, QAngle &angles )
{
	m_angle = angles;
	double delta[3] = { (src[0]-dst[0]), (src[1]-dst[1]), (src[2]-dst[2]) };
	double hyp = sqrt(delta[0]*delta[0] + delta[1]*delta[1]);

	angles[0] = (float) (atan(delta[2]/hyp) * M_RADPI);
	angles[1] = (float) (atan(delta[1]/delta[0]) * M_RADPI);
	angles[2] = 0.0f;

	if(delta[0] >= 0.0) { angles[1] += 180.0f; }
}


void* getEnterprise( CreateInterfaceFn* fn, PCHAR name )
{
	void *ret = 0;
	for( int i = 100; i > 0; --i )
	{
		PCHAR fmt = ( i < 10 ) ? "%s00%d" : "%s0%d";

		string swag = formatString( fmt, name, i );
		void *ptr = ( *fn )( swag.c_str(), 0 );
		if( ptr )
		{
			Msg(swag.c_str());
			Msg("\n");

			ret = ptr;
			break;
		}

		if ( i == 0 || i < 0 )
			break;

	}

	return ret;
}

int round_int( double r ) {
    return (r > 0.0) ? (r + 0.5) : (r - 0.5); 
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
};



bool IsGameOverlayOpen()
{
	return (GetCursorPos(NULL) == TRUE);
}

#include "Menu.cpp"