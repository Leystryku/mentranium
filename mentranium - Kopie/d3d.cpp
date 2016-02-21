#pragma once
#ifndef D3D_CPP
#define D3D_CPP


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

void PrintText( string pString, int x, int y, D3DCOLOR col, ID3DXFont *font)
{

	if ( !font )
		return;

	if ( !m_pDevice )
		return;

	if ( !&pString )
		return;

	LPCSTR lpcStr = pString.c_str();

	bNeedsFlush = true;

	RECT FontRect = { x, y, x, y };

	font->DrawText( NULL, lpcStr, strlen(lpcStr), &FontRect, DT_NOCLIP, col);

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

struct D3DTLVERTEX
{
        float x, y, z, rhw;
        DWORD color;
};

/*
void DrawLine( float X, float Y, float X2, float Y2, int Width, DWORD dwColor )
{
	if ( !m_pDevice )
		return;

    if( bNeedsFlush )
    {
        if ( pSprite )
			pSprite->Flush();
       
		bNeedsFlush = FALSE;
    }

	D3DTLVERTEX qV[2] = 
	{ 
		{ (float)X, (float)Y,        0.0f, 1.0f, dwColor },
		{ (float)X2, (float)Y2, 0.0f, 1.0f, dwColor },
	};
	
	m_pDevice->SetFVF( D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1 );
	m_pDevice->SetTexture( 0, NULL );
	m_pDevice->DrawPrimitiveUP( D3DPT_LINELIST, 1, qV, sizeof( D3DTLVERTEX ) );
	m_pDevice->SetFVF( D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1 );
}*/

void DrawLine(float x, float y, float x2, float y2, float width, DWORD color)
{

	if ( !pLine )
		return;

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

void FillRGB( int x, int y, int w, int h, D3DCOLOR color )
{
	if ( !m_pDevice )
		return;
	
	if ( bNeedsFlush )
	{
        if ( pSprite )
			pSprite->Flush();
       
		bNeedsFlush = FALSE;
    }

	if ( !x )x = 0;
	if ( !y )y = 0;
	if ( !w )w = 0;
	if ( !h )h = 0;

    if( w < 0 )w = 1;
    if( h < 0 )h = 1;
    if( x < 0 )x = 1;
    if( y < 0 )y = 1;

	D3DRECT rec = { x, y, x + w, y + h };
	m_pDevice->Clear( 1, &rec, D3DCLEAR_TARGET, color, 0, 0 );
}

void OutlineRGBA( int x, int y, int w, int h, int lw, D3DCOLOR color)
{

	FillRGB( x, y, w, lw, color );
	FillRGB( x, y, lw, h, color );
	FillRGB( x, y + h, w + lw, lw, color );
	FillRGB( x + w, y, lw, h, color );

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

#endif