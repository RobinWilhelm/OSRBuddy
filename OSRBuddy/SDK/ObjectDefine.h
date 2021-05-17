/*******************************************************************************************
  ATUM Character, Monster, Object, Texture define

  ��>
	  RC_C_D_BT01				13001200
		-RC : Resource			 -13 : type(ĳ����(01),����(02),������Ʈ(03),GUI(04), TileTex(05) ,Effect(06)��)
		-C : Character			 -0012 : object ����
		-D : Deca				 -00 : X������ Texture����(-ff : X������ Shadow����)

		-BT01 : ����

	  RC_G_INIT_BACKGROUND
		-RC : Resource
		-G : GUI
		-INIT : Init state
		-BACKGROUND : ���� ����

  �ۼ��� : �ǵ���
  �ۼ��� : 2002.10.30

  �ۼ��� : ������
  �ۼ��� : 2003.07.30

********************************************************************************************/

#include "d3dx9.h"
#include "AtumParam.h"

#ifndef __ATUM_OBJECTDEFINE_H__
#define __ATUM_OBJECTDEFINE_H__

struct SPRITEVERTEX
{
	D3DXVECTOR3 p;
	DWORD       color;
	FLOAT       tu, tv;
};
// FVF �÷���
#define D3DFVF_SPRITEVERTEX (D3DFVF_XYZ|D3DFVF_DIFFUSE|D3DFVF_TEX1)

/*
#define RC_C_D_BT01		"10000100"
#define RC_C_D_BT02		"10000200"
#define RC_C_D_BT03		"10000300"
#define RC_C_D_BT04		"10000400"

#define RC_C_D_OT01		"10001100"
#define RC_C_D_OT02		"10001200"
#define RC_C_D_OT03		"10001300"
#define RC_C_D_OT04		"10001400"

#define RC_C_D_DT01		"10002100"
#define RC_C_D_DT02		"10002200"
#define RC_C_D_DT03		"10002300"
#define RC_C_D_DT04		"10002400"

#define RC_C_D_ST01		"10003100"
#define RC_C_D_ST02		"10003200"
#define RC_C_D_ST03		"10003300"
#define RC_C_D_ST04		"10003400"
*/
// Map
#define RC_MAP_WORKSPACE		"deca.wok"

// Effect
#define RC_EFF_COLL_01					1100001
#define RC_EFF_GROUND_01				1100002
#define RC_EFF_GROUND_02				1100003
#define RC_EFF_HEAL_01					1100004
#define RC_EFF_LEVELUP_DT				1100005
#define RC_EFF_LEVELUP_BT				1100006
#define RC_EFF_LEVELUP_OT				1100007
#define RC_EFF_LEVELUP_ST				1100008
#define RC_EFF_CLOUD					1100009	
#define RC_EFF_WARP_ZONE				1100010	
#define RC_EFF_OTHER_WARP				1100011	
#define RC_EFF_BOOSTER					1100012	
#define RC_EFF_SELECT					1100013
//#define RC_EFF_HELP00					1100013	//	���۹�
//#define RC_EFF_HELP01					1100014	//	����
#define RC_EFF_HELP02					1100015	//	����
#define RC_EFF_HELP03					1100016	//	����
#define RC_EFF_HELP04					1100017	//	���ǻ�� �ȱ�
#define RC_EFF_HELP05					1100018	//	���Ű

#define RC_EFF_USEITEM_REPAIR_HP		1100022	//	������ ���� ����Ʈ	ü��(�Ϲ� ������ - A~�Ϲ�)
#define RC_EFF_USEITEM_REPAIR_DP		1100073	//	������ ���� ����Ʈ	����(�Ϲ� ������ - A~�Ϲ�)
#define RC_EFF_USEITEM_REPAIR_HPS		1100056	//	������ ���� ����Ʈ	ü��(�Ϲ� ������ - S)
#define RC_EFF_USEITEM_REPAIR_HPA		1100058	//	������ ���� ����Ʈ	ü��(�Ϲ� ������ - A+)
#define RC_EFF_USEITEM_REPAIR_DPS		1100057	//	������ ���� ����Ʈ	����(�Ϲ� ������ - S)
#define RC_EFF_USEITEM_REPAIR_DPA		1100059	//	������ ���� ����Ʈ	����(�Ϲ� ������ - A+)
#define RC_EFF_USEITEM_REPAIR_SPS		7002840	//	������ ���� ����Ʈ	��ų(�Ϲ� ������ - A)
#define RC_EFF_USEITEM_REPAIR_SPA		7002850	//	������ ���� ����Ʈ	��ų(�Ϲ� ������ - B)
#define RC_EFF_USEITEM_REPAIR_SP		7002860	//	������ ���� ����Ʈ	��ų(�Ϲ� ������ - C)

#define RC_EFF_USEITEM_REPAIR_EP		1100055 //  ������ ���� ����Ʈ
#define RC_EFF_BGEAR_TRACE				1100074	//	B��� �ܻ� ����Ʈ
#define RC_EFF_IGEAR_TRACE				1100075	//	I��� �ܻ� ����Ʈ
#define RC_EFF_MGEAR_TRACE				1100076	//	M��� �ܻ� ����Ʈ
#define RC_EFF_AGEAR_TRACE				1100077	//	A��� �ܻ� ����Ʈ
#define RC_EFF_DUMMY_BACK_POSITION		"00000000.eff"	//	��ǥ�� ���� ���� ����ǥ����Ʈ(A��� 1�����⸸ ����)
#define RC_EFF_DUMMY_POSITION			"00000001.eff"	//	��ǥ�� ���� ���� ����Ʈ 
#define RC_EFF_LANDING_TAKEOFF			1100014	//	������ ����Ʈ
// 1��
#define RC_EFF_LOCKON_AUTOMATIC			1100056
#define RC_EFF_LOCKON_VULCAN			1100020	
#define RC_EFF_LOCKON_GRENADE			1100057
#define RC_EFF_LOCKOND_CANNON			1100058
#define RC_EFF_LOCKON_RIFLE				1100059
#define RC_EFF_LOCKON_GATLING			1100060
#define RC_EFF_LOCKON_LAUNCHER			1100061
#define RC_EFF_LOCKON_MASSDRIVE			1100062
// 2��
#define RC_EFF_LOCKON_ROCKET			1100063
#define RC_EFF_LOCKON_MISSILE			1100021	
#define RC_EFF_LOCKON_BUNDLE			1100064
#define RC_EFF_LOCKON_MINE				1100065
#define RC_EFF_LOCKON_SHIELD			1100066
#define RC_EFF_LOCKON_DUMMY				1100067
#define RC_EFF_LOCKON_FIXER				1100068
#define RC_EFF_LOCKON_DECOY				1100069


#define RC_EFF_SNOW						1100040	//	��

#define RC_EFF_IGEAR_UPGRADE			1100042 //	- I-Gear Upgrade
#define RC_EFF_AGEAR_UPGRADE			1100043 //	- A-Gear Upgrade
#define RC_EFF_MGEAR_UPGRADE			1100044 //	- M-Gear Upgrade
#define RC_EFF_BGEAR_UPGRADE			1100045 //	- B-Gear Upgrade

#define RC_EFF_TARGET_ARROW				1100070	//	Ÿ�� ���� ȭ��ǥ
//ysw 9_19
#define RC_EFF_GAGE_BOX					1100019
#define RC_EFF_INTRO					1100023

#define	RC_EFF_UNIT_ARROW				1100026 
#define RC_EFF_FIRST_TARGET				1100028
#define	RC_EFF_SECOND_TARGET			1100027 

#define RC_EFF_SPD_NUM					1100029
#define RC_EFF_CURRENTBURN_NUM			1100030
#define RC_EFF_TOTALBURN_NUM			1100031
#define RC_EFF_CURRENTHP_NUM			1100032
#define RC_EFF_TOTALHP_NUM				1100033
#define RC_EFF_CURRENTUTC_NUM			1100034
#define RC_EFF_TOTALUTC_NUM				1100035
#define RC_EFF_CURRENTFUEL_NUM			1100036
#define RC_EFF_TOTALFUEL_NUM			1100037
#define RC_EFF_EXP_NUM					1100038
#define RC_EFF_EXP_MIDDLE_GAGE			1100039

#define RC_EFF_SUN						1100047
#define RC_EFF_SHIELD_HIT				1100050	// ���� ������ ��
#define RC_EFF_SHIELD_HIT2				7900790 // ���� ������ ��

#define RC_EFF_QUEST_MAP_POSITION		01100079

#define RC_EFF_AGEAR_FIRE				1100072	// �ӽ�A-Gear �� �߻� ȭ�̾� ����Ʈ
#define RC_EFF_GET_SKILL				1100078

#define RC_EFF_CHAFF_SKILL				1100080		//ü�� ��ų ����Ʈ.
#define RC_EFF_SCAN_SKILL				1100081		//��ĵ ��ų ����Ʈ.
// 2007-04-19 by bhsohn ��ġ���� ������ �߰�
#define RC_EFF_SCAN_ITEM				1100082		//��ĵ ��ų ����Ʈ.
// 2008-12-26 by bhsohn ��Ű�ӽ� ����Ʈ �߰�
#define RC_EFF_LUCKY_SUCCESS			1100083		//��Ű�ӽ� ����Ʈ
// end 2008-12-26 by bhsohn ��Ű�ӽ� ����Ʈ �߰�

// 2009. 07. 07 by ckPark �κ���� ��û����(�Ѹ�, ����ȭ��, ����, A�������)
#define RC_EFF_ROBOTAMOR_FIRE_EFFECT	1100084		// �κ��Ƹӿ� 1�� �߻� ����Ʈ
// end 2009. 07. 07 by ckPark �κ���� ��û����(�Ѹ�, ����ȭ��, ����, A�������)

