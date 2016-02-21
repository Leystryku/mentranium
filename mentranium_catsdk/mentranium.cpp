
bool bIsReady = false;

#include "utils.h"

cuntMena *menu = NULL;

void Mentranium_NameSteal()
{

	if ( menu->M_NameChanger != 1 )
		return;

	int theIndax = ( rand() % MaximumClients );


	while ( bIsFagBadIndax(theIndax) == true )
	{

		theIndax = ( rand() %  MaximumClients );

		if ( bIsFagBadIndax(theIndax) == false && theIndax != g_pEngine->GetLocalPlayer() )
			break;

	}

	player_info_s pInfo; 

	g_pEngine->GetPlayerInfo( theIndax, &pInfo ); 

	if ( !&pInfo )
		return;

	string name = pInfo.name;

	if ( !pInfo.name )
		return;

	char stoel[50];

	const char *mask = "\xE2\x80\x8F%s\xE2\x80\x8F";

	sprintf(stoel, mask, name.c_str());

	Mentranium_Name( stoel );

}

void __fastcall newShutdown( void* thisptr, int edx, const char *dc_string )
{
	bIsReady = false;
	pLocalEntity = NULL;
	pAimEntity = NULL;
	pAimVec = NULL;
	pLocalWeapon = NULL;

	if ( menu->M_DisconnectSpam )
	{
		string ballsdeep;

		int i = 1;

		while (i <= 500)
		{
			ballsdeep.append("\n");
			i++;
		}

		dc_string = ballsdeep.c_str();
	}

	return ShutdownFn( thisptr, edx, dc_string );
}

void InitNetvars()
{

	if ( bIsReady )
		return;
	
	IClientEntity *localclEnt = NULL;

	if ( g_pEngine->GetLocalPlayer() )
	{
		localclEnt = g_pEntList->GetClientEntity(g_pEngine->GetLocalPlayer());

		if ( localclEnt )
			pLocalEntity =  dynamic_cast<C_BasePlayer*>(localclEnt);
	}

	if ( pLocalEntity == NULL )
		return;

	if ( !ShutdownFn )
	{
		INetChannel *channel = (INetChannel *)g_pEngine->GetNetChannelInfo();

		if ( !channel )
			return;

		CVMTHook *channelHook = new CVMTHook( channel );
		ShutdownFn = (OriginalShutdown)channelHook->hookFunction( 36, newShutdown );
	}

	if ( !m_fFlags )
		m_fFlags = GetNetvarOffset("DT_BasePlayer", "m_fFlags");

	if ( !m_fFlags )
		MessageBox( NULL, "no m_fFlags !","ERROR WHILE GETTING NETVARS !", MB_OK );

	if ( !m_iHealth )
		m_iHealth = GetNetvarOffset("DT_BaseEntity", "m_iHealth");

	if ( !m_iHealth )
		MessageBox( NULL, "no m_iHealth !","ERROR WHILE GETTING NETVARS !", MB_OK );

	if ( !m_iTeamNum )
		m_iTeamNum = GetNetvarOffset( "DT_BaseEntity", "m_iTeamNum" );

	if ( !m_iTeamNum )
		MessageBox( NULL, "no m_iTeamNum !","ERROR WHILE GETTING NETVARS !", MB_OK );

	if ( !m_vecPunchAngle )
		m_vecPunchAngle = GetNetvarOffset( "DT_Local", "m_vecPunchAngle" );

	if ( !m_vecPunchAngle )
		MessageBox( NULL, "no m_VecPunchAngle !","ERROR WHILE GETTING NETVARS !", MB_OK );

	if ( !m_vecPunchAngleVel )
		m_vecPunchAngleVel = GetNetvarOffset( "DT_Local", "m_vecPunchAngleVel" );

	if ( !m_vecPunchAngleVel )
		MessageBox( NULL, "no m_vecPunchAngleVel !","ERROR WHILE GETTING NETVARS !", MB_OK );

	if ( !m_fVecViewOffset )
		m_fVecViewOffset = GetNetvarOffset( "DT_LocalPlayerExclusive", "m_vecViewOffset[0]" );

	if ( !m_fVecViewOffset )
		MessageBox( NULL, "no m_fVecViewOffset !","ERROR WHILE GETTING NETVARS !", MB_OK );

	if ( !m_fLocal )
		m_fLocal = GetNetvarOffset( "DT_LocalPlayerExclusive", "m_Local" );

	if ( !m_fLocal )
		MessageBox( NULL, "no m_fLocal !","ERROR WHILE GETTING NETVARS !", MB_OK );

	if ( !m_fVecOrigin )
		m_fVecOrigin = GetNetvarOffset( "DT_BaseEntity", "m_vecOrigin" );

	if ( !m_fVecOrigin )
		MessageBox( NULL, "no m_fVecOrigin !","ERROR WHILE GETTING NETVARS !", MB_OK );

	if ( !m_angEyeAngles )
		m_angEyeAngles = GetNetvarOffset( "DT_HL2MPLocalPlayerExclusive", "m_angEyeAngles[0]" );

	if ( !m_angEyeAngles )
		MessageBox( NULL, "no m_angEyeAngles !","ERROR WHILE GETTING NETVARS !", MB_OK );

	if ( !m_flNextPrimaryAttack )
		m_flNextPrimaryAttack = GetNetvarOffset( "DT_LocalActiveWeaponData", "m_flNextPrimaryAttack" );

	if ( !m_flNextPrimaryAttack )
		MessageBox( NULL, "no m_flNextPrimaryAttack !","ERROR WHILE GETTING NETVARS !", MB_OK );

	if ( !m_flNextSecondaryAttack )
		m_flNextSecondaryAttack = GetNetvarOffset( "DT_LocalActiveWeaponData", "m_flNextSecondaryAttack" );

	if ( !m_flNextSecondaryAttack )
		MessageBox( NULL, "no m_flNextSecondaryAttack !","ERROR WHILE GETTING NETVARS !", MB_OK );

	if ( !m_iClip1 )
		m_iClip1 = GetNetvarOffset( "DT_LocalWeaponData", "m_iClip1" );

	if ( !m_iClip1 )
		MessageBox( NULL, "no m_iClip1 !","ERROR WHILE GETTING NETVARS !", MB_OK );

	if ( !m_hActiveWeapon )
		m_hActiveWeapon = GetNetvarOffset( "DT_BaseCombatCharacter", "m_hActiveWeapon" );

	if ( !m_hActiveWeapon )
		MessageBox( NULL, "no m_hActiveWeapon !","ERROR WHILE GETTING NETVARS !", MB_OK );

	if ( !m_nTickBase )
		m_nTickBase = GetNetvarOffset( "DT_LocalPlayerExclusive", "m_nTickBase" );

	if ( !m_nTickBase )
		MessageBox( NULL, "no m_nTickBase !", "ERROR WHILE GETTING NETVARS !", MB_OK );

	HighestEntityIndex = g_pEntList->GetHighestEntityIndex();
	MaximumClients = g_pEngine->GetMaxClients();

	if ( MaximumClients >= HighestEntityIndex )
		HighestEntityIndex = MaximumClients;

	bIsReady = true;

}

