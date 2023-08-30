#if !defined(ATUMDEFINE_H__7699F556_5313_4782_B433_068C5F32BBC0__INCLUDED_)
#define ATUMDEFINE_H__7699F556_5313_4782_B433_068C5F32BBC0__INCLUDED_


#include "ObjectDefine.h"
//#include "Contents.h"

#define OPTION_DEFAULT_SOUNDVOLUME			-2000	// �Ҹ� 
#define OPTION_DEFAULT_STAGE_EFFECT_SOUNDVOLUME	-1000	// �Ҹ� 
#define OPTION_DEFAULT_MUSICVOLUME			8//-2000	// ����
#define OPTION_DEFAULT_GAMMA				0		// ����
#define OPTION_DEFAULT_LOWQUALITY			0		// �ּһ���
#define OPTION_DEFAULT_HELPDESK				1		// ����
#define OPTION_DEFAULT_REVERSE_LEFT			0		// �¿� ����
#define OPTION_DEFAULT_REVERSE_UP			0		// ���� ����
#define OPTION_DEFAULT_AUTO_BALACE			1		// �ڵ� ���� ����
#define OPTION_DEFAULT_PET_OP				1		// �޴� ���� �ڵ� ��������
#define OPTION_DEFAULT_MENU_USE				1		// 2010. 10. 26 by jskim �� ���۷����� �ɼ� ó��

#define OPTION_DEFAULT_MP3_USE				1		// ���� �÷��̾�




#define MAX_OPTION_VALUE						9



#define MIP_FILTER_DISTANCE						60




#define MAP_TYPE_CITY_UNIT_POS					D3DXVECTOR3(2400,19,2400)




#define HELPDESK_STATE_DEFAULT					0			// �����������ʴ´�
#define HELPDESK_STATE_NEW						1			// ���ο� ĳ���͸� ��������� ����
#define HELPDESK_STATE_CITY						2			// ���� ������ ����
#define HELPDESK_STATE_MISSION					3			// �̼� ����� ����
#define HELPDESK_STATE_FIELD					4			// �ʵ� ������ ����



// ĳ���������� ������ ��ġ
#define CHAT_MENU_CASH_START_W		65
#define CHAT_MENU_CASH_START_H		19
#define CHAT_MENU_CASH_START_X		(Pointer_CD3DApplication->GetBackBufferDesc().Width-CHAT_MENU_CASH_START_W)
#define CHAT_MENU_CASH_START_Y		(Pointer_CD3DApplication->GetBackBufferDesc().Height-CHAT_MENU_CASH_START_H-42)



// a��� 1�� ���� ȸ�� �߽���ǥ
//#define A_GEAR_PRIMARY_PORT_POSITION		D3DXVECTOR3(0.0f,0.662f,5.765f)
#define A_GEAR_PRIMARY_PORT_POSITION		D3DXVECTOR3(0.0f,0.0f,2.843f)


// 2009. 07. 07 by ckPark �κ���� ��û����(�Ѹ�, ����ȭ��, ����, A�������)
#define A_GEAR_ROBOT_PRIMARY_WEAPON_ITEM_NUM	7023980
// end 2009. 07. 07 by ckPark �κ���� ��û����(�Ѹ�, ����ȭ��, ����, A�������)




// sound code
#define SOUND_GET_ITEM						0
#define SOUND_WEAPON_RELOAD					7
#define SOUND_SEC_BULLET_RELOADED			9
#define SOUND_FLYING_M_A_GEAR				364//32
#define SOUND_HIGH_BOOSTER_START			360//33
#define SOUND_TAKINGOFF						34
#define SOUND_TAKEINGOFF_IN_CITY			35
#define SOUND_LOCKON_PRIMARY				36
#define SOUND_STAT_UP						38
#define SOUND_WEAR_WEAPON					39
#define SOUND_WARNING						40
#define SOUND_INPUT_CHAT					41
#define SOUND_SEND_CHAT						45
#define SOUND_SELECT_UNIT_CLICK				54
#define SOUND_SELECT_BUTTON					55
#define SOUND_SELECT_UNIT_STOP				56
#define SOUND_SELECT_ROTATE					57
#define SOUND_OFF_WEAPON					58
#define SOUND_MOVING_ON_WATER				60
#define SOUND_FLYING_B_I_GEAR				362//64
#define SOUND_LANDING						67
#define SOUND_LANDING_IN_CITY				68
#define SOUND_WARNING_HP					72
#define SOUND_BUTTON_MGAME					73
#define SOUND_BUTTON_OK						74
#define SOUND_BUTTON_CANCEL					75
#define SOUND_LOCKON_SECONDARY				76
#define SOUND_OPEN_MENU						80
#define SOUND_OPEN_MESSAGE_BOX				81
#define SOUND_WARP							82
#define SOUND_USEITEM_REPAIR_HP				83
#define SOUND_USEITEM_REPAIR_DP				84
#define SOUND_CLOSE_MENU					88
#define SOUND_CLOSE_MESSAGE_BOX				89
#define SOUND_GROUND_MOVING_A_GEAR			91
#define SOUND_LANDING_DONE					96
#define SOUND_MISSILE_WARNNING				97			// 2005-07-08 by ispark // �̻��� ���
#define SOUND_LUCKY_COIN					98
#define SOUND_LUCKY_SLOT					99
#define SOUND_WARP_2						2006023		// 2008-06-24 by dgwoo #define SOUND_WARP	82  ���� ���� �߰�.
#define	SOUND_DISSOLUTION					400031      // 2011-03-08 by jhahn ���� ����

#define SOUND_HIGH_BOOSTER					361//1033
#define SOUND_HIGH_BOOSTER_END				363//2033
#define SOUND_LOW_BOOSTER_START				360//3033
#define SOUND_LOW_BOOSTER					361//4033
#define SOUND_LOW_BOOSTER_END				365//5033

#define SOUND_PVP_COUNT						300000
#define SOUND_PVP_START						300002

// 2006-10-11 by ispark, ĸ�� ����
#define SOUND_POWER_ENERGY_CAPSULE			400001
#define SOUND_POWER_SHIELD_CAPSULE			400500
#define SOUND_POWER_SP_CAPSULE				22
#define SOUND_ADRENALIN_CAPSULE				400037
#define SOUND_BRAVE_CAPSULE					400504
#define SOUND_HYPER_BOOSTER_CAPSULE			400545



//#define IS_CLIENT_SET_AUTOMATIC_TIMER(x)	x == ITEMKIND_AUTOMATIC ||			\
//											x == ITEMKIND_GRENADE ||			\
//											x == ITEMKIND_RIFLE ||				\
//											x == ITEMKIND_LAUNCHER
#define IS_CLIENT_SET_AUTOMATIC_TIMER(x)	((x >= ORBIT_SINGLE_FIRE_200 && x <= ORBIT_SINGLE_FIRE_350 )||			\
											(x >= ORBIT_TWIN_FIRE_200 && x <= ORBIT_TWIN_FIRE_350)||				\
											(x >= ORBIT_STRAIGHT_ROCKET_250 && x <= ORBIT_STRAIGHT_MISSILE_300)||	\
											(x >= ORBIT_SINGLE_FIRE_100 && x <= ORBIT_TWIN_FIRE_150))



#define IS_OBJECTMONSTER_BY_MONSTERFORM(x)	((x) == FORM_OBJECT_STOP ||			\
											(x) == FORM_OBJECT_PLANE_ROTATE ||	\
											(x) == FORM_OBJECT_CANNON)








