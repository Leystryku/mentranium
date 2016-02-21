

#ifndef MENU
#define MENU
#pragma once

bool press(int key)
{    
    if(GetAsyncKeyState(key)&1){
        return true;
    } else {
        return false;
    }
}


char* getChar()
{

        if(press(0x30)){
            return "0";
        }
        if(press(0x31)){
            return "1";
        }
        if(press(0x32)){
            return "2";
        }
        if(press(0x33)){
            return "3";
        }
        if(press(0x34)){
            return "4";
        }
        if(press(0x35)){
            return "5";
        }
        if(press(0x36)){
            return "6";
        }
        if(press(0x37)){
            return "7";
        }
        if(press(0x38)){
            return "8";
        }
        if(press(0x39)){
            return "9";
        }
        if(press(0x40)){
            return "0";
        }
        if(press(0x41)){
            return "a";
        }
        if(press(0x42)){
            return "b";
        }
        if(press(0x43)){
            return "c";
        }
        if(press(0x44)){
            return "d";
        }
        if(press(0x45)){
            return "e";
        }
        if(press(0x46)){
            return "f";
        }
        if(press(0x47)){
            return "g";
        }
        if(press(0x48)){
            return "h";
        }
        if(press(0x49)){
            return "i";
        }
        if(press(0x4A)){
            return "j";
        }
        if(press(0x4B)){
            return "k";
        }
        if(press(0x4C)){
            return "l";
        }
        if(press(0x4D)){
            return "m";
        }
        if(press(0x4E)){
            return "n";
        }
        if(press(0x4F)){
            return "o";
        }
        if(press(0x50)){
            return "p";
        }
        if(press(0x51)){
            return "q";
        }
        if(press(0x52)){
            return "r";
        }
        if(press(0x53)){
            return "s";
        }
        if(press(0x54)){
            return "t";
        }
        if(press(0x55)){
            return "u";
        }
        if(press(0x56)){
            return "v";
        }
        if(press(0x57)){
            return "w";
        }
        if(press(0x58)){
            return "x";
        }
        if(press(0x59)){
            return "y";
        }
        if(press(0x5A)){
            return "z";
        }

	if(press(VK_BACK))
		return ".";

	if(press(VK_OEM_MINUS))
		return "_";

    if(press(VK_SPACE)){
        return " ";
    }
    return "-";
}


/************************************************************************/
/* COLOUR LIST                                                          */
/************************************************************************/
const D3DCOLOR Red			= D3DCOLOR_ARGB (255,	255,	0,		0	);
const D3DCOLOR Yellow		= D3DCOLOR_ARGB (255,	255,	255,	0	);
const D3DCOLOR Green		= D3DCOLOR_ARGB (255,	0,		255,	0	);
const D3DCOLOR Blue			= D3DCOLOR_ARGB (255,	0,		0,		255 );
const D3DCOLOR Purple		= D3DCOLOR_ARGB (255,	102,	0,		153 );
const D3DCOLOR Pink			= D3DCOLOR_ARGB (255,	255,	20,		147 );
const D3DCOLOR Orange		= D3DCOLOR_ARGB (255,	255,	165,	0	);
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
/************************************************************************/
/* MENU ITEM STRUCTURES                                                 */
/************************************************************************/

class Tab
{
public:
	char* Name;
	bool Active;
	int x;
	int y;
};
class Check
{
public:
	char* Parent;
	char* Name;
	bool Checked;
	int* Variable;
	int x;
	int y;
};
class Slider
{
public:
	char* Parent;
	char* Name;
	int MaxValue;
	int Value;
	int* Variable;
	int x;
	int y;
	int pos;
};

class TextBox
{
public:
	char* Parent;
	char* Name;
	std::string *Variable;
	bool Focused;
	int cursor;
	int x;
	int y;
};


/************************************************************************/
/* MENU CLASS                                                           */
/************************************************************************/
class cMenu
{
public:
	//Class Arrays.
	Tab Tabs[10];
	Check Checks[100];
	Slider Sliders[100];
	TextBox TextBoxes[100];

	//Menu Variables.
	int M_AimEnable, M_Aim_TeamKill, M_Aim_Silent, M_TriggerBot, M_AutoPistol, M_NoSpread, M_AutoReload, M_ESP,  M_ESP_Name, M_ESP_Health, M_ESP_HealthBar, M_ESP_3D, M_ESP_Weapons, M_NameChanger, M_Bhop, M_FreezeHack, M_Speed, M_FastJoin, M_DisconnectSpam, M_ClientSpectate, S_Speed, S_CrossHair, M_VoiceChatSpam, M_VoiceChatImitator, M_TextChatImitator, M_TextChatTeam, M_ChatSpam, M_FakeLag, M_Aim_KillNPC, M_ESP_NPCs, M_ESP_Players, M_ESP_ViewESP, M_Aim_KillPlayer;	
	std::string T_CustomESP, T_ChatSpam;

	int TabCount, CheckCount, SliderCount, TextBoxCount;
	char* ActiveName;
	POINT Cur;
	bool ClickToggle;
	int sizeoftab;
	int draging;
	//Functions.
	void InitMenu();
	void DrawMenu();
	void MenuNavigation();
	void CreateTab(char* Text);
	void CreateCheck(char* Parent, char* Text, int* Variable, bool is_checked = false);
	void CreateSlider(char* Parent, char* Text, int MaxValue, int* Variable);
	void CreateTextBox(char* Parent, char* Text, std::string *Variable );
	void DrawTab(int index, int x, int y, int width);
	void DrawCheckBox(int index, int x, int y);
	void DrawSlider(int index, int x, int y);
	void DrawTextBox(int index, int x, int y);
	void ThinkTextBox(int index);
	int MouseOver(int x, int y, int x2, int y2);
	void SwitchTab(int index);
};

extern cMenu* menu;
#endif