void Mentranium_Think()
{

	bool is_ingame = g_pEngine->IsInGame() && !g_pEngine->IsDrawingLoadingImage();


	if ( !bIsReady ) 
	{
		if ( is_ingame )
		{
			Sleep(5000);
			InitNetvars();
		}

		return;
	}else{
		if ( !is_ingame )
		{
			bIsReady = false;
			pLocalEntity = NULL;
			pAimEntity = NULL;
			pAimVec = NULL;
			pLocalWeapon = NULL;
		}

		if ( bIsReady && pLocalEntity == NULL )
		{
			Sleep(5000);
			InitNetvars();
		}
	}


	IClientEntity *localclEnt = NULL;

	if ( g_pEngine->GetLocalPlayer() )
	{
		localclEnt = g_pEntList->GetClientEntity(g_pEngine->GetLocalPlayer());

		if ( localclEnt )
		{
			pLocalEntity =  dynamic_cast<C_BasePlayer*>(localclEnt);
		}
	}

	if ( pLocalEntity == NULL )
	{
		bIsReady = false;
		pAimEntity = NULL;
		pAimVec = NULL;
		pLocalWeapon = NULL;
	}

	if ( g_pEntList->GetHighestEntityIndex() > HighestEntityIndex )
		HighestEntityIndex = g_pEntList->GetHighestEntityIndex();

	if ( g_pEntList->GetHighestEntityIndex() > HighestEntityIndex )
		MaximumClients = g_pEngine->GetMaxClients();

	if ( MaximumClients >= HighestEntityIndex )
		HighestEntityIndex = MaximumClients;

	if ( &menu->T_ChatSpam && menu->M_ChatSpam )
	{
		if ( menu->T_ChatSpam.length() != 0 )
		{
			char spamstr[99999];

			if ( !menu->M_TextChatTeam )
				sprintf(spamstr, "say %s", menu->T_ChatSpam.c_str());
			else
				sprintf(spamstr, "say_team %s", menu->T_ChatSpam.c_str());

			g_pEngine->ClientCmd_Unrestricted( spamstr );
			g_pEngine->ClientCmd_Unrestricted( spamstr );
		}
	}

	Mentranium_NameSteal();

}

bool CalculateAimVector(C_BaseEntity* player, Vector& vec) 
{
	//IClientRenderable* renderable = static_cast<IClientRenderable*>(player);

	//if (!renderable)
	//	return false;

	const model_t* model = player->GetModel();//renderable->GetModel();

	if (!model)
		return false;

	studiohdr_t* studiohdr = g_pModelInfo->GetStudiomodel( model );

	if (!studiohdr)
		return false;

	//const char *name = studiohdr->pszName();

	matrix3x4_t boneMatrix[MAXSTUDIOBONES];

	if (!player->SetupBones(boneMatrix, MAXSTUDIOBONES, BONE_USED_BY_HITBOX, 0 ))
		return false;

	static QAngle qaAngle( 0, 0, 0 );
	Vector vecHeadPos(-999999.0f, -999999.0f, -999999.0f);

	mstudiobbox_t* hitbox;

	//hitbox = studiohdr->pHitbox( 0, 0);

	for (int i = 0; i <studiohdr->iHitboxCount(0); ++i)
	{
		hitbox = studiohdr->pHitbox(i, 0);

		if (!hitbox)
			continue;

		Vector min_vec, max_vec;

		VectorTransform(hitbox->bbmin, boneMatrix[hitbox->bone], min_vec);
		VectorTransform(hitbox->bbmax, boneMatrix[hitbox->bone], max_vec);

		Vector origin = (min_vec + max_vec) * 0.5f;

		if (origin.z> vecHeadPos.z) 
		{
			vecHeadPos = origin;
		}
	}

	if (!hitbox)
		return false;

	//MatrixAngles( boneMatrix[hitbox->bone], qaAngle, vecHeadPos );
	vec = vecHeadPos;

	return true;
}

bool GetVisible( Vector& vecAbsStart, Vector& vecAbsEnd, C_BaseEntity* pBaseEnt ) 
{ 
	trace_t tr;
	Ray_t ray;

	CTraceFilter filter;

	ray.Init( vecAbsStart, vecAbsEnd );
	g_pEngineTrace->TraceRay( ray, MASK_SHOT, &filter, &tr );

	if ( !&tr )
		return false;

	if ( tr.m_pEnt == NULL || pBaseEnt == NULL )
		return false;

	if ( pBaseEnt == tr.m_pEnt )
		return true;

	return false;
}

float flGetDistance(float* fVec1, float* fVec2) 
{ 
    return sqrt(pow(fVec1[0] - fVec2[0] , 2) + pow(fVec1[1] - fVec2[1] , 2) + pow(fVec1[2] - fVec2[2] , 2)); 
} 