// ���� ���� Enemy Flag ����
#define PK_NONE		0x00000000
#define PK_PVP		0x00000001
#define PK_FVF		0x00000002
#define PK_GVG		0x00000004
#define PK_WAR		0x00000008
#define PK_NORMAL	0x00000010	// ���� PK
#define PK_ALL		0xFFFFFFFF



#define IS_WEAPON_ENABLESTATE(state,booster)	state == _NORMAL &&											\
												booster != BOOSTER_TYPE_AIRBREAK	&&						\
												!g_pGameMain->m_pTrade->m_bTrading &&						\
												!Pointer_CD3DApplication->m_bChatMode &&									\
												g_pGameMain->m_nLeftWindowInfo == LEFT_WINDOW_WEAPON &&		\
												g_pGameMain->m_nRightWindowInfo == RIGHT_WINDOW_WEAPON &&	\
												g_pShuttleChild->m_bRollUsed == FALSE &&					\
												g_pShuttleChild->m_bUnitStop == FALSE &&					\
												g_pShuttleChild->m_bPenaltyUnitStop == FALSE






#define BOOSTER_OVERHEAT_REPAIR_TIME			10.0f	// 10��




// ���� �ִ� ����
#define MAX_MINE_NUM				100






#define WATER_TEXTURE_COUNT			40




// 2004-10-13 by jschoi
// ��ų ���� 
#define SKILL_STATE_READY			0
#define SKILL_STATE_WAITING_PREPARE	1
#define SKILL_STATE_PREPARE			2
#define SKILL_STATE_WAITING			3
#define SKILL_STATE_USING			4
#define SKILL_STATE_WAIT_REATTACK	5
#define SKILL_STATE_RELEASE			6



// 2005-11-22 by ispark, �������� ����
//// ��ų ���� ����
//#define	SIEGE_MODE			7820050	// 2005-11-18 by ispark 7820040 -> 7820050
//#define SIEGE_DEFENSE_MODE	7821040	// 2005-11-18 by ispark 7821030 -> 7821040
//#define GROUND_ATTACK_MODE	7800040
//#define SMART_SPEED			7812020
//#define GROUND_ACCELERATOR	7822010	// 2005-11-18 by ispark 7822020 -> 7822010
//#define FLASH_ACCELERATOR	7822030


// ���� �� �̻� ��½� ���
#define ALTITUDE_APPLY_MIN			600.0f
#define ALTITUDE_APPLY_MAX			1600.0f
#define ALTITUDE_DEST_RATE			0.8f
#define ALTITUDE_SAPCE_ALTITUDE		800.0f






// 1�� ����, ��ü ���� �ӵ�
#define MAX_WEAPON_SPEED	3000.0f











// Object Type
#define OBJECT_NORMAL			0		// �Ÿ� �����ø��˻�,����ü �ø��˻�, EX:�Ϲ� ������Ʈ(����)
#define OBJECT_BIG				1		// �Ÿ��� ������� ������ ������,����ü �ø��� �˻�, EX:��������Ʈ,������
#define OBJECT_BIG_CULLED		2		// �����ø�*(������ �������� ������ �˻�), EX:�Ļ�
#define OBJECT_BIG_NO_COLLISION	3		// �����ø�*(������ �������� ������ �˻�), �浹�˻� ����, EX:�̿�
#define OBJECT_BIG_EFFECT		4		// �Ÿ� �����ø��� �˻�.( ����Ʈ�� ���� ������Ʈ ), EX:��������Ʈ,ȭ������Ʈ
#define OBJECT_MONSTER			7		// ������ ���ϰ�, �浹�˻� ���ϴ� ������Ʈ, EX:���� ������Ʈ
#define OBJECT_MONSTER_OBJECT	8		// ������Ʈ ���� ����� ��ü�Ǵ� ������Ʈ Ÿ�� , EX:�ھ� ������Ʈ
#define OBJECT_WATER			9		// �� Ÿ�� ������Ʈ(�����Ұ�,�̴ϸ� ������ �Ұ�,������ ������ ����� ������Ʈ �߻�,���� ���� ��Ͼ���)
// Object Type�� �߰�
#define OBJECT_BIG_CONTOUR		10		// �����ø�*(������ �������� ������ �˻�), �̴ϸʿ��� ���������� ����, �浹 �˻� ���� ����, EX:�� �ܰ� ������Ʈ
#define OBJECT_SHOP_NPC			11		// ���� NPC ĳ���� (���� �˻� ����� �������� ����(NO Picking))


















#define	UNIT_STATE_MOVE(x)		(x == _NORMAL ||		\
								x == _EXPLODING ||		\
								x == _FALLING ||		\
								x == _LANDING ||		\
								x == _TAKINGOFF)

#define UNIT_STATE_NO_MOVE(x)	(x == _LANDED ||		\
								x == _FALLEN ||			\
								x == _EXPLODED)



// 2006-01-18 by ispark
#define UNIT_STATE_DEAD(x)		(x == _FALLING ||		\
								x == _FALLEN)











#define STAGE_EFFECT_MASANGSOFT			0
#define STAGE_EFFECT_MGAME				1
#define STAGE_EFFECT_GAME_LOGO			2
#define STAGE_EFFECT_GAME_WAITING		3














// �ó׸� ���� Ÿ��
#define PATTERN_SOUND					0
#define PATTERN_UNIT					1
#define PATTERN_MONSTER					2
#define PATTERN_OBJECT					3
#define PATTERN_INTERFACE				4
#define PATTERN_TILE					5
#define PATTERN_EFFECT					6
#define PATTERN_ITEM					7
#define PATTERN_CAMERA					8

#define PATTERN_DEFAULT					"99999999"

#define PATTERN_CAMERA_DEFAULT			8000000		// ����Ʈ ī�޶�
#define PATTERN_CAMERA_COBRA			8000001		// ���� �ں�� ��ų ī�޶�
#define PATTERN_CAMERA_FALLING			8000002
#define PATTERN_CAMERA_WARP_OUT			8000003		// ���� ���ö�
#define PATTERN_CAMERA_WARP_IN			8000004		// ���� ����
#define PATTERN_CAMERA_CITY_OUT			8000005		// ��� ����
#define PATTERN_CAMERA_CITY_IN			8000006		// ��� ����
#define PATTERN_CAMERA_GAME_START		8000007
#define PATTERN_CAMERA_GAME_END			8000008
#define PATTERN_CAMERA_LANDING			8000009
#define PATTERN_CAMERA_AIRPORT_IN		8700000
#define PATTERN_CAMERA_AIRPORT_OUT		5020001		// 2006-11-01 by dgwoo //8800000
#define PATTERN_CAMERA_AIRPORT_NORMALCITY_OUT		5020002		// 2007-06-13 by bhsohn ��ī���̸� �ó׸� �߰�
#define PATTERN_CAMERA_FAIL_INFINITY	5020004		// ���Ǵ�Ƽ ���� ī�Ŷ� ����
#define PATTERN_CAMERA_SUCCESS_INFINITY	5020005		// ���Ǵ�Ƽ ���� ī�Ŷ� ����
#define PATTERN_CAMERA_FAIL_INFINITYTHIRD		5020006			// 2011-06-23 by jhahn ����3�� �ó׸� ���� ī�޶� ����
#define PATTERN_CAMERA_SUCCESS_INFINITYTHIRD	5020007			// 2011-06-23 by jhahn ����3�� �ó׸� ���� ī�޶� ����


