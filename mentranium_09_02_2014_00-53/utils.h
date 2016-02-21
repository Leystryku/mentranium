#include "includes.h"

ID3DXLine *pLine;
LPD3DXSPRITE pSprite;

class cFont
{
public:

	LPD3DXFONT g_pFont;

	void FontManager (LPDIRECT3DDEVICE9 pDevice)
	{
		if (g_pFont && pLine &&pSprite )
		{
			return;
		}

		D3DXCreateSprite( pDevice, &pSprite );

		D3DXCreateLine(  pDevice, &pLine );

		D3DXCreateFontA( pDevice, 12, 5, FW_THIN, 1, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY, DEFAULT_PITCH|FF_DONTCARE, "Tahoma",&g_pFont);
	}

}Font;

struct DXUT_SCREEN_VERTEX 
{ 
	float x, y, z, h;
	D3DCOLOR color;
	float tu, tv;
	static DWORD FVF; 
};

class CVertexList
{
public:
    FLOAT X, Y, Z;
    DWORD dColor;
};

void PrintText(char pString[], int x, int y, D3DCOLOR col, ID3DXFont *font)
{
	bNeedsFlush = true;

	RECT rct;    
	rct.left     = x - 1;    
	rct.right    = x + 1;    
	rct.top      = y - 1 ;    
	rct.bottom   = y + 1;  

    RECT FontRect = { x, y, x, y };
    font->DrawTextA( NULL, pString, -1, &rct, DT_NOCLIP, col);
}

void DrawFilledRectangle( float X, float Y, float Width, float Height, DWORD dwColor )
{
	if( !m_pDevice )
		return;

    if( bNeedsFlush )
    {
        pSprite->Flush();
        bNeedsFlush = FALSE;
    }

    CVertexList VertexList[4] = 
    {
        { X, Y + Height, 0.0f, dwColor },
        { X, Y, 0.0f, dwColor },
        { X + Width, Y + Height, 0.0f, dwColor },
        { X + Width, Y, 0.0f, dwColor },
    };

    m_pDevice->SetTexture( 0, NULL );
    m_pDevice->DrawPrimitiveUP( D3DPT_TRIANGLESTRIP, 2, VertexList, sizeof( CVertexList ) );
}

void GradientRect( float X, float Y, float Width, float Height, DWORD startCol, DWORD endCol )
{
	if( !m_pDevice )
		return;

    if( bNeedsFlush )
    {
        pSprite->Flush();
        bNeedsFlush = FALSE;
    }

    CVertexList VertexList[4] = 
    {
        { X, Y + Height, 0.0f, endCol },
        { X, Y, 0.0f, startCol },
        { X + Width, Y + Height, 0.0f, endCol },
        { X + Width, Y, 0.0f, startCol },
    };
 
    m_pDevice->SetTexture( 0, NULL );
    m_pDevice->DrawPrimitiveUP( D3DPT_TRIANGLESTRIP, 2, VertexList, sizeof( CVertexList ) );
}

//fix DrawBorder
void DrawBorder( float x, float y, float w, float h, DWORD color1, DWORD color2 )
{
	if( !m_pDevice )
		return;

    if( bNeedsFlush )
    {
        pSprite->Flush();
        bNeedsFlush = FALSE;
    }

	DXUT_SCREEN_VERTEX vertices[6] =
	{
		x + w, y, 0.0f, 1.0f, color2, 0,0,
		x + w, y + h, 0.0f, 1.0f, color2, 0,0,
		x, y + h, 0.0f, 1.0f, color2, 0,0,

		x, y + h, 0.0f, 1.0f, color1, 0,0,
		x, y, 0.0f, 1.0f, color1, 0,0,
		x + w, y, 0.0f, 1.0f, color1, 0,0,
	};

	m_pDevice->SetFVF( D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1 );
    m_pDevice->SetTexture( 0, NULL );
	m_pDevice->DrawPrimitiveUP( D3DPT_LINESTRIP, 5, vertices, sizeof(DXUT_SCREEN_VERTEX) );
	m_pDevice->SetFVF( D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1 );
}