#define RC_EFF_BOOSTER_00000		"06010000"

// 2006-01-12 by ispark, 1��, 2�� ���� ���
#define RC_EFF_PRIMARY_RIGHT_POSITION	"00000000.eff"
#define RC_EFF_PRIMARY_LEFT_POSITION	"00000001.eff"
#define RC_EFF_SECONDARY_RIGHT_POSITION	"00000002.eff"
#define RC_EFF_SECONDARY_LEFT_POSITION	"00000003.eff"

// 2010-06-15 by shcho&hslee ��ý��� - �� ���� ����
#define RC_EFF_PET_RIGHT_POSITION	"00000000.eff"
#define RC_EFF_PET_LEFT_POSITION	"00000001.eff"
// end 2010-06-15 by shcho&hslee ��ý��� - �� ���� ����

// 2011-03-21 by jhAhn ��ũ�ý��� ��ũ ��ġ ����
#define RC_EFF_MARK_POSITION		"00000004.eff"
// end 2011-03-21 by jhAhn ��ũ�ý��� ��ũ ��ġ ����

// 2006-10-11 by ispark, ĸ�� ����Ʈ
#define RC_EFF_POWER_ENERGY_CAPSULE		7800110
#define RC_EFF_POWER_SHIELD_CAPSULE		7810100
#define RC_EFF_POWER_SP_CAPSULE			7813010
#define RC_EFF_ADRENALIN_CAPSULE		7812020
#define RC_EFF_BRAVE_CAPSULE			7831030
#define RC_EFF_HYPER_BOOSTER_CAPSULE	7813030

// Texture
#define RC_TEX_GUI_LOADING_BACK		"back"
#define RC_TEX_GUI_LOADING_BAR		"bar"


#define FILTER_ENCODESTRING "ud830pwkldlkv[]f\20jdmvld;"


//ä�� Color	B|G|R
#define COLOR_CHARACTER_ID00		0xFFFFFF				//	���
#define COLOR_CHARACTER_ID01		0x0000FF				//	������
#define COLOR_CHARACTER_ID02		0x00FF00				//	������ // ���
#define COLOR_MONEY					0x73CDEB
#define COLOR_CHAT_ALL				0x00FFA8
#define COLOR_CHAT_REGION			0xFEFEFE				//	 ���
#define COLOR_CHAT_MAP				0x6DFF33				//  ��üä��
#define COLOR_CHAT_PTOP				0xDC92DC
#define COLOR_CHAT_GUILD			0xFF00FF				//0xEB6B43
#define COLOR_CHAT_CASH				0x00009E				// ĳ�� ��ü ä��
#define COLOR_CHAT_CHATROOM			0xCCCCFF				// ä�ù� ä��
#define COLOR_CHAT_WAR				0X2222EA
#define COLOR_CHAT_SELL				0x00AEFE				// �Ÿ� ä��
#define COLOR_BAZAAR_BUY			0xFF9933				// ��Ȳ��

#define COLOR_MONSTER_ID00			0xFF0101				//	Ǫ����
#define COLOR_MONSTER_ID01			0xFF8585
#define COLOR_MONSTER_ID02			0xFDFDFD				//	���
#define COLOR_MONSTER_ID03			0x8585FF
#define COLOR_MONSTER_ID04			0x0000FF				//	������
#define COLOR_HELP					0x64FFFF
#define COLOR_VOIP					0x0000FF				//	������
#define COLOR_SKILL_USE				0x00FF00				//	���
#define COLOR_SKILL_CANCEL			0xC8C8C8
#define COLOR_ARENA					0xFFAAAD				// ���� ä��.�Ʒ��� ä��.
#define COLOR_PARTY					0x82FF85
#define COLOR_TRADE					0xA6B843
#define COLOR_ITEM					0x00FFFF				//	�����
#define COLOR_INFLUENCE				0xFFFF00				//  ���� û��
#define COLOR_SPEAKER				0xFFFF00

#define COLOR_SYSTEM				0xFFB4FF
#define COLOR_ERROR					0x00FFF6
#define COLOR_DEBUG					0x00FFF6

#define BOOSTER_NORMAL_SPEEDRATE	1.0f
#define BOOSTER_FAST_SPEEDRATE		2.0f
#define BOOSTER_KEY_CHECK_TIME		0.2f
#define BOOSTER_START_CHECK_RATE	0.9f
#define BOOSTER_END_CHECK_RATE		0.0f


// TODO: reference additional headers your program requires here
enum ERRER_TYPE {
	APP_ERR_MAPLOAD,
	CLIENT_ERR_MESHLOAD,
	CLIENT_ERR_TEXINIT,
	CLIENT_ERR_SHUTTLE_MESHLORD,
	CLIENT_ERR_SHUTTLE_EFFECTINIT,
	CLIENT_ERR_SHUTTLE_EFFECTRESTORE,
	CLIENT_ERR_WEAPON_TEXINIT,
	CLIENT_ERR_WEAPON_VBRESTORE
};
enum State {
	_INITIALIZING = -1,
	_NORMAL,
	_WARP,
	_FALLING,						//�߶��ǰ��ִ� ����.
	_FALLEN,						//�߶��Ȼ���.
	_LANDING,
	_LANDED,
	_TAKINGOFF,
	_EXPLODING,						//������.
	_EXPLODED,						//����
	_CLOSE,
	_NCITYIN,
	_STAND,
	_WALK,
	_RUN,
	_FUELALLIN,						//���ᰡ ��� �߶��ϴ� ����.
	_AUTODESTROYED
};

enum GameState {
	_MOVIE,
	_LOGO,
	_INIT,
	_SELECT,
	_CREATE,
	_OPTION,
	_MAPLOAD,
	_GAME,
	_SHOP,
	_CITY, // ����
	_SCRIPT, // ���� ��ũ��Ʈ
	_WAITING,
	_GAMEOVER,
	_COMPLETE,
	_PROLOGUE,
	_ENDGAME,
	_ENDCLIENT,
	_SELECTCHANNEL,
	_BOSSMONSTERSUMMONREADY,
	_BOSSMONSTERSUMMON
};
enum PartType {
	_ADMIN, _SHUTTLE, _ENEMY, _MONSTER,				// Shuttle �� Enemy, Monster
	_ITEMFIELD,										// �ʵ忡 ������ ������
//				_CYCLOPSE,_ARROW,_HAMMERHEAD,					// Missile �� ( Shuttle )
_MISSILE,										// Missile �� ( Shuttle )
//				_FATBIRD,_BALLISTAR,_MOSQUITO,					// Rocket �� ( Shuttle )
_ROCKET,										// Rocket �� ( Shuttle )
_BUNDLE,										// Bundle �� ( Shuttle )
_MINE, //_SPOREMINE,_AXISMINE,_OCTOPUSMINE,		// Mine �� ( Shuttle )
_SHIELD,										// Shield �� (Shuttle )
_DUMMY,											// Dummy ��
_FIXER,											// Fixer ��
_LAY,											// ������ ������ (Shuttle : ��ĵ������Ʈ)
_WMHONIAN, _WMAMMON, _WMNATING, _WMMONSTERMISSILE, _WMWATCHER, _WMFLYSEED, _WMOVERWATCHER, _WMSCOUT, _WMSPOTTIE, _WMTETINO, _WMBALDRE,
_WMFRIGG, _WMTHOR, _WMFENRIR, _WMLUCANUS, _WMLOKI, _WMCURSESTORM,
_FASTDATA, _FIREDATA
};
// Party Type
enum PARTY_TYPE { _NOPARTY, _PARTYMASTER, _PARTYMEMBER, _PARTYOTHERMAPMASTER, _PARTYOTHERMAPMEMBER, _PARTYRESTARTMEMBER };//,_ATTACKENEMY };
// _NOPARTY:��Ƽ�� �ƴ�,_PARTYMASTER:��Ƽ��,_PARTYMEMBER:��Ƽ��,_ATTACKENEMY:���� ���

//#define DIRECTINPUT_VERSION         0x0800

enum ATTACK_MODE { _AIR, _GROUND, _SIEGE, _AIRBOMBING };



// Enemy Type
#define ENEMYDATA_ENEMYLIST					0x00
#define ENEMYDATA_TARGETLIST				0x01
#define ENEMYDATA_TARGET					0x02
// Monster Type 
#define MONSTERDATA_MONSTERLIST				0x03
#define MONSTERDATA_MONSTERTARGETLIST		0x04
#define MONSTERDATA_MONSTERTARGET			0x05

// Chat
#define WM_IM_ASYNC		(WM_USER_BASE + 770)
#define WM_IM_NOTIFY	(WM_USER_BASE + 771)

//#define REQUEST_LOCKON_TIME			1.0f

#define TILE_SIZE							40.0f

#define MAP_BLOCK_SIZE						640
#define SIZE_OBJECT_VISIBLERECT				(MAP_BLOCK_SIZE*3)
#define CHECK_OBJECT_RADIUS					320

struct TWO_BLOCK_INDEXES
{
	short sMinX;
	short sMinZ;
	short sMaxX;
	short sMaxZ;
};


#define	TEXTILE_NUM							500
#define SHUTTLE_NUM							16*4
#define MONSTER_NUM							100
//#define OBJECT_FRONT_NUM					120
//#define OBJECT_BACK_NUM						38
//#define OBJECT_NUM							(OBJECT_FRONT_NUM + OBJECT_BACK_NUM + 100)
#define OBJECT_NUM							300