#define PATTERN_UNIT_FALLING			1000001
#define PATTERN_UNIT_WARP_OUT			1000002
#define PATTERN_UNIT_WARP_IN			1000003
#define PATTERN_UNIT_CITY_OUT			1000004
#define PATTERN_UNIT_CITY_IN			1000005
#define PATTERN_UNIT_GAME_START			1000006		// ��� ����
#define PATTERN_UNIT_GAME_END			1000007		// ��� ����
#define PATTERN_UNIT_AIRPORT_IN			1700000
#define PATTERN_UNIT_AIRPORT_OUT		1800000



// �浹 Ÿ��
#define COLL_NONE		-1
#define COLL_FRONT		0
#define	COLL_BACK		1
#define	COLL_LEFT		2
#define	COLL_RIGHT		3
#define	COLL_UP			4
#define	COLL_DOWN		5
#define	COLL_WHOLE		6







// ���� ��ų ����
#define MONSTER_SKILL_ON				1
#define MONSTER_SKILL_OFF				2
#define MONSTER_WAIT_END_SKILL			3








// ���� ����Ÿ ��ǥ
#define DUMMY_POSITION_1			D3DXVECTOR3( 0.0f, -3.75f, -19.31f )
#define DUMMY_POSITION_2			D3DXVECTOR3( 19.31f, -3.75f, 11.80f )
#define DUMMY_POSITION_3			D3DXVECTOR3( -19.31f, -3.75f, 11.80f )
#define DUMMY_POSITION_4			D3DXVECTOR3( 0.0f, 9.7f, 11.80f )
#define DUMMY_POSITION_5			D3DXVECTOR3( 0.0f, -3.75f, 24.52f )













// ����Ʈ ���(�ó׸� ������)
#define DEFAULT_CURVATURE					1.0f




// �� ������Ʈ �з� ���� ũ��
#define BIG_OBJECT_SIZE		100


// �� ���� �з� ���� ũ��
#define BIG_MONSTER_SIZE	150.0f


#define GUI_FONT_COLOR						RGB(222, 222, 222)		// �⺻ ����(���) white
#define GUI_SELECT_FONT_COLOR				RGB(1, 1, 1)			// ���� ����(������) black
#define GUI_FONT_COLOR_YM					RGB(255, 168, 0)		// �⺻ ����(��Ȳ��) orange
#define GUI_FONT_COLOR_BM					RGB(178, 190, 255)		// �⺻ ����(�����ϴû�) light blue
#define GUI_FONT_COLOR_Y					RGB(255, 255, 0)		// �⺻ ����(�����) yellow
#define GUI_FONT_COLOR_R					RGB(255, 0, 0)			// �⺻ ����(������) red
#define GUI_FONT_COLOR_G					RGB(128, 128, 128)		// �⺻ ����(ȸ����) green
#define GUI_FONT_COLOR_B					RGB(0, 0, 255)			// �⺻ ����(�Ķ���) blue
#define GUI_FONT_COLOR_W					RGB(255, 255, 255)		// �⺻ ����(���) white
#define GUI_FONT_COLOR_GR					RGB(211, 211, 211)		// �⺻ ����(ȸ��) gray




#define NAME_COLOR_NORMAL					RGB(222, 222, 222)		// �⺻ �̸� ����
#define NAME_COLOR_ATTACKER					RGB(255, 50, 50)		// ���������� ������ �̸� ����
#define NAME_COLOR_DEFENSER					RGB(50, 50, 255)		// ���������� ����� �̸� ����





// ������ ����
#define ATTACK_AVAILABLE_STATE(X)	(X == _NORMAL || X == _LANDING || X == _TAKINGOFF || X == _LANDED) 
#define MOVE_AVAILABLE_STATE(X)		(X == _NORMAL || X == _LANDING || X == _TAKINGOFF || X == _LANDED) 












typedef DWORD InfUnitState_t;
// Inf Unit Warning
#define INF_UW_DANGER_MASK			(InfUnitState_t)0x00000001		// ��ü �ջ� ����
#define INF_UW_OVERHEAT_MASK		(InfUnitState_t)0x00000002		// �ν��� ����
#define INF_UW_LOWFUEL_MASK			(InfUnitState_t)0x00000004		// ���� ����
#define INF_UW_FULLITEM_MASK		(InfUnitState_t)0x00000008		// ������ �ʰ�(����)
#define INF_UW_TOOHIGH_MASK			(InfUnitState_t)0x00000010		// �� ����
#define INF_UW_LOWSHIELD_MASK		(InfUnitState_t)0x00000020		// ���� ����
#define INF_UW_FULLITEM1_MASK		(InfUnitState_t)0x00000040		// ������ �ʰ�(70%)
#define INF_UW_FULLITEM2_MASK		(InfUnitState_t)0x00000080		// ������ �ʰ�(80%)
#define INF_UW_FULLITEM3_MASK		(InfUnitState_t)0x00000100		// ������ �ʰ�(90%)

// Inf(�������̽�) Unit State
#define INF_US_TAKEOFF_MASK			(InfUnitState_t)0x00010000		// �̷��� ����(Take Off ) - �ٽ�����-0(ins)
#define INF_US_STOP_MASK			(InfUnitState_t)0x00020000		// ���� ���߿� ������ - ���� -����Ű W
#define INF_US_LOCK_MASK			(InfUnitState_t)0x00040000		// �����ϼ� ���� ����(Unit Lock) - R
#define INF_US_FORM_MASK			(InfUnitState_t)0x00080000		// formation ��������( �շ�Ű f2)
#define INF_US_LAND_MASK			(InfUnitState_t)0x00100000		// ���� Landing, ������ - �ٽ� �̷� W















// ��ư�� ����� �ٴ� ��ư�� ���.[2][2]
#define BUTTON_BOTH_STATE_NORMAL		0
#define BUTTON_BOTH_STATE_UP			1
#define BUTTON_BOTH_STATE_NUMBER		2

// �������̽� ��ư ����
#define BUTTON_STATE_UP			0
#define BUTTON_STATE_DOWN		1
#define BUTTON_STATE_DISABLE	2
#define BUTTON_STATE_NORMAL		3

#define BUTTON_STATE_NUMBER		4

// ����� ��ư.
#define	RADIOBUTTON_STATE_NORMAL	0
#define RADIOBUTTON_STATE_SELECT	1
#define RADIOBUTTON_STATE_NUMBER	2

// ������ �̹��� Ÿ�ٿ� ���� define
#define TOOLTIP_IMGTYPE_NORMAL					0
#define TOOLTIP_IMGTYPE_TELEPORT_SUC			1			// �ڷ���Ʈ�� ��ġ �Ǿ����ϴ�.
#define TOOLTIP_IMGTYPE_TELEPORT_DESTROY		2			// �ڷ���Ʈ�� �ı� �Ǿ����ϴ�.





// �������� ���� �Ծ��� ��� �ٵ������ ������ ���� ���(����, ����)
#define CHARACTER_DAMAGE_STATE_05		0.25f
#define CHARACTER_DAMAGE_STATE_10		0.35f
#define CHARACTER_DAMAGE_STATE_15		0.40f





// UNIT_STATE : ���� ����
#define CHARACTER_LOWFUEL_STATE			0.1f





// ���� Ÿ�� ����Ʈ �ߵ��� ����� ���ְ��� �Ÿ�
#define SIZE_OF_SHIELD_EFFECT						15.0f
// 1�� ���� ���ݽ� ���ֿ��� �����ϰ� �����ϴ� �Ÿ�
#define SIZE_OF_PRIMARY_ATTACK_RANDOM_DISTANCE		10








