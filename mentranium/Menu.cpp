#include "Menu.h"

bool InitializedMenu = false;

void cuntMena::InitMenu()
{

	if ( InitializedMenu )
		return;

	InitializedMenu = true;

	CreateTab("Aim");
	CreateTab("Gun");
	CreateTab("ESP");
	CreateTab("Misc");
	CreateTab("Chat");

	CreateCheck("Aim", "Aimbot", &M_AimEnable);
	CreateCheck("Aim", "Silent Aim", &M_Aim_Silent);
	CreateCheck("Aim", "PSilent Aim", &M_Aim_PSilent);
	CreateCheck("Aim", "Teamkill", &M_Aim_TeamKill);
	CreateCheck("Aim", "Kill Players", &M_Aim_KillPlayer);
	CreateCheck("Aim", "Kill NPCs", &M_Aim_KillNPC);
	CreateCheck("Aim", "Hitscan", &M_Aim_Hitscan);
	CreateCheck("Aim", "Random Hitgroup", &M_Aim_RandomHitgroup);
	CreateCheck("Aim", "Teamshoot", &M_Aim_TeamShoot);
	CreateCheck("Aim", "Triggerbot", &M_TriggerBot);
	CreateCheck("Aim", "Aim Corrector", &M_Aim_Correct);
	CreateCheck("Aim", "Ignore Ammo", &M_Aim_IgnoreAmmo);

	CreateCheck("Gun", "Auto Pistol", &M_AutoPistol);
	CreateCheck("Gun", "Auto Reload", &M_AutoReload);
	CreateCheck("Gun", "No Spread", &M_NoSpread);
	CreateCheck("Gun", "No Recoil", &M_NoRecoil);

	CreateCheck("ESP", "Box ESP", &M_ESP_Box);
	CreateCheck("ESP", "Name", &M_ESP_Name);
	CreateCheck("ESP", "Health", &M_ESP_Health);
	CreateCheck("ESP", "NPCs", &M_ESP_NPCs);
	CreateCheck("ESP", "Players", &M_ESP_Players);
	CreateCheck("ESP", "Weapons", &M_ESP_Weapons);
	CreateCheck("ESP", "View ESP", &M_ESP_ViewESP);

	CreateCheck("Misc", "Speedhack", &M_SpeedHack);
	CreateCheck("Misc", "Name Changer", &M_NameChanger);
	CreateCheck("Misc", "Bunny Hop", &M_Bhop);
	CreateCheck("Misc", "Perfect Bunny Hop", &M_Bhop_Perfect);
	CreateCheck("Misc", "Freeze Hack", &M_FreezeHack);
	CreateCheck("Misc", "Disconnect Spam", &M_DisconnectSpam);
	CreateCheck("Misc", "Anti Aim", &M_AntiAim);
	CreateCheck("Misc", "Flashlight Spam", &M_FlashlightSpam);


	if ( g_AppID == 4000 )
	{
		CreateCheck("Misc", "[GMod] Prop Kill", &M_PropKill);
	}

	CreateCheck("Chat", "Text Imitator", &M_TextChatImitator );
	CreateCheck("Chat", "Team-Text", &M_TextChatTeam );
	CreateCheck("Chat", "Chat Spam", &M_ChatSpam );
	CreateCheck("Chat", "Chat Jammer", &M_ChatJammer );
	CreateCheck("Chat", "Voice Spam", &M_VoiceChatSpam );

	//Create Sliders
	CreateSlider("Aim", "Aim Smoothing", 100, &S_Aim_Smooth );
	CreateSlider("Aim", "Aim FOV", 180, &S_Aim_FOV );
	CreateSlider("Aim", "Aim Hitgroup", 7, &S_HitGroup);
	CreateSlider("Aim", "Aim Targetmode", 3, &S_TargetMode);
	CreateSlider("Misc", "Crosshair", 5, &S_CrossHair);
	CreateSlider("Misc", "Speedhack", 10, &S_SpeedHack);

	//Create Text Boxes
	CreateTextBox("ESP", "Custom ESP", &T_CustomESP);

	CreateTextBox("Chat", "Chat Spam", &T_ChatSpam);
	//M_ClientSpectate


}