#define SHUTTLE_TARGET_MOUSE_CIRCLE_RADIUS	20.0f
#define SHUTTLE_ATTACK_CENTER_RADIUS		30.0f
#define SHUTTLE_MAX_RENDER_DISTANCE			1020.0f			// 
#define SHUTTLE_MAX_UPVEC_RATE				0.8f			//	Up Vector �� ����� �ִ� ��
#define SHUTTLE_MAX_SIDERATE				1.5f			//	�¿� ȸ�� �ִ� ��
#define SHUTTLE_MAX_UPDOWNRATE				1.9f			//	�Ʒ��� ����� �ִ� ��
#define SHUTTLE_LRUPRECOVERY_RATE			1.5f			//	�¿� Up Vec�� ����� ȸ�� �ӵ� ����
#define SHUTTLE_LRUPLEAN_RATE				1.0f			// �¿� Up Vec�� ����� �ӵ� ����

#define SHADOW_MAX_DISTANCE					500.0f

//#define MAX_SHUTTLE_MOVE_TYPE				11
//#define MAX_CAMERA_TYPE						2

#define MAX_SOUND_ITEM						100
#define MAX_SOUND_GROUND_BIRD				10				//	1~~~000����
#define MAX_SOUND_GROUND_WORM				10				//	1~~~100����
#define MAX_SOUND_GROUND_ANIMAL				10				//	1~~~200����
#define MAX_SOUND_GROUND_WATER	 			20				//	1~~~300����
#define MAX_SOUND_GROUND_WIND				10				//	1~~~400����
#define MAX_SOUND_GROUND_EXPLODE			5				//	1~~~500����
#define MAX_SOUND_GROUND_MACHINE			5				//	1~~~600����
#define MAX_SOUND_GROUND_HUMAN				10				//	1~~~700����
#define MAX_SOUND_GROUND					(MAX_SOUND_GROUND_BIRD + MAX_SOUND_GROUND_WORM + MAX_SOUND_GROUND_ANIMAL + MAX_SOUND_GROUND_WATER + MAX_SOUND_GROUND_WIND + MAX_SOUND_GROUND_EXPLODE + MAX_SOUND_GROUND_MACHINE + MAX_SOUND_GROUND_HUMAN)
#define MAX_SOUND_GUI						100
#define MAX_SOUND_VOICE						100
#define MAX_SOUND_MONSTER					100
#define MAX_SOUND_TOTAL						(MAX_SOUND_ITEM + MAX_SOUND_GROUND + MAX_SOUND_GUI + MAX_SOUND_VOICE + MAX_SOUND_MONSTER)



#define MAX_CHAT_PTOP_CONT					10

#define MAX_TRADE_ITEM_NUMBER				12

#define MAX_SNOW_AMOUNT						1
#define SNOW_CHECKTIME						0.1f

#define MAX_PARTY_NUMBER			6


// by dhkwon, GAGE BOX BODYCONDITION
#define GAGEBOX_NORMAL			0x000000000000007E		// ������ �ڽ�,��ư�� �븻
#define GAGEBOX_INFO_NORMAL		0x0000000000000004		// info button up
#define GAGEBOX_INVEN_NORMAL	0x0000000000000008		// inventory button up
#define GAGEBOX_PARTY_NORMAL	0x0000000000000010		// party button up
#define GAGEBOX_TRANS_NORMAL	0x0000000000000020		// trans button up
#define GAGEBOX_OPTION_NORMAL	0x0000000000000040		// option button up
#define GAGEBOX_INFO_UP			0x0000000000000080		// info button up
#define GAGEBOX_INVEN_UP		0x0000000000000100		// inventory button up
#define GAGEBOX_PARTY_UP		0x0000000000000200		// party button up
#define GAGEBOX_TRANS_UP		0x0000000000000400		// trans button up
#define GAGEBOX_OPTION_UP		0x0000000000000800		// option button up
#define GAGEBOX_INFO_DOWN		0x0000000000100000		// info button down
#define GAGEBOX_INVEN_DOWN		0x0000000000002000		// invetory button down
#define GAGEBOX_PARTY_DOWN		0x0000000000004000		// party button down
#define GAGEBOX_TRANS_DOWN		0x0000000000008000		// trans button down
#define GAGEBOX_OPTION_DOWN		0x0000000000010000		// option button down
#define GAGEBOX_AUTO_MODE_ON	0x0000000000200000		// auto mode
#define GAGEBOX_AUTO_MODE_OFF	0x0000000000400000
#define GAGEBOX_ACTIVE_MODE_ON	0x0000000000800000		// active mode
#define GAGEBOX_ACTIVE_MODE_OFF	0x0000000001000000