// shield bodycondition
#define BODYCON_SHIELD_ON_MASK			BODYCON_FIRE_MASK
#define BODYCON_SHIELD_OFF_MASK			BODYCON_HIT_MASK
#define BODYCON_SHIELD_ING_MASK			BODYCON_BULLET_MASK
// charging shot bodycondition
#define BODYCON_CHARGING_MASK			BODYCON_LANDED_MASK		// 2
#define BODYCON_USE_SKILL_MASK			BODYCON_FLY_MASK		// 1 , USE_SKILL�� ���� ����Ѵ�.
#define BODYCON_TARGET_USE_SKILL_MASK	BODYCON_DEAD_MASK		// 3 , ��ų�� ���� ����Ʈ �ٵ������








//ī�޶� Ÿ��
#define CAMERA_TYPE_NORMAL			0//3��Ī
#define CAMERA_TYPE_FPS				1//1��Ī








// ������ ���� ���� �Ÿ�
#define WEATHER_DEFAULT_FOG_START	50.0f
#define WEATHER_DEFAULT_FOG_END		640.0f
#define WEATHER_SUNNY_FOG_START		1900.0f//4000.0f
#define WEATHER_SUNNY_FOG_END		2500.0f//6300.0f
#define WEATHER_RAINY_FOG_START		100.0f
#define WEATHER_RAINY_FOG_END		400.0f
#define WEATHER_SNOWY_FOG_START		1000.0f//0.0f			// 2006-12-11 by ispark
#define WEATHER_SNOWY_FOG_END		1800.0f//600.0f			// 2006-12-11 by ispark
#define WEATHER_CLOUDY_FOG_START	300.0f
#define WEATHER_CLOUDY_FOG_END		2250.0f
#define WEATHER_FOGGY_FOG_START		0.0f
#define WEATHER_FOGGY_FOG_END		200.0f





#define SHOP_ITEM_SLOT_NUMBER		5
#define SHOP_ITEM_TAB_NUMBER		4






#define IS_ITEM_SHOP_TYPE(x)		(x == BUILDINGKIND_1ST_WEAPONSHOP ||	\
									x == BUILDINGKIND_2ND_WEAPONSHOP ||		\
									x == BUILDINGKIND_COMPONENTSHOP ||		\
									x == BUILDINGKIND_PETSHOP ||			\
									x == BUILDINGKIND_ANTIQUESHOP ||		\
									x == BUILDINGKIND_REFINERY	||			\
									x == BUILDINGKIND_TUNING_COLOR)
#define IS_STORE_SHOP_TYPE(x)		(x == BUILDINGKIND_STORE)					// â��
#define IS_WARP_SHOP_TYPE(x)		(x == BUILDINGKIND_CITYWARP)					// ���� �ݳ���, ����
#define IS_MISSION_SHOP_TYPE(x)		(x == BUILDINGKIND_PUBLICOFFICE ||		\
									x == BUILDINGKIND_MILITARYACADEMY)			// ����б���Ʈ
#define IS_RACING_SHOP_TYPE(x)		(x == BUILDINGKIND_RACETRACK)				// ���̽���Ʈ
#define IS_ACTIONHOUSE_SHOP_TYPE(x)	(x == BUILDINGKIND_ACTIONHOUSE)				// �����Ʈ
#define IS_LABORATORY_SHOP_TYPE(x)	(x == BUILDINGKIND_LABORATORY)				// ������(��æƮ)
#define IS_FACTORY_SHOP_TYPE(x)		(x == BUILDINGKIND_FACTORY)					// ���丮(����)
#define IS_SKILL_SHOP_TYPE(x)		(x == BUILDINGKIND_SKILL_SHOP)				// ��ų����
#define IS_AUCTION_SHOP_TYPE(x)		(x == BUILDINGKIND_AUCTION)					// ���
#define IS_CITY_OCCUPY_INFO_TYPE(x)	(x == BUILDINGKIND_CITY_OCCUPY_INFO)		// ���� ����
#define IS_TUNING_COLOR_SHOP(x)		(x == BUILDINGKIND_TUNING_COLOR)			// Į�� ����
#define IS_CASH_SHOP_TYPE(x)		(x == BUILDINGKIND_CASH_SHOP)				// ĳ�� ����
#define IS_WARPOINT_SHOP_TYPE(x)	(x == BUILDINGKIND_WARPOINT_SHOP)			// �Ʒ��� 
#define IS_OUTPOST_SHOP_TYPE(x)		(x == BUILDINGKIND_CITYLEADER_LEADER ||	\
									 x == BUILDINGKIND_CITYLEADER_OUTPOST)			// �Ʒ��� 



// ���� ��ư ���� �߰�(�������� ������ ����)
#define BUILDINGKIND_OUTDOOR					99	//������



// HELP ����Ÿ �����ִ� ����
#define SHOW_TEXT_HELP_LEVEL		6



// ���� ����Ʈ �ٵ� �����
#define BODYCON_WARP_MASK					BODYCON_DEAD_MASK

// 2007-04-18 by dgwoo �Ʒ��� �ʿ��� �� ����.
#define BODYCON_DOOR_CLOSE_MASK				BODYCON_DEAD_MASK			// ���� �����ִ� ����.
#define BODYCON_DOOR_OPENING_MASK			BODYCON_LANDING_MASK		// ���� ������ �ִ� ����.
#define BODYCON_DOOR_OPEN_MASK				BODYCON_LANDED_MASK			// ���� ������ ����.
#define BODYCON_DOOR_CLOSING_MASK			BODYCON_NOT_USED1_MASK		// ���� ������ �ִ� ����.


// ���� ���� �ٵ� �����, UnitData.cpp
#define	WEAPON_BODYCON_LOADING				BODYCON_FLY_MASK		// ���� ������(������)
#define WEAPON_BODYCON_FIRE_1				BODYCON_LANDED_MASK		// ���ֿ��� ���Ⱑ �߻�Ǵ� ����(1��)
#define WEAPON_BODYCON_FIRE_2				BODYCON_DEAD_MASK		// ����߻����(2��), ������׽� ���
#define WEAPON_BODYCON_RELOAD				BODYCON_NOT_USED1_MASK	// ������






// ������ ����,�����̷� ������ �ٵ� �����
/*
#define	WEAPON_BODYCON_NORMAL				BODYCON_FLY_MASK		// ����(���� �ߵ��ϱ� ��)
#define WEAPON_BODYCON_START				BODYCON_LANDED_MASK		// ����-->�ڵ����� ��� ���·� �Ѿ
//#define WEAPON_BODYCON_ING				BODYCON_DEAD_MASK		// ��� ����(���� �ߵ�)�ʿ����
#define WEAPON_BODYCON_END					BODYCON_NOT_USED1_MASK	// ���� ����(���� �ߵ� ����-->�ڵ����� NORMAL�� �Ѿ)
*/
#define TOGGLE_WEAPON_BODYCON_NORMAL		(BodyCond_t)0x0000000000000002	// ����
#define TOGGLE_WEAPON_BODYCON_USE			(BodyCond_t)0x0000000000000004	// ����-->USING�� ���ÿ� ���
#define TOGGLE_WEAPON_BODYCON_USING			(BodyCond_t)0x0000000000000008	// ��� ����
#define TOGGLE_WEAPON_BODYCON_END			(BodyCond_t)0x0000000000000010	// ��� ����-->NORMAL�� ���ÿ� ���
#define TOGGLE_WEAPON_BODYCON_RELOAD		(BodyCond_t)0x0000000000000020	// ������



// ���� �Ϲ� ������ �ٵ� �����(����Ʈ �߰� ����, 2004-03-23 by dhkwon)
#define WEAR_ITEM_BODYCON_NORMAL			BODYCON_FLY_MASK








// ������ �ٵ�������� ����ī�ε庰�� SHIFT�ʿ� ���� ����
#define UNIT_KIND_SHIFT_DEFAULT				0	// �⺻(���Ϳ� ���)
#define UNIT_KIND_SHIFT_B_GEAR				0	// B���
#define UNIT_KIND_SHIFT_M_GEAR				10	// M���
#define UNIT_KIND_SHIFT_A_GEAR				20	// A���
#define UNIT_KIND_SHIFT_I_GEAR				30	// I���







// �Ÿ� ���� ���
#define RANGE_OF_VISION						1000.0f//750.0f	// ȭ�鿡 ���̴� �þ�
#define GET_INFO_DISTANCE_OF_2D				30.0f	// ȭ��󿡼� Ŭ������ ��� ������ �������� �Ÿ�
#define GET_ITEM_FROM_FIELD_DISTANCE		200.0f	// �ʵ� �������� �����ϴ� �Ÿ�
#define GET_ITEM_NUMBER_IN_TICK				2		// �ѹ��� ������ �� �ִ� ������ ��
#define GET_ITEM_IN_TIME					1.0f	// 2006-07-18 by ispark, �ѹ��� ������ �� �ִ� Ű ������ Ÿ��
#define DETETE_FIELD_ITEM_DISTANCE			750.0f	// �ʵ� �������� �������� �Ÿ�
#define SUN_DISTANCE						8000.0f	// �¾�, ���� �Ÿ�
#define DEFAULT_COLLISION_DISTANCE			10000.0f // �浹 �˻� ������ �ִ�Ÿ�
#define SEND_FC_TARGET_DISTANCE				400.0f	// MSG_FC_MOVE_TARGET ������ �ι�° �Ÿ�
#define REMOVE_ENEMY_DISTANCE				1000.0f//700.0f	// Enemy�� ����� �Ÿ�






// ���� ������ ����
#define WEAR_ITEM_KIND_WEAPON_11				0
#define WEAR_ITEM_KIND_WEAPON_12				1
#define WEAR_ITEM_KIND_WEAPON_21				2
#define WEAR_ITEM_KIND_WEAPON_22				3
#define WEAR_ITEM_KIND_PROW						4
#define WEAR_ITEM_KIND_CENTER					5

// 2010-06-15 by shcho&hslee ��ý���
//#define WEAR_ITEM_KIND_ATTACHMENT		6		// 2006-06-28 by ispark, ������ �Ǽ��縮
#define WEAR_ITEM_KIND_ACCESSORY_UNLIMITED		6		// 2006-06-28 by ispark, ������ �Ǽ��縮

#define WEAR_ITEM_KIND_ENGINE					7

// 2010-06-15 by shcho&hslee ��ý���
//#define WEAR_ITEM_KIND_PET						8
#define WEAR_ITEM_KIND_ACCESSORY_TIME_LIMIT		8		// 2006-06-28 by ispark, �ð����� �Ǽ��縮

#define WEAR_ITEM_KIND_WINGIN					9		// 2006-06-28 by ispark, �ð����� �Ǽ��縮

// 2010-06-15 by shcho&hslee ��ý���
//#define WEAR_ITEM_KIND_PARTNER					10		// 2010-06-08 by dgwoo, ��ý��� �߰�. 
#define WEAR_ITEM_KIND_PET						10


// ���� ������ ����Ʈ ��ȣ ��Ģ
#define EFFECT_WEAR_WEAPON_1			100000		// ������ ��ȣ���� �̰��� ���ϸ� ����Ʈ ��ȣ�� �ȴ�.
#define EFFECT_WEAR_WEPAON_11_DEFAULT	12100000
#define EFFECT_WEAR_WEPAON_12_DEFAULT	12200000
#define EFFECT_WEAR_WEAPON_2			700000		// ������ ��ȣ���� �̰��� ���� ����Ʈ ��ȣ�� �ȴ�.
#define EFFECT_WEAR_WEPAON_21_DEFAULT	12300000
#define EFFECT_WEAR_WEPAON_22_DEFAULT	12400000

// 2005-08-23 by ispark
#define EFFECT_NUMBER_WEAR_WEAPON_11(p1,p2)	(p1 ? p1->SourceIndex + EFFECT_WEAR_WEAPON_1 : EFFECT_WEAR_WEPAON_11_DEFAULT + p2*100)
#define EFFECT_NUMBER_WEAR_WEAPON_12(p1,p2)	(p1 ? p1->SourceIndex + EFFECT_WEAR_WEAPON_1 : EFFECT_WEAR_WEPAON_12_DEFAULT + p2*100)
#define EFFECT_NUMBER_WEAR_WEAPON_21(p1,p2)	(p1 ? p1->SourceIndex - EFFECT_WEAR_WEAPON_2 : EFFECT_WEAR_WEPAON_21_DEFAULT + p2*100)
#define EFFECT_NUMBER_WEAR_WEAPON_22(p1,p2)	(p1 ? p1->SourceIndex - EFFECT_WEAR_WEAPON_2 : EFFECT_WEAR_WEPAON_22_DEFAULT + p2*100)
#define EFFECT_NUMBER_WEAR_RADAR(x)			(x + 500000)

#define SELECT_MENU_DEFAULT_WEAR_WEAPON_11(x)	(EFFECT_WEAR_WEPAON_11_DEFAULT + x*100)
#define SELECT_MENU_DEFAULT_WEAR_WEAPON_12(x)	(EFFECT_WEAR_WEPAON_12_DEFAULT + x*100)
#define SELECT_MENU_DEFAULT_WEAR_WEAPON_21(x)	(EFFECT_WEAR_WEPAON_21_DEFAULT + x*100)
#define SELECT_MENU_DEFAULT_WEAR_WEAPON_22(x)	(EFFECT_WEAR_WEPAON_22_DEFAULT + x*100)
// ������ ����ī�ε庰 SHIFT ��Ģ�� ������ �ʴ´�.
#define GET_SHIFT_BODYCON_OF_UNITKIND_EXCEPT_ENGINE		(nWearItemKind == WEAR_ITEM_KIND_ENGINE || nWearItemKind == WEAR_ITEM_KIND_PET ) ? UNIT_KIND_SHIFT_DEFAULT : GetShiftWeaponBodyconditionByUnitKind()









// IM ���� ���� ��Ȳ, CINFMapLoad, AtumApplication
#define IM_SERVER_STATE_NOT_LOGIN			0
#define IM_SERVER_STATE_TRY_LOGIN			1
#define IM_SERVER_STATE_SUCCESS_LOGIN		2
#define IM_SERVER_STATE_READY_FOR_GAMESTART	3








// ��� �̸� ���� ��Ģ
// 1° ¥�� : 1
// 2° �ڸ� : ������ �ܰ�(low:0, middle:1, high:2)
// 5° �ڸ� ��� ����( B:0, M:1, A:2, I:3 )
// 6° �ڸ� ���׷��̵� ( 1�� : 1 , 2�� : 2, 3�� : 3, 4�� : 4 )
#define UNIT_EFFECT_INDEX(x,y,z)		(10000000+1000000*x+1000*y+100*z)// x : ������ �ܰ�, y : ���, z : ���׷��̵�

// ������ �ִϸ��̼��� �����ϴ� �ٵ������
//#define BODYCON_BOOSTER_EX_STATE_CLEAR_MASK	(BodyCond_t)(BODYCON_BOOSTER1_MASK | BODYCON_BOOSTER2_MASK | BODYCON_BOOSTER3_MASK | BODYCON_BOOSTER4_MASK | BODYCON_BOOSTER5_MASK)

// 2009. 07. 07 by ckPark �κ���� ��û����(�Ѹ�, ����ȭ��, ����, A�������)
// BODYCON_ROLLING_MASK �Ѹ��� �ִϸ��̼� �߰�

// 2009. 11. 02 by ckPark ���Ǵ�Ƽ �ʵ� �ν��Ͻ� ���� �ý���
// BODYCON_CREATION_MASK �߰�
#define BODYCON_CHARACTER_ANIMATION_TIME	(BodyCond_t)(BODYCON_BOOSTER_EX_STATE_CLEAR_MASK |	\
											 BODYCON_LANDING_MASK |								\
											 BODYCON_LANDED_MASK |								\
											 BODYCON_DEAD_MASK |								\
											 BODYCON_NOT_USED1_MASK	|							\
											 BODYCON_ROLLING_MASK)
#define BODYCON_MONSTER_ANIMATION_TIME		(BodyCond_t)(BODYCON_BOOSTER_EX_STATE_CLEAR_MASK |	\
											 BODYCON_LANDING_MASK |								\
											 BODYCON_LANDED_MASK |								\
											 BODYCON_EXPLOSION_MASK |							\
											 BODYCON_MON_ATTACKALL_MASK|						\
 											 BODYCON_MON_AUTODESTROYED_MASK|					\
											 BODYCON_MON_BUILD_MASK|							\
											 BODYCON_CREATION_MASK)
//											 BODYCON_NOT_USED1_MASK)
// �ν��� ������ ����ϴ� �ٵ������(SetFlyBodyCondition)
#define BODYCON_BOOSTER_OFF_MASK			0


// 2009. 07. 07 by ckPark �κ���� ��û����(�Ѹ�, ����ȭ��, ����, A�������)
// BODYCON_ROLLING_MASK �Ѹ��� �ִϸ��̼� �߰�
// ���� �ٵ������ ����ũ(CUnitData: ChangeBodyCondition,ResetBodyCondition)
#define BODYCON_ENGINE_STATE_MASK			(BODYCON_BOOSTER_EX_STATE_CLEAR_MASK |				\
											BODYCON_LANDING_MASK |								\
											BODYCON_LANDED_MASK	|								\
											BODYCON_TAKEOFF_MASK |								\
											BODYCON_SIEGE_OFF_MASK |							\
											BODYCON_SIEGE_ON_MASK |								\
											BODYCON_ROLLING_MASK)
// ���� �ٵ������ �� �������� ���� BODYCON_LANDED_MASK �� �ٲ�� ��
#define BODYCON_UNIT_TO_ENGINE_LANDED		(BODYCON_EXPLOSION_MASK	|							\
											BODYCON_DEAD_MASK)

// Ŭ���̾�Ʈ�� ������ �ٵ�������� �ϳ����� ����Ѵ�.
#define BODYCON_CLIENT_SINGLE				(BODYCON_EX_STATE_CLEAR_MASK|						\
											BODYCON_BOOSTER_EX_STATE_CLEAR_MASK|				\
											BODYCON_EXPLOSION_MASK|								\
											BODYCON_TAKEOFF_MASK|								\
											BODYCON_SIEGE_ON_MASK|								\
											BODYCON_SIEGE_OFF_MASK)
// ���ʹ� ������ �ٵ�������� �ϳ����� ����Ѵ�.
#define BODYCON_MONSTER_SINGLE				(BODYCON_EX_STATE_CLEAR_MASK|						\
											BODYCON_BOOSTER_EX_STATE_CLEAR_MASK|				\
											BODYCON_EXPLOSION_MASK|								\
											BODYCON_CREATION_MASK|								\
											BODYCON_LANDING_MASK|								\
											BODYCON_LANDED_MASK|								\
											BODYCON_MON_AUTODESTROYED_MASK)
// �Ʒ��� ��.
#define BODYCON_ARENA_DOOR_STATE			(BODYCON_DOOR_CLOSE_MASK|							\
											BODYCON_DOOR_OPEN_MASK|								\
											BODYCON_DOOR_CLOSING_MASK|							\
											BODYCON_DOOR_OPENING_MASK)

// ���� �ٵ�.
#define BODYCON_WARP_STATE					(BODYCON_LANDED_MASK|							\
											BODYCON_DEAD_MASK)

#define SET_CLIENT_BODYCON_BIT(VAR, MASK)								\
{																\
	CLEAR_BODYCON_BIT(VAR, (BODYCON_EX_STATE_CLEAR_MASK|BODYCON_BOOSTER_EX_STATE_CLEAR_MASK));	\
	VAR |= MASK;												\
}

// IME ���� ���� (�ĺ�����Ʈ ���̴� ��ġ)
#define SET_MAIN_CHAT_CANDIDATE				0			// ä�� �κ� 
#define SET_WHISPER_CHAT_CANDIDATE			1			// �Ӹ�â �κ� 
#define SET_MESSAGEBOX_CANDIDATE			2			// �޼��� �ڽ� �κ�
#define SET_FAQ_CANDIDATE					3			// FAQ �κ�
#define SET_CREATEMENU_CANDIDATE			4			// ����â �κ�
#define SET_DELETEMENU_CANDIDATE			5			// ĳ���� �����

#define CHAR_INF_CANDIDATE					10			// �ĺ�â ����Ʈ�� �ִ� 10���� �Ѵ�






// �� Ÿ�� �ѹ�
#define MAP_TYPE_TUTORIAL		0
#define MAP_TYPE_CITY			1		// 1000 ~
//
#define MAP_TYPE_NORMAL_FIELD	3		// 3000 ~
#define MAP_TYPE_SPECIAL_FIELD	4		// 4000 ~
#define MAP_TYPE_QUEST			5		// 5000 ~







#define BOOSTER_TYPE_BACK		-2//���� �ν���
#define BOOSTER_TYPE_AIRBREAK	-1//���� �ξ�
#define BOOSTER_TYPE_STOP		0//����
#define BOOSTER_TYPE_MIN		1//�⺻ �ν���
#define BOOSTER_TYPE_MAX		2//���� �ν���

#define HYPER_BOOSTER_NORMAL	-1// ������ �ν��� ��� ����
#define HYPER_BOOSTER_MAX		1 // ������ �ν��� ���


// 2005-02-21 by jschoi - �� ����
// 2009-02-24 by bhsohn ĳ���� ���� �������� �߰�
// #define WEB_WIDTH		742		// 720
// #define WEB_HEIGHT		344		// 338
#define WEB_WIDTH		660		// 720
#define WEB_HEIGHT		550		// 338// 2009-03-03 by bhsohn �Ϻ��������� ũ�� ����
// end 2009-02-24 by bhsohn ĳ���� ���� �������� �߰�
#define WEB_START_X		((Pointer_CD3DApplication->GetBackBufferDesc().Width-WEB_WIDTH)/2)
#define WEB_START_Y		((Pointer_CD3DApplication->GetBackBufferDesc().Height-WEB_HEIGHT)/2)