void cuntMena::DrawMenu()
{

	if ( !&zFont || !g_pFont )
		return;

	GradientRect(10, 10, 300, 20, Grey, DGrey);
	DrawFilledRectangle(10,30,300,280,DGrey);
	DrawNonFilledRectangle(10,10,300,300,Outline);

	PrintText("Mentranium", 100,20,White,g_pFont);

	sizeoftab = 291 / (TabCount);
	DrawNonFilledRectangle(15,61, sizeoftab * TabCount, 243,Outline);

	for (int i = 0; i < TabCount; i++)
	{
		DrawTab(i, 15 + (i*sizeoftab), 41,sizeoftab);
	}

	int d = 0;
	for(int i = 0; i < CheckCount; i++)
	{
		if(ActiveName == Checks[i].Parent)
		{
			DrawCheckBox(i,30, 70 + (d*20));
			d++;
		}
	}

	d = 0;
	for(int i = 0; i < SliderCount; i++)
	{
		if(ActiveName == Sliders[i].Parent)
		{
			DrawSlider(i,150, 100 + (d*40));
			d++;
		}
	}

	d = 0;
	for(int i = 0; i < TextBoxCount; i++)
	{
		if(ActiveName == TextBoxes[i].Parent)
		{
			DrawTextBox(i,150, 100 + (d*40));
			d++;
		}
	}

	if ( !&menu->Cur )
		return;

	if ( menu->Cur.x == 0 && menu->Cur.y == 0 )
		return;

	DWORD color = LightCyan;

	POINT myCursor = menu->Cur;



	DrawFilledRectangle( menu->Cur.x,menu->Cur.y,11,1,color );
	DrawFilledRectangle( menu->Cur.x+1,menu->Cur.y+1,9,1,color );
	DrawFilledRectangle( menu->Cur.x+2,menu->Cur.y+2,7,1,color );
	DrawFilledRectangle( menu->Cur.x+3,menu->Cur.y+3,7,1,color );
	DrawFilledRectangle( menu->Cur.x+4,menu->Cur.y+4,8,1,color );
	DrawFilledRectangle( menu->Cur.x+5,menu->Cur.y+5,3,1,color );
	DrawFilledRectangle( menu->Cur.x+6,menu->Cur.y+6,2,1,color );


}

void cuntMena::MenuNavigation()
{

	if ( !menu_opened )
		return;

	POINT Balls;
	Balls.x = 0;
	Balls.y = 0;
	
	GetCursorPos( &Balls );
	
	if ( Balls.x != 0 && Balls.y != 0 )
	{
		Cur.x = Balls.x;
		Cur.y = Balls.y;
	}

	if ( Cur.x == 0 && Cur.y == 0 )
	{
		Cur.x = 1;
		Cur.y = 0;
	}

	bool ActiveCheck = false;
	for (int i = 0; i < TabCount; i++)
	{
		if(MouseOver(Tabs[i].x, Tabs[i].y, Tabs[i].x + sizeoftab, Tabs[i].y + 20) == 2)
			SwitchTab(i);

		if(Tabs[i].Active)
		{
			ActiveName = Tabs[i].Name;
			ActiveCheck = true;
		}
	}

	if(!ActiveCheck)
		Tabs[0].Active = true;

	for(int i = 0; i < CheckCount; i++)
	{
		if ( ActiveName != Checks[i].Parent )
			continue;
		
		if((MouseOver(Checks[i].x, Checks[i].y, Checks[i].x + 10 , Checks[i].y + 10) == 3) )
			*Checks[i].Variable = 0;

		if((MouseOver(Checks[i].x, Checks[i].y, Checks[i].x + 10 , Checks[i].y + 10) == 2) )
			*Checks[i].Variable = 1;
	}

	for(int i = 0; i < SliderCount; i++)
	{

		if ( ActiveName != Sliders[i].Parent )
			continue;

		if(((MouseOver(Sliders[i].x, Sliders[i].y - 3, Sliders[i].x + 160 , Sliders[i].y + 6) == 2)) )
		{
			//Calculate value based on click position.
			int Value1 = (Cur.x - Sliders[i].x);
			float Value2 = ((float)Value1 / (float)120) * Sliders[i].MaxValue;

			if((int)Value2 > Sliders[i].MaxValue)
				Value2 = (float)Sliders[i].MaxValue;

			if((int)Value2 < 0)
				Value2 = 0.0f;


			Sliders[i].Value = (int)Value2;
			*Sliders[i].Variable = Sliders[i].Value;
		}
	}

	for(int i = 0; i < TextBoxCount; i++)
	{

		if ( ActiveName != TextBoxes[i].Parent )
			continue;

		if((MouseOver(TextBoxes[i].x, TextBoxes[i].y, TextBoxes[i].x + 100 , TextBoxes[i].y + 20) == 2) )
			TextBoxes[i].Focused = 1;

		if((MouseOver(TextBoxes[i].x, TextBoxes[i].y, TextBoxes[i].x + 100 , TextBoxes[i].y + 20) == 3) )
			TextBoxes[i].Focused = 0;

		if ( TextBoxes[i].Focused )
			cuntMena::ThinkTextBox( i );

	}

}

void cuntMena::CreateTab(char* Text)
{
	Tabs[TabCount].Name = Text;
	Tabs[TabCount].Active = false;
	TabCount++;
}

void cuntMena::CreateCheck(char* Parent, char* Text, int* Variable )
{
	Checks[CheckCount].Parent = Parent;
	Checks[CheckCount].Name = Text;
	Checks[CheckCount].Variable = Variable;
	CheckCount++;
}