// messagebox
enum {
	_Q_PARTY_CREATE,				// ��� ����
	_Q_PARTY_INVITE,				// ��뿡 �շ��ϰڽ��ϱ�?"
	_Q_PARTY_BAN_MEMBER,			// ���� �߹�
	_Q_PARTY_SECEDE,				// ��� Ż��
	_Q_PARTY_LEAVE,				// ����
	_Q_PARTY_FORMATION,			// ����
	_Q_PARTY_TRANSFER_MASTER,	// ����� ����
	_Q_PARTY_INVITE_USER,		// ������ ��뿡 �ʴ��ϰڽ��ϱ�?
	_Q_PARTY_INVITE_USER_OK,		// ��� ����
	_Q_GUILD_CREATE,				// ����� ����
	_Q_GUILD_MARK,				// ����� ���� �����̸� ?
	_Q_GUILD_INVITE,				// ����� �ʴ�( C -> IM )
	_Q_GUILD_INVITE_QUESTION,	// ����� �ʴ� ���( IM -> C )
	_Q_GUILD_BAN_MEMBER,			// �߹�
	_Q_GUILD_LEAVE,				// Ż��
	_Q_GUILD_DISBAND,			// ����� ��ü ?
	_Q_GUILD_CANCEL,				// ����� ��ü ��� ?
	_Q_TRADE_INPUT_NAME,			// �ŷ��� ������ ?
	_Q_TRADE_REQUEST,			// ~�� �ŷ��Ͻðڽ��ϱ�?
	_Q_TRADE_OK,					// �ŷ� �Ϸ��Ͻðڽ��ϱ�?
	_Q_TRADE_CANCEL,				// �ŷ� ��� ?
	_Q_WARF_OK,
	_Q_SHOP_SELL_ENERGY,			// ��� �Ľðڽ��ϱ�?
	_Q_SHOP_SELL_ITEM,			// �������� �Ľðڽ��ϱ�?
	_Q_AUCTION_INPUT_ITEM,		// �������� ��ſ� �ø��ðڽ��ϱ�?
	_Q_AUCTION_DELETE_ITEM,		// ����� �������� �����Ͻðڽ��ϱ�?
	_Q_ITEM_DELETE,				// ������ 1���� ����ڽ��ϱ�?
	_Q_ITEM_DELETE_NUM,			// ������ ��� ����ڽ��ϱ�?
	_Q_TRADE_ITEM_NUMBER,		// �(��)�� �ø��ڽ��ϱ�?
	_Q_TRADE_COMPLETE_OK,		// ������
	_Q_VOIP_OK,					// ~�� ���������� �Ͻðڽ��ϱ�?
	_Q_VOIP_NAME,				// ���������� ���̵� �Է��Ͻÿ�
	_Q_DEAD_RETURN,				// ���� �� ���÷� �̵�
	_Q_PK_REQUEST,				// ~�� 1:1 ������ �Ͻðڽ��ϱ�?
	_Q_PK_LOSE_REQUEST,			// �׺��Ͻðڽ��ϱ�?
	_Q_PK_LOSE_REQUEST_OK,		// �׺��� �޾Ƶ��̰ڽ��ϱ�?
	_Q_USE_ENCHANT_ITEM_CARD,	// ��æƮ ������ ����Ŭ��(��æƮ�� �������� Ŭ���Ͻÿ�)
	_Q_REQUEST_PARTY_BATTLE,		// ��Ƽ������ �Ͻðڽ��ϱ�?
	_Q_SELECT_DELETE,			// ĳ���͸� ����ðڽ��ϱ�?
	_MESSAGE,					// �Ϲ� �޽���
	_MESSAGE_ERROR_CREATE,		// ĳ���� ���� �ÿ� ��Ÿ���� �޽���(�����ϴ� �̸�, �߸��� �̸�, �̸��� �Է��ϼ���)
	_MESSAGE_ERROR_NETWORK,		// ��Ʈ�� ���� ����(���� CGUITextBox��� ���)
	_Q_BATTLE_NAME,				// 1:1 ����� ����?
	_Q_OUTDOOR_WARP,				// �ܰ����� ����?
	_Q_LAB_ITEM_NUMBER,			// ��� �ø��ðڽ��ϱ�?
	_Q_REQUEST_GUILD_WAR,		// �������� �Ͻðڽ��ϱ�?
	_Q_STORE_PUT_COUNTABLE_ITEM,	// â�� � �ñ�ðڽ��ϱ�?
	_Q_INPUT_AUCTION_PRICE,		// ��ſ� �ø� ������ �󸶷� �Ͻðڽ��ϱ�?
	_Q_STORE_PUT_ITEM,			// â�� �������� �ñ�ðڽ��ϱ�?
	_Q_STORE_PUSH_ITEM,			// â���� ��� �������� ã���ðڽ��ϱ�?
	_Q_QUEST_DISCARD,			// �̼� ����?
	_Q_PARTYMASTER_VOIP,			// ��밣 ��ȭ ����
	_Q_JOIN_PARTY_VOIP,			// ��밣 ��ȭ ���� ?
	_Q_USE_HELP_SYSTEM,			// �ʺ� ����� �̿�?
	_Q_GUILDMASTER_VOIP,			// ���� ��ȭ ����
	_Q_JOIN_GUILD_VOIP,			// ���� ��ȭ ���� ?
	_Q_PUT_ITEM_SPI,				// â�� �󸶸� �±�ðڽ��ϱ�?
	_Q_GET_ITEM_SPI,				// â���� �󸶸� ã�ڽ��ϱ�?
	_Q_ADD_FRIEND,				// ģ���߰�
	_Q_DELETE_FRIEND,			// ģ���� �����Ͻðڽ��ϱ�?
	_Q_ADD_REJECT,				// �ź��߰�
	_Q_DELETE_REJECT,			// �źθ�Ͽ��� �����Ͻðڽ��ϱ�?
	_Q_ITEM_DELETE_SKILL,		// ��ų�� �����Ͻðڽ��ϱ�?
	_Q_GUILD_VOIP_END,			// ������ȭ�� ���� �Ͻðڽ��ϱ�?
	_Q_PARTY_VOIP_END,			// ��Ƽ��ȭ�� ���� �Ͻðڽ��ϱ�?
	_Q_VOIP_USING,				// �̹� ������ȭ�� ����Ͻð� �ֽ��ϴ�.	   
	_Q_TEX_SET,					// ���� �����ϱ�
	_Q_DATE_WAR,					// ��������� ��¥ �ð� ����
	_Q_STORE_USE,				// ���ܿ� �� â������ �����Ͻðڽ��ϱ�?	   
	_Q_GREATING_SET,				// ������ �ʱ� �λ縻 ����
	_Q_GET_TEX,					// ������ �������ðڽ��ϱ�?
	_Q_CASHITEM_BUY,				// ĳ���������� �����Ͻðڽ��ϱ�?
	_Q_CASHITEM_SHOP_OPEN,		// ĳ�������� ����Ͻðڽ��ϱ�?
	_Q_INPUT_SERIAL_NUM,			// �ø��� �ѹ� �Է�
	_Q_SUPER_RESTORE,			// ���� ��Ȱ ī��
	_Q_MEMBER_SUMMON,			// ���ܿ� �� �� ��ȯ ī��
	_Q_USE_SUPER_RESTORE,		// ���� ��Ȱ ī�带 ����Ͻðڽ��ϱ�?
	_Q_USE_NORMAL_RESTORE,		// �Ϲ� ��Ȱ ī�带 ����Ͻðڽ��ϱ�?
	_Q_MP3_DIRECTORY,			// MP3 ���丮 �Է�
	_Q_MP3_PLAYLIST_DEL,
	_Q_PART_STAT_RESET,			// ���� �ʱ�ȭ(��Ʈ)
	_Q_QUIT_MESSAGE,				// ���� �޼��� �ڽ�
	_Q_USEITEM_NAME_CHANGE,
	_Q_UNIT_STOP,				// ���� ���� �Ͻðڽ��ϱ�?
	_Q_AGEAR_FUEL_ALLIN,			// ���ᰡ �Ҹ�Ǿ� ���÷� �����˴ϴ�.
	_Q_MISSION_START,			// ~ �̼��� �����Ͻðڽ��ϱ�?
	_Q_VOIP_ONE_NAME,			// ��ȭ �� ���� ���̵� �Է��ϼ���.
	_Q_VOIP_MENU,				// �޴��� �����ϼ���.
	_Q_SKILL_CALLOFHERO,			// �ݿ�������θ� ���̽��ϴ�. ����Ͻðڽ��ϱ�?
	_Q_FUELALLIN_DEAD_RETURN,	// �ݳ���� �̵��մϴ�.
	_Q_INFLUENCEMAP_DEAD_RETURN,	// �ٸ� ���¸ʿ��� �׾��� �� �ڽ��� ������ ���ø����� �̵�
	_Q_EVENT_CALL_WARP_REQUEST,	// �̺�Ʈ�� 
	_Q_BAZAAR_OPEN_SHOP_END,		// ����(����)�� �����ðڽ��ϱ�?
	_Q_BAZAAR_INVALID_SHOP_END,	// ������ ���� �Ǿ����ϴ�.
	_Q_BAZAAR_SELL_OK,			// (�湮��)�������� �����Ͻðڽ��ϱ�?
	_Q_BAZAAR_BUY_OK,			// (�湮��)�������� �Ǹ��Ͻðڽ��ϱ�?
	_Q_USEITEM_KILL_MARK,		// ų��ũ�� EXP�� ��ȭ
	_Q_QUEST_REQUEST_PARTY_WARP,	// ����Ʈ ���� Ȯ�� ��û �޼���
	_Q_SHOP_MULTI_SELL_ITEM,		// �����۵��� �Ľðڽ��ϱ�?// 2007-02-12 by bhsohn Item ���� ���� ó��
	_Q_STORE_MULTI_PUT_ITEM,		// �����۵��� �ñ� �ڽ��ϱ�?// 2007-02-12 by bhsohn Item ���� ���� ó��
	_Q_STORE_MULTI_GET_ITEM,	    // ���õ� ��� �������� �������ðڽ��ϱ�?.?// 2007-02-12 by bhsohn Item ���� ���� ó��
	_Q_UPDATE_SUBLEADER_1,		// %s��(��) ��������1�� �����Ͻðڽ��ϱ�?
	_Q_UPDATE_SUBLEADER_2,		// %s��(��) ��������1�� �����Ͻðڽ��ϱ�?
	_Q_ARENA_PASSWORD,			// ��й�ȣ�� �Է��Ͻʽÿ�.
	_Q_ARENA_WARP,				// �Ʒ����� �̵��Ͻðڽ��ϱ�?
	_Q_ARENA_RESTART,			// ������������ �̵��մϴ�.
	_Q_TUTORIAL_START,			// Ʃ�丮�� ���� �̵��Ͻðڽ��ϱ�?
	_Q_USEITEM_SPEAKER_MSG,		// Message
	_Q_INFLUENCE_WAR_EXPENCE_OK_MSG,		// ȯ�޹��� �ݾ��� �Է��ϼ���.
	_Q_SECOND_PASS_CANCEL_MSG,		// ȯ�޹��� �ݾ��� �Է��ϼ���.
	_Q_POLL_CANDIDATE_VOTE,			// %s �ĺ����� ��ǥ�Ͻðڽ��ϱ�?
	_Q_POLL_CANDIDATE_DELETE,			// "�ĺ����� Ż���Ͻø�, ���� ���ſ� �⸶ �����մϴ�. Ż���Ͻðڽ��ϱ�?"
	_Q_GIFT_CHARACTER_TEXT,			// "�������� ������ ĳ���� ���� �Է��ϼ���."
	_Q_GIFT_ITEM,						// "%s �������� ���� �Ͻðڽ��ϱ�?"
	_Q_GIFT_ITEM_RING_IN,				// %s���� %s������ %d���� ���� �Ͽ����ϴ�. â���� Ȯ���ϼ���.
	_Q_COUPON,						// "���� ���� �޽���.
	// 2008-04-04 by bhsohn Ep3 Ŀ�´�Ƽ â
	_Q_GUILD_GIVE_SUBLEADER,			// "\\y%s\\y���� �ο��������� �Ӹ��Ͻðڽ��ϱ�?"
	_Q_GUILD_FALL_SUBLEADER,			// "�ο����� ������ �������� ����νðڽ��ϱ�?"
	_Q_GUILD_CHARGE_LEADER,			// "\\y%s\\y�Կ��� �������� �����Ͻðڽ��ϱ�?"	   
	_Q_GUILD_REQUEST,				// "\\y%s\\y���ܿ� ���� ��û �Ͻðڽ��ϱ�?"
	_Q_GUILD_REQUEST_CANCEL,			// "\\y%s\\y���ܿ� ���� ��û�� ����Ͻðڽ��ϱ�?"
	_Q_PARTY_JOIN_PASSWORD,			// ��й�ȣ�� �Է��Ͻʽÿ�.
	// end 2008-04-04 by bhsohn Ep3 Ŀ�´�Ƽ â	   
	_Q_CHATROOM_INVITE,				// "�ʴ��� ������ �Է��Ͻÿ�."
	_Q_CHATROOM_INVITE_FROM,			// "%s���� ä�ÿ� �ʴ��ϼ̽��ϴ�."
	_Q_CHATROOM_OUT,					//"ä�ù濡�� �����ðڽ��ϱ�?"
	_Q_CHATROOM_PASSWORD,			//"��й�ȣ�� �Է����ּ���."
	// 2008-09-17 by dgwoo ��� �������� ��ư ��ȹ�� 
	_Q_PARTY_BATTLE,					//"����� ����� ĳ���� ���� �Է��ϼ���"
	_Q_GUILD_BATTLE,					//"����� ������ ĳ���� ���� �Է��ϼ���"
	// 2008-11-13 by bhsohn ���̽�ƽ �۾�
	_Q_JOYSTICK_SETUP,				// ���̽�ƽ �ɼ� ����
	// end 2008-11-13 by bhsohn ���̽�ƽ �۾�
// 2008-12-09 by dgwoo �̼Ǹ�����.
_Q_MISSION_MASTER_CANCEL,			// ""�̼� ������ ����� ���� �Ͻðڽ��ϱ�?"
_Q_MISSION_MASTER_HELPER,			//"%s���� �̼� ������ ��û �Ͽ����ϴ�."
// end 2008-12-09 by dgwoo �̼Ǹ�����.
	// 2008-12-30 by bhsohn ������ ä�� ���� ī�� ��ȹ��
	_Q_USEITEM_LEADER_BAN_CHAT,
	// 2009-01-12 by bhsohn ģ�� ��� ���ϴ� ���� �޽���â ��� �߰�
	_Q_FRIEND_LIST_INSERT,

