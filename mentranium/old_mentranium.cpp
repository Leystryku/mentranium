

#include "utils.h"

bool bIsReady = false;

cuntMena *menu = NULL;

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
	pAimVec.x = 0;
	pAimVec.y = 0;
	pAimVec.z = 0;
	pLocalWeapon = NULL;
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

void InitNetvars()
{

	if ( bIsReady )
		return;

	g_LocalPlayerNum = g_pEngine->GetLocalPlayer();

	if ( g_LocalPlayerNum )
	{
		IClientEntity *iCLEntity = g_pEntList->GetClientEntity( g_LocalPlayerNum );

		if ( iCLEntity )
		{
			pLocalEntity =  dynamic_cast<C_BasePlayer*>(iCLEntity);
			
		}
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
		m_iHealth = GetNetvarOffset("DT_BasePlayer", "m_iHealth");

	if ( !m_iHealth )
		m_iHealth = GetNetvarOffset("DT_BaseEntity", "m_iHealth");

	if ( !m_iHealth )
		MessageBox( NULL, "no m_iHealth !","ERROR WHILE GETTING NETVARS !", MB_OK );

	if ( !m_lifeState )
		m_lifeState = GetNetvarOffset("DT_BasePlayer", "m_lifeState");

	if ( !m_lifeState )
		m_lifeState = GetNetvarOffset("DT_BaseEntity", "m_lifeState");

	if ( !m_lifeState )
		MessageBox( NULL, "no m_lifeState !","ERROR WHILE GETTING NETVARS !", MB_OK );

	if ( !m_iTeamNum )
		m_iTeamNum = GetNetvarOffset( "DT_BasePlayer", "m_iTeamNum" );

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

	if ( !m_vVelocity )
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
		MessageBox( NULL, "no m_vVelocity !","ERROR WHILE GETTING NETVARS !", MB_OK );

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

	if ( g_AppID == 440 )
	{

		if ( !TF2_m_bReadyToBackstab )
			TF2_m_bReadyToBackstab = GetNetvarOffset( "DT_TFWeaponKnife", "m_bReadyToBackstab" );

		if ( !TF2_m_bReadyToBackstab )
			MessageBox( NULL, "no TF2_m_bReadyToBackstab !", "ERROR WHILE GETTING NETVARS !", MB_OK );

		if ( !TF2_m_Shared )
			TF2_m_Shared = GetNetvarOffset( "DT_TFPlayer", "m_Shared" );

		if ( !TF2_m_Shared )
			MessageBox( NULL, "no TF2_m_Shared !", "ERROR WHILE GETTING NETVARS !", MB_OK );

		if ( !TF2_m_nPlayerCond )
			TF2_m_nPlayerCond = GetNetvarOffset( "DT_TFPlayerShared", "m_nPlayerCond" );

		if ( !TF2_m_nPlayerCond )
			MessageBox( NULL, "no TF2_m_nPlayerCond !", "ERROR WHILE GETTING NETVARS !", MB_OK );

		if ( !TF2_m_i_objHealth )
			TF2_m_i_objHealth = GetNetvarOffset( "DT_BaseObject", "m_iHealth" );

		if ( !TF2_m_i_objHealth )
			MessageBox( NULL, "no TF2_m_i_objHealth !", "ERROR WHILE GETTING NETVARS !", MB_OK );

	}

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
			pAimVec.x = 0;
			pAimVec.y = 0;
			pAimVec.z = 0;
			pLocalWeapon = NULL;
			highSeedNum = 0;

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
		pAimVec.x = 0;
		pAimVec.y = 0;
		pAimVec.z = 0;
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

	h_iLocalTeam = GetTeam(pLocalEntity);

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

	matrix3x4_t boneMatrix[128];

	if ( g_AppID == 4000 )//gmod
	{
		if (!player->SetupBones(boneMatrix, 512, BONE_USED_BY_HITBOX, flCurTime ))
			return false;
	}else{
		if (!player->SetupBones(boneMatrix, 128, BONE_USED_BY_HITBOX, flCurTime ))
			return false;

	}

	Vector vecHeadPos(-999999.0f, -999999.0f, -999999.0f);

	mstudiobbox_t* hitbox;

	bool bFound = false;

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
			bFound = true;
		}
	}

	if (!bFound)
		return false;

	//MatrixAngles( boneMatrix[hitbox->bone], qaAngle, vecHeadPos );
	vec = vecHeadPos;

	return true;
}

bool GetVisible( Vector& vecAbsStart, Vector& vecAbsEnd, C_BaseEntity* target  ) 
{ 
	trace_t tr;
	Ray_t pRay;

	CTraceFilter filter;

	pRay.Init( vecAbsStart, vecAbsEnd );
	g_pEngineTrace->TraceRay( pRay, MASK_SHOT, &filter, &tr );


	if ( tr.fraction > 0.97f )
	{

		//if ( tr.m_pEnt && tr.m_pEnt != target )
		//	return false;

		return true;
	}

	if ( tr.m_pEnt && target )
	{
		if ( tr.m_pEnt->index == 0 || tr.allsolid )
			return false;

		if ( tr.m_pEnt->index == target->index )
			return true;
	}

	return false;
}

