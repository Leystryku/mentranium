
#ifndef MENU
#define MENU
#pragma once

char* getChar()
{
    return "-"; //needs to be improved
}


/************************************************************************/
/* FARRRRRBEEEEEEEEENNNN                                                */
/************************************************************************/
const D3DCOLOR Red			= D3DCOLOR_ARGB (255,	255,	0,		0	);
const D3DCOLOR Yellow		= D3DCOLOR_ARGB (255,	255,	255,	0	);
const D3DCOLOR Green		= D3DCOLOR_ARGB (255,	0,		255,	0	);
const D3DCOLOR Blue			= D3DCOLOR_ARGB (255,	0,		0,		255 );
const D3DCOLOR Purple		= D3DCOLOR_ARGB (255,	102,	0,		153 );
const D3DCOLOR Orange		= D3DCOLOR_ARGB (255,	255,	165,	0	);
const D3DCOLOR Pink			= D3DCOLOR_ARGB (255,	255,	20,		147 );
const D3DCOLOR YellowGreen	= D3DCOLOR_ARGB (255,	154,	205,	50	);
const D3DCOLOR LightGrey	= D3DCOLOR_ARGB (255,	211,	211,	211	);
const D3DCOLOR LightCyan	= D3DCOLOR_ARGB (255,	122,	139,	139	);
const D3DCOLOR Snow			= D3DCOLOR_ARGB (255,	139,	137,	137	);
const D3DCOLOR TransBlue	= D3DCOLOR_ARGB (150,	0,		0,		255 );
const D3DCOLOR TransBlack	= D3DCOLOR_ARGB (150,	0,		0,		0	);
const D3DCOLOR TransBlack2	= D3DCOLOR_ARGB (80,	0,		0,		0	);
const D3DCOLOR Aqua			= D3DCOLOR_ARGB (255,	54,		231,	255	);
const D3DCOLOR White		= D3DCOLOR_ARGB (255,	255,	255,	255 );
const D3DCOLOR Black		= D3DCOLOR_ARGB (255,	0,		0,		0	);
const D3DCOLOR DGrey		= D3DCOLOR_ARGB (255,	59,		55,		57	);
const D3DCOLOR Grey			= D3DCOLOR_ARGB (255,	84,		79,		81	);
const D3DCOLOR Outline		= D3DCOLOR_ARGB (255,	140,	140,	140	);

class Slider
{
public:
	char* Name;
	char* Parent;
	int MaxValue;
	int Value;
	int* Variable;
	int x;
	int y;
	int pos;
};

class Tab
{
public:
	bool Active;
	char* Name;
	int x;
	int y;
};

class TextBox
{
public:
	char* Name;
	char* Parent;
	std::string *Variable;
	bool Focused;
	int cursor;
	int x;
	int y;
};

class Check
{
public:
	char* Name;
	char* Parent;
	bool Checked;
	int* Variable;
	int x;
	int y;
};



/************************************************************************/
/* MENÜE                                                       */
/************************************************************************/
class cuntMena
{
public:
	//KLASSEN ARRAIS.
	Check Checks[100];
	Tab Tabs[10];
	TextBox TextBoxes[100];
	Slider Sliders[100];
	

	//VARKRIABLEN.
	int M_AimEnable, M_Aim_TeamKill, M_Aim_IgnoreFriends, M_Aim_Silent, M_Aim_TeamShoot, M_TriggerBot, M_AutoPistol, M_NoSpread, M_NoRecoil, M_AutoReload, M_ESP_Box,  M_ESP_Name, M_ESP_Health, M_ESP_Weapons, M_NameChanger, M_Bhop, M_FreezeHack, M_DisconnectSpam, M_ClientSpectate, M_VoiceChatSpam, M_TextChatImitator, M_TextChatTeam, M_ChatSpam, M_Aim_KillNPC, M_ESP_NPCs, M_ESP_Players, M_ESP_ViewESP, M_Aim_KillPlayer, M_Aim_IgnoreAmmo, M_Aim_Correct;	
	int S_CrossHair;

	std::string T_CustomESP, T_ChatSpam;

	int TabCount, CheckCount, SliderCount, TextBoxCount;
	char* ActiveName;
	POINT Cur;
	bool ClickToggle;
	int sizeoftab;

	//FUNKTIONEN.
	void DrawMenu();
	void InitMenu();
	void MenuNavigation();
	void CreateCheck(char* Parent, char* Text, int* Variable);
	void CreateTab(char* Text);
	void CreateSlider(char* Parent, char* Text, int MaxValue, int* Variable);
	void CreateTextBox(char* Parent, char* Text, std::string *Variable );
	void DrawSlider(int index, int x, int y);
	void DrawTab(int index, int x, int y, int width);
	void DrawCheckBox(int index, int x, int y);
	void DrawTextBox(int index, int x, int y);
	void ThinkTextBox(int index);
	int MouseOver(int x, int y, int x2, int y2);
	void SwitchTab(int index);
};

extern cuntMena* menu;
#endif