	// 2009. 01. 12 by ckPark ���� ���� �ý���
	_Q_WAR_DECLARE_GIVE_UP,				//"������ ���� ������ �����Ͻðڽ��ϱ�?"
	_Q_WAR_DECLARE,						//"%d�� %d�� %02d�� %02d�п� %s ���¿��� �������� �Ͻðڽ��ϱ�?"
	// end 2009. 01. 12 by ckPark ���� ���� �ý���
	_Q_GUILD_CREATE_CONFIRM,				// ����� ���� Ȯ��â // 2009-02-02 by bhsohn ���� ������ Ȯ��â �߰�
	// 2009-02-13 by bhsohn ���� ��ŷ �ý���
	_Q_CREATE_NICKNAME_OKCANCEL,	// �г��� ���� Ȯ��â
	_Q_CREATE_NICKNAME,				// �г��� ����â		
	// end 2009-02-13 by bhsohn ���� ��ŷ �ý���
	// 2009-04-08 by bhsohn ���� ���ý�, ����ũ �� ��æƮ �� ������ �ǸŽ� ��� �޽��� ��� ��ȹ ����(K0000174)
	_Q_MULTI_SEL_WARNING,		// "%s �������� \\y����ũ\\y �������Դϴ�. ������ ���� �Ͻðڽ��ϱ�?"
	// end 2009-04-08 by bhsohn ���� ���ý�, ����ũ �� ��æƮ �� ������ �ǸŽ� ��� �޽��� ��� ��ȹ ����(K0000174)

	// 2009. 10. 08 by ckPark �ʵ� â�� ������ �ߺ� �Ұ� ó��
	_Q_ALREADY_HAVE_ITEM,		// "���� ���� �������� ���Ⱓ�� ���� ���� �ʾ� �������� ����� �� �����ϴ�. ���Ⱓ�� ����� �� ����� �ּ���."
	// end 2009. 10. 08 by ckPark �ʵ� â�� ������ �ߺ� �Ұ� ó��

	// 2009. 11. 02 by ckPark ���Ǵ�Ƽ �ʵ� �ν��Ͻ� ���� �ý���
	_Q_INFINITY_GIVE_UP,		// "���Ǵ�Ƽ �ʵ��� ������ ���� �ϰ� ���÷� ��ȯ �Ͻðڽ��ϱ�?"
	_Q_REVIVE_WAIT_5SECOND,		// "\\r%d��\\r �Ŀ� ��Ȱ�� �����մϴ�."
	_Q_BUY_INFINITYSHOP_ITEM,	// "�������� ���� �Ͻðڽ��ϱ�?"
	_Q_INFINITY_RETURN_TO_CITY,	// "���Ǵ�Ƽ �ʵ带 �����ϰ� ���÷� ��ȯ �Ͻðڽ��ϱ�?"
	_Q_RETURN_TO_PROGRESS_INFINITY,// ������ ���ᰡ �Ǿ����ϴ�. �������� ���Ǵ�Ƽ �ʵ�� �̵� �Ͻðڽ��ϱ�?
	// end 2009. 11. 02 by ckPark ���Ǵ�Ƽ �ʵ� �ν��Ͻ� ���� �ý���
	// 2010. 06. 07 by jskim ��Ʈ�� �ý��� ���� - ��Ʈ�� ����â
	_Q_PARTNER_NEW_NAME_CHANGE,
	_Q_PARTNER_NAME_OKCANCLE,
	//end 2010. 06. 07 by jskim ��Ʈ�� �ý��� ���� - ��Ʈ�� ����â
	// 2010. 06. 18 by jskim ��æƮ ��� �޽��� �߰�
	_Q_ENCHANT_PREVENTION,
	//end 2010. 06. 18 by jskim ��æƮ ��� �޽��� �߰�
	_Q_DIS_BOOM			 // 2010-08-31 by shcho&&jskim, ���� �ý��� ����

};
// �������̽� MsgProc ���ϰ�
#define INF_MSGPROC_CLOSE	0	// �� ���� ������ ���� �����.
#define INF_MSGPROC_NORMAL	1	// ���������� ó���� ����Ѵ�.
#define INF_MSGPROC_BREAK	2	// �޽����� ������.��, �Ʒ� Msg Proc������ ���� msg�� �������� �ʴ´�.

#define TIME_HOUR		4
#define TIME_MINUTE		60
#define TIME_SECOND		60
#define TIME_DAY_CHANGE	300.0f


#define MAX_BEGIN_QUEST_COUNT	70	// �ʺ� ���(Ʃ�丮��) ����Ʈ ��


typedef struct _VERTEXINFO
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 nor;
} VERTEXINFO;

typedef struct _TILEINFOCLIENT // tile type
{
	INT			useTexNumber;		// ����ؽ����� �ε���
	// 2005-04-06 by jschoi ��Ÿ�� �߰�
	DWORD		dwWaterType;		// useWater��� ��Ÿ������ ����
//	BOOL		useWater;			// Water ���
	INT			waterHeight;		// Water ����
	SHORT		waterTexNumber;		// Water Texture
	BYTE		bMove;				// Move Type
	BOOL		bEnableLand;		// ��������
	BYTE		bEventType;			// �̺�Ʈ Ÿ�� 1:(���� �Ա�) 2:(���� �ⱸ) 3:����
} TILEINFOCLIENT;


typedef struct _OBJECTINFOCLIENT
{
	DWORD		dwObjType;			// Object Ÿ��
	INT			nObjCount;
	D3DXVECTOR3 vPos;
	D3DXVECTOR3 vVel;
	D3DXVECTOR3 vUp;
	DWORD		dwObjectMonsterUniqueNumber;	// 2004-11-27 by jschoi with cmkwon
	BYTE		bObjectTexIndex;
	UINT		nObjectSrcIndex;
	BYTE		bBodyCondition;
	BOOL		bIsEvent;
	BYTE		bEventType;
	short		sEventIndexFrom;
	short		sEventIndexTo;
	short		sEventIndex3;
	char		strEventParam[40];
} OBJECTINFOCLIENT;

typedef struct _MAP_DATA
{
	FLOAT			fTileSize;
	int				nVertexNumber;
	int				nTileInfoNumber;
	int				nObjectNumber;
}MapInfo;

typedef struct _WORKSPACE
{
	char workspaceName[40];
	int numberOfProject;
} WORKSPACE;

typedef struct _PROJECTINFO
{
	int			useTileSetIndex;
	char		strProjectName[40];
	char		strFieldIP[16];
	short		sFieldPort;
	short		sFieldPortUDP;
	char		strNPCIP[16];
	short		sNPCPort;
	short		sNPCPortUDP;
	short		sXSize;
	short		sYSize;
	float		fHeightMax;
	float		fHeightMin;
	float		fWaterHeight;
	float		fDiffuseR1;
	float		fDiffuseG1;
	float		fDiffuseB1;
	float		fAmbientR1;
	float		fAmbientG1;
	float		fAmbientB1;
	float		fDiffuseR2;
	float		fDiffuseG2;
	float		fDiffuseB2;
	float		fAmbientR2;
	float		fAmbientG2;
	float		fAmbientB2;
} PROJECTINFO;

struct GROUNDVERTEX
{
	D3DXVECTOR3 p;
	D3DXVECTOR3 n;
	FLOAT       tu, tv;

	// 2008. 12. 11 by ckPark ��������
	// ���� �� �ؽ��� ��ǥ�� ���
	// FLOAT       tu2, tv2;				// �����ϰ� WATERBUMPVERTEX ���� ����
	// end 2008. 12. 11 by ckPark ��������
};


// 2008. 12. 11 by ckPark ��������
struct WATERBUMPVERTEX
{
	D3DXVECTOR3 p;
	D3DXVECTOR3 n;
	FLOAT       tu, tv;
	FLOAT       tu2, tv2;		// ���� �� �ؽ��� ��ǥ�� ���
};
// end 2008. 12. 11 by ckPark ��������


typedef struct _WATERINFO
{
	BOOL		useWater;			// Water ���
	INT			waterHeight;		// Water ����
	SHORT		waterTexNumber;		// Water Texture
} WATERINFO;

typedef struct _NOSPRITE
{
	D3DXVECTOR3 p;
	DWORD       color;
} NOSPRITE;


struct FOGVERTEX
{
	D3DXVECTOR3 p;
	D3DXVECTOR3 n;
	FLOAT       tu, tv;
};

typedef struct _SKILLITEMCHECKTIME
{
	BOOL	bReady;
	FLOAT	fCurrentTime;
}SKILLITEMCHECKTIME;

typedef struct _EFFECTINFO
{
	char		strEffectName[40];
	INT			nType;
	BOOL		bRegion;
	BOOL		bLoop;
	FLOAT		fReTime;
	FLOAT		fCheckTime;
	D3DXVECTOR3 vPos;
} EFFECTINFO;

typedef struct _EFFECTINFOCLIENT
{
	INT			nType;
	BOOL		bRegion;
	BOOL		bLoop;
	FLOAT		fReTime;
	D3DXVECTOR3 vPos;
	FLOAT		fCheckTime;
} EFFECTINFOCLIENT;

typedef struct _PARTYINFO
{
	PartyID_t	PartyID;
	PARTY_TYPE	bPartyType;
	BYTE		bFormationFlyingType;
	BYTE		bFormationFlyingPositionType;
	UINT		nMasterUniqueNumber;	// ��Ƽ(��)�� ��ȣ, added!
}PARTYINFO;