void cuntMena::CreateSlider(char* Parent, char* Text, int MaxValue, int* Variable)
{
	Sliders[SliderCount].Parent = Parent;
	Sliders[SliderCount].Name = Text;
	Sliders[SliderCount].MaxValue = MaxValue;
	Sliders[SliderCount].Variable = Variable;
	SliderCount++;
}

void cuntMena::CreateTextBox(char* Parent, char* Text, std::string *Variable )
{
	TextBoxes[TextBoxCount].Parent = Parent;
	TextBoxes[TextBoxCount].Name = Text;
	TextBoxes[TextBoxCount].Variable = Variable;
	TextBoxCount++;
}

void cuntMena::DrawTab(int index, int x, int y, int width)
{
	Tabs[index].x = x;
	Tabs[index].y = y;

	if(Tabs[index].Active)
	{
		GradientRect(x, y, width, 20, Grey, DGrey);
		DrawNonFilledRectangle(x,y,width,20,Outline);
		DrawFilledRectangle(x + 1 ,y + 1 ,width - 1 ,3 ,Red);
		DrawFilledRectangle(x+1,y+19, width - 1, 2,DGrey);
	}
	else
	{
		DrawFilledRectangle(x+1,y+19, width - 1, 2,DGrey);
		DrawNonFilledRectangle(x,y,width,20,Outline);
	}

	PrintText(Tabs[index].Name, x + 10, y + 5, White, g_pFont);
}

void cuntMena::DrawCheckBox(int index, int x, int y)
{
	Checks[index].x = x;
	Checks[index].y = y;
	DrawNonFilledRectangle(x,y,10,10,Outline);
	PrintText(Checks[index].Name, x + 22, y, White, g_pFont);

	if(*Checks[index].Variable == 1)
		DrawFilledRectangle(x + 1, y + 1, 9, 9, Red);
}

void cuntMena::DrawSlider(int index, int x, int y)
{
	Sliders[index].x = x;
	Sliders[index].y = y;
	DrawLine(x,y,x+120,y,3, Outline);
	PrintText(Sliders[index].Name, x + 5, y - 15, White, g_pFont);
	char lol[256];
	sprintf(lol, "%i", Sliders[index].Value);
	PrintText(lol, x + 55, y + 5, White, g_pFont);

	//Actual Slider
	float fpos = ((float)Sliders[index].Value/(float)Sliders[index].MaxValue)*((float)120);
	float pos = (float)x + (float)fpos;
	Sliders[index].pos = (int)pos;

	DrawFilledRectangle(Sliders[index].pos - 10, y - 3, 20, 5, Grey);
	DrawNonFilledRectangle(Sliders[index].pos - 10, y - 3, 20, 5, White);
}

void cuntMena::DrawTextBox(int index, int x, int y)
{
	TextBoxes[index].x = x;
	TextBoxes[index].y = y;
	PrintText(TextBoxes[index].Name, x + 5, y - 15, White, g_pFont);

	PrintText(const_cast<char *>(TextBoxes[index].Variable->c_str()), x + 5, y + 5, White, g_pFont);

	if ( TextBoxes[index].Focused )
		DrawNonFilledRectangle(x,y,100,20,Red);
	else
		DrawNonFilledRectangle(x,y,100,20,White);

}

bool upperMode = false;
void cuntMena::ThinkTextBox(int index)
{
	
	char* curChar = menu->textCharBuf;

	if ( curChar == NULL )
		return;

	char* newcurChar = strdup(curChar);

	curChar = newcurChar;

	if( strstr(curChar, "\b") )
	{

		if(TextBoxes[index].cursor > 0)
		{
			TextBoxes[index].Variable->erase( TextBoxes[index].cursor - 1, TextBoxes[index].cursor );

			TextBoxes[index].cursor = TextBoxes[index].cursor - 1;

		}

		menu->textCharBuf[0] = '\0';
		strcpy(menu->textCharBuf, "{_}");

		return;
	}

	if ( strstr(curChar, "{_}") )
		return;

	TextBoxes[index].Variable->append( curChar );

	TextBoxes[index].cursor = TextBoxes[index].cursor + 1;

	menu->textCharBuf[0] = '\0';
	strcpy(menu->textCharBuf, "{_}");

}

int cuntMena::MouseOver(int x, int y, int x2, int y2)
{
	if(Cur.x > x && Cur.x < x2 && Cur.y > y && Cur.y < y2)
	{
		if(GetAsyncKeyState( VK_LBUTTON ) & 0x8000)
			return 2;

		if(GetAsyncKeyState( VK_RBUTTON ) & 0x8000)
			return 3;

		return 1;
	}
	return 0;
}

void cuntMena::SwitchTab(int index)
{
	for (int i = 0; i < TabCount; i++)
	{
		if(i == index)
			Tabs[i].Active = true;
		else
			Tabs[i].Active = false;
	}
}