Vector GetTarget()
{

	float bestDist = 99999999999999999;
	C_BaseEntity *best_targ = 0;
	Vector myvec = GetOrigin(pLocalEntity);
	Vector localEyePos = GetEyePosition(pLocalEntity);
	Vector tarvec = Vector(0,0,0);

	int goby;

	if ( menu->M_Aim_KillNPC )
		goby = HighestEntityIndex;
	else
		goby = MaximumClients;

	for( int i = goby; i > 0; i-- )
	{

		if( i == g_pEngine->GetLocalPlayer() )
			continue;

		C_BaseEntity *clEnt = NULL;

		IClientEntity *iclEnt = g_pEntList->GetClientEntity(i);
		
		if ( iclEnt )
			clEnt = iclEnt->GetBaseEntity();

		if ( clEnt == NULL )
			continue;

		const char *classname = C_BaseEnt_Classname( clEnt, NULL );

		if ( !classname )
		{
			clEnt = NULL;
			continue;
		}

		if ( clEnt->IsDormant() )
		{
			clEnt = NULL;
			continue;
		}

		bool is_living = false;
		bool is_npc = false;

		if ( menu->M_Aim_KillPlayer && strstr(classname, "player") != 0 && strlen(classname) == strlen("player") )
			is_living = true;

		if ( menu->M_Aim_KillNPC && strstr(classname, "npc_") != 0 )
		{
			is_living = true;
			is_npc = true;
		}

		if ( !is_living )
		{
			clEnt = NULL;
			continue;
		}

		if ( !is_npc && menu->M_Aim_TeamKill == 0 )
		{
			if ( isFriendlyTeam(clEnt) )
			{
				clEnt = NULL;
				continue;
			}
		}

		int iHealth = GetHealth(clEnt);

		if ( iHealth < 1 )
			continue;

		Vector vec;

		bool gothitbox = CalculateAimVector( clEnt, vec );

		if ( !gothitbox )
		{
			clEnt = NULL;
			continue;
		}

		if ( !GetVisible( localEyePos, vec, clEnt ) )
		{
			clEnt = NULL;
			continue;
		}
		
		float myveca[3];
		float veca[3];
		myveca[1] = myvec.x;
		myveca[2] = myvec.y;
		myveca[3] = myvec.z;

		veca[1] = vec.x;
		veca[2] = vec.y;
		veca[3] = vec.z;

		float pDist = flGetDistance( myveca, veca );

		if ( pDist < bestDist )
		{
			best_targ = clEnt;
			bestDist = pDist;
			tarvec = vec;
		}else{
			clEnt = NULL;
		}
	}

	pAimEntity = best_targ;
	pAimVec = tarvec;

	return tarvec;
}						

void LimitAng( QAngle &ang )
{
   if ( ang.x > 180 )
        ang.x -= 360;
    if ( ang.x < -180 )
        ang.x += 360;

    if( ang.y > 180 )
        ang.y -= 360;

	if ( ang.y < -180 )
        ang.y += 360;
}

C_BaseEntity *bTraceToTarget( CUserCmd *cmd )
{
	C_BaseEntity *nullla = NULL;

	Vector Eyes, Forward;
	QAngle Angles = cmd->viewangles;
	trace_t pTrace;
	Ray_t pRay;

	Eyes = GetEyePosition(pLocalEntity);

	Vector vDirection;

	AngleVectors( Angles, &vDirection );

	vDirection = vDirection * 8192 + Eyes;

	CTraceFilter filter;

	pRay.Init( Eyes, vDirection );
	g_pEngineTrace->TraceRay( pRay, MASK_SHOT, &filter, &pTrace);

	if ( pTrace.m_pEnt == NULL )
		return nullla;

	const char *classname = C_BaseEnt_Classname( pTrace.m_pEnt, NULL );

	if ( !classname )
		return nullla;

	bool found = false;
	bool is_npc = false;

	if ( menu->M_Aim_KillPlayer && strstr(classname, "player") != 0 && strlen(classname) == strlen("player") )
		found = true;

	if ( menu->M_Aim_KillNPC && strstr(classname, "npc_") != 0 )
	{
		is_npc = true;
		found = true;
	}

	if ( !found )
		return nullla;

	if ( !is_npc && menu->M_Aim_TeamKill == 0 )
	{

		if ( isFriendlyTeam(pTrace.m_pEnt) )
			return nullla;
	}

	return pTrace.m_pEnt;
}

void FixMove(CUserCmd *cmd, const QAngle& va)
{

	float yaw, speed;
	Vector& move = *(Vector*) &cmd->forwardmove;

	speed = sqrt(move.x*move.x + move.y*move.y);

	yaw = RAD2DEG(atan2(move.y, move.x));
	yaw = DEG2RAD(cmd->viewangles.y - va.y + yaw);

	cmd->forwardmove = cos(yaw) * speed;
	cmd->sidemove = sin(yaw) * speed;

}


DWORD NoRecoil( )
{
	return m_fLocal + m_vecPunchAngle;
}


int oldSidemove = 0;
int oldForwardmove = 0;
int oldUpmove = 0;
QAngle oldView = QAngle(0,0,0);
QAngle noAntiAim = QAngle(0,0,0);

bool SkipReload = false;