/*typedef struct _ENEMYINFO
{
	MEX_OTHER_CHARACTER_INFO CharacterInfo;
	CHARACTER_RENDER_INFO	 CharacterRenderInfo;			// ������������ ����
	MAP_CHANNEL_INDEX		 MapChannelIndex;
	SHORT			HP;
	float			CurrentHP;
	SHORT			DP;
	float			CurrentDP;
	SHORT			SP;
	SHORT			CurrentSP;
	SHORT			EP;
	SHORT			CurrentEP;
	BYTE			Level;
	//	UINT			CharacterUniqueNumber;
	//	char			CharacterName[SIZE_MAX_CHARACTER_NAME];
	//	ClientIndex_t	ClientIndex;					// 
	//	BYTE			PilotFace;
	//	USHORT			UnitKind;
	//	USHORT			Race;
	//	UINT			GuildUniqueNumber;
	//	BodyCond_t		BodyCondition;
}ENEMYINFO;*/
/*
typedef struct _ITEM_ENCHANT
{
	INT			ItemNum;						// ������ ������ȣ, ���� �������� �� (ITEM_BASE*)
	BYTE		Kind;							// ������ ����(�����, ��, ����, ��ų.....), ITEMKIND_XXX
	char		ItemName[SIZE_MAX_ITEM_NAME];	// ������ �̸�
	float		AbilityMin;						// �������ּҼ���
	float		AbilityMax;						// �������ִ뼺��
	USHORT		ReqRace;						// �ʿ�����
	Stat_t		ReqAttackPart;					// �ʿ������Ʈ
	Stat_t		ReqDefensePart;					// �ʿ䳻����Ʈ
	Stat_t		ReqFuelPart;					// �ʿ俬����Ʈ
	Stat_t		ReqSoulPart;					// �ʿ䰨����Ʈ
	Stat_t		ReqShieldPart;					// �ʿ�����Ʈ
	Stat_t		ReqDodgePart;					// �ʿ�ȸ����Ʈ, 0 ~ 255�� Ȯ��
	USHORT		ReqUnitKind;					// �ʿ���������
	BYTE		ReqLevel;						// �ʿ䷹��
	USHORT		Weight;							// ����
	Prob256_t	HitRate;						// ����Ȯ��(0~255)
	BYTE		Defense;						// ����
	Prob256_t	FractionResistance;				// �Ӽ����׷�(0~255)
	BYTE		NaturalFaction;					// õ���迭, ����(����, ĳ����) Index (õ��)
	BYTE		SpeedPenalty;					// ���ǵ����Ƽ, �̵��ӵ�����ġ�� ����(-:����)
	float		Range;							// ���ݹ���// by dhkwon , 2003.11.5
	BYTE		Position;						// ������ġ
	BYTE		Scarcity;						// ��ͼ�, ���ӻ� ���� Ȯ��, define�ؼ� ���, see below
	float		Endurance;						// ������, ������
	Prob256_t	AbrasionRate;					// ������, �������� �پ��� ������(0~255)
	USHORT		Charging;						// ����������� �ִ� ��ź ��, �������� �ѹ��� ����Ǵ� ����
	BYTE		Luck;							// ���
	UINT		Price;							// ����
	BYTE		DestParameter1;					// ����Ķ����1
	BYTE		DestParameter2;					// ����Ķ����2
	float		ParameterValue1;				// �����Ķ����1
	float		ParameterValue2;				// �����Ķ����2
	UINT		ReAttacktime;					// �� ���ݽð�(ms)
	USHORT		Time;							// ���� �ð�(��ų�� ��)
	USHORT		RepeatTime;						// ����������� ���� �Ѿ� ���� ���, �������� ����, �ð��� ��ų������ ���� �ð�, ������ ��ų�� ��� ����
	USHORT		Material;						// ����
	USHORT		ReqMaterial;					// �ʿ��� ���� ��(����,������ �ʿ�)
	float		RangeAngle;						// ��������(0 ~ PI)
	BYTE		UpgradeNum;						// ���׷��̵� ��, ���׷��̵��� �Ѱ踦 ��Ÿ��.
	INT			LinkItem;						// ��ũ������, �����۰� ������ ������(�Ѿ�)
	BYTE		MultiTarget;					// ���ÿ� ���� �� �ִ� Ÿ���� ��
	USHORT		ExplosionRange;					// ���߹ݰ�(���� �� �������� ������ ��ġ�� �ݰ�)
	BYTE		ShotNum;						// ���� ��,	���� �� �߻� ���� ��Ÿ����.
	BYTE		MultiNum;						// ���� �߻� ź ��,	1�� �߻翡 ����� ���ÿ� ��������
	USHORT		AttackTime;						// ���ݽð�, ������ �ϱ� ���� �ʿ��� �ð�
	BYTE		ReqSP;							// SP �Ҹ�(��ų)
	INT			SummonMonster;					// ��ȯ����(��ų), check: �� �̻� �� ���̹Ƿ� �ð��� �� ����������! 20030918, kelovon
	INT			NextSkill;						// ���� �ܰ��� ��ų ������ �ѹ�(��ų)
	BYTE		SkillLevel;						// ����
	Prob256_t	SkillHitRate;					// ��ų����Ȯ��(0~255)
	BYTE		SkillType;						// ��ų����(�ð� �� �ߵ� ����), ����|Ŭ��|�ð�|����
} ITEM_ENCHANT, *LPITEM_ENCHANT;
*/
struct GUIUnitRenderInfo
{
	//	D3DXVECTOR3 vnextpos;
	//	D3DXVECTOR3 vcurrentpos;
	//	D3DXVECTOR3 vup;
	//	D3DXVECTOR3 vtarget;
	D3DXMATRIX	matrix;
	UINT		rendertype;	// ����ī�ε� --> �Ƹ� ����
};

typedef struct _MONSTER_DATA
{
	char		strRegionName[40];
	UINT		nMonType;				//	���� Ÿ��(�ε���)
	short		sStartx;				//	������ ������ǥ X
	short		sStartz;				//	������ ������ǥ Y
	short		sEndx;					//	������ ����ǥ X
	short		sEndz;					//	������ ����ǥ Y
	short		sMaxMon;				//	
	short		sResNum;				//
	short		sResTime;				//
	BYTE		bMonType;				// 0:���� 1:���� 2:���� 3:����
} MONSTERINFO;

typedef struct _INVEN_DISPLAY_INFO
{
	char IconName[20];
	char Name[50];
	ITEM_BASE* pItem;//ITEM_BASE�� �� ������ ITEM_GENERAL�� ITEM_SKILL�� �����ϱ� ���ؼ�..
} INVEN_DISPLAY_INFO;

typedef enum
{
	_VOIP_NOTLOGIN,
	_VOIP_TRY_REGISTER,
	_VOIP_REGISTERED,
	_VOIP_DIALBLOCK,
	_VOIP_ALERTINGSTATE,
	_VOIP_DIALINGSTATE,
	_VOIP_ERRORSTATE,
}VOIPState;

typedef enum
{
	_CALLSTATE_1TO1,
	_CALLSTATE_PARTY,
	_CALLSTATE_GUILD
} CallState;

typedef struct _VOIP_STATE
{
	HWND		m_hWndAtumVoIPClient;
	BOOL		bCaller;	// ���� �ݷ��̸� TRUE
	VOIPState	nVOIPState;
	CallState	nCallState;	// 1:1, ��밣, ����
	UINT		nCalledAccountUniqueNumber;
	char		szName[SIZE_MAX_CHARACTER_NAME];
	char		szVoIP1to1ServerIP[SIZE_MAX_IPADDRESS];
	USHORT		nVoIP1to1ServerPort;
	char		szVoIPNtoNServerIP[SIZE_MAX_IPADDRESS];
	USHORT		nVoIPNtoNServerPort;
	UINT		nConnectCount;
} VOIP_STATE;



struct STAGE_EFFECT_DATA
{
	INT* pWarpObject;
	INT				nMissionIndex;

	STAGE_EFFECT_DATA()
	{
		pWarpObject = NULL;
		nMissionIndex = -1;
	}
};


#define D3DFVF_TILEVERTEX (D3DFVF_XYZ|D3DFVF_DIFFUSE|D3DFVF_TEX1)
#define D3DFVF_FOGVERTEX (D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_TEX1)
#define D3DFVF_NOSPRITE (D3DFVF_XYZ|D3DFVF_DIFFUSE)


// 2008. 12. 11 by ckPark ��������
//#define D3DFVF_GROUNDVERTEX (D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_TEX2)
#define D3DFVF_GROUNDVERTEX (D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_TEX1)

#define D3DFVF_WATERBUMPVERTEX		(D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_TEX2)
// end 2008. 12. 11 by ckPark ��������




#define MOUSE_TYPE_0	0	// ���콺 �Ϲ�
#define MOUSE_TYPE_1	1	// ���� ����
#define MOUSE_TYPE_2	2	// ���콺 ������
#define MOUSE_TYPE_3	3	// ���콺 �Ķ���
#define MOUSE_TYPE_4	4	// ���콺 ������ ȸ��
#define MOUSE_TYPE_5	5	// ���콺 �Ķ��� ȸ��

#define MOUSE_TYPE_6	6	// ���� �� ������ �Ʒ� ȭ��ǥ
#define MOUSE_TYPE_7	7	// ���� �Ʒ� ������ �� ȭ��ǥ
#define MOUSE_TYPE_8	8	// ���� ������ ȭ��ǥ
#define MOUSE_TYPE_9	9	// �� �Ʒ� ȭ��ǥ
#define MOUSE_TYPE_10	10	// ���� ȭ��ǥ