// 2005-03-03 by jschoi - RequestEnable
#define REQUEST_ENABLE_INIT_TIME	-4.0f//-1.0f	// 2006-09-22 by ispark, ������ ��ٸ��� Ÿ��(ȭ�鿡 ���� �غ� Ÿ��)
#define REQUEST_ENABLE_TIME			1.0f			// 2006-08-11 by ispark
#define REQUEST_ENABLE_BOX_WIDTH	255
#define REQUEST_ENABLE_BOX_HEIGHT	35


// 2005-03-08 by jschoi  - Check Gate Distance
#define CHECK_WARP_GATE_DISTANCE	500.0f


// 2005-03-25 by jschoi - Ÿ���� DEFINE
#define OLD_TARGETTING	0
#define NEW_TARGETTING	1
#define OLD2_TARGETTING	2

// // 2005-04-19 by jschoi - TUTORIAL
enum { NONEBOX, SKIPBOX, IMAGEBOX, IMAGEVIEW };
enum { ALPHA_WAVE, ALPHA_DELAY_WAVE, ALPHA_FADE_IN, ALPHA_FADE_OUT };

// 2005-07-07 by ydkim Mission ����
#define MISSION_RUN_SUCCESS		0	// �̼� ��� ���� ����
#define MISSION_RUN_RENDER_ERR	1	// �̼�â ���� ���°� �ƴϴ�
#define MISSION_RUN_ERROR		2	// ��Ÿ ���� ����

// 2005-07-07 by ispark
// �Ѹ� ���� ���ǹ�
#define ROLLING_USE_TIME	2.0f

// �̼� �޼��� ������( �̹��� ������ �� )
#define SENDMESSAGE_MISSION_COMPLETE		1
#define SENDMESSAGE_MISSION_CANCER			2
#define SET_MISSION_RESAULT_IMG_X			((Pointer_CD3DApplication->GetBackBufferDesc().Width/2)-142)
#define SET_MISSION_RESAULT_IMG_Y			((Pointer_CD3DApplication->GetBackBufferDesc().Height/3)-24)

// 2005-07-27 by ispark
// Picking ������Ʈ
#define PICKING_OBJECT_NUMBER		1100015

// ĳ���� �ٵ� �����
#define BODYCON_HUMAN_ANIMATION_TIME	(BODYCON_CHARACTER_MODE_STOP|BODYCON_CHARACTER_MODE_WALK|BODYCON_CHARACTER_MODE_RUN)

// ĳ���� ���� ���ǹ�
#define CHARACTER_SCALE				1.5f			// ĳ���� ������
#define CHARACTER_SHADOW_SCALE		6.0f			// ĳ���� �׸��� ������(�밢�� ������ ũ���̴�.

// 2005-08-08 by ydkim �۷��� �̹��� ���� ����
typedef enum
{
	MISSION_SUC = 0,		// �̼� ����
	MISSION_FAI = 1,		// �̼� ����
	MISSION_OUT = 2,
	OUT_ZONE = 3,

	GLOBAL_IMAGE_MAX_COUNT = 4		// �ִ� �̹��� ��
} IMAGE_LIST;

#define ICON_EXP_ITEMNUM						 7011210	//       39     ������_����ġ
#define ICON_LEV_ITEMNUM						 7011220	//       39     ������_����
#define ICON_BUN_ITEMNUM						 7011230	//       39     ������_���ʽ�����
#define ICON_PRO_ITEMNUM						 7011240	//       39     ������_��

#define CHARACTER_CAMERA_DISTANCE_MIN	10.0f	// �ּ� �Ÿ�
#define CHARACTER_CAMERA_DISTANCE_MAX	100.0f	// �ִ� �Ÿ�

enum { VOICE_NONE, VOICE_ONE, VOICE_PARTY, VOICE_GUILD };			// ���� ä�� ����

// 2005-10-07 by ispark
// Ʃ�丮�� ����Ʈ
enum { L0, L1, L2, L3, L4, L5, L6, L7, L8, L9, L10 };


// 2005-10-27 ydkim ������ â �켱�������� ó��
// ��Ī ������ �Լ� ��Ī �̸��տ� WND�� ���̴� ������ �Ѵ�
// ex)WND********
typedef enum
{
	WNDGameGlobalImage,		// �۷ι� �̹���
	WNDInfWindow,			// Infwindow
	WNDGameMain,			// GameMain
	WNDSysWnd,				// �ý��� â
	WNDBazaarShop,			// ���λ���
	WNDCityBase,			// ����
	WNDMissionInfo,			// �̼� ó��
	WNDMiniMap,				// �̴ϸ� ó��
	WNDMp3Player,			// MP3 �÷��̾�
	WNDInfSkill,			// ��ų ����
	WNDRenderHelp,			// Help
	WNDGameMainFaq,			// FAQ
	WNDCommunityVOIP,		// VOIP
	WNDQSlotIconFlag,		// QSlot
	WNDItemInfo,			// ������ ����
	WNDMenuList,			// �޴�����Ʈ
	WNDMainChatStartMenu,	// ����ê �޴�����Ʈ
	WNDLeftRightWindow,		// �κ�, ĳ��, ��Ƽ ��
	WNDOpJoystick,				// ���̽�ƽ �ɼ�â // 2008-11-13 by bhsohn ���̽�ƽ �۾�
	WNDCommunityWnd,				// Ŀ�´��� â	// 2008-04-04 by bhsohn Ep3 Ŀ�´�Ƽ â
	WNDInvenWnd,				// �κ� â	// 2008-08-22 by bhsohn EP3 �κ��丮 ó��
	WNDCharacterWnd,			// ĳ���� â	// 2008-09-22 by bhsohn EP3 ĳ���� â
	WNDVoiceWnd,				// ����
	WNDMacroWnd,				// ��ũ�� â	
	// 2009. 01. 12 by ckPark ���� ���� �ý���
	WNDWarDecalre,				// �������� ����â
	// end 2009. 01. 12 by ckPark ���� ���� �ý���
	WNDWorldRank,				// ���� ��ŷ â // 2009-02-13 by bhsohn ���� ��ŷ �ý���
	WNDIndexEnd				// �࿭�� ������
}WNDWINDOWSINDEX;

#define DOUBLEKEY_TIME			0.24f		// ����Ű üũ�� �ð�
#define SHUTTLE_ROTATION_DEFAULT_X		-0.65f	// �κ��丮 ��Ʋ�� �⺻ ����
#define SHUTTLE_ROTATION_DEFAULT_Z		-0.55f	// �κ��丮 ��Ʋ�� �⺻ ����

//////////////////////////////////////////////////////////////////////////

#define INVEN_RESOLUTION_1				800
#define INVEN_RESOLUTION_2				1024
#define INVEN_RESOLUTION_3				1280
#define INVEN_RESOLUTION_3_1			1440			// 2008-02-11 by dgwoo �ػ� �߰�.(1440 * 900)
#define INVEN_RESOLUTION_4				1600
// 2009. 10. 19 by ckPark �ػ� �߰�(1680x1050, 1920x1080, 1920x1200)
#define INVEN_RESOLUTION_5				1680
#define	INVEN_RESOLUTION_6				1920
// end 2009. 10. 19 by ckPark �ػ� �߰�(1680x1050, 1920x1080, 1920x1200)
#define INVEN_RESOLUTION_W				792
#define INVEN_RESOLUTION_WINDOW_1024	1018			// 2007-07-14 by dgwoo
#define INVEN_RESOLUTION_WINDOW_1280	1274			// 2007-07-14 by dgwoo
#define INVEN_RESOLUTION_WINDOW_1600	1594			// 2007-07-14 by dgwoo