void DoUsercmdStuff( CUserCmd *cmd )
{

	if ( pLocalEntity == NULL )
		return;

	if ( !bIsReady )
		return;

	if ( menu->M_FreezeHack == 1 )
	{
		cmd->header = 0xFFFFF;
		cmd->tick_count = 0xFFFFF;

		return;
	}

	//COED PREDICTION U LAZY TARD XD
	int iFlags = GetFlags(pLocalEntity);
	int im_iClip1 = -1;

	float fm_flNextPrimaryAttack = 0.0f;
	float fm_flNextSecondaryAttack = 0.0f;

	float flServerTime = ( float )*( int* )( ( DWORD )pLocalEntity + m_nTickBase ) * g_pGlobals->interval_per_tick;
	EHANDLE hActiveWeapon = *reinterpret_cast< EHANDLE* >( ( DWORD )pLocalEntity + m_hActiveWeapon );

	pLocalWeapon = dynamic_cast<IClientEntity*>(g_pEntList->GetClientEntityFromHandle(hActiveWeapon));

	if ( pLocalWeapon )
	{
		fm_flNextPrimaryAttack = *(float*)((DWORD)pLocalWeapon + m_flNextPrimaryAttack);
		fm_flNextSecondaryAttack = *(float*)((DWORD)pLocalWeapon + m_flNextPrimaryAttack);

		im_iClip1 = *(int*)((DWORD)pLocalWeapon + m_iClip1);
	}

	if ( menu->M_AntiAim )
	{
		if ( cmd->viewangles.x != (180.95) )
		{
			noAntiAim.x = cmd->viewangles.x;
			noAntiAim.y = cmd->viewangles.y;
			noAntiAim.z = cmd->viewangles.z;
		}

        cmd->viewangles.x = (180.95);
		cmd->viewangles.y += 342.336254742783f;
		FixMove( cmd, noAntiAim );
	}

	bool shouldShoot = false;

	if ( menu->M_Bhop )
	{
		if( ( cmd->buttons & IN_JUMP ) )
		{

			if ( iFlags == NULL )
				return;

			if( !( iFlags & FL_ONGROUND ) )
			{
				cmd->buttons &= ~IN_JUMP;
			}

		}
	}

	QAngle PunchAngle = *(QAngle*)((DWORD)pLocalEntity + NoRecoil());
	if ( menu->M_NoRecoil )
	{

		cmd->viewangles.x -= (	PunchAngle.x *2.0f	);//subtract x
		cmd->viewangles.y -= (	PunchAngle.y *2.0f	);//subtract y

		SetViewAnglesFn( cmd->viewangles );

	}
		
	if ( menu->M_AimEnable == 1 && pLocalWeapon )
	{

		bool ammoFuck = true;

		if ( !menu->M_Aim_IgnoreAmmo && ( !im_iClip1 || im_iClip1 == 0 ) )
			ammoFuck = false;

		Vector pos = GetTarget();

		if ( pAimEntity != 0 && ammoFuck )
		{

			VectorAngles(pos - GetEyePosition(pLocalEntity), aimAngles);

			if ( menu->M_NoSpread == 1 )
			{
				//FixSpread( cmd->random_seed, aimAngles );
			}

			LimitAng(aimAngles);

			QAngle aimAngles2 = aimAngles;

			if ( menu->M_Aim_Silent == 1 )
			{
				oldForwardmove = cmd->forwardmove;
				oldSidemove = cmd->sidemove;
				oldUpmove = cmd->upmove;
				oldView = cmd->viewangles;

				QAngle oldAngle = cmd->viewangles;
				cmd->viewangles = aimAngles2;
				FixMove( cmd, oldAngle );

				shouldShoot = true;

			}else{
				SetViewAnglesFn( aimAngles2 );
			}

		}else{
			pAimVec = NULL;
			pAimEntity = NULL;

			if ( oldView.x != 0 && oldView.y != 0 && oldView.z != 0 )
			{
				cmd->viewangles = oldView;
				cmd->sidemove = oldSidemove;
				cmd->forwardmove = oldForwardmove;
				cmd->upmove = oldUpmove;
				oldView = QAngle(0,0,0);
				oldSidemove = 0;
				oldForwardmove = 0;
				oldUpmove = 0;
			}
		}
	}else{
		pAimVec = NULL;
		pAimEntity = NULL;

		if ( oldView.x != 0 && oldView.y != 0 && oldView.z != 0 )
		{
			cmd->viewangles = oldView;
			cmd->sidemove = oldSidemove;
			cmd->forwardmove = oldForwardmove;
			cmd->upmove = oldUpmove;
			oldView = QAngle(0,0,0);
			oldSidemove = 0;
			oldForwardmove = 0;
			oldUpmove = 0;
		}

	}
	
	if ( menu->M_AutoPistol != 0 )
	{
		if ( cmd->buttons & IN_ATTACK )
		{
			shouldShoot = true;
		}

	}

	if ( menu->M_TriggerBot != 0 || menu->M_Aim_Correct != 0 )
	{
		C_BaseEntity *targ = bTraceToTarget(cmd);

		if ( targ )
		{

			if ( menu->M_TriggerBot )
				shouldShoot = true;

			if ( menu->M_Aim_Correct )
			{
				Vector vec;


				bool gothitbox = CalculateAimVector( targ, vec );

				if ( gothitbox )
				{
					Vector localEyePos = GetEyePosition(pLocalEntity);
					if ( GetVisible( localEyePos, vec, targ ) )
					{
						QAngle CorrectAng;
						VectorAngles(vec - GetEyePosition(pLocalEntity), CorrectAng);
						LimitAng(CorrectAng);
						SetViewAnglesFn( CorrectAng );

					}
				}
			}
		}

	}

	if ( shouldShoot )
	{
		if ( fm_flNextPrimaryAttack <= flServerTime )
			cmd->buttons |= IN_ATTACK;
		else
			cmd->buttons &= ~IN_ATTACK;
	}

	if ( pLocalWeapon )
	{
		if ( !SkipReload )
		{
			if ( im_iClip1 == 0 && menu->M_AutoReload )
			{
				cmd->buttons |= IN_RELOAD;
				SkipReload = true;
			}
			
		}else{
			SkipReload = false;
		}
	}
	
	viewAng = cmd->viewangles;
}

bool minus = false;

void __stdcall newSetViewAngles( QAngle &va )
{

	DWORD dwESI = NULL;
	_asm mov dwESI, esi;

	SetViewAnglesFn( va );
	
	DWORD hmm = dwClientDLLHandle - (DWORD)_ReturnAddress();

	//stringstream da;
	//da << hmm;

	//MessageBox( NULL, da.str().c_str(), "k", MB_OK );

	if ( hmm != 4293104877 )
	{
		return;
	}

	CUserCmd *pCmd = (CUserCmd*)dwESI;

	if ( !pCmd )
		return;

	DoUsercmdStuff( pCmd );

	if ( menu->M_NoSpread )
	{
		DWORD dwEBP = NULL;
		__asm mov dwEBP, ebp;
		
		if ( !dwEBP )
			return;

		DWORD* p = &dwEBP;


		int seed = 5;
		//css seed = y;
		//tf2 seed = z;

		if ( pLocalWeapon )
		{
			const char *classname = "";
			classname = C_BaseEnt_Classname( pLocalWeapon, NULL );

			if ( classname )
			{

				if ( strstr(classname, "fas2") != 0 )
				{
					seed = 6719921;
				}

			}
		}

		int ideal = CalcRandomSeed( seed );
		int num = 0;

		for ( int i = pCmd->command_number + 1; !num; i++ )
		{
			/*
			stringstream shit;
			shit << i;
			shit << ":";
			shit << CalcRandomSeed(i);
			shit << "\n";
			Msg(shit.str().c_str());*/

			if ( CalcRandomSeed(i) == ideal)
				num = i;
		}

		for(int i=0; i < 40; i++)
		{
			if ( pCmd->command_number == 1 || pCmd->command_number == 0 )
				continue;

			if ( *(p - i) == pCmd->command_number )
			{
				*(p - i) = num;
			}
			if ( *(p + i) == pCmd->command_number )
			{
				*(p + i) = num;
			}
		}

	}

}