//fix DrawNonFilledRectangle you retard
void DrawNonFilledRectangle( float x, float y, float w, float h, DWORD dwColor )
{
	if( !m_pDevice )
		return;

    if( bNeedsFlush )
    {
        pSprite->Flush();
        bNeedsFlush = FALSE;
    }

	DXUT_SCREEN_VERTEX vertices[6] =
	{
		x + w, y,	  0.0f, 1.0f, dwColor, 0.0f, 0.0f,
		x + w, y + h, 0.0f, 1.0f, dwColor, 0.0f, 0.0f,
		x, y + h, 0.0f, 1.0f, dwColor, 0.0f, 0.0f,

		x, y + h, 0.0f, 1.0f, dwColor, 0.0f, 0.0f,
		x, y,	  0.0f, 1.0f, dwColor, 0.0f, 0.0f,
		x + w, y, 0.0f, 1.0f, dwColor, 0.0f, 0.0f,
	};

	m_pDevice->SetFVF( D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1 );
	m_pDevice->SetTexture( 0, NULL );
	m_pDevice->DrawPrimitiveUP( D3DPT_LINESTRIP, 5, vertices, sizeof(DXUT_SCREEN_VERTEX) );
	m_pDevice->SetFVF( D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1 );
}

void DrawBorderWithFill( float x, float y, float w, float h, DWORD color1, DWORD color2, DWORD Fill )
{
	if( !m_pDevice )
		return;

	DXUT_SCREEN_VERTEX vertices[6] =
	{
		x + w, y, 0.0f, 1.0f, color2, 0,0,
		x + w, y + h, 0.0f, 1.0f, color2, 0,0,
		x, y + h, 0.0f, 1.0f, color2, 0,0,

		x, y + h, 0.0f, 1.0f, color1, 0,0,
		x, y, 0.0f, 1.0f, color1, 0,0,
		x + w, y, 0.0f, 1.0f, color1, 0,0,
	};

	m_pDevice->SetFVF( D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1 );
    m_pDevice->SetTexture( 0, NULL );
	m_pDevice->DrawPrimitiveUP( D3DPT_LINESTRIP, 5, vertices, sizeof(DXUT_SCREEN_VERTEX) );
	DrawFilledRectangle( x + 1, y + 1, w - 1, h - 1, Fill );
	m_pDevice->SetFVF( D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1 );

}

void FillRGB( int x, int y, int w, int h, D3DCOLOR color )
{
    if( w < 0 )w = 1;
    if( h < 0 )h = 1;
    if( x < 0 )x = 1;
    if( y < 0 )y = 1;

    D3DRECT rec = { x, y, x + w, y + h };
    m_pDevice->Clear( 1, &rec, D3DCLEAR_TARGET, color, 0, 0 );

}

void OutlineRGBA( int x, int y, int w, int h, int lw, D3DCOLOR color, IDirect3DDevice9* pDevice )
{

	FillRGB( x, y, w, lw, color );
	FillRGB( x, y, lw, h, color );
	FillRGB( x, y + h, w + lw, lw, color );
	FillRGB( x + w, y, lw, h, color );

}

void DrawHealthBox( int x, int y, int r, int g, int b, int a, int CurHealth, int MaxHealth )
{
	if( CurHealth == 0 || MaxHealth == 0 )
		return;

	float mx = MaxHealth / 4;
	float wx = CurHealth / 4;

	if( mx == 0 ) return;

	x -= ( mx / 2 );

	FillRGB( x - 1, y - 1, mx + 2, 4 + 2, D3DCOLOR_ARGB(a, 0,0, 0) );
	FillRGB( x, y, wx, 4, D3DCOLOR_ARGB(a, r, g, b) );
}

void CenterText( int x, int y, int r, int g, int b, int a, const char *text, ... )
{
	if( text == NULL ) return;

	va_list va_alist;

	char TotalBufferMaxLength[ 1024 ] = { 0 };

	memset( TotalBufferMaxLength, 0, sizeof( char ) * 1024 );

	va_start( va_alist, text );
	
	_vsnprintf( TotalBufferMaxLength + strlen( TotalBufferMaxLength ), 
		sizeof( TotalBufferMaxLength ) - strlen( TotalBufferMaxLength ), 
		text, va_alist );

	va_end( va_alist );

	int CharLength = strlen( TotalBufferMaxLength ) * 5;

	int xx = x - ( CharLength / 2 );
	PrintText( TotalBufferMaxLength, xx, y, D3DCOLOR_ARGB(a,r,g,b), Font.g_pFont );
}