// 2007-12-26 by dgwoo �ػ��� Height��.
#define RESOLUTION_FULL_H_720				720
#define RESOLUTION_FULL_H_768				768
#define RESOLUTION_FULL_H_800				800
#define RESOLUTION_FULL_H_900				900
#define RESOLUTION_FULL_H_960				960
// 2009. 10. 19 by ckPark �ػ� �߰�(1680x1050, 1920x1080, 1920x1200)
#define RESOLUTION_FULL_H_1050				1050
#define	RESOLUTION_FULL_H_1080				1080
// end 2009. 10. 19 by ckPark �ػ� �߰�(1680x1050, 1920x1080, 1920x1200)
#define RESOLUTION_FULL_H_1024				1024
#define RESOLUTION_FULL_H_1200				1200



// 2006-01-16 by ispark
// ���� ������ �ε���
#define WEAPON_POSITION_1_1_1			1
#define WEAPON_POSITION_1_1_2			2
#define WEAPON_POSITION_2_1_1			3
#define WEAPON_POSITION_2_1_2			4
#define ENGINE_POSITION					5


// 2006-03-16 by ispark
// �Է� ���
enum { INPUT_LANGUAGE_KOR = 1, INPUT_LANGUAGE_ENG, INPUT_LANGUAGE_VIET_TELEX, INPUT_LANGUAGE_VIET_VNI, INPUT_LANGUAGE_CHINA, INPUT_LANGUAGE_END };

// 2006-04-17 by ispark
// 2006-04-17 by ispark
#define RED_FONT				'r'
#define GREEN_FONT				'g'
#define BLUE_FONT				'b'
#define YELLOW_FONT				'y'
#define CYAN_FONT				'c'
#define MAGENTA_FONT			'm'
#define WHITE_FONT				'w'
#define ENCHANT_FONT			'e'
#define GRAY_FONT				'q'
#define DARKBLUE_FONT			'a'
// 2013-10-17 by ssjung ��Ʈ ���� �߰�
#ifdef C_FONT_COLOR_ADD
#define PINK_FONT		'p'
#define LIGHTGREEN_FONT 'l'
#define BLACK_FONT		'z'
#define TEAL_FONT       't'
#define NAVY_FONT       'n'
#define STEELBLUE_FONT  's'
#define RBROWN_FONT     'u'
#endif

#define PALEPINK_FONT			'p'
#define LIGHTGREEN_FONT			't'
#define BLACK_FONT				'x'
#define ORANGE_FONT				'o'
#define TAN_FONT				'n'
#define SALMON_FONT				's'
#define CORNFLOWER_BLUE_FONT	'u'
#define DARK_TURQUOISE_FONT		'd'
#define HOT_PINK_FONT			'h'
#define FIREBRICK_FONT			'z'
#define GOLDENROD_FONT			'f'
#define LIGHTBLUE_FONT			'l'
#define BROWN_FONT				'j'
#define VIOLET_FONT				'v'

#define HFONT_ARGB(a,r,g,b) \
    ((D3DCOLOR)((((a)&0xff)<<24)|(((b)&0xff)<<16)|(((g)&0xff)<<8)|((r)&0xff)))

enum { SPECIAL_STRING = 1 };

// 2006-07-26 by ispark, ������ ��ġ
enum { ITEM_NOT_POS, ITEM_INVEN_POS, ITEM_SKILL_POS, ITEM_QSLOT_POS, ITEM_STORE_POS, ITEM_LAB_POS, ITEM_BAZAAR_POS };

#define GAME_SHUTDOWN_TIME					30.0f
#define SIZE_MAX_BAZAAR_FULL_NAME			42

// 2006-08-22 by ispark, ������ ���� �ڽ� 
enum { LOW_LEVEL_STAT_HELP, LOW_LEVEL_MISSION_HELP };
#define HELP_SPECIAL_COUNT			2

// 2006-09-07 by ispark, �������� ����Ʈ ������ ó�� �ε���
// 2007-10-01 by bhsohn ó�� Ʃ�丮�� ����� ���ѷα� �ȳ����� ���� ó��
enum { NOT_ACTION, TUTORIAL_SKIP, TUTORIAL_COMPLETE, MISSION_PRE, TUTORIAL_CHART_END };

// 2006-09-19 by ispark, ��� ���� ����Ʈ
enum { DONOTKNOW = -1, FLIGHT, BREAKDOWN };

// 2006-11-21 by ispark, ��ų ó���� ���� �ε���
enum { CL_SKILL_NONE, CL_SKILL_INVISIBLE, CL_SKILL_CAMOUFLAGE };

#define CHARACTER_MALE_COUNT		6
#define CHARACTER_FEMALE_COUNT		6

// 2009. 11. 23 by jskim ���ҽ� �ε� ���� ����
enum
{
	_MOST_SIGNIFICANT_PRIORITY,
	_MY_CHARACTER_PRIORITY,
	_MESH_PRIORITY,
	_BULLET_PRIORITY,
	_NOTHING_PRIORITY,		// �ܰ躰 �ý��� ��� 
	_NOTHING_STEP   // ���� �ý��� ���
};

enum
{
	_RESOURCE_LOADING_START,
	_RESOURCE_LOADING_STEP1,
	_RESOURCE_LOADING_STEP2,
	_RESOURCE_LOADING_STEP3,
	_RESOURCE_LOADING_STEP4,
	_RESOURCE_LOADING_STEP5,
	_RESOURCE_LOADING_STEP6,
	_RESOURCE_LOADING_END
};

enum
{
	_EFFECT_TYPE,
	_CHARACTER_TYPE,
	_OBJECT_TYPE,
	_MONSTER_TYPE,
	_UNIT_TYPE,
};
//end 2009. 11. 23 by jskim ���ҽ� �ε� ���� ����

// 2010-06-15 by shcho&hslee ��ý��� - �� �⺻ ��ǥ
#define PET_DEFULT_POS_X 18
#define PET_DEFULT_POS_Y 1.5
#define PET_DEFULT_POS_Z 8

// 2011-03-21 by jhAhn ��ũ�ý��� ��ũ ��ġ ����
#define MARK_DEFULT_POS_X 0
#define MARK_DEFULT_POS_Y 0
#define MARK_DEFULT_POS_Z 0
// end 2011-03-21 by jhAhn ��ũ�ý��� ��ũ ��ġ ����

#define PET_CITY_DEFULT_POS_X 6
#define PET_CITY_DEFULT_POS_Y 15
#define PET_CITY_DEFULT_POS_Z 0

#define PET_CITY_GAP_POS_X	  2	 
#define PET_CITY_GAP_POS_Y	  5

enum
{
	OP_PET = 1,
};

// 2010. 10. 05 by jskim �ʷε� ���� ����
enum
{
	_MAP_LOADING_START,
	_MAP_LOADING_STEP1,
	_MAP_LOADING_STEP2,
	_MAP_LOADING_STEP3,
	_MAP_LOADING_STEP4,
	_MAP_LOADING_STEP5,
	_MAP_LOADING_END
};
// end 2010. 10. 05 by jskim �ʷε� ���� ����

#endif	//ATUMDEFINE_H__7699F556_5313_4782_B433_068C5F32BBC0__INCLUDED_endif