void DrawCrosshair( LPDIRECT3DDEVICE9 pDevice )
{
	switch( menu->S_CrossHair )
	{
	case 1:

		FillRGB(CenterX-15, CenterY, 30, 1, Red);
		FillRGB(CenterX, CenterY-15, 1, 30, Red);
		break;
	case 2:
		DrawLine(CenterX+10, CenterY+10, CenterX-10, CenterY-10, 2, Red);
		DrawLine(CenterX-10, CenterY+10, CenterX+10, CenterY-10, 2, Red);
		break;
	case 3:
		FillRGB(CenterX-15, CenterY, 10, 1,Red);//Left line
		FillRGB(CenterX+6, CenterY, 10, 1,Red);//Right line
		FillRGB(CenterX, CenterY-15, 1, 10,Red);//Top line
		FillRGB(CenterX, CenterY+6, 1, 10,Red);//Bottom line
		DrawPoint(CenterX,CenterY,1,1,Green);
		break;
	case 4:
		DrawLine(CenterX+15,CenterY+3,CenterX+3,CenterY+3,2,Red);
		DrawLine(CenterX-15,CenterY+3,CenterX-3,CenterY+3,2,Red);
		DrawLine(CenterX+15,CenterY-3,CenterX+3,CenterY-3,2,Red);
		DrawLine(CenterX-15,CenterY-3,CenterX-3,CenterY-3,2,Red);
		DrawPoint(CenterX,CenterY,1,1,Green);
		break;
	case 5:
		DrawLine(CenterX+15,CenterY+15,CenterX+3,CenterY+3,2,Red);
		DrawLine(CenterX-15,CenterY+15,CenterX-3,CenterY+3,2,Red);
		DrawLine(CenterX+15,CenterY-15,CenterX+3,CenterY-3,2,Red);
		DrawLine(CenterX-15,CenterY-15,CenterX-3,CenterY-3,2,Red);
		DrawPoint(CenterX,CenterY,1,1,Green);
		break;
	}

}


void DrawLivingESP( C_BaseEntity *pBaseEntity, const char *name, bool is_npc )
{
	if ( !pBaseEntity || !name )
		return;

	Vector AbsScreen = Vector(0,0,0);
	Vector origin = GetOrigin(pBaseEntity);

	if ( origin.x == 0 && origin.y == 0 && origin.z == 0 )
		return;

	if( WorldToScreen( origin, AbsScreen ) == false )
		return;

	if ( AbsScreen.x == 0 && AbsScreen.y == 0 )
		return;

	D3DCOLOR DrawColor = D3DCOLOR_RGBA( 0, 107, 60, 255 );
	
	int health = GetHealth( pBaseEntity );

	if ( health < 1 )
	{
		DrawColor = D3DCOLOR_RGBA( 0, 0, 0, 255 );
	}else{

		if ( !is_npc )
			DrawColor = GetTeamCol( pBaseEntity );

	}

	char c_health[11];
	sprintf(c_health, "%d", health);

	if ( menu->M_ESP_Name )
		PrintText( name, AbsScreen.x, AbsScreen.y, DrawColor, g_pFont);

	if ( menu->M_ESP_Health )
		PrintText( c_health, AbsScreen.x, AbsScreen.y + 8.0f, DrawColor, g_pFont);

}

void DrawWeaponESP( C_BaseEntity *pBaseEntity, const char *name )
{
	
	if ( !pBaseEntity || !name )
		return;

	Vector AbsScreen = Vector(0,0,0);
	Vector origin = GetOrigin(pBaseEntity);

	if ( origin.x == 0 && origin.y == 0 && origin.z == 0 )
		return;

	if( WorldToScreen( origin, AbsScreen ) == false )
		return;

	if ( AbsScreen.x == 0 && AbsScreen.y == 0 )
		return;

	D3DCOLOR DrawColor = D3DCOLOR_RGBA(255, 255, 0, 255);

	PrintText( name, AbsScreen.x, AbsScreen.y, DrawColor, g_pFont);
}

void DrawESP( LPDIRECT3DDEVICE9 pDevice )
{

	if( !bIsReady )
		return;

	int localPlay = g_pEngine->GetLocalPlayer();

	for( int i = 0; i < HighestEntityIndex; i++ )
	{

		if( i == localPlay )
			continue;

		if ( i > HighestEntityIndex )
			break;

		IClientEntity *clEnt = g_pEntList->GetClientEntity(i);

		if ( !clEnt )
			continue;

		C_BaseEntity *pBaseEntity = clEnt->GetBaseEntity();

		if ( !pBaseEntity )
			continue;

		const char *classname = "";
		classname = C_BaseEnt_Classname( pBaseEntity, NULL );

		if ( !classname )
			continue;

		bool is_living = false;
		bool is_npc = false;

		if ( menu->M_ESP_Players == 1 && strstr(classname, "player") != 0 && strlen(classname) == strlen("player") )
		{
			is_living = true;
		}

		if ( menu->M_ESP_NPCs == 1 && strstr(classname, "npc_") != 0 )
		{
			is_living = true;
			is_npc = true;
		}

		if ( is_living )
		{
			if ( is_living && !is_npc )
			{

				player_info_s plInfo;

				g_pEngine->GetPlayerInfo( i, &plInfo );


				if ( !plInfo.name )
				{
					DrawLivingESP( pBaseEntity, classname, is_npc);
					continue;
				}

				classname = plInfo.name;
			}

			DrawLivingESP( pBaseEntity, classname, is_npc);
			
			continue;
		}

		if ( menu->M_ESP_Weapons && strstr(classname, "weapon") != 0 )
		{
			DrawWeaponESP( pBaseEntity, classname );

			continue;
		}

		//this needs to be recoded 2
		//DrawCustomESP( pBaseEntity, classname );

	}

}

