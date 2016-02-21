#include "Menu.h"

/************************************************************************/
/* INITIATE MENU                                                        */
/************************************************************************/
void cMenu::InitMenu()
{
	//Create Tabs.
	CreateTab("Aim");
	CreateTab("Gun");
	CreateTab("ESP");
	CreateTab("Misc");
	CreateTab("Chat");

	//Create Check Boxes.
	CreateCheck("Aim", "Aimbot", &M_AimEnable);
	CreateCheck("Aim", "Silent Aim", &M_Aim_Silent);
	CreateCheck("Aim", "Teamkill", &M_Aim_TeamKill);
	CreateCheck("Aim", "Kill Players", &M_Aim_KillPlayer);
	CreateCheck("Aim", "Kill NPCs", &M_Aim_KillNPC);
	CreateCheck("Aim", "Triggerbot", &M_TriggerBot);


	CreateCheck("Gun", "Auto Pistol", &M_AutoPistol);
	CreateCheck("Gun", "Auto Reload", &M_AutoReload);
	CreateCheck("Gun", "No Spread", &M_NoSpread);

	CreateCheck("ESP", "Enable", &M_ESP);
	CreateCheck("ESP", "Name", &M_ESP_Name);
	CreateCheck("ESP", "Health", &M_ESP_Health);
	CreateCheck("ESP", "Health Bar", &M_ESP_HealthBar);
	CreateCheck("ESP", "3D Boxes", &M_ESP_3D);
	CreateCheck("ESP", "NPCs", &M_ESP_NPCs);
	CreateCheck("ESP", "Players", &M_ESP_Players);
	CreateCheck("ESP", "Weapons", &M_ESP_Weapons);
	CreateCheck("ESP", "View ESP", &M_ESP_ViewESP);

	CreateCheck("Misc", "Name Changer", &M_NameChanger);
	CreateCheck("Misc", "Bunny Hop", &M_Bhop);
	CreateCheck("Misc", "Freeze Hack", &M_FreezeHack);
	CreateCheck("Misc", "Fake Lag", &M_FakeLag);
	CreateCheck("Misc", "Fast Join", &M_FastJoin);
	CreateCheck("Misc", "Disconnect Spam", &M_DisconnectSpam);
	CreateCheck("Misc", "Speedhake", &M_Speed);

	CreateCheck("Chat", "Voice Imitator", &M_VoiceChatImitator );
	CreateCheck("Chat", "Text Imitator", &M_TextChatImitator );
	CreateCheck("Chat", "Team-Text", &M_TextChatTeam );
	CreateCheck("Chat", "Chat Spam", &M_ChatSpam );
	CreateCheck("Chat", "Voice Spam", &M_VoiceChatSpam );

	//Create Sliders
	CreateSlider("Misc", "Speed", 100, &S_Speed);
	CreateSlider("Misc", "Crosshair", 5, &S_CrossHair);

	//Create Text Boxes
	CreateTextBox("ESP", "Custom ESP", &T_CustomESP);
	CreateTextBox("Chat", "Chat Spam", &T_ChatSpam);

	//M_ClientSpectate

}

/************************************************************************/
/* DRAW MENU                                                            */
/************************************************************************/
void cMenu::DrawMenu()
{
	//Body Stuff.
	GradientRect(10, 10, 300, 20, Grey, DGrey);
	DrawFilledRectangle(10,30,300,280,DGrey);
	DrawNonFilledRectangle(10,10,300,300,Outline);
	PrintText("Mentranium", 100,20,White,Font.g_pFont);
	
	//Tabs.
	sizeoftab = 291 / (TabCount);
	DrawNonFilledRectangle(15,61, sizeoftab * TabCount, 243,Outline);
	for (int i = 0; i < TabCount; i++)
	{
		DrawTab(i, 15 + (i*sizeoftab), 41,sizeoftab);
	}
	
	//Checks.
	int d = 0;
	for(int i = 0; i < CheckCount; i++)
	{
		if(ActiveName == Checks[i].Parent)
		{
			DrawCheckBox(i,30, 70 + (d*20));
			d++;
		}
	}

	//Sliders.
	d = 0;
	for(int i = 0; i < SliderCount; i++)
	{
		if(ActiveName == Sliders[i].Parent)
		{
			DrawSlider(i,150, 100 + (d*40));
			d++;
		}
	}

	//Text Boxes.
	d = 0;
	for(int i = 0; i < TextBoxCount; i++)
	{
		if(ActiveName == TextBoxes[i].Parent)
		{
			DrawTextBox(i,150, 100 + (d*40));
			d++;
		}
	}
}