void DrawCircle(int X, int Y, int radius, int numSides, DWORD Color) 
{ 

    D3DXVECTOR2 Line[128]; 
    float Step = PI * 2.0 / numSides; 
    int Count = 0; 
    for (float a=0; a < PI*2.0; a += Step) 
    { 
        float X1 = radius * cos(a) + X; 
        float Y1 = radius * sin(a) + Y; 
        float X2 = radius * cos(a+Step) + X; 
        float Y2 = radius * sin(a+Step) + Y; 
        Line[Count].x = X1; 
        Line[Count].y = Y1; 
        Line[Count+1].x = X2; 
        Line[Count+1].y = Y2; 
        Count += 2; 
    } 
    pLine->Begin(); 
    pLine->Draw(Line,Count,Color); 
    pLine->End(); 
}

void DrawPoint(int x, int y, int w, int h, DWORD color )
{
    FillRGB((int)x, (int)y, (int)w, (int)h, color );

}

void DrawLine(float x, float y, float x2, float y2, float width, DWORD color)
{
    D3DXVECTOR2 vLine[2];
    pLine->SetWidth( width );
    pLine->SetAntialias( false );
    pLine->SetGLLines( true );
    vLine[0].x = x;
    vLine[0].y = y;
    vLine[1].x = x2;
    vLine[1].y = y2;
    pLine->Begin();
    pLine->Draw( vLine, 2, color );
    pLine->End();
}

void DrawBorder( int x, int y, int w, int h, int px, D3DCOLOR BorderColor )
{
    FillRGB( x, (y + h - px), w, px,    BorderColor );
    FillRGB( x, y, px, h,                BorderColor );
    FillRGB( x, y, w, px,                BorderColor );
    FillRGB( (x + w - px), y, px, h,    BorderColor );
}

void DrawBox( int x, int y, int w, int h, D3DCOLOR BoxColor, D3DCOLOR BorderColor )
{
    FillRGB( x, y, w, h,        BoxColor );
    DrawBorder( x, y, w, h, 1,    BorderColor );
}

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

bool bDataCompare(const BYTE* pData, const BYTE* bMask, const char* szMask)
{
	for(;*szMask;++szMask,++pData,++bMask)
		if(*szMask=='x' && *pData!=*bMask )
			return false;
	return (*szMask) == NULL;
}

DWORD dwFindPattern(DWORD dwAddress,BYTE *bMask,char * szMask)
{
	DWORD dwLen = dwAddress - (DWORD)bMask;

	for(DWORD i=0; i < dwLen; i++)
	{
		if( bDataCompare( (BYTE*)( dwAddress+i ),bMask,szMask) )
			return (DWORD)(dwAddress+i);
	}
	return 0;
}