#define MOUSE_TYPE_11	11	// ��ų Ÿ�� ���콺

// Ű���� �޽��� LPARAM ��
#define WM_KEYDOWN_LPARAM_Q				0x00100001
#define WM_KEYDOWN_LPARAM_R				0x00130001
#define WM_KEYUP_LPARAM_R				0xc0130001
#define WM_KEYDOWN_LPARAM_F				0x00210001
#define WM_KEYDOWN_LPARAM_V				0x002f0001
#define WM_KEYDOWN_LPARAM_M				0x00320001
#define WM_KEYDOWN_LPARAM_PLUS			0x000d0001
#define WM_KEYDOWN_LPARAM_KEYPAD_PLUS	0x004e0001
#define WM_KEYUP_LPARAM_KEYPAD_PLUS		0xc04e0001
#define WM_KEYDOWN_LPARAM_MINUS			0x000c0001
#define WM_KEYDOWN_LPARAM_KEYPAD_MINUS	0x004a0001
#define WM_KEYDOWN_LPARAM_I				0x00170001
#define WM_KEYDOWN_LPARAM_N				0x00310001
#define WM_KEYDOWN_LPARAM_E				0x00120001
#define WM_KEYUP_LPARAM_E				0xc0120001
#define WM_KEYDOWN_LPARAM_Z				0x002c0001
#define WM_KEYUP_LPARAM_Z				0xc02c0001
#define WM_KEYDOWN_LPARAM_T				0x00140001
#define WM_KEYDOWN_LPARAM_B				0x00300001
#define WM_KEYDOWN_LPARAM_P				0x00190001
#define WM_KEYDOWN_LPARAM_A				0x001e0001
#define WM_KEYUP_LPARAM_A				0xc01e0001
#define WM_KEYDOWN_LPARAM_D				0x00200001
#define WM_KEYUP_LPARAM_D				0xc0200001
#define WM_KEYDOWN_LPARAM_L				0x00260001
#define WM_KEYDOWN_LPARAM_K				0x00250001
#define WM_KEYDOWN_LPARAM_FLOW			0x00290001	// `Ű // 2008-10-23 by bhsohn �ڱ� �ڽ����� �� ����Ű �߰�


#define DEFAULT_OBJECT_MONSTER_OBJECT	90000000
#define IS_OBJECT_MONSTER_OBJECT_CODE(x)		(( (int)((x)/DEFAULT_OBJECT_MONSTER_OBJECT) == 1 ) ? TRUE:FALSE)

#define WARP_GATE_OBJECT_NUM			3003500
#define WARP_GATE_OBJECT_NUM_2			3151300					// 2008-06-24 by dgwoo ���� ����Ʈ �߰�.
// 2007-07-10 by dgwoo �Ʒ��� ���� Ʃ�丮�� ����Ʈ ����.
#define TUTORIAL_GATE					3107400
#define TUTORIAL_LAND_GATE				3107500
//#define TUTORIAL_GATE					3024500
#define ARENA_DOOR_OBJECT				3099100


#define ZERO_MEMORY(x)					memset( x, 0x00, sizeof(x));	// ���� �ʱ�ȭ ����

#define SKILL_OBJECT_ALPHA_NONE				255
#define SKILL_OBJECT_ALPHA_DEFAULT			135
#define SKILL_OBJECT_ALPHA_OTHER_INFLUENCE	0

// 2007-04-19 by bhsohn ��ġ���� ������ �߰�
// ��ĵ ���� Ư����
#define SCAN_SKILL						0
#define SCAN_ITEM						1
#define MAX_SCAN						2

// 2007-09-06 by dgwoo �������� ����
#define OUTPOST_STATE_BEFORE				1	
#define OUTPOST_STATE_WAR_START				2
#define OUTPOST_STATE_WAR_END				3
#define OUTPOST_STATE_PROTECT_DESTROY		4
#define OUTPOST_STATE_RESET_START			5
#define OUTPOST_STATE_RESET_DESTROY			6
#define OUTPOST_STATE_RESET_SUCCESS			7

// ���� ����
#define	MOTHERSHIP_MAX_INFLUENCE					2	// �ִ� ������ 
#define	MOTHERSHIP_INFLUENCE_VCN					0	// ����������
#define	MOTHERSHIP_INFLUENCE_ANI					1	// �˸���

// 2007-11-22 by bhsohn �Ʒ��� ���ռ���
// �Ʒ��� ���� �����Ȳ
#define	ARENA_STATE_NONE					0	// �Ϲ� ���� ����
#define	ARENA_STATE_CONNECTING_FS			1	// �Ʒ��� �ʵ� ���� ������
#define	ARENA_STATE_ARENA_WAIT				2	// �Ʒ��� �±����
#define	ARENA_STATE_ARENA_MAIN_TO_ARENA		3	// �Ʒ��� ����ϰ� ������ ���� ������ ��ٸ��� ����
#define	ARENA_STATE_ARENA_LOAD_GAME_INFO	4	// �Ʒ��� �ʿ� �̵��ؼ� ���� ������ �ε� 
#define	ARENA_STATE_ARENA_GAMING			5	// �Ʒ��� ������ 
#define	ARENA_STATE_ARENA_ARENA_TO_MAIN		6	// �Ʒ��� ������ ���μ����� �̵�

// 2008-02-15 by bhsohn ��Ʈ��ũ �ӵ� üũ
typedef struct
{
	int nMaxRepeatCnt;			// �ִ� �ݺ���
	int nCurruntRepeatCnt;		// ���� �ݺ���
	DWORD dwLastCheckTime;		// ������ üũ Ÿ��
	DWORD dwSumCheckTime;		// �ð� ���� �߰�
} structNetCheckInfo;

// 2008-02-25 by bhsohn �Ʒ��� ���� ���� ������ ǥ���ϰ� ����
#define SIZE_MAX_ARENA_FULL_NAME	(SIZE_MAX_CHARACTER_NAME+SIZE_MAX_SERVER_NAME+1)

// 2008-05-19 by dgwoo ä�� �޴� ����Ʈ �ε���.
#define CHAT_TAB_SPEAKER						0							// ����Ŀ.	
#define CHAT_TAB_ALLUSER						1							// ��� �������� ä��.
#define CHAT_TAB_NORMAL							2							// �Ϲ� ä��
#define CHAT_TAB_WAR							3							// ���� ä��
#define CHAT_TAB_TRADE							4							// �ŷ� ä��
#define CHAT_TAB_MAP							5							// �� ä��
#define CHAT_TAB_GUILD							6							// ���� ä��
#define CHAT_TAB_PARTY							7							// ��� ä��
#define CHAT_TAB_ARENA							8							// �Ʒ��� ä��  
#define CHAT_TAB_CHATROOM						9							// ä�ù�
#define CHAT_TAB_SYSTEM							10							// �ý��� �޽���
#define CHAT_TAB_HELPDESK						11							// ����
#define CHAT_TAB_INFLUENCE_LEADER				12							// ���� ������
#define CHAT_TAB_SOUND					        13							// ���� ä��
#define CHAT_TAB_PTOP							14							// �ӼӸ�
#define CHAT_TAB_CASH							15							// ���� ä��
#define CHAT_TAB_GAMEMASTER						16							// ���� ������.
#define CHAT_TAB_NUMBER_ALL						17							// ä������ ��(��ü)

// 2008-04-04 by bhsohn Ep3 Ŀ�´�Ƽ â
struct structReadLetterItemInfo
{
	UID64_t   LetterUID;
	char chSendUser[SIZE_MAX_ARENA_FULL_NAME];					//���� ����
	char chLetterTitle[SIZE_MAX_ARENA_FULL_NAME];				// ���� ����	
	ATUM_DATE_TIME	atimeMail;									// ���� ���� �������
	BOOL bReadMail;												// �о��� �����̳�?
	BOOL bAllMail;												// ��ü �����̳�?
};


// ���� ����
struct structGuildInfo
{
	char	MemberName[SIZE_MAX_CHARACTER_NAME];		// ������
	UID32_t	MemberUniqueNumber;

	USHORT	UnitKind;						// ������ ����
	int		nUnitIdx;						// ���ּ���
	char	chUnitKind[SIZE_MAX_CHARACTER_NAME];		// ������ ����

	char 	chLevel[SIZE_MAX_CHARACTER_NAME];							//
	BYTE	GuildRank;				// GUILD_RANK_XXX
	BYTE	GuildOrderIdx;			// ��� �켱����
	BYTE	IsUseVOIP;				// 1: TRUE, 0: FALSE
	BYTE	IsOnline;				// 1: TRUE, 0: FALSE
	BYTE	IsUseSpeakeingVOIP;		// ���ϰ� �ִ��� ���� // 2008-10-14 by bhsohn VOIP����
};

// end 2008-04-04 by bhsohn Ep3 Ŀ�´�Ƽ â

// 2008-06-16 by bhsohn �±� ���� ������ �������� �߿�� ��
#define CLOSE_WEBSTIE		_T("http://ace.winner.co.th/ads/promotion.asp")