/************************************************************************/
/* MENU NAVIGATION                                                      */
/************************************************************************/
void cMenu::MenuNavigation()
{
	GetCursorPos( &Cur );

	//Tabs.
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

	//Checks.
	for(int i = 0; i < CheckCount; i++)
	{
		if ( ActiveName != Checks[i].Parent )
			continue;

		if((MouseOver(Checks[i].x, Checks[i].y, Checks[i].x + 10 , Checks[i].y + 10) == 3) )
			Checks[i].Checked = 0;

		if((MouseOver(Checks[i].x, Checks[i].y, Checks[i].x + 10 , Checks[i].y + 10) == 2) )
			Checks[i].Checked = 1;

		if(Checks[i].Checked)
			*Checks[i].Variable = 1;
		else
			*Checks[i].Variable = 0;
	}

	//Sliders.
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
	//TextBoxes.
	for(int i = 0; i < TextBoxCount; i++)
	{

		if ( ActiveName != TextBoxes[i].Parent )
			continue;

		if((MouseOver(TextBoxes[i].x, TextBoxes[i].y, TextBoxes[i].x + 100 , TextBoxes[i].y + 20) == 2) )
			TextBoxes[i].Focused = 1;

		if((MouseOver(TextBoxes[i].x, TextBoxes[i].y, TextBoxes[i].x + 100 , TextBoxes[i].y + 20) == 3) )
			TextBoxes[i].Focused = 0;

		if ( TextBoxes[i].Focused )
			cMenu::ThinkTextBox( i );

	}
}

/************************************************************************/
/* CREATE TAB                                                           */
/************************************************************************/
void cMenu::CreateTab(char* Text)
{
	Tabs[TabCount].Name = Text;
	Tabs[TabCount].Active = false;
	TabCount++;
}

/************************************************************************/
/* CREATE ITEM                                                          */
/************************************************************************/
void cMenu::CreateCheck(char* Parent, char* Text, int* Variable, bool is_checked )
{
	Checks[CheckCount].Parent = Parent;
	Checks[CheckCount].Name = Text;
	Checks[CheckCount].Checked = is_checked;
	Checks[CheckCount].Variable = Variable;
	CheckCount++;
}

/************************************************************************/
/* CREATE SLIDER                                                        */
/************************************************************************/
void cMenu::CreateSlider(char* Parent, char* Text, int MaxValue, int* Variable)
{
	Sliders[SliderCount].Parent = Parent;
	Sliders[SliderCount].Name = Text;
	Sliders[SliderCount].MaxValue = MaxValue;
	Sliders[SliderCount].Variable = Variable;
	SliderCount++;
}

/************************************************************************/
/* CREATE SLIDER                                                        */
/************************************************************************/
void cMenu::CreateTextBox(char* Parent, char* Text, std::string *Variable )
{
	TextBoxes[TextBoxCount].Parent = Parent;
	TextBoxes[TextBoxCount].Name = Text;
	TextBoxes[TextBoxCount].Variable = Variable;
	TextBoxCount++;
}