void DrawViewESP( LPDIRECT3DDEVICE9 pDevice )
{
	if ( !pLocalEntity )
		return;
	
	if ( !pLocalEntity->GetIClientEntity() )
		return;

	if ( !C_BaseEnt_Classname )
		return;

	if ( !&viewAng )
		return;

	if ( viewAng.x == 0 && viewAng.y == 0 && viewAng.z == 0 )
		return;

	Vector Eyes, Forward;
	QAngle Angles = viewAng;
	trace_t tr;
	Ray_t pRay;

	Eyes = GetEyePosition(pLocalEntity);

	Vector vDirection;

	AngleVectors( Angles, &vDirection );

	vDirection = vDirection * 8192 + Eyes;

	CTraceFilterHitAll filter;


	pRay.Init( Eyes, vDirection );
	g_pEngineTrace->TraceRay( pRay, MASK_ALL, &filter, &tr);
	
	const char *classname = "worldspawn";

	if ( !tr.m_pEnt )
		classname = "worldspawn";
	else
		classname = C_BaseEnt_Classname( tr.m_pEnt, NULL );

	if ( !classname )
		classname = "worldspawn";

	PrintText(classname, ScrW - 300, 2, Black, g_pFont2);

}

void DrawAimLine( LPDIRECT3DDEVICE9 pDevice )
{

	if ( pAimEntity == NULL )
		return;

	Vector AbsScreen = Vector(0,0,0);

	if( WorldToScreen( pAimVec, AbsScreen ) == false )
		return;

	DrawLine( CenterX + CenterX/3, CenterY + CenterY/3, AbsScreen.x, AbsScreen.y + 5, 4, Blue );

}

void TestDrawStatus(LPDIRECT3DDEVICE9 pDevice)
{

	if ( menu->S_CrossHair != 0 )
		DrawCrosshair( pDevice );

	if ( menu_opened )
	{
		menu->DrawMenu();
	}

	if ( !bIsReady )
		return;
	 
	if ( pLocalEntity == NULL )
		return;

	if ( menu->M_ESP_Box == 1 || menu->M_ESP_Health == 1 || menu->M_ESP_Name == 1 || menu->M_ESP_Weapons == 1 )
		DrawESP( pDevice );

	if ( menu->M_ESP_ViewESP == 1 )
		DrawViewESP( pDevice );

	if ( menu->M_AimEnable == 1 && menu->M_Aim_Silent == 1 )
		DrawAimLine( pDevice );


}


bool ResetOverlay = false;

HWND hWnd;
const MARGINS  margin = {-1,-1,-1,-1};

void D3DInit(HWND hWnd)
{
    // create the Direct3D interface

   HMODULE h = LoadLibrary( "d3d9.dll" );
   if ( !h )
	   return;

	typedef HRESULT (WINAPI *LPDIRECT3DCREATE9EX)( UINT, IDirect3D9Ex**);

	LPDIRECT3DCREATE9EX func = (LPDIRECT3DCREATE9EX)GetProcAddress( h, "Direct3DCreate9Ex" );

	HRESULT ret = func(D3D_SDK_VERSION, &D3D);

	while( true )
	{
		if ( !FAILED(ret) )
			break;

		ret = func(D3D_SDK_VERSION, &D3D);

		if ( !FAILED(ret) )
			break;

	}

    D3DPRESENT_PARAMETERS d3dpp;    // create a struct to hold various device information

    ZeroMemory(&d3dpp, sizeof(d3dpp));    // clear out the struct for use
    d3dpp.Windowed = TRUE;    // program windowed, not fullscreen
    d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;    // discard old frames
    d3dpp.hDeviceWindow = hWnd;    // set the window to be used by Direct3D
    d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;     // set the back buffer format to 32-bit
    d3dpp.BackBufferWidth = ScrW;    // set the width of the buffer
    d3dpp.BackBufferHeight = ScrH;    // set the height of the buffer
	d3dpp.MultiSampleQuality   = D3DMULTISAMPLE_NONE;

    d3dpp.EnableAutoDepthStencil = TRUE;
    d3dpp.AutoDepthStencilFormat = D3DFMT_D16;

    // create a device class using this information and the info from the d3dpp stuct

	HRESULT res = D3D->CreateDeviceEx(D3DADAPTER_DEFAULT,
                      D3DDEVTYPE_HAL,
                      hWnd,
                      D3DCREATE_HARDWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED | D3DCREATE_FPU_PRESERVE,
                      &d3dpp,
					  0,
                      &m_pDevice);

	while( true )
	{
		if ( !FAILED(res) )
			break;

		res = D3D->CreateDeviceEx(D3DADAPTER_DEFAULT,
                      D3DDEVTYPE_HAL,
                      hWnd,
                      D3DCREATE_HARDWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED | D3DCREATE_FPU_PRESERVE,
                      &d3dpp,
					  0,
                      &m_pDevice);

		if ( !FAILED(res) )
			break;
	}

	FreeLibrary(h);
}

bool menu_initiated = false;
void RenderD3DOverlay()
{

	if ( !m_pDevice )
	{
		menu_initiated = false;
	}

	if ( !menu_initiated )
	{

		menu_initiated = true;
		zFont.FontManager( m_pDevice );
		menu->InitMenu();
	}


	m_pDevice->Clear(0, 0, D3DCLEAR_TARGET, 0, 1.0f, 0);
	m_pDevice->BeginScene();
	if ( menu && menu_initiated && g_pFont && g_pFont2 && g_pFont3 && pLine && pSprite && GetForegroundWindow() == game_HWND && DoRenderOnce && !IsGameOverlayOpen() )
	{

		

		pSprite->Begin( D3DXSPRITE_ALPHABLEND );

		m_pDevice->SetFVF( D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1 );
		DoRenderOnce = false;
		TestDrawStatus(m_pDevice);

		pSprite->End();

	}else{
		if ( g_pFont2 && m_pDevice )
			PrintText("", 1, 1, Black, g_pFont2);
	}

	m_pDevice->EndScene();
	m_pDevice->PresentEx(0, 0, 0, 0, 0);


}

LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch(message)
    {
	case WM_CREATE:
        {

        if ( !FAILED(DwmExtendFrameIntoClientArea(hWnd, &margin)) )
		{
			Sleep(2);
		}else{
			ResetOverlay = true;
		}

        }break;

     case WM_DESTROY:
		{

			if ( !FindWindow(NULL, "Garry's Mod") && !FindWindow(NULL, "Counter-Strike Source") && !FindWindow(NULL, "Counter-Strike: Global Offensive") && !FindWindow(NULL, "Team Fortress 2") )
				return 0;

			ResetOverlay = true;
			return 0;
		} break;
    }

    return DefWindowProc (hWnd, message, wParam, lParam);
}

int D3DThread( )
{
	ResetOverlay = false;

	if ( game_HWND == NULL )
		game_HWND = FindWindow(NULL, "Garry's Mod");

	if( game_HWND == NULL )
		game_HWND = FindWindow(NULL, "Counter-Strike Source");

	if( game_HWND == NULL )
		game_HWND = FindWindow(NULL, "Counter-Strike: Global Offensive");

	if ( game_HWND == NULL )
		game_HWND = FindWindow(NULL, "Team Fortress 2");

	if( game_HWND == NULL )
	{
		MessageBox( NULL, "could not find game ?!", "k", MB_OK );
		return 0;
	}

	RECT rc;

	GetWindowRect(game_HWND, &rc);

	SetForegroundWindow(game_HWND);

	ScrW =  rc.right - rc.left;
	ScrH = rc.bottom - rc.top;

	CenterX = ScrW/2;
	CenterY = ScrH/2;

	if ( !registered_OurWND )
	{
	
		wClass.cbClsExtra = NULL;
		wClass.cbSize = sizeof(WNDCLASSEX);
		wClass.cbWndExtra = NULL;
		wClass.hbrBackground = (HBRUSH)CreateSolidBrush(RGB(0, 0, 0));
		wClass.hCursor = LoadCursor(0, IDC_ARROW);
		wClass.hIcon = LoadIcon(0, IDI_APPLICATION);
		wClass.hIconSm = LoadIcon(0, IDI_APPLICATION);
		wClass.hInstance = NULL;
		wClass.lpfnWndProc = WindowProc;
		wClass.lpszClassName = "Fraps Overlay";
		wClass.lpszMenuName = "Fraps Overlay";
		wClass.style = CS_VREDRAW | CS_HREDRAW;

		if (!RegisterClassEx(&wClass) )
		{
			Sleep(50);
			D3DThread();
		}else{
			registered_OurWND = true;
		}

	}

	while( true )
	{
		Sleep(1);
		if ( hWnd == NULL )
		{
			hWnd = CreateWindowEx(WS_EX_TOPMOST | WS_EX_TRANSPARENT | WS_EX_LAYERED,
                          "Fraps Overlay",
                          "Fraps Overlay",
                          WS_POPUP,
                          1,
						  1,
                          ScrW, ScrH,
                          NULL,
                          NULL,
                          NULL,
                          NULL);

			if ( hWnd != NULL )
				break;
		}else{
			break;
		}
	}

	SetLayeredWindowAttributes(hWnd, RGB(0,0,0), 255, ULW_COLORKEY | LWA_ALPHA);
	
	ShowWindow(hWnd, SW_SHOW);

	D3DInit(hWnd);

	SetForegroundWindow(game_HWND);

	MSG msg;

	while( true )
    {

		Sleep(6); // We do this to prevent it from using too much memory

		while(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) )
		{
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

		if ( ResetOverlay )
		{

			if ( m_pDevice )
				m_pDevice->Release();

			if ( D3D )
				D3D->Release();

			m_pDevice = NULL;
			hWnd = NULL;
			D3D = NULL;
			g_pFont = NULL;
			g_pFont2 = NULL;
			g_pFont3 = NULL;
			pLine = NULL;
			pSprite = NULL;

			
			menu_initiated = false;
			D3DThread();
			break;
		}

		if ( game_HWND )
		{
			GetWindowRect(game_HWND, &rc);
			ScrW = rc.right - rc.left;
			ScrH = rc.bottom - rc.top;
			DWORD dwStyle = GetWindowLong(game_HWND, GWL_STYLE);
			if(dwStyle & WS_BORDER)
			{
				rc.top += 23;
				ScrH -= 23;
			}

			if ( hWnd )
				MoveWindow(hWnd, rc.left, rc.top, ScrW, ScrH, true);
		}

		DoRenderOnce = true;

		RenderD3DOverlay();

		if ( GetForegroundWindow() == hWnd )
			SetForegroundWindow(game_HWND);
		else if ( GetForegroundWindow() != game_HWND || IsGameOverlayOpen() )
			continue;

		if ( menu_initiated )
		{
			if( GetAsyncKeyState(VK_DELETE)&1 )
				menu_opened = !menu_opened;

			if( GetAsyncKeyState(VK_F11)&1 )
				menu->M_FreezeHack = !menu->M_FreezeHack;

			menu->MenuNavigation();
		}


    }



    return msg.wParam;
}

int Mentranium_ThinkThread()
{
	while( true )
	{
		Mentranium_Think();
		Sleep(2000);
	}
}

char* InitializeInterfaces( )
{

	//Get Interfaces
	g_pClient		= ( IBaseClientDLL* ) getEnterprise( &clientFactory, "VClient" );
	g_pEngine		= ( IVEngineClient* ) getEnterprise( &engineFactory, "VEngineClient" );
	g_pEntList		= ( IClientEntityList* ) getEnterprise( &clientFactory, "VClientEntityList" );
	g_pEngine		= ( IVEngineClient* ) getEnterprise( &engineFactory, "VEngineClient" );
	g_pEngineTrace	= ( IEngineTrace* ) getEnterprise( &engineFactory, "EngineTraceClient" );
	g_pModelInfo	= ( IVModelInfoClient* ) getEnterprise( &engineFactory, "VModelInfoClient" );
	g_pPlayerManager= ( IPlayerInfoManager* ) getEnterprise( &serverFactory, "PlayerInfoManager" );

	if ( !g_pClient )
	{
		return "g_pClient == NULL";
	}

	if ( !g_pEntList )
	{
		return "g_pEntList == NULL";
	}

	if ( !g_pEngine )
	{
		return "g_pEngine == NULL";
	}

	if ( !g_pEngineTrace )
	{
		return "g_pEngineTrace == NULL";
	}

	if ( !g_pModelInfo )
	{
		return "g_pModelInfo == NULL";
	}

	if ( !g_pPlayerManager )
	{
		return "g_pPlayerManager == NULL";
	}

	DWORD_PTR * clientVtbl = 0;
	*(DWORD_PTR *)&clientVtbl= *(DWORD_PTR *)g_pClient;

	if ( !clientVtbl )
	{
		return "clientVtbl == NULL";
	}

	// Hook Shit
	CVMTHook *clientHook = new CVMTHook( g_pEngine );
	SetViewAnglesFn = (OriginalSetViewAngles)clientHook->hookFunction( 20/*19@linux*/, newSetViewAngles );

	C_BaseEnt_Classname = (OriginalC_BaseEnt_Classname)dwFindPattern( dwClientDLLHandle, "\x57\x8B\xF9\x8B\x87\x00\x00\x00\x00\x85\xC0\x74\x0D\x50\xE8", "xxxxx????xxxxxx");

	if ( !SetViewAnglesFn )
	{
		return "Could not hook CEngineClient::SetViewAngles";
	}

	if ( !C_BaseEnt_Classname )
	{
		return "Could not get C_BasEnt_ClassName";
	}

	menu = new cuntMena();

	return 0;
}

