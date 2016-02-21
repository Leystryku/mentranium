
bool bIsReady = false;

#include "utils.h"

using namespace std;

cMenu *menu = NULL;


CUserCmd* __stdcall GetUserCmd(int sequence_number)
{

	static CUserCmd* cmds = *(CUserCmd**)((DWORD)g_pInput + 0xC4);

	return &cmds[sequence_number % 90]; 
};

CInput::CVerifiedUserCmd* GetVerifiedCmd(int sequence_number)
{
	static CInput::CVerifiedUserCmd* verifieds = *(CInput::CVerifiedUserCmd **)((DWORD)g_pInput + 0xC8);

	return &verifieds[sequence_number % 90];
};

DWORD GetTableOffset( PCHAR pClassName, PCHAR pVarName, RecvTable* pTable )
{
	DWORD dwReturn = NULL;

	for( int i = 0; i < pTable->GetNumProps( ); i++ )
	{
		RecvProp* pProp = pTable->GetPropA( i );

		if( !pProp )
			continue;

		RecvTable* pChild = pProp->GetDataTable( );

		if( pChild && pChild->GetNumProps( ) )
			dwReturn += GetTableOffset( pClassName, pVarName, pChild );

		if( !strcmp( pTable->GetName( ), pClassName ) && !strcmp( pProp->GetName( ), pVarName ) )
		{
			dwReturn += pProp->GetOffset( );
			break;
		}
	}

	return dwReturn;
}

DWORD GetNetvarOffset( PCHAR pClassName, PCHAR pVarName )
{
	ClientClass* pClientClass = g_pClient->GetAllClasses( );

	if( !pClientClass )
		return NULL;

	DWORD dwReturn = NULL;

	for( ; pClientClass; pClientClass = pClientClass->m_pNext )
	{
		RecvTable* pTable = pClientClass->m_pRecvTable;

		if( !pTable )
			continue;

		if( !pTable->GetNumProps( ) )
			continue;

		if( !strstr( pTable->GetName( ), "DT_" ) )
			continue;

		dwReturn = GetTableOffset( pClassName, pVarName, pTable );

		if( dwReturn )
			break;
	}

	return dwReturn;
}

CUserCmd* __stdcall newGetUserCmd( int sequence_number )
{
	CUserCmd *pCmd = GetUserCmd( sequence_number );

	return pCmd;
}

void Mentranium_NameSteal()
{

	if ( menu->M_NameChanger != 1 )
		return;

	int iIndex = ( rand() % g_pEngine->GetMaxClients() );

	while ( bIsBadIndex(iIndex) == true )
	{

		iIndex = ( rand() % g_pEngine->GetMaxClients() );

		if ( bIsBadIndex(iIndex) == false && iIndex != g_pEngine->GetLocalPlayer() )
			break;

	}

	player_info_s pInfo; 

	g_pEngine->GetPlayerInfo( iIndex, &pInfo ); 

	if ( !&pInfo )
		return;

	string name = pInfo.name;

	if ( !pInfo.name )
		return;

	char stolen[50];

	const char *mask = "\xE2\x80\x8F%s\xE2\x80\x8F";

	sprintf(stolen, mask, name.c_str());

	Mentranium_Name( stolen );

}