/************************************************************************/
/* DRAW TAB                                                             */
/************************************************************************/
void cMenu::DrawTab(int index, int x, int y, int width)
{
	Tabs[index].x = x;
	Tabs[index].y = y;

	if(Tabs[index].Active)
	{
		GradientRect(x, y, width, 20, Grey, DGrey);
		DrawNonFilledRectangle(x,y,width,20,Outline);
		DrawFilledRectangle(x + 1 ,y + 1 ,width - 1 ,3 ,Aqua);
		DrawFilledRectangle(x+1,y+19, width - 1, 2,DGrey);
	}
	else
	{
		DrawFilledRectangle(x+1,y+19, width - 1, 2,DGrey);
		DrawNonFilledRectangle(x,y,width,20,Outline);
	}

	PrintText(Tabs[index].Name, x + 10, y + 5, White, Font.g_pFont);
}

/************************************************************************/
/* DRAW CHECKBOX                                                        */
/************************************************************************/
void cMenu::DrawCheckBox(int index, int x, int y)
{
	Checks[index].x = x;
	Checks[index].y = y;
	DrawNonFilledRectangle(x,y,10,10,Outline);
	PrintText(Checks[index].Name, x + 22, y, White, Font.g_pFont);

	if(Checks[index].Checked)
		DrawFilledRectangle(x + 1, y + 1, 8, 8, Aqua);
}

/************************************************************************/
/* DRAW SLIDER                                                          */
/************************************************************************/
void cMenu::DrawSlider(int index, int x, int y)
{
	Sliders[index].x = x;
	Sliders[index].y = y;
	DrawLine(x,y,x+120,y,3, Outline); //may change size of the line
	PrintText(Sliders[index].Name, x + 5, y - 15, White, Font.g_pFont);
	char lol[256];
	sprintf(lol, "%i", Sliders[index].Value);
	PrintText(lol, x + 55, y + 5, White, Font.g_pFont);

	//Actual Slider
	float fpos = ((float)Sliders[index].Value/(float)Sliders[index].MaxValue)*((float)120);
	float pos = (float)x + (float)fpos;
	Sliders[index].pos = (int)pos;

	DrawFilledRectangle(Sliders[index].pos - 10, y - 3, 20, 5, Grey);
	DrawNonFilledRectangle(Sliders[index].pos - 10, y - 3, 20, 5, White);
}

/************************************************************************/
/* DRAW TEXTBOX                                                         */
/************************************************************************/
void cMenu::DrawTextBox(int index, int x, int y)
{
	TextBoxes[index].x = x;
	TextBoxes[index].y = y;
	PrintText(TextBoxes[index].Name, x + 5, y - 15, White, Font.g_pFont);

	PrintText(const_cast<char *>(TextBoxes[index].Variable->c_str()), x + 5, y + 5, White, Font.g_pFont);

	if ( TextBoxes[index].Focused )
		DrawNonFilledRectangle(x,y,100,20,Red);
	else
		DrawNonFilledRectangle(x,y,100,20,White);

}

/************************************************************************/
/* TEXTBOX THINK                                                        */
/************************************************************************/
void cMenu::ThinkTextBox(int index)
{

	char* curChar = getChar();

	std::string dicka = curChar;

	dicka.erase(1);
	char* newcurChar = strdup(curChar);

	curChar = newcurChar;

	if( strstr(curChar, ".") )
	{

		if(TextBoxes[index].cursor > 0)
		{
			TextBoxes[index].Variable->erase( TextBoxes[index].cursor - 1, TextBoxes[index].cursor );

			TextBoxes[index].cursor = TextBoxes[index].cursor - 1;

		}

		return;
	}

	if ( strstr(curChar, "-") )
		return;
	

	TextBoxes[index].Variable->append( curChar );

	TextBoxes[index].cursor = TextBoxes[index].cursor + 1;


}

/************************************************************************/
/* MOUSE OVER                                                           */
/************************************************************************/
int cMenu::MouseOver(int x, int y, int x2, int y2)
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

/************************************************************************/
/* SWITCH TAB                                                           */
/************************************************************************/
void cMenu::SwitchTab(int index)
{
	for (int i = 0; i < TabCount; i++)
	{
		if(i == index)
			Tabs[i].Active = true;
		else
			Tabs[i].Active = false;
	}
}