// 2008-06-20 by bhsohn EP3 �ɼǰ��� ó��
// ������ �¾�����
#define		OPTION_RADIO_MAN_TO_MAN			0	// 1:1����
#define		OPTION_RADIO_FORMATIONWAR		1	// �������
#define		OPTION_RADIO_GUILD_WAR			2	// ��������
#define		OPTION_RADIO_WHISPER			3	// �ӼӸ�
#define		OPTION_RADIO_FORMATION_INVITE	4	// ����ʴ�
#define		OPTION_RADIO_GUILD_INVITE		5	// �����ʴ�
#define		OPTION_RADIO_EXCHANGE			6	// ��ȯ
#define		OPTION_RADIO_INTERFACE_POS		7	// �������̽� ��ġ ����
#define		OPTION_RADIO_INTERFACE_HIDE		8	// �������̽� ��� ���߱�
#define		OPTION_RADIO_FRIEND_ID_HIDE		9	// ���� ���� ���̵� ���߱�
#define		OPTION_RADIO_ENEMY_ID_HIDE		10	// �ٸ� ���� ���̵� ���߱�
#define		OPTION_RADIO_MOUSE_LOCK			11	// ���콺 ���α�(������ ����)
#define		OPTION_RADIO_CHAT_FILTER		12	// ������
#define		MAX_OPTION_RADIO				13	

typedef struct
{
	float	fRateX;
	float	fRateY;
	float	fRateWidth;
	float	fRateHeight;
	float	fGameWidth;
	float	fGameHeight;
}stcuctRateRect;

typedef struct
{
	BOOL		bRadioInfo[MAX_OPTION_RADIO];			// ���� ��ư ����
	stcuctRateRect	stRateRect;

	// 2009. 02. 03 by ckPark ä��â �������̽� ũ�� ����
	stcuctRateRect	stChatRect;
	// end 2009. 02. 03 by ckPark ä��â �������̽� ũ�� ����
}sOPTION_ETC;
// end 2008-06-20 by bhsohn EP3 �ɼǰ��� ó��

// 2008-07-10 by bhsohn Ÿ������ �ȵǴ� ���� �ذ�
#define FRAME_START_Y		250//85
#define PARTY_FRAME_SIZE_X			130
#define PARTY_FRAME_SIZE_Y			34
// end 2008-07-10 by bhsohn Ÿ������ �ȵǴ� ���� �ذ�


// 2009. 09. 21 by ckPark ���Ǵ�Ƽ �ʵ� ���� ��ų ����
#define PARTY_FRAME_DEBUFF_ICON_SIZE	15
#define PARTY_FRAME_DEBUFF_START_X		(PARTY_FRAME_SIZE_X + 5)
#define PARTY_FRAME_DEBUFF_Y			(PARTY_FRAME_SIZE_X + 5)
#define PARTY_FRAME_DEBUFF_LINE_PER_ICON 5
// end 2009. 09. 21 by ckPark ���Ǵ�Ƽ �ʵ� ���� ��ų ����


// 2008-08-19 by bhsohn ���� ��ũ �ý��� �߰�
// ��ũ ������Ʈ
#define MARK_INFLUENCE_VCU_OBJECT		7014740		// ����������
#define MARK_INFLUENCE_ANI_OBJECT		7014770		// �˸���
// end 2008-08-19 by bhsohn ���� ��ũ �ý��� �߰�

// 2008-09-26 by bhsohn �ű� ��þƮ ó��
typedef struct
{
	POINT				ptItemIvenPos;
	POINT				ptEqIvenPos;
	BOOL				bItemSetPos;		// ��ġ�� �����߳�?
	BOOL				bEqSetPos;		// ��ġ�� �����߳�?
	BOOL				bShowEqWnd;		// �Ϲ� �κ����â
	BOOL				bShowEqShopWnd;	// ���� ���â
	POINT				ptEqIvenShopPos;
	BOOL				bEqShopSetPos;
} structInvenPosInfo;

// end 2008-09-26 by bhsohn �ű� ��þƮ ó��

// 2008-10-15 by bhsohn ���ҽ� �޸� ��ȣ ��� �߰�
#define NOT_HAVE_OBJECT					3157700
#define INTERFCE_NOT_HAVE_TEXTURE		"xxx"
// end 2008-10-15 by bhsohn ���ҽ� �޸� ��ȣ ��� �߰�

// 2008-10-16 by bhsohn �������� ����, ������ ����â
struct structMotherShipInfo
{
	ATUM_DATE_TIME SummonTime;					// 2008-08-19 by bhsohn ������, ���� ���� ��ȯ �ð����� ����
	char chAttackInfluence[64];							// ���� ����
	char chWinInfluence[64];							// �¸� ����
	char chMotherShipName[SIZE_MAX_MONSTER_NAME];		// ���� ���� ��
	char chWarPoint[64];								// ��������Ʈ
	char chTimeCap[512];								// ������ ���� �ð�	
};

struct structWarPointInfo
{
	ATUM_DATE_TIME SummonTime;					// 2008-08-19 by bhsohn ������, ���� ���� ��ȯ �ð����� ����
	char chAttackInfluence[64];							// ���� ����
	char chWinInfluence[64];							// �¸� ����
	char MapName[SIZE_MAX_MAP_NAME];					// ������ ���̸�	
	char chTimeCap[512];								// ������ ���� �ð�	
};
// end 2008-10-16 by bhsohn �������� ����, ������ ����â

// 2008-11-13 by bhsohn ���̽�ƽ �۾�
// ���̽�ƽ ��ɸ��� �ɼ�
#define	JOSTICK_OPTION_MOUSE_UP					0		// ���콺(��)
#define	JOSTICK_OPTION_MOUSE_DOWN				1		// ���콺(��)
#define	JOSTICK_OPTION_MOUSE_LEFT				2		// ���콺(��)
#define	JOSTICK_OPTION_MOUSE_RIGHT				3		// ���콺(��)
#define	JOSTICK_OPTION_UNIT_GO					4		// go
#define	JOSTICK_OPTION_UNIT_MIN_SPEED			5		// �ּ� �ӵ��� 's'Ű
#define	JOSTICK_OPTION_UNIT_LEFT				6		// Left
#define	JOSTICK_OPTION_UNIT_RIGHT				7		// Right
#define	JOSTICK_OPTION_TARGET_ME				8		// �ڽ� Ÿ��
#define	JOSTICK_OPTION_WEAPON_1					9		// 1������
#define	JOSTICK_OPTION_WEAPON_2					10		// 2������
#define	JOSTICK_OPTION_TARGET_LOCKON			11		// Ÿ�� ����
#define	JOSTICK_OPTION_BOSTER					12		// �ν���
#define	JOSTICK_OPTION_UNITSTOP					13		// ��������
#define	JOSTICK_OPTION_TAKEOFF					14		// ������
#define	JOSTICK_OPTION_BACKVIEW					15		// ���?
#define	JOSTICK_OPTION_JOIN_FORMATION			16		// ��� ���� ����
#define	JOSTICK_OPTION_SLOT_CHANGE				17		// ��ų ���� ���� 
#define	JOSTICK_OPTION_SLOT_0					18		// 1
#define	JOSTICK_OPTION_SLOT_1					19		// 2
#define	JOSTICK_OPTION_SLOT_2					20		// 3
#define	JOSTICK_OPTION_SLOT_3					21		// 4
#define	JOSTICK_OPTION_SLOT_4					22		// 5
#define	JOSTICK_OPTION_SLOT_5					23		// 6
#define	JOSTICK_OPTION_SLOT_6					24		// 7
#define	JOSTICK_OPTION_SLOT_7					25		// 8
#define	JOSTICK_OPTION_SLOT_8					26		// 9
#define	JOSTICK_OPTION_SLOT_9					27		// 10
// 2009-01-16 by bhsohn ���̽�ƽ �߰� ����/��� �߰�
//#define	JOSTICK_OPTION_SLOT_EMPTY				28		// empty
//#define	MAX_JOSTICK_OPTION						30		
#define	JOSTICK_OPTION_OK						28		// 
#define	JOSTICK_OPTION_CANCEL					29		// 
#define	MAX_JOSTICK_OPTION						40		
// end 2009-01-16 by bhsohn ���̽�ƽ �߰� ����/��� �߰�
struct structJoystickKey
{
	int nKeyIdx;					// Ű
	int nKeyValue;					// Ű��
};

typedef struct
{
	BOOL		bUseJoystick;				// ���̽�ƽ ��� ����
	char		chJoySelJoy[MAX_PATH];		// ���� �� ���̽�ƽ ��ġ
	BOOL		bUseFeedJoyStick;			// ���� ��� ����
	int			nJoysticSense;				// ���� ����
	char		chJoyKeyFile[MAX_PATH];		// Ű ���ϸ� ����	

} structJoyStickOptionInfo;

// �ִ� ���� ��
#define		MAX_JOSTICK_OPTION_SLOT				5
// �ִ� �ൿ ��ϼ�
#define		MAX_JOSTICK_OPTION_BEHAVIOR			10

struct structJoystickSetupKeyTable
{
	int nKeySetup;					// Ű
	int nBehavior[MAX_JOSTICK_OPTION_SLOT];					// �ൿ ���̺�
};
// end 2008-11-13 by bhsohn ���̽�ƽ �۾�

// 2009-02-05 by bhsohn ī�޶� ������ ���� ó��
#define CHARACTER_CAMERA_DISTANCE		30.0f	// �ʱ�Ÿ�
#define CHARACTER_CAMERA_HEIGHT			30.0f	// �ʱ����
#define CHARACTER_CAMERA_WHEEL_DISTANCE 6.0f	// �� ����
// end 2009-02-05 by bhsohn ī�޶� ������ ���� ó��

// 2009-02-13 by bhsohn ���� ��ŷ �ý���
#define	INFLUENCE_NAME_ANI			"ANI"			
#define	INFLUENCE_NAME_BCU			"BCU"	

#define	WORLD_RANKING_LEVEL			"LEVEL"			
#define	WORLD_RANKING_FAME			"FAME"
#define	WORLD_RANKING_PVP			"PVP"
// end 2009-02-13 by bhsohn ���� ��ŷ �ý���

#endif