void InitNetvars()
{

	if ( bIsReady )
		return;
	
	IClientEntity *localclEnt = NULL;

	if ( g_pEngine->GetLocalPlayer() )
		localclEnt = g_pEntList->GetClientEntity(g_pEngine->GetLocalPlayer());

	if ( localclEnt )
		pLocalEntity =  dynamic_cast<C_BasePlayer*>(localclEnt);

	if ( pLocalEntity == NULL )
		return;

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

	if ( !m_bAlive )
		m_bAlive   = GetNetvarOffset( "DT_PlayerResource", "m_bAlive" );

	if ( !m_bAlive )
		MessageBox( NULL, "no m_bAlive !","ERROR WHILE GETTING NETVARS !", MB_OK );

	if ( !m_fVecPunchAngle )
		m_fVecPunchAngle = GetNetvarOffset( "DT_Local", "m_vecPunchAngle" );

	if ( !m_fVecPunchAngle )
		MessageBox( NULL, "no m_fVecPunchAngle !","ERROR WHILE GETTING NETVARS !", MB_OK );

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

	if ( !m_iObserverMode )
		m_iObserverMode = GetNetvarOffset( "DT_BasePlayer", "m_iObserverMode" );

	if ( !m_iObserverMode )
		MessageBox( NULL, "no m_iObserverMode !","ERROR WHILE GETTING NETVARS !", MB_OK );

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
	bool is_ingame = g_pEngine->IsInGame();

	if ( !g_pEngine->IsConnected() || g_pEngine->IsDrawingLoadingImage() )
		is_ingame = false;

	if ( !bIsReady ) 
	{
		if ( is_ingame )
			InitNetvars();

	}else{
		if ( !is_ingame )
		{
			bIsReady = false;
			pLocalEntity = NULL;
			pAimEntity = NULL;
			pAimVec = NULL;
			pLocalWeapon = NULL;
		}
	}

	IClientEntity *localclEnt = NULL;

	if ( g_pEngine->GetLocalPlayer() )
		localclEnt = g_pEntList->GetClientEntity(g_pEngine->GetLocalPlayer());

	if ( localclEnt )
		pLocalEntity =  dynamic_cast<C_BasePlayer*>(localclEnt);

	if ( pLocalEntity == NULL )
	{
		bIsReady = false;
		pAimEntity = NULL;
		pAimVec = NULL;
		pLocalWeapon = NULL;
	}

	if ( !bIsReady )
		return;

	HighestEntityIndex = g_pEntList->GetHighestEntityIndex();
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

bool CalculateHitboxVector(C_BaseEntity* player, Vector& vec) 
{
	IClientRenderable* renderable = static_cast<IClientRenderable*>(player);

	if (!renderable)
		return false;

	const model_t* model = renderable->GetModel();

	if (!model)
		return false;

	studiohdr_t* studiohdr = g_pModelInfo->GetStudiomodel(model);

	if (!studiohdr)
		return false;

	matrix3x4_t boneMatrix[200];

	if (!renderable->SetupBones(boneMatrix, MAXSTUDIOBONES, BONE_USED_BY_HITBOX, 0.0f))
		return false;

	bool originFound = false;
	Vector highestOrigin(-999999.0f, -999999.0f, -999999.0f);

	for (int i = 0; i <studiohdr->iHitboxCount(0); ++i)
	{
		mstudiobbox_t* hitbox = studiohdr->pHitbox(i, 0);

		if (!hitbox)
			continue;

		Vector min_vec, max_vec;

		VectorTransform(hitbox->bbmin, boneMatrix[hitbox->bone], min_vec);
		VectorTransform(hitbox->bbmax, boneMatrix[hitbox->bone], max_vec);

		Vector origin = (min_vec + max_vec) * 0.5f;

		if (origin.z> highestOrigin.z) 
		{
			originFound = true;
			highestOrigin = origin;
		}
	}

	if (!originFound)
		return false;

	vec = highestOrigin;

	return true;
}

bool GetVisible( Vector& vecAbsStart, Vector& vecAbsEnd, C_BaseEntity* pBaseEnt ) 
{ 
	trace_t tr;
	Ray_t ray;

	CTraceFilter filter;
	filter.pSkip = pLocalEntity;

	ray.Init( vecAbsStart, vecAbsEnd );
	g_pEngineTrace->TraceRay( ray, MASK_SHOT, &filter, &tr );

	if ( tr.m_pEnt == NULL || pBaseEnt == NULL )
		return false;

	if ( tr.m_pEnt->index == 0 || tr.allsolid )
		return false;

	if ( pBaseEnt->index == tr.m_pEnt->index )
		return true;

	return false;
}

float flGetDistance( Vector from, Vector to )
{
    Vector angle;
    angle.x = to.x - from.x;	angle.y = to.y - from.y;	angle.z = to.z - from.z;
    
	return sqrt(angle.x*angle.x + angle.y*angle.y + angle.z*angle.z);
}

Vector GetTarget()
{

	float bestDist = 99999999999999999;
	C_BaseEntity *best_targ = 0;
	Vector myvec = GetOrigin(pLocalEntity);
	Vector localEyePos = GetEyePosition(pLocalEntity);
	Vector tarvec;

	int localteamnum = GetTeam(pLocalEntity);

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
		
		if ( iclEnt && iclEnt->GetBaseEntity() )
			clEnt = dynamic_cast<C_BaseEntity*>(iclEnt);

		if ( clEnt == NULL )
			continue;

		if ( clEnt->IsDormant() )
			continue;

		bool pass = false;

		int iHealth =  *(int*)((DWORD)clEnt + m_iHealth);

		if ( iHealth == 0 )
			continue;

		const char *classname = C_BaseEnt_Classname( clEnt, NULL );

		if ( !classname )
			continue;

		bool is_living = false;
		bool is_npc = false;

		if ( menu->M_Aim_KillPlayer && strstr(clEnt->GetIClientEntity()->GetClientNetworkable()->GetClientClass()->GetName(), "Player") )
			is_living = true;

		if ( menu->M_Aim_KillNPC && strstr(classname, "npc_") )
		{
			is_living = true;
			is_npc = true;
		}

		if ( !is_living )
			continue;


		if ( !is_npc && menu->M_Aim_TeamKill == 0 )
		{
			int teamnum = GetTeam(clEnt);

			if ( teamnum == localteamnum )
				continue;
		}

		Vector vec;

		bool gothitbox = CalculateHitboxVector( clEnt, vec );

		if ( !gothitbox )
			continue;
			
		if ( !GetVisible( localEyePos, vec, clEnt ) )
			continue;

		float pDist = flGetDistance( myvec, clEnt->GetAbsOrigin() );

		if ( pDist < bestDist )
		{
			best_targ = clEnt;
			bestDist = pDist;
			tarvec = vec;
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

bool bTraceToTarget( CUserCmd *cmd )
{

	Vector Eyes, Forward;
	QAngle Angles = cmd->viewangles;
	trace_t pTrace;
	Ray_t pRay;

	Eyes = GetEyePosition(pLocalEntity);

	Vector vDirection;

	AngleVectors( Angles, &vDirection );

	vDirection = vDirection * 8192 + Eyes;

	CTraceFilter filter;
	filter.pSkip = pLocalEntity;

	pRay.Init( Eyes, vDirection );
	g_pEngineTrace->TraceRay( pRay, MASK_SHOT, &filter, &pTrace);

	if ( pTrace.m_pEnt == NULL || pTrace.m_pEnt->GetIClientEntity() == NULL )
		return false;

	ClientClass *cc = pTrace.m_pEnt->GetClientClass();

	if ( pTrace.m_pEnt->IsDormant() )
		return false;

	const char *classname = C_BaseEnt_Classname( pTrace.m_pEnt, NULL );

	if ( !classname )
		return false;

	bool found = false;
	bool is_npc = false;

	if ( menu->M_Aim_KillPlayer && strstr(pTrace.m_pEnt->GetIClientEntity()->GetClientNetworkable()->GetClientClass()->GetName(), "Player") )
		found = true;

	if ( menu->M_Aim_KillNPC && strstr(classname, "npc_") )
	{
		is_npc = true;
		found = true;
	}

	if ( !found )
		return false;

	int iHealth =  *(int*)((DWORD)pTrace.m_pEnt + m_iHealth);

	if ( iHealth == 0 )
		return false;

	if ( !is_npc && menu->M_Aim_TeamKill == 0 )
	{

		int localteamnum = GetTeam(pLocalEntity);
		int teamnum = GetTeam(pTrace.m_pEnt);

		if ( teamnum == localteamnum )
			return false;
	}

	return false;
}

int speedCmd = 1;
int skipSpeedCmd = 1;

void DoUsercmdStuff( CUserCmd *cmd, int num )
{

	if ( pLocalEntity == NULL )
		return;

	viewAng = cmd->viewangles;

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

	float oldForward = cmd->forwardmove;
	float oldSide = cmd->sidemove;
	float oldUp = cmd->upmove;
	QAngle oldAngles = cmd->viewangles;

	if ( speedCmd > 1 )
	{
		skipSpeedCmd -=1;

		if ( skipSpeedCmd == 0 )
		{
			speedCmd -= 1;
			*CL_Move -= 0x5;
			skipSpeedCmd = 1;
		}
	}else{

		if ( !menu->M_Speed )
			speedCmd = 0;
		else
			speedCmd = menu->S_Speed;
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

	QAngle punchAngle = *(QAngle*)((DWORD)pLocalEntity + m_fLocal + m_fVecPunchAngle );


	if ( menu->M_NoSpread == 1 )
	{
		//FixSpread( cmd->random_seed, cmd->viewangles );

		cmd->viewangles.x -= punchAngle.x + punchAngle.x;
		cmd->viewangles.y -= punchAngle.y + punchAngle.y;
	}

	if ( menu->M_AimEnable != 0 && fm_flNextPrimaryAttack <= flServerTime && !(cmd->buttons & IN_ATTACK) )
	{
		Vector pos = GetTarget();

		if ( pAimEntity != 0 )
		{

			VectorAngles(pos - GetEyePosition(pLocalEntity), aimAngles);

			if ( menu->M_NoSpread == 1 )
			{
				//FixSpread( cmd->random_seed, aimAngles );

				aimAngles.x -= punchAngle.x + punchAngle.x;
				aimAngles.y -= punchAngle.y + punchAngle.y;
				aimAngles.z -= punchAngle.z + punchAngle.z;
			}

			LimitAng(aimAngles);

			QAngle aimAngles2 = aimAngles;

			if ( menu->M_Aim_Silent == 1 )
			{

				cmd->viewangles = aimAngles2;

				shouldShoot = true;

			}else{
				g_pEngine->SetViewAngles( aimAngles2 );
			}

		}else{
			pAimVec = NULL;
		}
	}else{
		pAimVec = NULL;
		pAimEntity = NULL;
	}

	
	if ( menu->M_AutoPistol != 0 )
	{
		if ( cmd->buttons & IN_ATTACK )
		{
			shouldShoot = true;
		}

	}

	if ( menu->M_TriggerBot != 0 )
	{
		if ( bTraceToTarget(cmd) )
		{
			shouldShoot = true;
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
		
		if ( im_iClip1 == 0 && menu->M_AutoReload )
		{
			cmd->buttons |= IN_RELOAD;
		}else{

			if ( menu->M_AutoReload && im_iClip1 == 0 && ( cmd->buttons & IN_RELOAD ) )
				cmd->buttons &= ~IN_RELOAD;

		}

	}

}

bool __fastcall newWriteUsercmdDeltaToBuffer( void *thisptr, int edx, void* buf, int from, int to, bool isnew)
{

	CUserCmd nullcmd, *F, *T;

	if (from == -1)
		F = &nullcmd;
	else if (!(F = GetUserCmd(from)))
		F = &nullcmd;

	if (!(T = GetUserCmd(to)))
		T = &nullcmd;

	WriteUserCmd(buf, T, F);

	if ( menu->M_FreezeHack )
		return false;

	return !(*(bool*)((DWORD)buf + 0x10));
}




void __fastcall newCreateMove( void *thisptr, int edx, int sequence_number, float input_sample_frametime, bool active )
{

	CreateMoveFn( thisptr, edx, sequence_number, input_sample_frametime, active);

	if ( !active )
		return;

	if ( !bIsReady )
		return;

	CUserCmd *cmd = GetUserCmd( sequence_number );

	if ( menu->M_NoSpread == 1 )
	{
		cmd->command_number = 142;
		cmd->random_seed = MD5_PseudoRandom(cmd->command_number) & 0x7FFFFFFF;
	}

	if ( !CL_Move )
	{
		PDWORD *pdwEBP = NULL;
		__asm MOV pdwEBP, EBP
		
		CL_Move = (PDWORD)(*(PCHAR*)pdwEBP + 4);
	}

	DoUsercmdStuff( cmd, sequence_number );



}

const char *cdisc = "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";


void __fastcall newShutdown( void* thisptr, int edx, const char *dc_string )
{	

	if ( menu->M_DisconnectSpam )
		dc_string =  cdisc;


	bIsReady = false;
	pLocalEntity = NULL;
	pAimEntity = NULL;
	pAimVec = NULL;
	pLocalWeapon = NULL;

	return ShutdownFn( thisptr, edx, dc_string );
}

int __fastcall newInKeyEvent( void* thisptr, int edx, int code, ButtonCode_t num, const char* bind )
{

	if ( num == KEY_DELETE )
		return 0;

	if ( num == KEY_F11 )
	{
		menu->M_FreezeHack = !menu->M_FreezeHack;
		return 0;
	}

	if ( num == KEY_F12 )
	{
		menu->M_Speed = !menu->M_Speed;
		return 0;
	}

	if ( menu_isopen )
	{
		if ( num == MOUSE_LEFT || num == MOUSE_RIGHT )
			return 0;
	}

	return InKeyEventFn( thisptr, edx, code, num, bind );

}

bool hookedNetchan = false;

class MentraniumEventHandler : public IGameEventListener2
{
	void FireGameEvent( IGameEvent* event )
	{
		if(Q_strcmp(event->GetName(), "game_newmap") == 0)
		{

			bIsReady = false;
			pLocalEntity = NULL;
			pAimEntity = NULL;
			pAimVec = NULL;
			pLocalWeapon = NULL;

			INetChannel *channel = (INetChannel *)g_pEngine->GetNetChannelInfo();

			if ( !channel )
				return;

			if ( !hookedNetchan )
			{
				DWORD_PTR * channelVtbl = 0;
				*(DWORD_PTR *)&channelVtbl= *(DWORD_PTR *)channel;
				ShutdownFn = (OriginalShutdown)DetourCreate((void*)channelVtbl[36], (void*)newShutdown, DETOUR_TYPE_JMP);
				hookedNetchan = true;
			}

		}

	}
} GameEventHandler;

void __cdecl newCL_QueueDownload( const char *pszFileName )
{

	if ( menu->M_FastJoin )
	{
		string extension = boost::filesystem::extension( pszFileName );
		
		
		if ( !extension.find( ".bsp" ) )
			CL_QueueDownloadFn( pszFileName );
	}else{

		CL_QueueDownloadFn( pszFileName );

	}

}

int GetInterfaces( )
{
	g_pCVar			= ( ICvar* ) getInterface(&CvarFactory, "VEngineCvar");
	g_pClient		= ( IBaseClientDLL* ) getInterface( &clientFactory, "VClient" );
	g_pEntList		= ( IClientEntityList* ) getInterface( &clientFactory, "VClientEntityList" );
	g_pEngine		= ( IVEngineClient* ) getInterface( &engineFactory, "VEngineClient" );
	g_pEngineTrace	= ( IEngineTrace* ) getInterface( &engineFactory, "EngineTraceClient" );
	g_pModelInfo	= ( IVModelInfoClient* ) getInterface( &engineFactory, "VModelInfoClient" );
	g_pGameManager	= ( IGameEventManager2* ) getInterface( &engineFactory, "GAMEEVENTSMANAGER" );
	g_pDebugOverlay = (IVDebugOverlay* ) getInterface( &engineFactory, "VPhysicsDebugOverlay" );
	g_pPlayerManager =  ( IPlayerInfoManager* ) getInterface( &serverFactory, "PlayerInfoManager" );
	random			= (IUniformRandomStream*)getInterface( &engineFactory, "VEngineRandom");


	PDWORD pdwClientVirtual = *reinterpret_cast< PDWORD* >( g_pClient );

	PDWORD pdwInputVMT = (PDWORD)*(PDWORD)(g_pInput = (CInput*)(*(PDWORD)*(PDWORD)(dwFindPattern(pdwClientVirtual[21], (PBYTE)"\x8B\x0D????\x8B\x01\x8B\x40\x0C\x52\x8B\x55\x08\x51\xD9\x1C\x24", "xx????xxxxxxxxxxxxx") + 2)));

	if ( !g_pCVar )
	{
		MessageBox( NULL, "g_pCVar == NULL", "Mentranium", MB_OK );
		return -1;
	}

	if ( !g_pClient )
	{
		MessageBox( NULL, "g_pClient == NULL", "Mentranium", MB_OK );
		return -1;
	}

	if ( !g_pEntList )
	{
		MessageBox( NULL, "g_pEntList == NULL", "Mentranium", MB_OK );
		return -1;
	}

	if ( !g_pEngine )
	{
		MessageBox( NULL, "g_pEngine == NULL", "Mentranium", MB_OK );
		return -1;
	}

	if ( !g_pInput )
	{
		MessageBox( NULL, "g_pInput == NULL", "Mentranium", MB_OK );
		return -1;
	}

	if ( !g_pEngineTrace )
	{
		MessageBox( NULL, "g_pEngineTrace == NULL", "Mentranium", MB_OK );
		return -1;
	}

	if ( !g_pModelInfo )
	{
		MessageBox( NULL, "g_pEngineTrace == NULL", "Mentranium", MB_OK );
		return -1;
	}

	if ( !g_pGameManager )
	{
		MessageBox( NULL, "g_pGameManager == NULL", "Mentranium", MB_OK );
		return -1;
	}

	if ( !g_pDebugOverlay )
	{
		MessageBox( NULL, "g_pDebugOverlay == NULL", "Mentranium", MB_OK );
		return -1;
	}

	if ( !g_pPlayerManager )
	{
		MessageBox( NULL, "g_pPlayerManager == NULL", "Mentranium", MB_OK );
		return -1;
	}

	g_pGlobals = g_pPlayerManager->GetGlobalVars();

	if ( !g_pGlobals )
	{
		MessageBox( NULL, "g_pGlobals == NULL", "Mentranium", MB_OK );
		return -1;
	}

	return 0;
}

/*

BOOL WINAPI newSetCursorPos( int X, int Y )
{
	menu->Cur.x = X;
	menu->Cur.y = Y;

	if ( menu_isopen )
		return false;

	return _SetCursorPos( X, Y );
}

*/

int HookStuff( )
{

	DWORD_PTR * clientVtbl = 0;
	*(DWORD_PTR *)&clientVtbl= *(DWORD_PTR *)g_pClient;

	CreateMoveFn = (OriginalCreateMove)DetourCreate((void*)clientVtbl[21], (void*)newCreateMove, DETOUR_TYPE_JMP);
	InKeyEventFn = (OriginalInKeyEvent)DetourCreate((void*)clientVtbl[20], (void*)newInKeyEvent, DETOUR_TYPE_JMP);
	WriteUsercmdDeltaToBufferFn = (OriginalWriteUsercmdDeltaToBuffer)DetourCreate((void*)clientVtbl[23], (void*)newWriteUsercmdDeltaToBuffer, DETOUR_TYPE_JMP);



	DWORD_PTR * inputVtbl = 0;
	*(DWORD_PTR *)&inputVtbl= *(DWORD_PTR *)g_pInput;

	DWORD dw_GetUserCmd = (DWORD)DetourCreate((void*)inputVtbl[8], (void*)newGetUserCmd, DETOUR_TYPE_JMP);

	DWORD dwCL_QueueDownload = dwFindPattern(dwEngineDLLHandle, (PBYTE)"\x55\x8B\xEC\x83\x3D\x00\x00\x00\x00\x00\x7E\x62", "xxxxx?????xx" );

	if ( dwCL_QueueDownload )
		CL_QueueDownloadFn = (OriginalCL_QueueDownload)DetourCreate((void*)dwCL_QueueDownload, (void*)newCL_QueueDownload, DETOUR_TYPE_JMP);

	C_BaseEnt_Classname = (OriginalC_BaseEnt_Classname)dwFindPattern( (DWORD)dwClientDLLHandle, (BYTE*)"\x57\x8B\xF9\x8B\x87\x00\x00\x00\x00\x85\xC0\x74\x0D\x50\xE8", "xxxxx????xxxxxx");

	WriteUserCmd = (OriginalWriteUserCmd)dwFindPattern( dwClientDLLHandle, (PBYTE)"\x55\x8B\xEC\x8B\x45\x10\x8B\x48\x04", "xxxxxxxxx");

	HMODULE hand = GetModuleHandleA("user32.dll");

	if ( !hand )
		MessageBox( NULL, "no hand", "k", MB_OK );

	DWORD dwSetCursorPos = (DWORD)GetProcAddress(hand, "SetCursorPos");
	
	if ( !dwSetCursorPos )
		MessageBox( NULL, "Noset ", "k", MB_OK );

	//_SetCursorPos = (int(__stdcall*)(int, int))(DetourCreate( SetCursorPos, (void*)newSetCursorPos, DETOUR_TYPE_JMP ));

	if ( !CreateMoveFn )
	{
		//LogText( "Could not hook IBaseClient::CreateMove\n" );
		return -1;
	}

	if ( !InKeyEventFn )
	{
		//LogText( "Could not hook IBaseClient::InKeyEvent\n" );
		return -1;
	}

	if ( !WriteUsercmdDeltaToBufferFn )
	{
		//LogText( "Could not hook IInput::WriteUsercmdDeltaToBufferFn\n" );
		return -1;
	}

	if ( !dw_GetUserCmd )
	{
		//LogText( "Could not hook CInput::GetUserCmd\n" );
		return -1;
	}

	if ( !CL_QueueDownloadFn )
	{
		//LogText( "" );
		return -1;
	}

	if ( !C_BaseEnt_Classname )
	{
		//LogText( "" );
		return -1;
	}

	if ( !WriteUserCmd )
	{
		//LogText( "" );
		return -1;
	}

	//LogText( "Hooked IBaseClient::CreateMove\n" );
	//LogText( "Hooked CInput::GetUserCmd\n" );
	//LogText( "\n" );

	return 0;
}

D3DVIEWPORT9 viewport;

void GetCenter( LPDIRECT3DDEVICE9 pDevice )
{
	
	pDevice->GetViewport( &viewport );

	if ( !&viewport ) return;
	
	ScrW = viewport.Width;
	ScrH = viewport.Height;

	CenterX = (viewport.Width/2);
	CenterY = (viewport.Height/2);

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
		DrawLine(CenterX+10, CenterY+10, CenterX-10, CenterY-10, 1, Red);
		DrawLine(CenterX-10, CenterY+10, CenterX+10, CenterY-10, 1, Red);
		break;
	case 3:
		DrawCircle(CenterX,CenterY,8,8,Red);
		FillRGB(CenterX-17, CenterY, 10, 1,Red);
		FillRGB(CenterX+9, CenterY, 10, 1,Red);
		FillRGB(CenterX, CenterY-17, 1, 10,Red);
		FillRGB(CenterX, CenterY+9, 1, 10,Red);
		DrawPoint(CenterX, CenterY, 1, 1, Red);
		break;
	case 4:
		DrawCircle(CenterX-1,CenterY-1,8,8,Red);
		FillRGB(CenterX-13, CenterY, 10, 1,Red);
		FillRGB(CenterX+4, CenterY, 10, 1,Red);
		FillRGB(CenterX, CenterY-13, 1, 10,Red);
		FillRGB(CenterX, CenterY+4, 1, 10,Red);
		DrawPoint(CenterX-1 , CenterY-1, 1, 1, Green);
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

void DrawLivingESP( int index, C_BaseEntity *pBaseEntity, const char *classname )
{

	Vector AbsScreen;

	if( TransformVector( GetOrigin(pBaseEntity), AbsScreen ) == false )
		return;

	Color DrawColor = GetTeamColor( pBaseEntity );

	if ( !&DrawColor )
		return;

	char pszNameTrun[256] = { 0 };

	player_info_t pi;

	g_pEngine->GetPlayerInfo( index, &pi );

	if ( !pi.name || strstr(classname, "npc_") )
		strcpy( pszNameTrun, classname );
	else
		strcpy( pszNameTrun, pi.name );

	size_t p = strlen( pszNameTrun );

	if( p > 16 )
	{
		pszNameTrun[ 8 ] = '\0';

		strcat( pszNameTrun, ".." );
	}

	if ( p < 3 )
		return;

	int iHealth =  *(int*)((DWORD)pBaseEntity + m_iHealth);

	if ( !iHealth )
		return;

	if( iHealth < 1 )
		iHealth = 0;

	int maxhealth = 100.0f;

	if ( iHealth > 100 )
		maxhealth = iHealth;

	char c_enthealth[9999];
	sprintf(c_enthealth, "%d", iHealth);

	if ( iHealth == 0 )
		DrawColor.SetColor(0,0,0,255);

	if ( menu->M_ESP_Name )
		CenterText( AbsScreen.x, AbsScreen.y, DrawColor.r(), DrawColor.g(), DrawColor.b(), DrawColor.a(), pszNameTrun );
		
	if ( menu->M_ESP_Health )
		CenterText( AbsScreen.x, AbsScreen.y + 25.f, DrawColor.r(), DrawColor.g(), DrawColor.b(), DrawColor.a(), c_enthealth );
		
	if ( menu->M_ESP_HealthBar )
		DrawHealthBox( AbsScreen.x, AbsScreen.y + 20.f, DrawColor.r(), DrawColor.g(), DrawColor.b(), DrawColor.a(), 
			iHealth, maxhealth );


	if ( menu->M_ESP_3D )
	{

	}else{

			Vector mon, nom;

			int flags = GetFlags( pBaseEntity );

			if ( !flags )
				return;

			nom = GetOrigin( pBaseEntity );

			if ( !&nom )
				return;


			if (flags & FL_DUCKING)
			{
				mon = nom + Vector( 0, 0, 50.f );
			}
			else
			{
				mon = nom + Vector( 0, 0, 70.f );
			}

			Vector bot, top;

			if( TransformVector( nom, bot ) && TransformVector( mon, top ) )
			{
				if ( !&bot || !&top )
					return;

				float h = ( bot.y - top.y );

				float w = h / 4.f;

				OutlineRGBA( top.x - w, top.y, w * 2, ( bot.y - top.y ), 1, D3DCOLOR_ARGB(DrawColor.a(),DrawColor.r(),DrawColor.g(),DrawColor.b()), m_pDevice );
			}

	}

}

void DrawWeaponESP( C_BaseEntity *pBaseEntity, const char *classname)
{
	if ( !menu->M_ESP_Weapons )
		return;

	Vector AbsScreen;
	Vector origin = GetOrigin(pBaseEntity);

	if ( origin.x == 0 && origin.y == 0 && origin.z == 0 )
		return;

	if( TransformVector( origin, AbsScreen ) == false )
		return;

	Color DrawColor = Color(255, 255, 0, 255);

	CenterText( AbsScreen.x, AbsScreen.y, DrawColor.r(), DrawColor.g(), DrawColor.b(), DrawColor.a(), classname );

}

void DrawCustomESP( C_BaseEntity *pBaseEntity, char *classname)
{
	
	if ( !classname )
		return;

	if ( !&menu->T_CustomESP )
	{
		return;
	}

	string strClassnames = menu->T_CustomESP;

	std::vector<std::string> Classnames;
	boost::split(Classnames, strClassnames, boost::is_any_of(" "), boost::algorithm::token_compress_on);
	
	if ( !&Classnames )
		return;

	bool is_valid = false;
	int pretty = Classnames.size() - 1;

	if ( !pretty )
		return;

	for(int i = 0; i <= pretty; i++)
	{

		if ( !&Classnames[i] )
			continue;

		if ( !Classnames[i].c_str() )
			continue;

		if ( Classnames[i].compare( classname ) == 0 )
		{
			is_valid = true;
			break;
		}
	}

	if ( !is_valid )
		return;

	Vector AbsScreen;
	Vector origin = GetOrigin(pBaseEntity);

	if ( origin.x == 0 && origin.y == 0 && origin.z == 0 )
		return;

	if( TransformVector( origin, AbsScreen ) == false )
		return;

	if ( AbsScreen.x == 0 && AbsScreen.y == 0 && AbsScreen.z == 0 )
		return;

	Color DrawColor = Color(255, 255, 0, 255);

	CenterText( AbsScreen.x, AbsScreen.y, DrawColor.r(), DrawColor.g(), DrawColor.b(), DrawColor.a(), classname );

}


void DrawESP( LPDIRECT3DDEVICE9 pDevice )
{

	if( !bIsReady )
		return;

	for( int i = 1; i < HighestEntityIndex; i++ )
	{

		if( i == g_pEngine->GetLocalPlayer() )
			continue;

		IClientEntity *clEnt = g_pEntList->GetClientEntity(i);

		if ( !clEnt )
			continue;


		C_BaseEntity *pBaseEntity = clEnt->GetBaseEntity();

		if ( !pBaseEntity )
			continue;

		const char *classname = C_BaseEnt_Classname( pBaseEntity, NULL );

		if ( !classname )
			continue;

		bool is_living = false;
		bool is_npc = false;

		if ( menu->M_Aim_KillPlayer && strstr(clEnt->GetIClientEntity()->GetClientNetworkable()->GetClientClass()->GetName(), "Player") )
		{
			is_living = true;
		}

		if ( menu->M_ESP_NPCs && strstr(classname, "npc_") )
		{
			is_npc = true;
			is_living = true;
		}

		if ( is_living )
		{
			DrawLivingESP( i, pBaseEntity, classname );
			continue;
		}

		if ( strstr(classname, "weapon") )
		{
			DrawWeaponESP( pBaseEntity, classname );
			continue;
		}

		//DrawCustomESP( pBaseEntity, classname );

	}

}

void DrawViewESP( LPDIRECT3DDEVICE9 pDevice )
{

	Vector Eyes, Forward;
	QAngle Angles = viewAng;
	trace_t tr;
	Ray_t pRay;

	Eyes = GetEyePosition(pLocalEntity);

	Vector vDirection;

	AngleVectors( Angles, &vDirection );

	vDirection = vDirection * 8192 + Eyes;

	CTraceFilter filter;
	filter.pSkip = pLocalEntity;

	pRay.Init( Eyes, vDirection );
	g_pEngineTrace->TraceRay( pRay, MASK_ALL, &filter, &tr);
	
	const char *classname = "worldspawn";

	if ( !tr.m_pEnt || tr.m_pEnt->index == 0 )
		classname = "worldspawn";
	else
		classname = C_BaseEnt_Classname( tr.m_pEnt, NULL );

	PrintText(classname, ScrW - 300, 2, Black, Font.g_pFont2);

}

void DrawAimLine( LPDIRECT3DDEVICE9 pDevice )
{

	if ( pAimEntity == NULL )
		return;

	Vector AbsScreen;

	if( TransformVector( pAimVec, AbsScreen ) == false )
		return;

	DrawLine( CenterX + CenterX/3, CenterY + CenterY/3, AbsScreen.x, AbsScreen.y + 5, 4, Blue );

}

void DrawMouse( )
{

	DWORD color = LightCyan;

	POINT myCursor = menu->Cur;

	DrawFilledRectangle( myCursor.x,myCursor.y,11,1,color );
	DrawFilledRectangle( myCursor.x+1,myCursor.y+1,9,1,color );
	DrawFilledRectangle( myCursor.x+2,myCursor.y+2,7,1,color );
	DrawFilledRectangle( myCursor.x+3,myCursor.y+3,7,1,color );
	DrawFilledRectangle( myCursor.x+4,myCursor.y+4,8,1,color );
	DrawFilledRectangle( myCursor.x+5,myCursor.y+5,3,1,color );
	DrawFilledRectangle( myCursor.x+6,myCursor.y+6,2,1,color );
	DrawFilledRectangle( myCursor.x+7,myCursor.y+6,1,1,color );
	DrawFilledRectangle( myCursor.x+5,myCursor.y+10,4,1,color );
	DrawFilledRectangle( myCursor.x+6,myCursor.y+12,2,1,color );

}

void TestDrawStatus(LPDIRECT3DDEVICE9 pDevice)
{

	HRESULT coopLevel = pDevice->TestCooperativeLevel();

	if ( coopLevel != D3D_OK )
	{
		Sleep(500);
		Font.g_pFont->OnResetDevice();
		Font.g_pFont2->OnResetDevice();
		pSprite->OnResetDevice();
		pLine->OnResetDevice();
		CenterX = 0;
		CenterY = 0;

		return;
	}

	if ( !pDevice )
			return;

	if ( CenterX == 0 || CenterY == 0 )
		GetCenter( pDevice );

	if ( menu->S_CrossHair != 0 )
		DrawCrosshair( pDevice );

	if ( bIsReady )
	{

		if ( menu->M_ESP != 0 )
			DrawESP( pDevice );

		if ( menu->M_ESP_ViewESP != 0 )
			DrawViewESP( pDevice );

		if ( menu->M_AimEnable && menu->M_Aim_Silent )
			DrawAimLine( pDevice );

	}

	if ( menu_isopen )
	{
		menu->DrawMenu();
		DrawMouse( );
	}

}

bool once = true;
DWORD dwOldFVF, old_Alpha, old_zEnable;
IDirect3DBaseTexture9 *dw_oldNullTex;
IDirect3DPixelShader9 *pOldShader;
HRESULT __fastcall newPresent(void* thisptr, int edx, LPDIRECT3DDEVICE9 pDevice, const RECT* rect_source, const RECT* rect_dest, HWND dest_hwnd, const RGNDATA* dirtyregion)
{
	if ( !m_pDevice )
		m_pDevice = pDevice;

	if ( once )
	{
		Font.FontManager(pDevice);
		menu->InitMenu();
		once = false;

		menu_isopen = true;

		return PresentFn( thisptr, edx, pDevice, rect_source, rect_dest, dest_hwnd, dirtyregion );
	}

	if ( !old_Alpha || !old_zEnable || !pOldShader || !dwOldFVF )
	{
		pDevice->GetRenderState(D3DRS_ALPHABLENDENABLE, &old_Alpha);
		pDevice->GetRenderState(D3DRS_ZENABLE, &old_zEnable);
		pDevice->GetTexture( NULL, &dw_oldNullTex );
		pDevice->GetPixelShader( &pOldShader );
		pDevice->GetFVF( &dwOldFVF );
	}

    pSprite->Begin( D3DXSPRITE_ALPHABLEND );
	pDevice->SetTexture( NULL, NULL );
	pDevice->SetRenderState( D3DRS_ALPHABLENDENABLE, D3DZB_TRUE );
	pDevice->SetRenderState( D3DRS_ZENABLE, D3DZB_FALSE );
    pDevice->SetFVF( D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1 );

	TestDrawStatus(pDevice);

	pSprite->End();
	pDevice->SetRenderState( D3DRS_ALPHABLENDENABLE, old_Alpha );
	pDevice->SetRenderState( D3DRS_ZENABLE, old_zEnable );

	pDevice->SetPixelShader( pOldShader );
    pDevice->SetFVF( dwOldFVF );	
	pDevice->SetTexture( NULL, dw_oldNullTex );

	return PresentFn( thisptr, edx, pDevice, rect_source, rect_dest, dest_hwnd, dirtyregion );

}


void timers( )
{
    while(1)
	{
		if( GetAsyncKeyState(VK_DELETE)&1 )
			menu_isopen = !menu_isopen;

		Mentranium_Think();
		menu->MenuNavigation();
		Sleep(50);
	}

}

int StartLoading( )
{
	while( true )
	{

		if ( GetModuleHandleA( "client.dll" ) && GetModuleHandleA( "engine.dll" ) && GetModuleHandleA("server.dll") && GetModuleHandleA( "gameoverlayrenderer.dll") )
			break;

		Sleep(50);
	}
	
	Sleep(300);

	ClientDLLHandle = GetModuleHandleA("client.dll");
	EngineDLLHandle = GetModuleHandleA( "engine.dll" );
	ServerDLLHandle = GetModuleHandleA("server.dll");
	GameOverlayDLLHandle = GetModuleHandleA( "gameoverlayrenderer.dll" );

	dwClientDLLHandle = (DWORD)ClientDLLHandle;
	dwEngineDLLHandle = (DWORD)EngineDLLHandle;
	dwServerDLLHandle = (DWORD)ServerDLLHandle;
	dwGameOverlayDLLHandle = (DWORD)GameOverlayDLLHandle;


	CvarFactory = VStdLib_GetICVarFactory();
	clientFactory = (CreateInterfaceFn)GetProcAddress( ClientDLLHandle, "CreateInterface" );
	engineFactory = (CreateInterfaceFn)GetProcAddress( EngineDLLHandle, "CreateInterface" );
	serverFactory = (CreateInterfaceFn)GetProcAddress( ServerDLLHandle, "CreateInterface" );

	if( !CvarFactory || !clientFactory || !engineFactory )
	{
		//MessageBox( NULL, "Could not get a factory !", "Critical Error !!!", MB_OK );
		char *p = NULL;
		char x = NULL;
		*p = x;
		return 0;
	}

    // Hook required functions
	if ( GetInterfaces() == -1 )
	{
		char *p = NULL;
		char x = NULL;
		*p = x;
		return 0;
	}

	if ( HookStuff() == -1 )
	{
		char *p = NULL;
		char x = NULL;
		*p = x;
		return 0;
	}

	if ( g_pGameManager == NULL )
	{
		MessageBox( NULL, "Could not get game g_pGameManager !", "Critical Error !!!", MB_OK );
		return 0;
	}

	g_pGameManager->AddListener( &GameEventHandler, "game_newmap", false);

	DWORD dwPresent = dwFindPattern(dwGameOverlayDLLHandle, (PBYTE)"\x55\x8B\xEC\x83\xEC\x44\x53\x56\x8B\x75\x08\x57\x8B\x3D\x00\x00\x00\x00\x33\xDB\x89\x75\xFC\x85\xFF\x74\x0F\x6A\xFF", "xxxxxxxxxxxxxx????xxxxxxxxxxx");

	if  ( !dwPresent )
	{
		MessageBox( NULL, "no Present", "go back to the past", MB_OK );
		return 0;
	}

	menu = new cMenu();

	PresentFn = (OriginalPresent)DetourCreate((void*)dwPresent, (void*)newPresent, DETOUR_TYPE_JMP);

	CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)timers, NULL, NULL, NULL);

	return 0;
}

DWORD WINAPI hookthread( LPVOID Param )
{
	StartLoading();

	return 1;
}

BOOL WINAPI DllMain( HMODULE hModule, DWORD reason, LPVOID lpReserved )
{

	if (reason == DLL_PROCESS_ATTACH)
	{
		CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)hookthread, NULL, NULL, NULL);
		return 1;
	}

	return 0;
}