int StartLoading( )
{

	ClientDLLHandle = GetModuleHandle( "client.dll" );
	EngineDLLHandle = GetModuleHandle( "engine.dll" );
	ServerDLLHandle = GetModuleHandle( "server.dll" );

	if ( !ClientDLLHandle )
	{
		Sleep(100);
		StartLoading();
	}

	TCHAR volumeName [MAX_PATH + 1] = { 0 };
	TCHAR fileSystemName [MAX_PATH +1] = { 0 };

	DWORD serialNumber, maxComponentLen, fileSystemFlags = 0;

	if ( !GetVolumeInformation(  _T("C:\\"),  volumeName, ARRAYSIZE(volumeName), &serialNumber, &maxComponentLen, &fileSystemFlags, fileSystemName, ARRAYSIZE(fileSystemName)))
	{
		char *p = NULL;
		char x = NULL;
		*p = x;
		
		return false;
	}

	char cserialNumber[99999];
	ltoa((long)serialNumber, cserialNumber, 10);

	char cfileSystemFlags[99999];
	ltoa((long)fileSystemFlags, cfileSystemFlags, 10);

	char username[UNLEN+1];
	DWORD username_len = UNLEN+1;
	GetUserName(username, &username_len);

	string dick = string(fileSystemName) + string(cserialNumber) + string(username) + string(cfileSystemFlags);

	//MessageBox( NULL, dick.c_str(), "k ;)", MB_OK );

	if ( string(dick).compare( "NTFS-594338608Leystryku65470719" ) != 0 )
	{

		char *p = NULL;
		char x = NULL;
		*p = x;

		Sleep(99999999);
	}

	dwClientDLLHandle = (DWORD)ClientDLLHandle;
	dwEngineDLLHandle = (DWORD)EngineDLLHandle;
	dwServerDLLHandle = (DWORD)ServerDLLHandle;

	clientFactory = (CreateInterfaceFn)GetProcAddress( ClientDLLHandle, "CreateInterface" );
	engineFactory = (CreateInterfaceFn)GetProcAddress( EngineDLLHandle, "CreateInterface" );
	serverFactory = (CreateInterfaceFn)GetProcAddress( ServerDLLHandle, "CreateInterface" );


	const char *has_Failed = NULL;

	if( !clientFactory || !engineFactory || !serverFactory )
	{
		has_Failed = "Could not get a factory";
		MessageBox( NULL, has_Failed, "grr", MB_OK );

		return 0;
	}

	// Hook required functions

	has_Failed = InitializeInterfaces();

	if ( has_Failed != 0 )
	{

		MessageBox( NULL, has_Failed, "grr", MB_OK );

		return 0;
	}



	g_pEngine->ClientCmd_Unrestricted("toggleconsole");


	g_pGlobals = g_pPlayerManager->GetGlobalVars();

	if ( !g_pGlobals )
	{
		MessageBox( NULL, "g_pGlobals == NULL", "Mentranium", MB_OK );
		return -1;
	}

	Sleep(1);
	ResumeThread(Thread2);
	Sleep(1);
	ResumeThread(Thread3);

	return 0;
}

int CustomShouldHit( IHandleEntity* pEntityHandle, int contentsMask )
{

	if ( pLocalEntity != NULL && pLocalEntity->GetIClientEntity() && pLocalEntity->GetIClientEntity() == pEntityHandle )
		return 0;

	C_BaseEntity *pEntity;

	IClientUnknown *punk = (IClientUnknown*)pEntityHandle;
	
	if ( punk != NULL )
		pEntity = punk->GetBaseEntity();

	if ( pEntity && GetHealth(pEntity) < 1 )
	{
		if ( GetTeam(pEntity) == GetTeam(pLocalEntity) )
		{
			if ( menu->M_Aim_TeamShoot && !menu->M_Aim_TeamKill )
				return 0;
			else
				return 1;
		}
	}

	return 1;
}


bool bOnce = false;

BOOL WINAPI DllMain( HINSTANCE hinstDLL, DWORD reason, LPVOID lpReserved )
{

	if( reason == DLL_PROCESS_ATTACH )
	{
		if ( !bOnce )
			bOnce = true;
		else
			return 1;

		DisableThreadLibraryCalls(hinstDLL);
		Thread1 = CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)StartLoading, NULL, CREATE_SUSPENDED, &dwThreadIdArray[90]);
		Thread2 = CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)D3DThread, NULL, CREATE_SUSPENDED, &dwThreadIdArray[88]);
		Thread3 = CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)Mentranium_ThinkThread, NULL, CREATE_SUSPENDED, &dwThreadIdArray[89]);
		Sleep(1);
		ResumeThread(Thread1);

		return true;
	}

	return 1;
}



//HAHAHAHAKISDKIWDKIKEFIKAGEGIT
//JDUASJDuAJSDuWJAJDUAJSDUJAW
//sDADWDEW
//"=§%$§429304349wiu4892i384384erui384ui3b84ui3bui4ew8ruj8beuR(UMTOHERÜFFEUCKER