bool ScreenTransform( const Vector& point, Vector& screen )
{
	float w;

	DWORD dwWorldToSreenAddr = dwEngineDLLHandle+0x5D1DC0;

	if ( !dwWorldToSreenAddr || !(dwWorldToSreenAddr) )
		return false;

	const VMatrix &worldToScreen = *(VMatrix*)(dwWorldToSreenAddr); //g_pEngine->WorldToScreenMatrix();

	if ( !&worldToScreen )
		return false;

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

bool TransformVector( Vector v, Vector &s )
{
	if( ScreenTransform( v, s ) != false )
		return false;

	if ( ScrW == 0 || ScrH == 0 )
		return false;

	float x = ScrW / 2;
	float y = ScrH / 2;

	x += 0.5 * s.x * ScrW + 0.5;
	y -= 0.5 * s.y * ScrH + 0.5;

	s.x = x;
	s.y = y;

	return true;
}

Vector GetOrigin( C_BaseEntity *pEntity )
{
	bool fuckyou = (DWORD)pEntity + m_fVecOrigin;

	return *(Vector*)((DWORD)pEntity + m_fVecOrigin);
}


Vector GetViewOffset( C_BaseEntity* pEntity )
{
	return *(Vector*)((DWORD)pEntity + m_fVecViewOffset);
}

Vector GetEyePosition( C_BaseEntity* pEntity )
{
	Vector vecViewOffset = GetOrigin(pEntity) + GetViewOffset(pEntity);

	return vecViewOffset;
}

void DrawBoundingBoxes( C_BaseEntity *pEnt, int r, int g, int b, int a )
{
	if ( !m_pDevice )
		return;

	Vector mon, nom;

	if ( !m_fFlags )
		return;

	int flags = *reinterpret_cast< int* >( reinterpret_cast< int >( pEnt ) + m_fFlags );

	if ( !flags )
		return;

	nom = GetOrigin(pEnt) + Vector( 0, 0, 50 );

	if ( !&nom )
		return;

	if (!( flags & FL_DUCKING ))
	{
		mon = nom + Vector( 0, 0, 20 );
	}

	Vector bot, top;

	if( TransformVector( nom, bot ) && TransformVector( mon, top ) )
	{
		if ( !&bot || !&bot || !&top )
			return;

		float h = ( bot.y - top.y );

		float w = h / 4.f;

		OutlineRGBA( top.x - w, top.y, w * 2, ( bot.y - top.y ), 1, D3DCOLOR_ARGB(a,r,g,b), m_pDevice );
	}

}

bool IsVecVisible( Vector s, Vector e )
{
	Ray_t	ray;
	trace_t tr;

	ray.Init( s, e );

	if ( !&ray )
		return false;

	g_pEngineTrace->TraceRay( ray, 0x4600400B, NULL, &tr );

	if ( !&ray )
		return false;

	if ( !&tr )
		return false;

	return ( tr.fraction == 1.0f );
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

void CalcAngela( Vector &src, Vector &dst, QAngle &angles )
{
	double delta[3] = { (src[0]-dst[0]), (src[1]-dst[1]), (src[2]-dst[2]) };
	double hyp = sqrt(delta[0]*delta[0] + delta[1]*delta[1]);

	angles[0] = (float) (atan(delta[2]/hyp) * M_RADPI);
	angles[1] = (float) (atan(delta[1]/delta[0]) * M_RADPI);
	angles[2] = 0.0f;

	if(delta[0] >= 0.0) { angles[1] += 180.0f; }
}

float GetFov( QAngle angle, Vector src, Vector dst ) 
{ 
	QAngle ang,aim; 
	float fov; 

	CalcAngela(src, dst, ang); 
	MakeVector(angle, aim); 
	MakeVector(ang, ang);      

	float mag_s = sqrt((aim[0]*aim[0]) + (aim[1]*aim[1]) + (aim[2]*aim[2])); 
	float mag_d = sqrt((aim[0]*aim[0]) + (aim[1]*aim[1]) + (aim[2]*aim[2])); 

	float u_dot_v = aim[0]*ang[0] + aim[1]*ang[1] + aim[2]*ang[2]; 

	fov = acos(u_dot_v / (mag_s*mag_d)) * (180.0 / M_PI); 

	return fov; 
}

Color GetTeamColor( CBaseEntity *pEntity )
{
	Color ReturnColor( 255, 255, 255, 255 );

	if ( !pLocalEntity )
		return ReturnColor;

	if ( !m_iTeamNum )
		return ReturnColor;

	int teamnum = *(int*)((DWORD)pEntity + m_iTeamNum);

	int localteamnum = *(int*)((DWORD)pLocalEntity + m_iTeamNum);
	

	if ( localteamnum == 0 && teamnum == 0 )
		return ReturnColor;

	if ( teamnum == localteamnum )
	{
		ReturnColor = Color( 16, 255, 16, 255 );
	}else{
		ReturnColor = Color( 255, 16, 16, 255 );
	}

	return ReturnColor;
}


#include "Menu.cpp"

bool bIsBadIndex( int iIndex ) 
{
    player_info_s Info; 

    if( iIndex == g_pEngine->GetLocalPlayer( ) ) 
        return true; 

    if( g_pEngine->GetPlayerInfo( iIndex, &Info ) == false ) 
        return true; 

    if ( ( Info.fakeplayer ) || ( Info.friendsID == 0 ) ) 
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

void* getInterface( CreateInterfaceFn* fn, PCHAR name )
{

	void* ptr = 0;

	for( int i = 100; i > 0; --i )
	{
		PCHAR fmt = ( i < 10 ) ? "%s00%d" : "%s0%d";

		ptr = ( *fn )( formatString( fmt, name, i ).c_str(), 0 );
		if( ptr )
		{
			//MessageBox( NULL, formatString( fmt, name, i ).c_str(), "Got interface", MB_OK );
			break;
		}
	}

	return ptr;
}