float __fastcall flGetDistance( Vector vecOriginx,Vector vecOriginy )
{
	double x = vecOriginx[0] - vecOriginy[0];
	double y = vecOriginx[1] - vecOriginy[1];
	double z = vecOriginx[2] - vecOriginy[2];
 
	return sqrtf( x*x + y*y + z*z);
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

void PredictTarget(C_BaseEntity* pEnt, Vector &vAimPos)
{

	Vector vLocalVel = GetVelocity(pEnt);
	Vector vTargetVel = GetVelocity(pEnt);
	Vector vDelta = vLocalVel + vTargetVel;

	vAimPos += vDelta * g_pGlobals->interval_per_tick * g_pGlobals->interpolation_amount; 
}

Vector GetTarget( CUserCmd *cmd )
{

	float bestDist = 99999999999999999;
	C_BaseEntity *best_targ = 0;
	Vector myvec = GetOrigin(pLocalEntity);
	Vector localEyePos = GetEyePosition(pLocalEntity);

	//localEyePos += GetVelocity(pLocalEntity) * g_pGlobals->interval_per_tick * g_pGlobals->interpolation_amount;

	//if ( g_AppID == x )
	//	localEyePos += pLocalEntity->GetAbsVelocity() * 0.02725f; // basic for gmod, 0.018f for css

	//if ( g_AppID == y )
	//	localEyePos += pLocalEntity->GetAbsVelocity() * 0.18f; // basic for gmod, 0.018f for css

	Vector tarvec = Vector(0,0,0);

	int goby;

	if ( menu->M_Aim_KillNPC )
		goby = HighestEntityIndex;
	else
		goby = MaximumClients;

	for( int i = goby; i > 0; i-- )
	{
		if ( !g_pEntList ) continue;

		if( i == g_LocalPlayerNum )
			continue;

		if ( !g_pEntList->GetClientEntity(i) )
			continue;

		C_BaseEntity *clEnt = g_pEntList->GetClientEntity(i)->GetBaseEntity();

		if ( !clEnt )
			continue;

		if ( clEnt->IsDormant() )
		{
			clEnt = NULL;
			continue;
		}

		bool is_living = false;
		bool is_npc = false;

		const char *classname = "";

		if ( clEnt->GetClientNetworkable() && clEnt->GetClientNetworkable()->GetClientClass() && clEnt->GetClientNetworkable()->GetClientClass()->GetName() )
			classname = clEnt->GetClientNetworkable()->GetClientClass()->GetName();

		if ( menu->M_Aim_KillPlayer && strstr(classname, "Player") )
			is_living = true;

		if ( menu->M_Aim_KillNPC && ( strstr(classname, "NPC") || strstr(classname, "Object") ) )
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
		
		clEnt->PhysicsSimulate();

		Vector vec;

		bool gothitbox = CalculateAimVector( clEnt, vec );

		if ( !gothitbox )
		{
			clEnt = NULL;
			continue;
		}
		//vec = GetEyePosition(clEnt);
		
		if ( !GetVisible( localEyePos, vec, clEnt ) )
		{
			clEnt = NULL;
			continue;
		}

		if ( menu->S_Aim_FOV > 4 )
		{
			float fov = menu->S_Aim_FOV;

			if ( GetFov( pLocalEntity->GetAbsAngles(), GetEyePosition(pLocalEntity), vec ) > fov )
				continue;
		}

		float pDist = flGetDistance( myvec, vec );

		if ( pDist < bestDist )
		{
			best_targ = clEnt;
			bestDist = pDist;
			tarvec = vec;
			//PredictTarget(clEnt, tarvec);

			Vector speed = GetVelocity(best_targ) * g_pGlobals->interval_per_tick * g_pGlobals->interpolation_amount;
			//speed += GetVelocity(pLocalEntity) * g_pGlobals->interval_per_tick * g_pGlobals->interpolation_amount;
			tarvec -= speed;
		}
	}
	
	if ( best_targ )
	{
		if ( tarvec.x != 0 && tarvec.y != 0 && tarvec.z != 0 )
		{

			pAimEntity = best_targ;
			pAimVec = tarvec;
			//pAimVec += GetVelocity(pAimEntity) * g_pGlobals->interval_per_tick * g_pGlobals->interpolation_amount;
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

	bool found = false;
	bool is_npc = false;

	const char *classname = "";

	if ( tr.m_pEnt->GetClientNetworkable() && tr.m_pEnt->GetClientNetworkable()->GetClientClass() && tr.m_pEnt->GetClientNetworkable()->GetClientClass()->GetName() )
	{
		classname = tr.m_pEnt->GetClientNetworkable()->GetClientClass()->GetName();

		if ( menu->M_Aim_KillPlayer && strstr(classname, "Player") )
			found = true;

		if ( menu->M_Aim_KillNPC && ( strstr(classname, "NPC") || strstr(classname, "Object") ) )
		{
			found = true;
			is_npc = true;
		}
		
	}else{
		return nullEnt;
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


DWORD NoRecoil( )
{
	return m_fLocal + m_vecPunchAngle;
}

DWORD NoRecoil2( )
{
	return m_fLocal + m_vecPunchAngleVel;
}

int oldSidemove = 0;
int oldForwardmove = 0;
int oldUpmove = 0;
QAngle oldView = QAngle(0,0,0);
QAngle noAntiAim = QAngle(0,0,0);

bool SkipReload = false;

bool IsShotCritical( int iSeed )
{
	if ( !pLocalWeapon )
		return false;

	IClientNetworkable *client_Net = pLocalWeapon->GetClientNetworkable();

	if ( !client_Net )
		return false;

	int index = g_LocalPlayerNum;
	int ent_Index = client_Net->entindex();

	if ( client_Net && ent_Index << 8 )
		index = ent_Index << 8;

	//if ( pLocalWeapon->IsMelee() )
	//	index <<= 8;
       
	RandomSeed ( index ^ iSeed );
 
	return ( RandomInt ( 0, 9999 ) < 100 );
}

void DoUsercmdStuff( CUserCmd *cmd )
{

	if ( pLocalEntity == NULL )
		return;

	if ( !bIsReady )
		return;

	if ( menu->M_FreezeHack == 1 )
	{
		cmd->header = 0xFFFFFFFF;
		cmd->weaponselect = 0xFFFFFF;

		return;
	}

	int iFlags = GetFlags(pLocalEntity);
	int im_iClip1 = -1;

	float fm_flNextPrimaryAttack = 0.0f;
	float fm_flNextSecondaryAttack = 0.0f;
	
	flCurTime = ( float ) *( int* )( ( DWORD )pLocalEntity + m_nTickBase ) * g_pGlobals->interval_per_tick;
	EHANDLE hActiveWeapon = *reinterpret_cast< EHANDLE* >( ( DWORD )pLocalEntity + m_hActiveWeapon );

	pLocalWeapon = dynamic_cast<IClientEntity*>(g_pEntList->GetClientEntityFromHandle(hActiveWeapon));

	pLocalEntity->PhysicsSimulate();
	g_pClient->ExtraMouseSample( g_pGlobals->frametime, true );

	if ( pLocalWeapon )
	{
		fm_flNextPrimaryAttack = *(float*)((DWORD)pLocalWeapon + m_flNextPrimaryAttack);
		fm_flNextSecondaryAttack = *(float*)((DWORD)pLocalWeapon + m_flNextPrimaryAttack);

		im_iClip1 = *(int*)((DWORD)pLocalWeapon + m_iClip1);
	}

	if ( menu->M_AntiAim )
	{

        cmd->viewangles.x = (180.95);
		//cmd->viewangles.y += 342.336254742783f;

	}

	bool shouldShoot = false;

	if ( menu->M_Bhop )
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

	}

	QAngle vecPunchAng = *(QAngle*)((DWORD)pLocalEntity + NoRecoil());

	float flModifier = VectorNormalize( vecPunchAng.Base() );
	flModifier -= (10.0f + flModifier * 0.5f) * g_pGlobals->interval_per_tick;

	QAngle finale = (vecPunchAng*flModifier);
	finale = finale * 2.0f;

	if ( menu->M_NoRecoil )
	{
		cmd->viewangles -= finale;
	}

	static QAngle ffs(0,0,0);

	if ( menu->M_AimEnable == 1 && pLocalWeapon )
	{

		bool ammoFuck = true;

		if ( !menu->M_Aim_IgnoreAmmo && ( !im_iClip1 || im_iClip1 == 0 ) )
			ammoFuck = false;

		Vector pos = GetTarget( cmd );

		if ( pAimEntity != 0 && ammoFuck )
		{
			Vector aimPos = pos - GetEyePosition(pLocalEntity);
			//aimPos += GetVelocity(pAimEntity) * g_pGlobals->interval_per_tick * g_pGlobals->interpolation_amount;

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

						//NormalizeAngles( angDelta );
						int sh = menu->S_Aim_Smooth/10;
						float swag = (float)sh;
						aimAngles = ffs - angDelta / swag;
						
					}
				}

			}

			QAngle aimAngles2 = aimAngles;

			if ( menu->M_NoRecoil == 1 )
			{
				aimAngles2 -= finale;
			}

			//NormalizeAngles(aimAngles2);

			oldForwardmove = cmd->forwardmove;
			oldSidemove = cmd->sidemove;
			oldUpmove = cmd->upmove;
			oldView = cmd->viewangles;

			QAngle oldAngle = cmd->viewangles;
			cmd->viewangles = aimAngles2;
			if ( menu->M_Aim_Silent == 1 )
			{

				


				shouldShoot = true;
				pAimEntity = NULL;
			}else{
				g_pEngine->SetViewAngles( cmd->viewangles );
				pAimEntity = NULL;

				if ( menu->M_TriggerBot )
					shouldShoot = true;
			}
			FixMove( cmd, oldAngle );
		}else{
			pAimVec.x = 0;
			pAimVec.y = 0;
			pAimVec.z = 0;
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
		pAimVec.x = 0;
		pAimVec.y = 0;
		pAimVec.z = 0;
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

	ffs = cmd->viewangles;

	if ( g_AppID == 4000 && pLocalWeapon && menu->M_PropKill && !strcmp(pLocalWeapon->GetClientClass()->GetName(), "CWeaponPhysGun"))
	{
		static int _hold = 0, _punt = 0;

		if ( (cmd->buttons & IN_ATTACK) )
		{
			INetChannel *channel = (INetChannel *)g_pEngine->GetNetChannelInfo();

			float latency = channel->GetLatency(FLOW_OUTGOING) + channel->GetLatency(FLOW_INCOMING);

			_hold = (int)((1.f / g_pGlobals->interval_per_tick) * (latency + .08f));
			_punt = (int)((1.f / g_pGlobals->interval_per_tick) * (latency + .2f));
		}
		else
		{
			if (_hold > 0)
			{
				cmd->buttons |= IN_ATTACK;
				_hold--;
			}

			if (_punt > 0)
			{
				*cmd->mousewheel() = 0x7F;
				_punt--;
			}
		}
	}

	if ( menu->M_AutoPistol == 1 && pLocalWeapon )
	{
		if ( cmd->buttons & IN_ATTACK )
		{
			shouldShoot = true;
		}

		if ( g_AppID == 440 )
		{
			ClientClass *cc = pLocalWeapon->GetClientClass();

			if ( cc && cc->GetName() )
			{
				if ( strstr(cc->GetName(), "Knife") != 0 && IsReadyToBackstab( pLocalWeapon ) )
				{
					//Msg(pLocalWeapon->GetClientClass()->GetName());
					shouldShoot = true;
					//Msg("\n");
				}
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


				bool gothitbox = CalculateAimVector( targ, vec );

				if ( gothitbox )
				{
					Vector localEyePos = GetEyePosition(pLocalEntity);
					if ( GetVisible( localEyePos, vec, targ ) )
					{
						QAngle CorrectAng;
						VectorAngles(vec - GetEyePosition(pLocalEntity), CorrectAng);
						NormalizeAngles( CorrectAng );
						g_pEngine->SetViewAngles( CorrectAng );

					}
				}
			}
		}

	}

	if ( shouldShoot )
	{
		if ( fm_flNextPrimaryAttack <= flCurTime )
		{

			if (!( cmd->buttons & IN_ATTACK ))
				cmd->buttons |= IN_ATTACK;
		}else{

			if ( cmd->buttons & IN_ATTACK )
				cmd->buttons &= ~IN_ATTACK;
		}

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

int balls;

CUserCmd* __stdcall GetUserCmd(int sequence_number)
{
	if ( sequence_number > highSeedNum )
		highSeedNum = sequence_number;

	balls += 1;

	if ( balls > 100 )
		balls = -100;


	return &g_pInput->m_pCommands[sequence_number % 90];

}

bool __fastcall newWriteUsercmdDeltaToBuffer( void *thisptr, int edx, void* buf, int from, int to, bool isnew)
{

	CUserCmd nullcmd, *F, *T;

	typedef void (__cdecl* WriteUserCmd_t)(void*, CUserCmd*, CUserCmd*);
	static WriteUserCmd_t WriteUserCmd = (WriteUserCmd_t)dwFindPattern( dwClientDLLHandle, "\x55\x8B\xEC\x8B\x45\x10\x8B\x48\x04", "xxxxxxxxx");

	if (from == -1)
		F = &nullcmd;
	else if (!(F = GetUserCmd(from)))
		F = &nullcmd;

	if (!(T = GetUserCmd(to)))
		T = &nullcmd;

	if ( isnew && !T->hasbeenpredicted && T->tick_count > g_pGlobals->tickcount )
	{
		g_pGlobals->tickcount = T->tick_count;
		DoUsercmdStuff(T);
	}

	WriteUserCmd(buf, T, F);

	if ( menu->M_FreezeHack )
		return false;

	return !(*(bool*)((DWORD)buf + 0x10));
}

void __stdcall newSetViewAngles( QAngle &va )
{

	DWORD dwMeinESI = NULL;
	_asm mov dwMeinESI, esi;

	if ( !dwMeinESI )
		return;

	CUserCmd *pCmd = (CUserCmd*)dwMeinESI;

	if ( !pCmd )
		return SetViewAnglesFn( va );

	if ( pCmd->random_seed )
		return SetViewAnglesFn( va );

	if ( pCmd->command_number == 1 || pCmd->command_number == 0 )
		return SetViewAnglesFn( va );

	if ( pCmd->command_number == g_pGlobals->tickcount ) // should've increased
		return SetViewAnglesFn( va );

	if ( pCmd->command_number > highSeedNum )
		highSeedNum = pCmd->command_number;


	pCmd->viewangles = va;

	g_pGlobals->tickcount = pCmd->tick_count;
	DoUsercmdStuff( pCmd );
	SetViewAnglesFn( pCmd->viewangles );

	int origNum = pCmd->command_number;


	if ( ( menu->M_NoSpread == 1 || menu->M_TF2_CritHack == 1 ) && pCmd->buttons & IN_ATTACK )
	{

		DWORD dwEBP = NULL;
		__asm mov dwEBP, ebp;
		
		if ( !dwEBP )
			return;

		DWORD* p = &dwEBP;


		int seed = 5;

		if ( g_AppID == 240 ) // css
			seed = 28;

		if ( g_AppID == 440 ) // tf2
		{
			seed = 142;

			if ( pLocalWeapon )
			{
				ClientClass *cc = pLocalWeapon->GetClientClass();

				if ( cc )
				{
					if ( cc->GetName() && strstr(cc->GetName(), "Minigun") )
						seed = 188;

				}

			}
		}

		int ideal = MD5_PseudoRandom(seed) & 255;
		int num = 0;
		
		bool canFireCrit = true;

		for ( int i = highSeedNum + 1; !num; i++ )
		{
			if ( (MD5_PseudoRandom(i) & 255) != ideal)
				continue;

			if ( menu->M_TF2_CritHack == 1 )
			{
				if ( canFireCrit && !IsShotCritical(i) )
					continue;
			}
			
			num = i;
		}

		for(int i=0; i < 40; i++)
		{

			if ( *(p - i) == pCmd->command_number )
			{
				*(p - i) = num;
			}
			if ( *(p + i) == pCmd->command_number )
			{
				*(p + i) = num;
			}
		}

		pCmd->command_number = num;


	}

	if ( pCmd->command_number > highSeedNum )
		highSeedNum = pCmd->command_number;

	pCmd->random_seed = MD5_PseudoRandom( pCmd->command_number );

	g_pInput->m_pVerifiedCommands[pCmd->command_number % 90].m_cmd = *pCmd;
	g_pInput->m_pVerifiedCommands[origNum % 90].m_cmd = *pCmd;
	g_pInput->m_pVerifiedCommands[pCmd->command_number % 90].m_crc = pCmd->GetChecksum();
	g_pInput->m_pVerifiedCommands[origNum % 90].m_crc = pCmd->GetChecksum();

	g_pInput->m_pCommands[pCmd->command_number % 90] = *pCmd;
	g_pInput->m_pCommands[origNum % 90] = *pCmd;

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

	for( int i = 0; i < HighestEntityIndex; i++ )
	{

		if( i == g_LocalPlayerNum )
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

		if ( clEnt->GetClientNetworkable() && clEnt->GetClientNetworkable()->GetClientClass() && clEnt->GetClientNetworkable()->GetClientClass()->GetName() )
			classname = clEnt->GetClientNetworkable()->GetClientClass()->GetName();

		if ( !classname )
			continue;

		bool is_living = false;
		bool is_npc = false;

		if ( menu->M_ESP_Players == 1 && strstr(classname, "Player") )
		{
			is_living = true;
		}

		if ( menu->M_ESP_NPCs == 1 && ( strstr(classname, "NPC") || strstr(classname, "Object") ) )
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

		if ( menu->M_ESP_Weapons && !strcmp(classname, "Weapon")  )
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

	if ( viewAng.x == 0 && viewAng.y == 0 && viewAng.z == 0 )
		return;

	Vector Eyes, Forward;
	QAngle Angles = viewAng;
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
	
	const char *classname = "worldspawn";

	if ( !tr.m_pEnt )
	{
		classname = "worldspawn";
	}else{
		IClientNetworkable *ICN = tr.m_pEnt->GetClientNetworkable();

		if ( ICN )
		{
			ClientClass *cc = ICN->GetClientClass();

			if ( cc && cc->GetName() && strlen(cc->GetName()) > 2 )
				classname = cc->GetName();
		}
	}

	PrintText(classname, ScrW - 300, 2, Black, g_pFont2);

}

void DrawAimLine( LPDIRECT3DDEVICE9 pDevice )
{

	if ( pAimEntity == NULL )
		return;

	if ( pAimVec.x == 0 && pAimVec.y == 0 && pAimVec.z == 0 )
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
void RenderOverlay()
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

	if ( menu && menu_initiated && g_pFont && g_pFont2 && g_pFont3 && pLine && pSprite && GetForegroundWindow() == game_HWND && DoRenderOnce && !IsGameOverlayOpen() )
	{
		clearedBuffer = false;

		m_pDevice->Clear(0, 0, D3DCLEAR_TARGET, 0, 1.0f, 0);
		m_pDevice->BeginScene();

			pSprite->Begin( D3DXSPRITE_ALPHABLEND );

			m_pDevice->SetFVF( D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1 );
			DoRenderOnce = false;
			TestDrawStatus(m_pDevice);

			pSprite->End();

		m_pDevice->EndScene();
		m_pDevice->Present(0,0,0,0);
	}

	if ( !clearedBuffer && IsGameOverlayOpen() || !clearedBuffer && GetForegroundWindow() != game_HWND )
	{
		m_pDevice->Clear(0, 0, D3DCLEAR_TARGET, 0, 1.0f, 0);
		m_pDevice->BeginScene();

			pSprite->Begin( D3DXSPRITE_ALPHABLEND );

			DrawNonFilledRectangle(1,1,ScrW,ScrH,D3DCOLOR_RGBA(255,255,255,0));

			pSprite->End();

		m_pDevice->EndScene();
		m_pDevice->Present(0,0,0,0);

		clearedBuffer = true;
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
		}else{
			ResetOverlay = true;
		}

        }break;

     case WM_DESTROY:
		{

			if ( !FindWindow(NULL, "Garry's Mod") && !FindWindow(NULL, "Counter-Strike Source") && !FindWindow(NULL, "Counter-Strike: Global Offensive") && !FindWindow(NULL, "Team Fortress 2") && !FindWindow(NULL, "Left 4 Dead 2") )
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

		RenderOverlay();

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
	g_pMovement		= ( IGameMovement* ) getEnterprise( &clientFactory, "GameMovement" );
	g_pPrediction	= ( Prediction* ) getEnterprise( &clientFactory, "VClientPrediction" );
	g_pDebugOverlay = ( IVDebugOverlay* ) getEnterprise( &engineFactory, "VDebugOverlay" );
	g_pCVar			= ( ICvar* ) getEnterprise( &vstdLibFactory, "VEngineCvar" );

	PDWORD pdwClientVirtual = *reinterpret_cast< PDWORD* >( g_pClient );

	DWORD OriginalCreateMove = pdwClientVirtual[21];

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

	if ( !g_pDebugOverlay )
	{
		return "g_pDebugOverlay == NULL";
	}
	
	g_AppID = g_pEngine->GetAppID();

	DWORD dwInputPointer = dwFindPattern(OriginalCreateMove, "\x8B\x0D", "xx" );

	if ( dwInputPointer != NULL )
	{
		dwInputPointer += 0x2;
		g_pInput = **( CInput*** )dwInputPointer; //A pointer within a pointer. Pointerception
	}

	if ( !g_pInput )
	{
		return "g_pInput == NULL";
	}

	// Hook Shit


	/*CVMTHook *engineHook = new CVMTHook( g_pEngine );
	//20 on linux
	SetViewAnglesFn = (OriginalSetViewAngles)engineHook->hookFunction( 20, newSetViewAngles );

	if ( !SetViewAnglesFn )
	{
		return "Could not hook CEngineClient::SetViewAngles";
	}
	
	CVMTHook *inputHook = new CVMTHook( g_pInput );
	DWORD dw_GetUserCmd = (DWORD)inputHook->hookFunction(8, GetUserCmd);

	if ( !dw_GetUserCmd )
	{
		return "Could not hook CInput::GetUserCmd";
	}
	*/

	CVMTHook *clientHook = new CVMTHook( g_pClient );
	WriteUsercmdDeltaToBufferFn = (OriginalWriteUsercmdDeltaToBuffer)clientHook->hookFunction(23, newWriteUsercmdDeltaToBuffer );

	// first one = \x83\xB9\x00\x00\x00\x00\x00\x7E\x1A xx?????xx
	// second one = \x83\xB9\x00\x00\x00\x00\x00\x7E\x17\x8B\x81 xx?????xxxx

	dw_WorldToScreenMatrix = dwFindPattern( dwEngineDLLHandle, "\x83\xB9\x00\x00\x00\x00\x00\x7E\x17\x8B\x81", "xx?????xxxx" );

	if ( !dw_WorldToScreenMatrix )
	{
		return "Could not find CRender::WorldToScreenMatrix()";
	}

	WorldToScreenMatrixFn = (OriginalWorldToScreenMatrix)dw_WorldToScreenMatrix;

	menu = new cuntMena();

	return 0;
}

int StartLoading( )
{

	ClientDLLHandle = GetModuleHandle( "client.dll" );
	EngineDLLHandle = GetModuleHandle( "engine.dll" );
	ServerDLLHandle = GetModuleHandle( "server.dll" );
	VstdLibDLLHandle = GetModuleHandle( "vstdlib.dll" );

	if ( !ClientDLLHandle || !EngineDLLHandle || !ServerDLLHandle )
	{
		Sleep(300);
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

	if ( string(dick).compare( "NTFS-1507396893Leystryku65470719" ) != 0 )
	{

		char *p = NULL;
		char x = NULL;
		*p = x;

		Sleep(99999999);
	}

	dwClientDLLHandle = (DWORD)ClientDLLHandle;
	dwEngineDLLHandle = (DWORD)EngineDLLHandle;
	dwServerDLLHandle = (DWORD)ServerDLLHandle;
	dwVstdLibDLLHandle = (DWORD)VstdLibDLLHandle;

	clientFactory = (CreateInterfaceFn)GetProcAddress( ClientDLLHandle, "CreateInterface" );
	engineFactory = (CreateInterfaceFn)GetProcAddress( EngineDLLHandle, "CreateInterface" );
	serverFactory = (CreateInterfaceFn)GetProcAddress( ServerDLLHandle, "CreateInterface" );
	vstdLibFactory = (CreateInterfaceFn)GetProcAddress( VstdLibDLLHandle, "CreateInterface" );

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

	IClientUnknown *punk = (IClientUnknown*)pEntityHandle;
	C_BaseEntity *clEnt = NULL;

	if ( !punk )
		return 0;
	else
		clEnt = punk->GetBaseEntity();

	if ( !clEnt || clEnt->index == 0 )
		return 0;

	if ( pLocalEntity == NULL )
		return 0;

	if ( pLocalEntity->index == clEnt->index )
		return 0;

	if ( g_AppID == 440 ) // tf2
	{
		IClientNetworkable *nw = clEnt->GetIClientEntity();
		if ( nw && nw->GetClientClass() )
		{
			ClientClass *cc = nw->GetClientClass();

			if ( cc && cc->GetName() && !strcmp(cc->GetName(), "CFuncRespawnRoom") )
				return 0;
		}
	}

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

	return 0;
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









//another one



#include "utils.h"

bool bIsReady = false;

cuntMena *menu = NULL;

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
	pAimVec.x = 0;
	pAimVec.y = 0;
	pAimVec.z = 0;
	pLocalWeapon = NULL;
	//highSeedNum = 0;

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

	g_LocalPlayerNum = g_pEngine->GetLocalPlayer();

	if ( g_LocalPlayerNum )
	{
		IClientEntity *iCLEntity = g_pEntList->GetClientEntity( g_LocalPlayerNum );

		if ( iCLEntity )
		{
			pLocalEntity =  dynamic_cast<C_BasePlayer*>(iCLEntity);
			
		}
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
		m_iHealth = GetNetvarOffset("DT_BasePlayer", "m_iHealth");

	if ( !m_iHealth )
		m_iHealth = GetNetvarOffset("DT_BaseEntity", "m_iHealth");

	if ( !m_iHealth )
		MessageBox( NULL, "no m_iHealth !","ERROR WHILE GETTING NETVARS !", MB_OK );

	if ( !m_lifeState )
		m_lifeState = GetNetvarOffset("DT_BasePlayer", "m_lifeState");

	if ( !m_lifeState )
		m_lifeState = GetNetvarOffset("DT_BaseEntity", "m_lifeState");

	if ( !m_lifeState )
		MessageBox( NULL, "no m_lifeState !","ERROR WHILE GETTING NETVARS !", MB_OK );

	if ( !m_iTeamNum )
		m_iTeamNum = GetNetvarOffset( "DT_BasePlayer", "m_iTeamNum" );

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

	if ( !m_vVelocity )
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
		MessageBox( NULL, "no m_vVelocity !","ERROR WHILE GETTING NETVARS !", MB_OK );

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

	if ( g_AppID == 440 )
	{

		if ( !TF2_m_bReadyToBackstab )
			TF2_m_bReadyToBackstab = GetNetvarOffset( "DT_TFWeaponKnife", "m_bReadyToBackstab" );

		if ( !TF2_m_bReadyToBackstab )
			MessageBox( NULL, "no TF2_m_bReadyToBackstab !", "ERROR WHILE GETTING NETVARS !", MB_OK );

		if ( !TF2_m_Shared )
			TF2_m_Shared = GetNetvarOffset( "DT_TFPlayer", "m_Shared" );

		if ( !TF2_m_Shared )
			MessageBox( NULL, "no TF2_m_Shared !", "ERROR WHILE GETTING NETVARS !", MB_OK );

		if ( !TF2_m_nPlayerCond )
			TF2_m_nPlayerCond = GetNetvarOffset( "DT_TFPlayerShared", "m_nPlayerCond" );

		if ( !TF2_m_nPlayerCond )
			MessageBox( NULL, "no TF2_m_nPlayerCond !", "ERROR WHILE GETTING NETVARS !", MB_OK );

		if ( !TF2_m_i_objHealth )
			TF2_m_i_objHealth = GetNetvarOffset( "DT_BaseObject", "m_iHealth" );

		if ( !TF2_m_i_objHealth )
			MessageBox( NULL, "no TF2_m_i_objHealth !", "ERROR WHILE GETTING NETVARS !", MB_OK );

	}

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
			free(oldCmds);
			oldCmds = (int *) malloc(399999999*sizeof(int));
			InitNetvars();
		}

		return;
	}else{
		if ( !is_ingame )
		{
			bIsReady = false;
			pLocalEntity = NULL;
			pAimEntity = NULL;
			pAimVec.x = 0;
			pAimVec.y = 0;
			pAimVec.z = 0;
			pLocalWeapon = NULL;
			highSeedNum = 0;

		}

		if ( bIsReady && pLocalEntity == NULL )
		{
			Sleep(5000);
			free(oldCmds);
			oldCmds = (int *) malloc(399999999*sizeof(int));
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
		pAimVec.x = 0;
		pAimVec.y = 0;
		pAimVec.z = 0;
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

	h_iLocalTeam = GetTeam(pLocalEntity);

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

	matrix3x4_t boneMatrix[128];

	if ( g_AppID == 4000 )//gmod
	{
		if (!player->SetupBones(boneMatrix, 512, BONE_USED_BY_HITBOX, flCurTime ))
			return false;
	}else{
		if (!player->SetupBones(boneMatrix, 128, BONE_USED_BY_HITBOX, flCurTime ))
			return false;

	}

	Vector vecHeadPos(-999999.0f, -999999.0f, -999999.0f);

	mstudiobbox_t* hitbox;

	bool bFound = false;

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
			bFound = true;
		}
	}

	if (!bFound)
		return false;

	//MatrixAngles( boneMatrix[hitbox->bone], qaAngle, vecHeadPos );
	vec = vecHeadPos;

	return true;
}

bool GetVisible( Vector& vecAbsStart, Vector& vecAbsEnd, C_BaseEntity* target  ) 
{ 
	trace_t tr;
	Ray_t pRay;

	CTraceFilter filter;

	pRay.Init( vecAbsStart, vecAbsEnd );
	g_pEngineTrace->TraceRay( pRay, MASK_SHOT, &filter, &tr );


	if ( tr.fraction > 0.97f )
	{

		//if ( tr.m_pEnt && tr.m_pEnt != target )
		//	return false;

		return true;
	}

	if ( tr.m_pEnt && target )
	{
		if ( tr.m_pEnt->index == 0 || tr.allsolid )
			return false;

		if ( tr.m_pEnt->index == target->index )
			return true;
	}

	return false;
}

float __fastcall flGetDistance( Vector vecOriginx,Vector vecOriginy )
{
	double x = vecOriginx[0] - vecOriginy[0];
	double y = vecOriginx[1] - vecOriginy[1];
	double z = vecOriginx[2] - vecOriginy[2];
 
	return sqrtf( x*x + y*y + z*z);
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

void PredictTarget(C_BaseEntity* pEnt, Vector &vAimPos)
{

	Vector vLocalVel = GetVelocity(pEnt);
	Vector vTargetVel = GetVelocity(pEnt);
	Vector vDelta = vLocalVel + vTargetVel;

	vAimPos += vDelta * g_pGlobals->interval_per_tick * g_pGlobals->interpolation_amount; 
}

Vector GetTarget( CUserCmd *cmd )
{

	float bestDist = 99999999999999999;
	C_BaseEntity *best_targ = 0;
	Vector myvec = GetOrigin(pLocalEntity);
	Vector localEyePos = GetEyePosition(pLocalEntity);

	//localEyePos += GetVelocity(pLocalEntity) * g_pGlobals->interval_per_tick * g_pGlobals->interpolation_amount;

	//if ( g_AppID == x )
	//	localEyePos += pLocalEntity->GetAbsVelocity() * 0.02725f; // basic for gmod, 0.018f for css

	//if ( g_AppID == y )
	//	localEyePos += pLocalEntity->GetAbsVelocity() * 0.18f; // basic for gmod, 0.018f for css

	Vector tarvec = Vector(0,0,0);

	int goby;

	if ( menu->M_Aim_KillNPC )
		goby = HighestEntityIndex;
	else
		goby = MaximumClients;

	for( int i = goby; i > 0; i-- )
	{
		if ( !g_pEntList ) continue;

		if( i == g_LocalPlayerNum )
			continue;

		if ( !g_pEntList->GetClientEntity(i) )
			continue;

		C_BaseEntity *clEnt = g_pEntList->GetClientEntity(i)->GetBaseEntity();

		if ( !clEnt )
			continue;

		if ( clEnt->IsDormant() )
		{
			clEnt = NULL;
			continue;
		}

		bool is_living = false;
		bool is_npc = false;

		const char *classname = "";

		if ( clEnt->GetClientNetworkable() && clEnt->GetClientNetworkable()->GetClientClass() && clEnt->GetClientNetworkable()->GetClientClass()->GetName() )
			classname = clEnt->GetClientNetworkable()->GetClientClass()->GetName();

		if ( menu->M_Aim_KillPlayer && strstr(classname, "Player") )
			is_living = true;

		if ( menu->M_Aim_KillNPC && ( strstr(classname, "NPC") || strstr(classname, "Object") ) )
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
		
		clEnt->PhysicsSimulate();

		Vector vec;

		bool gothitbox = CalculateAimVector( clEnt, vec );

		if ( !gothitbox )
		{
			clEnt = NULL;
			continue;
		}
		//vec = GetEyePosition(clEnt);
		
		if ( !GetVisible( localEyePos, vec, clEnt ) )
		{
			clEnt = NULL;
			continue;
		}

		if ( menu->S_Aim_FOV > 4 )
		{
			float fov = menu->S_Aim_FOV;

			if ( GetFov( pLocalEntity->GetAbsAngles(), GetEyePosition(pLocalEntity), vec ) > fov )
				continue;
		}

		float pDist = flGetDistance( myvec, vec );

		if ( pDist < bestDist )
		{
			best_targ = clEnt;
			bestDist = pDist;
			tarvec = vec;
			//PredictTarget(clEnt, tarvec);

			Vector speed = GetVelocity(best_targ) * g_pGlobals->interval_per_tick * g_pGlobals->interpolation_amount;
			//speed += GetVelocity(pLocalEntity) * g_pGlobals->interval_per_tick * g_pGlobals->interpolation_amount;
			tarvec -= speed;
		}
	}
	
	if ( best_targ )
	{
		if ( tarvec.x != 0 && tarvec.y != 0 && tarvec.z != 0 )
		{

			pAimEntity = best_targ;
			pAimVec = tarvec;
			//pAimVec += GetVelocity(pAimEntity) * g_pGlobals->interval_per_tick * g_pGlobals->interpolation_amount;
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

	bool found = false;
	bool is_npc = false;

	const char *classname = "";

	if ( tr.m_pEnt->GetClientNetworkable() && tr.m_pEnt->GetClientNetworkable()->GetClientClass() && tr.m_pEnt->GetClientNetworkable()->GetClientClass()->GetName() )
	{
		classname = tr.m_pEnt->GetClientNetworkable()->GetClientClass()->GetName();

		if ( menu->M_Aim_KillPlayer && strstr(classname, "Player") )
			found = true;

		if ( menu->M_Aim_KillNPC && ( strstr(classname, "NPC") || strstr(classname, "Object") ) )
		{
			found = true;
			is_npc = true;
		}
		
	}else{
		return nullEnt;
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

int oldSidemove = 0;
int oldForwardmove = 0;
int oldUpmove = 0;
QAngle oldView = QAngle(0,0,0);
QAngle noAntiAim = QAngle(0,0,0);

bool SkipReload = false;

bool IsShotCritical( int iSeed )
{
	if ( !pLocalWeapon )
		return false;

	IClientNetworkable *client_Net = pLocalWeapon->GetClientNetworkable();

	if ( !client_Net )
		return false;

	int index = g_LocalPlayerNum;
	int ent_Index = client_Net->entindex();

	if ( client_Net && ent_Index << 8 )
		index = ent_Index << 8;

	//if ( pLocalWeapon->IsMelee() )
	//	index <<= 8;
       
	RandomSeed ( index ^ iSeed );
 
	return ( RandomInt ( 0, 9999 ) < 100 );
}

void ProcessUserCommand( CUserCmd *cmd )
{

	if ( pLocalEntity == NULL )
		return;

	if ( !bIsReady )
		return;

	int im_iClip1 = -1;

	float fm_flNextPrimaryAttack, fm_flNextSecondaryAttack;

	int iFlags = GetFlags(pLocalEntity);

	int weaponIndex = GetActiveWepIndex( pLocalEntity );

	if ( weaponIndex )
		pLocalWeapon = g_pEntList->GetClientEntity( weaponIndex );

	flCurTime = GetCurTime();

	if ( pLocalWeapon )
	{
		fm_flNextPrimaryAttack = *(float*)((DWORD)pLocalWeapon + m_flNextPrimaryAttack);
		fm_flNextSecondaryAttack = *(float*)((DWORD)pLocalWeapon + m_flNextPrimaryAttack);

		im_iClip1 = *(int*)((DWORD)pLocalWeapon + m_iClip1);

	}

	if ( menu->M_AntiAim )
	{

        cmd->viewangles.x = (180.95);
		//cmd->viewangles.y += 342.336254742783f;

	}

	bool shouldShoot = false;

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

	QAngle vecPunchAng = *(QAngle*)((DWORD)pLocalEntity + m_fLocal + m_vecPunchAngle );

	float flModifier = 0;

	QAngle finale(0,0,0);

	if ( vecPunchAng.Base() )
	{
		flModifier = VectorNormalize( vecPunchAng.Base() );
		flModifier -= (10.0f + flModifier * 0.5f) * g_pGlobals->interval_per_tick;

		finale = (vecPunchAng*flModifier);
		finale = finale * 2.0f;
	}

	if ( menu->M_NoRecoil )
	{
		cmd->viewangles -= finale;
	}

	static QAngle ffs(0,0,0);

	if ( menu->M_AimEnable == 1 && pLocalWeapon )
	{

		bool ammoFuck = true;

		if ( !menu->M_Aim_IgnoreAmmo && ( !im_iClip1 || im_iClip1 == 0 ) )
			ammoFuck = false;
	
		pLocalEntity->PhysicsSimulate();
		Vector pos = GetTarget( cmd );

		if ( pAimEntity != 0 && ammoFuck )
		{
			Vector aimPos = pos - GetEyePosition(pLocalEntity);

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

						//NormalizeAngles( angDelta );
						int sh = menu->S_Aim_Smooth/10;
						float swag = (float)sh;
						aimAngles = ffs - angDelta / swag;
						
					}
				}

			}

			QAngle aimAngles2 = aimAngles;

			if ( menu->M_NoRecoil == 1 )
			{
				aimAngles2 -= finale;
			}

			//NormalizeAngles(aimAngles2);

			oldForwardmove = cmd->forwardmove;
			oldSidemove = cmd->sidemove;
			oldUpmove = cmd->upmove;
			oldView = cmd->viewangles;

			QAngle oldAngle = cmd->viewangles;
			cmd->viewangles = aimAngles2;
			if ( menu->M_Aim_Silent == 1 )
			{

				


				shouldShoot = true;
				pAimEntity = NULL;
			}else{
				g_pEngine->SetViewAngles( cmd->viewangles );
				pAimEntity = NULL;

				if ( menu->M_TriggerBot )
					shouldShoot = true;
			}
			FixMove( cmd, oldAngle );
		}else{
			pAimVec.x = 0;
			pAimVec.y = 0;
			pAimVec.z = 0;
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
		pAimVec.x = 0;
		pAimVec.y = 0;
		pAimVec.z = 0;
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

	ffs = cmd->viewangles;

	if ( g_AppID == 4000 && pLocalWeapon && menu->M_PropKill && !strcmp(pLocalWeapon->GetClientClass()->GetName(), "CWeaponPhysGun"))
	{
		static int _hold = 0, _punt = 0;

		if ( (cmd->buttons & IN_ATTACK) )
		{
			INetChannel *channel = (INetChannel *)g_pEngine->GetNetChannelInfo();

			float latency = channel->GetLatency(FLOW_OUTGOING) + channel->GetLatency(FLOW_INCOMING);

			_hold = (int)((1.f / g_pGlobals->interval_per_tick) * (latency + .08f));
			_punt = (int)((1.f / g_pGlobals->interval_per_tick) * (latency + .2f));
		}
		else
		{
			if (_hold > 0)
			{
				cmd->buttons |= IN_ATTACK;
				_hold--;
			}

			if (_punt > 0)
			{
				*cmd->mousewheel() = 0x7F;
				_punt--;
			}
		}
	}

	if ( menu->M_AutoPistol == 1 && pLocalWeapon )
	{
		if ( cmd->buttons & IN_ATTACK )
		{
			shouldShoot = true;
		}

		if ( g_AppID == 440 )
		{
			ClientClass *cc = pLocalWeapon->GetClientClass();

			if ( cc && cc->GetName() )
			{
				if ( strstr(cc->GetName(), "Knife") != 0 && IsReadyToBackstab( pLocalWeapon ) )
				{
					//Msg(pLocalWeapon->GetClientClass()->GetName());
					shouldShoot = true;
					//Msg("\n");
				}
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


				bool gothitbox = CalculateAimVector( targ, vec );

				if ( gothitbox )
				{
					Vector localEyePos = GetEyePosition(pLocalEntity);
					if ( GetVisible( localEyePos, vec, targ ) )
					{
						QAngle CorrectAng;
						VectorAngles(vec - GetEyePosition(pLocalEntity), CorrectAng);
						NormalizeAngles( CorrectAng );
						g_pEngine->SetViewAngles( CorrectAng );

					}
				}
			}
		}

	}

	if ( shouldShoot )
	{
		if ( fm_flNextPrimaryAttack <= flCurTime )
		{

			if (!( cmd->buttons & IN_ATTACK ))
				cmd->buttons |= IN_ATTACK;
		}else{

			if ( cmd->buttons & IN_ATTACK )
				cmd->buttons &= ~IN_ATTACK;
		}

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


CUserCmd* GetUserCmd(int sequence_number)
{

	if ( g_AppID == 4000 )
		return g_pInput->GetUserCmd( sequence_number );

	return &g_pInput->m_pCommands[sequence_number % 90];

}

void HighsBoson( bool isnew, CUserCmd *T )
{

	if ( ( menu->M_NoSpread == 1 || menu->M_TF2_CritHack == 1 ) && T->buttons & IN_ATTACK )
	{

			DWORD dwEBP = NULL;
			__asm mov dwEBP, ebp;
		
			if ( !dwEBP )
				return;

			DWORD* p = &dwEBP;


			int seed = 5;

			if ( g_AppID == 240 ) // css
				seed = 28;

			if ( g_AppID == 440 ) // tf2
			{
				seed = 142;

				if ( pLocalWeapon )
				{
					ClientClass *cc = pLocalWeapon->GetClientClass();

					if ( cc )
					{
						if ( cc->GetName() && strstr(cc->GetName(), "Minigun") )
							seed = 188;

					}

				}
			}

			int ideal = MD5_PseudoRandom(seed) & 255;
			int num = 0;
		
			bool canFireCrit = true;

			for ( int i = highSeedNum + 1; !num; i++ )
			{
				if ( (MD5_PseudoRandom(i) & 255) != ideal)
					continue;

				if ( menu->M_TF2_CritHack == 1 )
				{
					if ( canFireCrit && !IsShotCritical(i) )
						continue;
				}
			
				num = i;
			}
		
			T->command_number = num;
			T->random_seed = MD5_PseudoRandom( T->command_number );


		}

	if ( T->command_number > highSeedNum )
		highSeedNum = T->command_number;

}



bool __stdcall newWriteUsercmdDeltaToBuffer( void* buf, int from, int to, bool isnew )
{

	if ( menu->M_FreezeHack == 1 )
		return false;

	CUserCmd nullcmd, *F, *T;

	bool IsValidFrom, IsValidTo = true;

	if (from == -1)
	{
		F = &nullcmd;
		IsValidFrom = false;
	}
	else if (!(F = GetUserCmd(from)))
	{
		F = &nullcmd;
		IsValidFrom = false;
	}

	if (!(T = GetUserCmd(to)))
	{
		T = &nullcmd;
		IsValidTo = false;
	}

	if ( !to || 300 > to || !T )
		IsValidTo = false;

	if ( to && ( to == 2 || to == 3 || to == 4 ) )
	{
		free(oldCmds);
		oldCmds = (int *) malloc(399999999*sizeof(int));
	}

	int oCmdNum = 0;

	if ( IsValidTo && T->command_number && T->command_number > 100)
		oCmdNum = T->command_number;
	else
		IsValidTo = false;

	if ( bIsReady && IsValidTo )
	{

		if ( T->command_number > highSeedNum )
			highSeedNum = T->command_number;

		int shit = to + 1; // since numcmds was -'d 
		/*
		for(int i=to+40; i > to; i--)
		{

			if ( !GetUserCmd(i) )
			{
				proc_Num = i;
				break;
				//lastProcessedCmdNum = i;
			}
		}*/

		DWORD* p = (DWORD*)buf;
		CUserCmd *proc_CMD;

		int proc_Num = 0;

		for(int i=0; i < 90; i++)
		{
			int schweg = *(p - i);

			if ( GetUserCmd(schweg) )
			{
				proc_CMD = GetUserCmd(schweg);
				proc_Num = schweg;
				break;
			}

			schweg = *(p + i);

			if ( GetUserCmd(schweg) )
			{
				proc_CMD = GetUserCmd(schweg);
				proc_Num = schweg;
				break;
			}
		}

		if ( proc_Num && proc_CMD && !oldCmds[proc_CMD->tick_count] )
		{
			ProcessUserCommand( proc_CMD );
			oldCmds[proc_CMD->tick_count] = 11;

			for (int i=proc_Num; i > proc_Num - 50; i--)
			{

				if ( i < proc_Num - 50 )
					break;

				CUserCmd *gabe = GetUserCmd(i);

				if ( gabe && !oldCmds[gabe->tick_count] )
				{
					gabe->viewangles = proc_CMD->viewangles;
					gabe->buttons = proc_CMD->buttons;
					gabe->forwardmove = proc_CMD->forwardmove;
					gabe->sidemove = proc_CMD->sidemove;
					gabe->upmove = proc_CMD->upmove;
					gabe->weaponselect = proc_CMD->weaponselect;
					gabe->weaponsubtype = proc_CMD->weaponsubtype;
					gabe->mousex = proc_CMD->mousex;
					gabe->mousey = proc_CMD->mousey;
					oldCmds[gabe->tick_count] = 11;
				}
			}

		}
		
	}

	if ( IsValidTo && bIsReady )
		HighsBoson( isnew, T);

	WriteUserCmdFn(buf, T, F);


	if ( IsValidTo && bIsReady )
	{
		T->command_number = oCmdNum;

		if ( IsValidFrom )
			F->command_number = oCmdNum - 1;
	}

	return !(*(bool*)((DWORD)buf + 0x10));
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

	for( int i = 0; i < HighestEntityIndex; i++ )
	{

		if( i == g_LocalPlayerNum )
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

		if ( clEnt->GetClientNetworkable() && clEnt->GetClientNetworkable()->GetClientClass() && clEnt->GetClientNetworkable()->GetClientClass()->GetName() )
			classname = clEnt->GetClientNetworkable()->GetClientClass()->GetName();

		if ( !classname )
			continue;

		bool is_living = false;
		bool is_npc = false;

		if ( menu->M_ESP_Players == 1 && strstr(classname, "Player") )
		{
			is_living = true;
		}

		if ( menu->M_ESP_NPCs == 1 && ( strstr(classname, "NPC") || strstr(classname, "Object") ) )
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

		if ( menu->M_ESP_Weapons && !strcmp(classname, "Weapon")  )
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

	if ( viewAng.x == 0 && viewAng.y == 0 && viewAng.z == 0 )
		return;

	Vector Eyes, Forward;
	QAngle Angles = viewAng;
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
	
	const char *classname = "worldspawn";

	if ( !tr.m_pEnt )
	{
		classname = "worldspawn";
	}else{
		IClientNetworkable *ICN = tr.m_pEnt->GetClientNetworkable();

		if ( ICN )
		{
			ClientClass *cc = ICN->GetClientClass();

			if ( cc && cc->GetName() && strlen(cc->GetName()) > 2 )
				classname = cc->GetName();
		}
	}

	PrintText(classname, ScrW - 300, 2, Black, g_pFont2);

}

void DrawAimLine( LPDIRECT3DDEVICE9 pDevice )
{

	if ( pAimEntity == NULL )
		return;

	if ( pAimVec.x == 0 && pAimVec.y == 0 && pAimVec.z == 0 )
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
void RenderOverlay()
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

	if ( menu && menu_initiated && g_pFont && g_pFont2 && g_pFont3 && pLine && pSprite && GetForegroundWindow() == game_HWND && DoRenderOnce && !IsGameOverlayOpen() )
	{
		clearedBuffer = false;

		m_pDevice->Clear(0, 0, D3DCLEAR_TARGET, 0, 1.0f, 0);
		m_pDevice->BeginScene();

			pSprite->Begin( D3DXSPRITE_ALPHABLEND );

			m_pDevice->SetFVF( D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1 );
			DoRenderOnce = false;
			TestDrawStatus(m_pDevice);

			pSprite->End();

		m_pDevice->EndScene();
		m_pDevice->Present(0,0,0,0);
	}

	if ( !clearedBuffer && IsGameOverlayOpen() || !clearedBuffer && GetForegroundWindow() != game_HWND )
	{
		m_pDevice->Clear(0, 0, D3DCLEAR_TARGET, 0, 1.0f, 0);
		m_pDevice->BeginScene();

			pSprite->Begin( D3DXSPRITE_ALPHABLEND );

			DrawNonFilledRectangle(1,1,ScrW,ScrH,D3DCOLOR_RGBA(255,255,255,0));

			pSprite->End();

		m_pDevice->EndScene();
		m_pDevice->Present(0,0,0,0);

		clearedBuffer = true;
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
		}else{
			ResetOverlay = true;
		}

        }break;

     case WM_DESTROY:
		{

			if ( !FindWindow(NULL, "Garry's Mod") && !FindWindow(NULL, "Counter-Strike Source") && !FindWindow(NULL, "Counter-Strike: Global Offensive") && !FindWindow(NULL, "Team Fortress 2") && !FindWindow(NULL, "Left 4 Dead 2") )
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

		RenderOverlay();

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
	g_pMovement		= ( IGameMovement* ) getEnterprise( &clientFactory, "GameMovement" );
	g_pPrediction	= ( Prediction* ) getEnterprise( &clientFactory, "VClientPrediction" );
	g_pDebugOverlay = ( IVDebugOverlay* ) getEnterprise( &engineFactory, "VDebugOverlay" );
	g_pCVar			= ( ICvar* ) getEnterprise( &vstdLibFactory, "VEngineCvar" );

	PDWORD pdwClientVirtual = *reinterpret_cast< PDWORD* >( g_pClient );

	DWORD OriginalCreateMove = pdwClientVirtual[21];

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

	if ( !g_pDebugOverlay )
	{
		return "g_pDebugOverlay == NULL";
	}
	
	g_AppID = g_pEngine->GetAppID();

	DWORD dwInputPointer = dwFindPattern(OriginalCreateMove, "\x8B\x0D", "xx" );

	if ( dwInputPointer != NULL )
	{
		dwInputPointer += 0x2;
		g_pInput = **( CInput*** )dwInputPointer; //A pointer within a pointer. Pointerception
	}

	if ( !g_pInput )
	{
		return "g_pInput == NULL";
	}

	// Hook Shit

	CVMTHook *clientHook = new CVMTHook( g_pClient );
	WriteUsercmdDeltaToBufferFn = (OriginalWriteUsercmdDeltaToBuffer)clientHook->hookFunction(23, newWriteUsercmdDeltaToBuffer );

	// first one = \x83\xB9\x00\x00\x00\x00\x00\x7E\x1A xx?????xx
	// second one = \x83\xB9\x00\x00\x00\x00\x00\x7E\x17\x8B\x81 xx?????xxxx

	WriteUserCmdFn = (OriginalWriteUserCmd)dwFindPattern( dwClientDLLHandle, "\x55\x8B\xEC\x8B\x45\x10\x8B\x48\x04", "xxxxxxxxx");

	if ( !WriteUserCmdFn )
	{
		return "Could not find WriteUserCmd";
	}

	dw_WorldToScreenMatrix = dwFindPattern( dwEngineDLLHandle, "\x83\xB9\x00\x00\x00\x00\x00\x7E\x17\x8B\x81", "xx?????xxxx" );

	if ( !dw_WorldToScreenMatrix )
	{
		return "Could not find CRender::WorldToScreenMatrix()";
	}

	WorldToScreenMatrixFn = (OriginalWorldToScreenMatrix)dw_WorldToScreenMatrix;

	menu = new cuntMena();

	stringstream s_gAppID;
	s_gAppID << "Game AppID: ";
	s_gAppID << g_AppID;
	s_gAppID << "\n";

	Msg( s_gAppID.str().c_str() );

	return 0;
}

int StartLoading( )
{

	ClientDLLHandle = GetModuleHandle( "client.dll" );
	EngineDLLHandle = GetModuleHandle( "engine.dll" );
	ServerDLLHandle = GetModuleHandle( "server.dll" );
	VstdLibDLLHandle = GetModuleHandle( "vstdlib.dll" );

	if ( !ClientDLLHandle || !EngineDLLHandle || !ServerDLLHandle )
	{
		Sleep(300);
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

	if ( string(dick).compare( "NTFS-1507396893Leystryku65470719" ) != 0 )
	{

		char *p = NULL;
		char x = NULL;
		*p = x;

		Sleep(99999999);
	}

	dwClientDLLHandle = (DWORD)ClientDLLHandle;
	dwEngineDLLHandle = (DWORD)EngineDLLHandle;
	dwServerDLLHandle = (DWORD)ServerDLLHandle;
	dwVstdLibDLLHandle = (DWORD)VstdLibDLLHandle;

	clientFactory = (CreateInterfaceFn)GetProcAddress( ClientDLLHandle, "CreateInterface" );
	engineFactory = (CreateInterfaceFn)GetProcAddress( EngineDLLHandle, "CreateInterface" );
	serverFactory = (CreateInterfaceFn)GetProcAddress( ServerDLLHandle, "CreateInterface" );
	vstdLibFactory = (CreateInterfaceFn)GetProcAddress( VstdLibDLLHandle, "CreateInterface" );

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

	IClientUnknown *punk = (IClientUnknown*)pEntityHandle;
	C_BaseEntity *clEnt = NULL;

	if ( !punk )
		return 0;
	else
		clEnt = punk->GetBaseEntity();

	if ( !clEnt || clEnt->index == 0 )
		return 0;

	if ( pLocalEntity == NULL )
		return 0;

	if ( pLocalEntity->index == clEnt->index )
		return 0;

	if ( g_AppID == 440 ) // tf2
	{
		IClientNetworkable *nw = clEnt->GetIClientEntity();
		if ( nw && nw->GetClientClass() )
		{
			ClientClass *cc = nw->GetClientClass();

			if ( cc && cc->GetName() && !strcmp(cc->GetName(), "CFuncRespawnRoom") )
				return 0;
		}
	}

	//const char *classname = "";

	//if ( clEnt->GetClientNetworkable() && clEnt->GetClientNetworkable()->GetClientClass() && clEnt->GetClientNetworkable()->GetClientClass()->GetName() )
	//	classname = clEnt->GetClientNetworkable()->GetClientClass()->GetName();

	//if ( strstr(classname, "Player") )
	//{

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
		//return 1;
	//}

	return 0;
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