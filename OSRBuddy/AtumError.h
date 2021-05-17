#pragma once
#ifndef _ATUM_ERROR_H_
#define _ATUM_ERROR_H_

///////////////////////////////////////////////////////////////////////////////
// ERROR CODES
///////////////////////////////////////////////////////////////////////////////

/*
	- Common Error (0x2000 ~ 0x20FF): �������� ���� �� �ִ� ������� �ϴ��� ����Ӵϴ�.
	- DB Error (0x2100 ~ 0x21FF)
	- Server Error (0x2200 ~ 0x22FF)
	- Protocol Error (0x2300 ~ 0x23FF)
	- Network Error (0x2400 ~ 0x24FF)
	- ClientSocket Error (0x2500 ~ 0x25FF)
	- ClientDirectX Error (0x2600 ~ 0x26FF)
	- ClientUser Error (0x2700 ~ 0x27FF)
	- Chatting Error (0x2800 ~ 0x28FF)
*/

#ifndef	ERR_NO_ERROR
#define ERR_NO_ERROR								0x0000
#endif

/////////////////////////////////////
// Common Error (0x2000 ~ 0x20FF)
#define ERR_COMMON_UNKNOWN_ERROR						0x2000
#define ERR_COMMON_LOGIN_FAILED							0x2001
#define ERR_COMMON_NO_SUCH_CHARACTER					0x2002
#define ERR_COMMON_CHARACTER_ALREADY_EXISTS				0x2003
#define ERR_COMMON_TOO_LONG_PACKET						0x2004
#define ERR_COMMON_SERVICE_TEMPORARILY_PAUSED			0x2005
#define ERR_COMMON_INVALID_CLIENT_VERSION				0x2006
#define ERR_COMMON_NOT_ALLOWED_TO_MYSELF				0x2007		// �ڱ� �ڽſ��Դ� �� ��
#define ERR_COMMON_INVALID_BUILDINGKIND					0x2008
#define ERR_COMMON_NO_SUCH_BUILDINGKIND					0x2009
#define ERR_COMMON_BAD_NETWORK							0x200A
#define ERR_COMMON_CONNECTING_GAME						0x200B		// 2008-11-26 by cmkwon, �븸 Netpower_Tpe ������ ������ �߰� ���ν��� �߰� - ���ӿ� ���� ���̴�.

#define ERR_COMMON_SOCKET_CLOSED						0x20F0

/////////////////////////////////////
// DB Error (0x2100 ~ 0x21FF)
#define ERR_DB_ACCOUNT_ALREAY_EXISTS					0x2100		// �ش� ���̵� �̹� ����(pk integrity constraint), 23000
#define ERR_DB_ACCOUNT_CHARACTER_NO_MATCH				0x2101		// ĳ���Ϳ� account�� ��ġ���� ����(�ٸ� ����� ĳ����), SQL_NO_DATA
//#define ERR_DB_AUTH_FAILD								0x2102		// ���̵� �������� �ʰų� �н����尡 Ʋ�� ���, SQL_NO_DATA
#define ERR_DB_INTEGRITY_CONSTRAINT_VIOLATION			0x2103		// integrity constraint violation, 23000
#define ERR_DB_INVALID_PARAMETER						0x2104		// �Ķ���� �� �̻�, 22018
#define ERR_DB_INVALID_UNIQUE_NUMBER					0x2105		// ĳ������ unique number�� �������� ����, SQL_NO_DATA
#define ERR_DB_NO_SUCH_ACCOUNT							0x2106		// �ش� �̸��� account�� ����, SQL_NO_DATA
//#define ERR_DB_NO_SUCH_CHARACTER						0x2107		// �ش� �̸��� ĳ���Ͱ� ����, SQL_NO_DATA
#define ERR_DB_NUMERIC_VALUE_OUT_OF_RANGE				0x2108		// ���ڰ��� ������ ���, 22003
#define ERR_DB_STRING_TOO_LONG							0x2109		// string�� schema�� ���̺��� �� ��, 22001
// item ���� ����
#define ERR_DB_NO_SUCH_STORE_ITEM						0x210A		// DB�� �ش� �������� �������� ����
#define ERR_DB_CANNOT_INSERT_DEFAULT_ITEMS				0x210B		// �⺻ ������ ���� ����
#define ERR_DB_CONNECTION_ERROR							0x210C		// DB���� ������ ����
#define ERR_DB_EXECUTION_FAILED							0x210D		// SQLExecDirect() ����
#define ERR_DB_NO_SUCH_DATA								0x210E		// 2008-06-12 by dhjin, EP3 ����Ÿ �� ���� ��� ���� �߰�
#define ERR_DB_INSERT_QUERY_ERROR						0x210F		// 2008-11-26 by cmkwon, �븸 Netpower_Tpe ������ ������ �߰� ���ν��� �߰� - 

/////////////////////////////////////
// PROTOCOL Error (0x2100 ~ 0x21FF)
#define ERR_PROTOCOL_INVALID_PROTOCOL_TYPE				0x2400		// Client�� ���� ���� Protocol Type�� ��ȿ���� ����
#define ERR_PROTOCOL_INVALID_FIELD_DATA					0x2401		// Client�� ���� ���� Data Size�� Field Type�� ���� Data Size���� ����
#define ERR_PROTOCOL_INVALID_ACCOUNT_UNIQUENUMBER		0x2402		// AccountUniqueNumber�� ��ȿ���� ����
#define ERR_PROTOCOL_INVALID_CHARACTER_UNIQUENUMBER		0x2403		// CharacterUniqueNumber�� ��ȿ���� ����
#define ERR_PROTOCOL_INVALID_UNITKIND					0x2404		// Unit Kind�� ��ȿ���� ����
#define ERR_PROTOCOL_INVALID_CLIENTINDEX				0x2405		// �ڽ� �Ǵ� Target�� ClientIndex�� ��ȿ���� ����
#define ERR_PROTOCOL_INVALID_PACKET						0x2406		// ���� ��Ŷ�� ��ȿ���� ����
#define ERR_PROTOCOL_INVALID_PACKET_SIZE				0x2407		// ���� ��Ŷ�� Size�� ��ȿ���� ����
#define ERR_PROTOCOL_INVALID_SEQUENCE_NUMBER			0x2408		// ���� ��Ŷ�� Sequence Number�� ��ȿ���� ����
#define ERR_PROTOCOL_INVALID_PEER						0x2409		// UDP�� ���� ��Ŷ�� IP�� Port�� ������ ������ Client�� IP, Port�� ���� �ʴ�
#define ERR_PROTOCOL_INVALID_STAT_VALUE_OR_KIND			0x240A		// ���ʽ� ����Ʈ�� ���ų� Stat�� ������ ��ȿ���� �ʴ�
#define ERR_PROTOCOL_EMPTY_ACCOUNTNAME					0x2410		// AccountName�� ��� ����
#define ERR_PROTOCOL_DUPLICATE_LOGIN					0x2411		// ���� �α���
#define ERR_PROTOCOL_NOT_LOGINED						0x2412		// Login ���� �ʾ���
#define ERR_PROTOCOL_INVALID_SERVER_GROUP_NAME			0x2413		// Server Group Name�� ��ȿ���� ����
#define ERR_PROTOCOL_LIMIT_GROUP_USER_COUNT				0x2414		// Limit Server Group User Count�� �ɸ�
#define ERR_PROTOCOL_ACCOUNT_BLOCKED					0x2415		// ���� �з�
#define ERR_PROTOCOL_INVALID_TARGET_INDEX				0x2416		// Target Index �� ��ȿ���� ����
#define ERR_PROTOCOL_LIMIT_STAT_POINT					0x2417		// �ִ� ���� ����Ʈ��
#define ERR_PROTOCOL_INVALID_GETCHARACTER				0x2418		// ��ȿ���� ���� GetCharacter �޽���
#define ERR_PROTOCOL_INVALID_CHARACTER_STATE			0x2419		// Character�� ��ȿ���� ����

#define ERR_PROTOCOL_ALREADY_MAX_CHARACTER				0x2420		// ���̻� Character�� ����� ����, �ִ� 3(SIZE_MAX_NUM_CHARACTER)
#define ERR_PROTOCOL_EMPTY_CHARACTERNAME				0x2421		// CharacterName�� �������
#define ERR_PROTOCOL_STATE_MINUSVALUE					0x2422		// ���� State ���߿� ���̳ʽ� ���� ����
#define ERR_PROTOCOL_STATE_SUMISNOTBONUS				0x2423		// ���� State ���ð��� ���� [20]�� �ƴ�
#define ERR_PROTOCOL_INVALID_GAMESTART					0x2424		// ��ȿ���� ���� Game Start �޽���
#define ERR_PROTOCOL_INVALID_SOCKET_FORNPC				0x2425		// NPC ������ ���� IOCPSocket�� ��ȿ ���� �ʴ�.
#define ERR_PROTOCOL_INVALID_CONNECT_GAMESTART			0x2426		// ��ȿ���� ���� Connect Game Start �޽���
#define ERR_PROTOCOL_INVALID_CONNECT_WARP				0x2427		// ��ȿ���� ���� Warp Connect �޽���
#define ERR_PROTOCOL_INVALID_POSITION					0x2428		// Ŭ���̾�Ʈ�� Position�� ��ȿ���� �ʴ�.
#define ERR_PROTOCOL_INVALID_GAMEEND					0x2429		// GameEnd�� ��ȿ ���� ����
#define ERR_PROTOCOL_GAMESTARTROUTINE_FAILED			0x242A		// GameStartRoutine() ���� ����
#define ERR_PROTOCOL_INVALID_CHARACTER_NAME				0x242B		// �߸��� ĳ���� �̸�
#define ERR_PROTOCOL_INVALID_PEER_CHARACTER				0x242C		// ������ ��ȿ���� �ʽ��ϴ�.
#define ERR_PROTOCOL_INVALID_AUTOSTAT_TYPE				0x242D		// �ڵ��й轺��Ÿ���� ��ȿ���� ����
#define ERR_PROTOCOL_NOT_TUTORIAL_MAP					0x242E		// Ʃ�丮�� ���� �ƴϴ�
#define ERR_PROTOCOL_RACE_PERMISSION_DENIED				0x242F		// ������ ����
#define ERR_PROTOCOL_NOT_ENOUGH_ELAPSE_TIME				0x2430		// ���� �ð��� ������� ����
#define ERR_PROTOCOL_INVALID_CHARACTERNAME				0x2431		// CharacterName�� ��ȿ���� ����
#define ERR_PROTOCOL_CHARACTER_MODE_NOT_MATCHED			0x2432		// CharacterMode�� �������� ����
#define ERR_PROTOCOL_UNKNOWN_CHARACTER_ACTION_TYPE		0x2433		// �˼� ���� CharacterActionType
#define ERR_PROTOCOL_BUILDING_KIND_NOT_MATCHED			0x2434		// BuildingKind�� �������� ����

#define ERR_PROTOCOL_INVALID_BODYCONDITION				0x2440		// body condition�� �� �� ��(ex: warp�ÿ� warping�� �ƴ�)
#define ERR_PROTOCOL_INVALID_MAP_EVENT_INFO				0x2441		// map�� event_info ����ü�� ������ �� �� �Ǿ��� ��
#define ERR_PROTOCOL_MAP_ALREADY_SERVED_BY_FEILD_SERVER	0x2442		// �ٸ� field server�� �̹� map�� ����Ͽ���
#define ERR_PROTOCOL_NO_SUCH_FIELD_SERVER				0x2443		// �ش� field server�� ����
#define ERR_PROTOCOL_NO_SUCH_MAP_SERVED					0x2444		// �ش� ���� ��ϵǾ� ���� ����
#define ERR_PROTOCOL_NO_SUCH_CHANNEL					0x2445		// �ش� ä���� ����
#define ERR_PROTOCOL_MAP_CHANNEL_NOT_MATCHED			0x2446		// ��ä���� ��ġ���� ����
#define ERR_PROTOCOL_CANNOT_WARP						0x2447		// WarpToMap()�Լ� ó�� �� ������ �����Ͽ� ���� �Ұ�
#define ERR_PROTOCOL_CANNOT_WARP_INVALID_STATE			0x2448		// ��ȿ���� ���� ����(���� ����...)�̱� ������ ���� �Ұ�
#define ERR_PROTOCOL_DOING_WARP							0x2449		// ������

#define ERR_PROTOCOL_INVALID_FIELDSERVER_CLIENT_STATE	0x2450		// Field Server �������� client state�� �߸���
#define ERR_PROTOCOL_INVALID_PRESERVER_CLIENT_STATE		0x2451		// Pre Server�������� client state�� �߸���
#define ERR_PROTOCOL_NO_SUCH_SERVER_GROUP				0x2452		// Field server�� ���� �������� ����
#define ERR_PROTOCOL_FIELD_SERVER_ALREADY_REGISTERD		0x2453		// �ش� field server�� �̹� ��ϵǾ���
#define ERR_PROTOCOL_FIELD_SERVER_ID_NOT_MATCHED		0x2454		// PreServer�� ����� (client�� �����ؾ� ��)FieldServer�� ID��, ���Ǹ� ��û�ϴ� FieldServer�� ID�� �ٸ�(AUTH_USER ���...)
#define ERR_PROTOCOL_ALL_FIELD_SERVER_NOT_ALIVE			0x2455		// ��� field server�� �� �׾��� =.=
#define ERR_PROTOCOL_NO_SUCH_SHOP						0x2456		// �ش� ���� ����
#define ERR_PROTOCOL_NO_SUCH_SHOP_ITEM					0x2457		// �޿��� �ش� �������� ���� ����
#define ERR_PROTOCOL_NOT_ENOUGH_MONEY					0x2458		// �� ����, ������ ���� �Ұ�
#define ERR_PROTOCOL_ITEM_KIND_NOT_MATCHED				0x2459		//
#define ERR_PROTOCOL_NO_SUCH_ITEM						0x245A		// �ش� �������� ����
#define ERR_PROTOCOL_ITEM_AMOUNT_EXCEED					0x245B		// ���� �������� ������ ���� ����
#define ERR_PROTOCOL_CLIENT_IP_NOT_MATCHED				0x245C		//
#define ERR_PROTOCOL_IMSERVER_ALREADY_CONNECTED			0x245D		// pre server�� �ش� �׷��� im server�� �̹� ����Ǿ� ����
#define ERR_PROTOCOL_GENERAL_ITEM_ERROR					0x245E		// �Ϲ� ������ ����
#define ERR_PROTOCOL_IM_SERVER_NOT_ALIVE				0x245F		// IM Server�� ����Ǿ����� ����
// 2007-10-12 by dhjin, ��ȣ �� á��
//////////////////////////////////////////////////////////////////////////

// ��Ƽ ���� ����
#define ERR_PROTOCOL_PARTY_MASTER_NOT_MATCHED			0x2460		// ��Ƽ�� ����ġ
#define ERR_PROTOCOL_NO_SUCH_PARTY_MEMBER				0x2461		// �ش� ��Ƽ�� ����
#define ERR_PROTOCOL_PARTY_PERMISSION_DENIED			0x2462		// ������ ����
#define ERR_PROTOCOL_PARTY_MEMBER_ALREADY_EXISTS		0x2463		// �̹� ��������
#define ERR_PROTOCOL_NO_SUCH_PARTY						0x2464		// �ش� ��Ƽ�� ����
#define ERR_PROTOCOL_CANNOT_INVITE_USER					0x2465		// �ʴ��� �� ����
#define ERR_PROTOCOL_GET_MEMBER_FAIL					0x2466		// ��Ƽ�� ������ ���� �� ����(�������� �ƴϰų� �ٸ� �ʿ� ����)
#define ERR_PROTOCOL_PARTY_ID_NOT_MATCHED				0x2467		// ��Ƽ ���̵� ����ġ
#define ERR_PROTOCOL_ALREADY_MAX_PARTY_MEMBER			0x2468		// ��Ƽ ���� �ʰ�
#define ERR_PROTOCOL_ALREADY_PARTY_BATTLE				0x2469		// �̹� ��Ƽ�� ����
#define ERR_PROTOCOL_ALREADY_REQUESTING_PARTY_BATTLE	0x246A		// �̹� ��Ƽ�� ��û����
#define ERR_PROTOCOL_DOING_PARTY_BATTLE					0x246B		// ��Ƽ�� ����
#define ERR_PROTOCOL_IMPOSSIBLE_IN_PARTY				0x246C		// ��Ƽ�ÿ��� �Ұ�

// ��� ���� ����
#define ERR_PROTOCOL_NOT_ENOUGH_PARTY_MEMBER			0x2470		// ��带 ����� ���� �ּ��� ��Ƽ�� ���� ������
#define ERR_PROTOCOL_GUILD_NAME_ALREADY_EXISTS			0x2471		// ���� �̸��� ��尡 ������
#define ERR_PROTOCOL_GUILD_MEMBER_ALREADY_EXISTS		0x2472		// �̹� ��������
#define ERR_PROTOCOL_GUILD_PERMISSION_DENIED			0x2473		// ������ ����
#define ERR_PROTOCOL_NOT_HAVE_GUILD						0x2474		// ��忡 �������� �ʾ���
#define ERR_PROTOCOL_GUILD_NOT_MATCHED					0x2475		// ���� ��尡 ��ġ���� ����
#define ERR_PROTOCOL_NO_SUCH_GUILD_MEMBER				0x2476		// �ش� ��Ƽ�� ����
#define ERR_PROTOCOL_NOT_HAVE_PARTY						0x2477		// ��Ƽ�� �������� �ʾ���
#define ERR_PROTOCOL_NO_SUCH_GUILD						0x2478		// �ش� ��尡 ����
#define ERR_PROTOCOL_NOT_GUILD_MASTER					0x2479		// ������� �ƴϴ�
#define ERR_PROTOCOL_GUILD_CARD_ALREADY_USING			0x247A		// ����ī�尡 �̹� �������
#define ERR_PROTOCOL_INVLID_GUILDNAME					0x247B		// ������ ��ȿ���� �ʴ�, 2006-03-06 by cmkwon
#define ERR_PROTOCOL_NOT_GET_GUILDSTORE_MEMBER			0x247C		// 2006-09-25 by dhjin, ���� â�� �̿� ������ ������ �ƴϴ� ����� �̻� ��밡��
#define ERR_PROTOCOL_DOING_GUILDWAR_BATTLE				0x247D		// ������ ����
#define ERR_PROTOCOL_INVLID_GuildMarkSize				0x247E		// 2007-08-02 by cmkwon, ���� ��ũ �ɻ� �ý��� ���� - ���ܸ�ũ ������ ����
#define ERR_PROTOCOL_OVER_MEMBERCOUNT					0x247F		// 2008-05-27 by dhjin, EP3 ���� ���� ���� - ���ܿ� ���� ĳ�� ������, �ִ� ���ܿ� �� �ѱ�

// Trade ���� error
#define ERR_PROTOCOL_TOO_FAR_TO_TRADE					0x2480		// �� ĳ���� �Ÿ��� �־ �ŷ��� ���� �� ��
#define ERR_PROTOCOL_ALREADY_TRADING					0x2481		// �̹� �ŷ� ����
#define ERR_PROTOCOL_PEER_TRADER_NOT_MATCHED			0x2482		// �ŷ� ��밡 Ʋ��
#define ERR_PROTOCOL_TRADE_NOT_STARTED					0x2483		// �ŷ��� ���۵��� �ʾ���
#define ERR_PROTOCOL_INVALID_ITEMNUM					0x2484		// ItemNum�� �߸��Ǿ���
#define ERR_PROTOCOL_INVALID_ITEM_COUNT					0x2485		// Item ������ invalid��, ��) energy���� �ƴѵ� �ŷ� ������ �������̴�
#define ERR_PROTOCOL_TRADE_ERROR						0x2486		// �Ϲ� �ŷ� ����
#define ERR_PROTOCOL_INVALID_ITEM_KIND					0x2487		// Item Kind�� �߸��Ǿ���
#define ERR_PROTOCOL_MIN_TRADE_QUANTITY_ERROR			0x2488		// �ּ� �ŷ� ���� ���� ����
#define ERR_PROTOCOL_ALREADY_TRADE_ITEM					0x2489		// �̹� �÷��� �������̴�(��ī���ͺ� ������)

// Skill ���� error
#define ERR_PROTOCOL_NO_SUCH_SKILL						0x2490		// ��ų�� �������� ����
#define ERR_PROTOCOL_CANNOT_USE_SKILL					0x2491		// ��ų�� ����� �� ����, ��) level ����, ���� ���� ������
#define ERR_PROTOCOL_INVALID_SKILLTYPE					0x2492		// ��ų Ÿ���� �� �� �Ǿ���
#define ERR_PROTOCOL_NOT_ENOUGH_SP						0x2493		// SP ����(��ų ��� �Ұ�)

// Timer ���� error
#define ERR_PROTOCOL_NO_SUCH_TIME_LIMIT_EVENT_IN_BUCKET	0x24A0		// �ش� �̺�Ʈ�� TIMER_EVENT_BUCKET �ȿ� ����
#define ERR_PROTOCOL_NO_SUCH_TIMER_EVENT_TYPE			0x24A1		// �ش� �̺�Ʈ type�� �ȿ� ����

// ENCHANT ���� ����
#define ERR_PROTOCOL_ALREADY_MAX_ENCHANT_PER_ITEM		0x24A2		// �ִ� ��æƮ ���� �ʰ�
#define ERR_PROTOCOL_ALREADY_HAVE_RARE_FIX				0x24A3		// �̹� Rare Fix�� ���� ��������
#define ERR_PROTOCOL_ALREADY_INITIALIZE_RARE_FIX		0x24A4		// �̹� Rare Fix�� ���� ��������
#define ERR_PROTOCOL_CANNOT_USE_ITEMKIND_PREVENTION_DELETE_ITEM		0x24A5	// �Ĺ�(�ı�����) ��� �� �� ����
#define ERR_PROTOCOL_CANNOT_USE_ITEMKIND_PREVENTION_DELETE_ITEM_BY_STARTCOUNT		0x24A6	// 2009-01-19 by dhjin, ��þƮ Ȯ�� ����, 10��þ �Ĺ� ī�� - ��� ������ ��þƮ ���� �ƴϴ�.

// ���� & ������ ���� ����
#define ERR_PROTOCOL_NOT_ENOUGH_EP						0x24B0		// EP ����(�ν��� �۵� �Ұ�, beam�� �߻� �Ұ�)
#define ERR_PROTOCOL_TOO_LONG_DISTANCE					0x24B1		// �Ÿ��� �ʹ� �ִ�(ex. SIZE_VISIBLERECT_X�̻���)
#define ERR_PROTOCOL_ALREADY_P2P_PK						0x24B2		// �̹� �ϴ��� PK ����
#define ERR_PROTOCOL_TOO_FAR_TO_P2P_PK					0x24B3		// �ʹ� �־ �ϴ��� PK �Ұ�
#define ERR_PROTOCOL_HIGH_LEVEL_GAP_TO_P2P_PK			0x24B4		// ���� ���� ���� ���� PK �Ұ�
#define ERR_PROTOCOL_NOT_DOING_P2P_PK					0x24B5		// PK ���� �ƴ�
#define ERR_PROTOCOL_NOT_ALLOWED_ATTACK					0x24B6		// ���� �Ұ�

// Item ���� ����
#define ERR_PROTOCOL_CANNOT_USE_ITEM							0x2600		// ������ ��� �Ұ�
#define ERR_PROTOCOL_ALREADY_HAVE_ITEM							0x2601		// �̹� �������� ������ �ֽ��ϴ�
#define ERR_PROTOCOL_ALREADY_HAVE_SKILL							0x2602		// �̹� ��ų�� ������ �ֽ��ϴ�
#define ERR_PROTOCOL_INVALID_ITEM_WINDOW_POSITION				0x2603		// �߸��� Item Window Position
#define ERR_PROTOCOL_ALREADY_ITEM_ACTIVATED						0x2604		// �̹� �������� ���� ��(dummy�� ��)
#define ERR_PROTOCOL_NO_SUCH_DES_PARAM							0x2605		// DES_XXX�� �߸��Ǿ���
#define ERR_PROTOCOL_NOT_ENOUGH_BULLET							0x2606		// �Ѿ�(ź��)�� ������
#define ERR_PROTOCOL_ITEM_CANNOT_TRANSFER						0x2607		// �������� �̵��� �� �����ϴ�.
#define ERR_PROTOCOL_NO_SUCH_MIXING_INFO						0x2608		// ������ ���� ������ ����
#define ERR_PROTOCOL_ITEM_OVER_WEIGHT							0x2609		// ���緮 �ʰ�
#define ERR_PROTOCOL_DO_NOT_HAVE_LINK_ITEM						0x260A		// ��ũ �������� ������ ���� ����
#define ERR_PROTOCOL_INVENTORY_FULL_ITEM						0x260B		// �κ��丮�� �� ��
#define ERR_PROTOCOL_STORE_FULL_ITEM							0x260C		// â�� �� ��
#define ERR_PROTOCOL_ALREADY_USE_ITEM							0x260D		// �̹� ��� ���� �������̴�
#define ERR_PROTOCOL_ALREADY_USE_OTHER_ITEM						0x260E		// �̹� �ٸ� ��� ���� �������� �ִ�(���� ItemNum)
#define ERR_PROTOCOL_STAT_ERROR_STATE							0x260F		// ���� ������ ���� ������
#define ERR_PROTOCOL_STAT_INITIALIZE_STATE						0x2610		// ������ �ʱ�ȭ ������
#define ERR_PROTOCOL_AREADY_USING_HP_UP_ITEM					0x2611		// �̹� HP UP �������� �������
#define ERR_PROTOCOL_AREADY_USING_DP_UP_ITEM					0x2612		// �̹� DP UP �������� �������
#define ERR_PROTOCOL_AREADY_USING_SP_UP_ITEM					0x2613		// �̹� SP UP �������� �������
#define ERR_PROTOCOL_AREADY_USING_EP_UP_ITEM					0x2614		// �̹� EP UP �������� �������
#define ERR_PROTOCOL_AREADY_FULL_HP								0x2615		// �̹� HP �� ������
#define ERR_PROTOCOL_AREADY_FULL_DP								0x2616		// �̹� DP �� ������
#define ERR_PROTOCOL_AREADY_FULL_SP								0x2617		// �̹� SP �� ������
#define ERR_PROTOCOL_AREADY_FULL_EP								0x2618		// �̹� EP �� ������
#define ERR_PROTOCOL_CANNOT_USEITEM_IN_PARTY					0x2619		// ��Ƽ �����߿��� ������ ��� �Ұ�
#define ERR_PROTOCOL_CANNOT_IN_CITY_MAP_CHANNEL					0x261A		// ���øʿ����� ��� �Ұ�
#define ERR_PROTOCOL_CHANNEL_USER_OVERFLOW						0x261B		// ä�� ����ڰ� ����.
#define ERR_PROTOCOL_NO_SUCH_EVENT_AREA_INDEX					0x261C		// ������ Event Area Index�� ���� �̺�Ʈ�� ã���� ����.
#define ERR_PROTOCOL_MAX_ITEM_COUNTS_OVER						0x261D		// ī���ͺ� �������� �ִ� ī��Ʈ ����(MAX_ITEM_COUNTS - 20�ﰳ)
#define ERR_PROTOCOL_NOTIFY_MAX_ITEM_COUNTS_OVER				0x261E		// ī���ͺ� �������� �ִ� ī��Ʈ ������ �߻� �� �� ������ �˸�
#define ERR_PROTOCOL_CANNOT_UNWEAR_ARMOR						0x261F		// 2005-10-31 by cmkwon, �ƸӴ� ���� ���� �� �� ����, ��ü�� �����ϴ�
#define ERR_PROTOCOL_NO_SUCH_BULLET_ITEM						0x2620		// 2005-11-02 by cmkwon, �Ѿ� �������� ����
#define ERR_PROTOCOL_CANNOT_ENCHANT_ITEM						0x2621		// 2005-11-21 by cmkwon, ��æƮ/������ �� �� ���� ������
#define ERR_PROTOCOL_BAZAAR_NO_SUCH_ITEM						0x2622		// 2006-08-02 by dhjin, ���λ����� ã�� �� ���� �������϶�
#define ERR_PROTOCOL_GUILD_STORE_FULL_ITEM						0x2623		// 2006-09-23 by dhjin, ��� â�� �� ��
#define ERR_PROTOCOL_CANNOT_USE_ITEM_IN_ARENA					0x2624		// 2007-06-01 by dhjin, �Ʒ��� �ʿ��� ��� �Ұ� ������
#define ERR_PROTOCOL_INVALID_MIXING_INFO						0x2625		// 2009-10-01 by cmkwon, �׷��� ���ҽ� ���� ���� �ʱ�ȭ ��� ���� - 
#define ERR_PROTOCOL_NOT_WEARING_STATE							0x2626		// 2009-09-09 ~ 2010-02-10 by dhjin, ���Ǵ�Ƽ - �ߵ�������������, ���� ���°� �ƴϴ�. 
#define ERR_PROTOCOL_INVALID_INVOKING_TYPE						0x2627		// 2009-09-09 ~ 2010-02-10 by dhjin, ���Ǵ�Ƽ - �ߵ�������������, �ߵ� Ÿ�� ����
#define ERR_PROTOCOL_FAIL_INVOKING_BY_RATE						0x2628		// 2009-09-09 ~ 2010-02-10 by dhjin, ���Ǵ�Ƽ - �ߵ�������������, �ߵ� �̽�
#define ERR_PROTOCOL_FAIL_INVOKING_BY_REQITEMNUM				0x2629		// 2009-09-09 ~ 2010-02-10 by dhjin, ���Ǵ�Ƽ - �ߵ�������������, �ߵ� ���� �� ����
#define ERR_PROTOCOL_COOLING_TIME_INVOKING_ITEM					0x262A		// 2009-09-09 ~ 2010-02-10 by dhjin, ���Ǵ�Ƽ - �ߵ�������������, �ߵ��� ������ ��Ÿ����
#define ERR_PROTOCOL_CANNOT_RARE_ITEM							0x262B		// 2009-09-09 ~ 2010-02-10 by dhjin, ���Ǵ�Ƽ - �ߵ�������������


// �䱸 ���� ���� ����			
#define ERR_PROTOCOL_REQ_EXPERIENCE_NOT_MATCHED					0x2640
#define ERR_PROTOCOL_REQ_RACE_NOT_MATCHED						0x2641		//
#define ERR_PROTOCOL_REQ_ATTACK_PART_NOT_MATCHED				0x2642		//
#define ERR_PROTOCOL_REQ_DEFENSE_PART_NOT_MATCHED				0x2643		//
#define ERR_PROTOCOL_REQ_FUEL_PART_NOT_MATCHED					0x2644		//
#define ERR_PROTOCOL_REQ_SOUL_PART_NOT_MATCHED					0x2645		//
#define ERR_PROTOCOL_REQ_SHIELD_PART_NOT_MATCHED				0x2646		//
#define ERR_PROTOCOL_REQ_DODGE_PART_NOT_MATCHED					0x2647		//
#define ERR_PROTOCOL_REQ_UNITKIND_NOT_MATCHED					0x2648		//
#define ERR_PROTOCOL_REQ_LEVEL_NOT_MATCHED						0x2649		//
#define ERR_PROTOCOL_REQ_MINLEVEL_NOT_MATCHED					0x264A		// �ּ� �������� ������ ����
#define ERR_PROTOCOL_REQ_MAXLEVEL_NOT_MATCHED					0x264B		// �ִ� �������� ������ ����
#define ERR_PROTOCOL_REQ_ITEM_NOT_MATCHED						0x264C		//
#define ERR_PROTOCOL_REQ_QUEST_NOT_MATCHED						0x264D		//
#define ERR_PROTOCOL_REQ_NUM_OF_CHARACTER_NOT_MATCHED			0x264E		//
#define ERR_PROTOCOL_TOO_FAR_TO_DO								0x264F		// ������ �ϱ⿡ �Ÿ��� �ʹ� �ִ�
#define ERR_PROTOCOL_NO_SUCH_REQUEST_TYPE						0x2650		// �ش� REQUEST_TYPE �� ����
#define ERR_PROTOCOL_LOW_PROBABILITY							0x2651		// Ȯ�� �������� ���� ����
#define ERR_PROTOCOL_REQ_NOT_CITY_MAP_CHANNEL					0x2652		// �ݳ���(���ø�)�� �ƴϴ�
#define ERR_PROTOCOL_REQ_MUST_RELEASE_ALL_ITEM					0x2653		// �ݵ�� ��� �������� ���� ���� �ؾ���
#define ERR_PROTOCOL_REQ_WARP_REQUIREMENTS_NOT_MATCHED			0x2654		// ���� �䱸 ���� ����
#define ERR_PROTOCOL_REQ_INFLUENCE_NOT_MATCHED					0x2655		// ����
#define ERR_PROTOCOL_REQ_MAP_OBJECT_NOT_MATCHED					0x2656		// ������ Map Object�� �ٸ���
#define ERR_PROTOCOL_REQ_MAP_AREA_NOT_MATCHED					0x2657		// ������ Map Area�� �ٸ���, 2005-08-29 by cmkwon
#define ERR_PROTOCOL_REQ_MONSTER_NOT_MATCHED					0x2658		// �䱸 ���� ī��Ʈ�� �ٸ���
#define ERR_PROTOCOL_REQ_PARTYMEMBERS_NOT_MATCHED				0x2659		// ��Ƽ�� ���ų� �䱸 ��Ƽ������ �ٸ���.
#define ERR_PROTOCOL_REQ_PARTYMEMBERS_LEVEL_NOT_MATCHED			0x265A		// �ְ��� ��Ƽ���� �������� ���� 10�̻� �̴�
#define ERR_PROTOCOL_REQ_PARTYMEMBERS_SOMEONE_CANNOT_WARP		0x265B		// ��Ƽ���� ������ ���� �� �� ���� �����̴�
#define ERR_PROTOCOL_REQ_PARTYMEMBERS_SOMEONE_NOT_COMPLETION	0x265C		// ��Ƽ���� ������ ����Ʈ �Ϸ� ���°� �ƴϴ�.
#define ERR_PROTOCOL_REQ_MIX_ITEM_NOT_MATCHED					0x265D		// 2007-04-02 by cmkwon, ����Ʈ �Ϸ� ���ǿ� ���� ������� �ʿ���
#define ERR_PROTOCOL_REQ_PW_NOT_MATCHED							0x265E		// 2008-06-03 by dhjin, EP3 ��� ���� - PW����
#define ERR_PROTOCOL_NOT_WARP_BURNING_MAP						0x265F		// 2010-11-24 by shcho, �ݿ��� ����� ���� ����Ÿ�� ���̸� ��ȯ�Ұ� ó��

// Quest ���� ����
#define ERR_PROTOCOL_NO_SUCH_CHARACTER_QUEST					0x2700
#define ERR_PROTOCOL_QUEST_ALREADY_COMPLETED					0x2701		// �̹� ���� �Ϸ�� quest��
#define ERR_PROTOCOL_QUEST_NOT_IN_PROGRESS						0x2702		// �������� ����Ʈ�� �ƴ�
#define ERR_PROTOCOL_QUEST_RESULT_PROCESS_FAILED				0x2703		// ����Ʈ ��� ó�� ����
#define ERR_PROTOCOL_QUEST_GENERAL_ERROR						0x2704		// ����Ʈ �Ϲ� ����
#define ERR_PROTOCOL_TIME_LIMIT_ERROR							0x2705		// �ð� �������� ���� ����
#define ERR_PROTOCOL_REQ_NOT_GUILD_MASTER						0x2706		// ����常 ������ ����Ʈ�̴�
#define ERR_PROTOCOL_QUEST_ALREADY_EXIST_CITYWAR				0x2707		// �̹� �ٸ� ���������� ����Ʈ�� �������̴�
#define ERR_PROTOCOL_QUEST_NEVER_COMPLITION_BY_USER				0x2708		// ������ ���ؼ� ����Ʈ�� �Ϸ�Ұ���
#define ERR_PROTOCOL_QUEST_INVALID_CITYWAR_QUEST_INDEX			0x2709		// ����Ʈ �ε����� ��ȿ���� �ʴ�
#define ERR_PROTOCOL_QUEST_CANNOT_CITYWAR_QUEST					0x270A		// ���������� ����Ʈ�� ������ ����(�������� �������� ����)
#define ERR_PROTOCOL_QUEST_CITYWAR_MGAMESERVERID_NOT_MATCHED	0x270B		// ���������� ����Ʈ�� ��Ҵ� ���� ���������� �����ϴ�
#define ERR_PROTOCOL_QUEST_COUPON_INVALID_NUMBER				0x2710		// ������ȣ�� DB�� �������� �ʰų�
#define ERR_PROTOCOL_QUEST_COUPON_ALREADY_USED					0x2711		// �̹� ���� ����
#define ERR_PROTOCOL_QUEST_COUPON_EXPIRED						0x2712		// ���� ��ȿ�Ⱓ ���
#define ERR_PROTOCOL_QUEST_COUPON_USE_ERROR						0x2713		// ���� ��� Error
#define ERR_PROTOCOL_QUEST_NO_LEVEL_UP							0x2714		// �������� ���� ����
#define ERR_PROTOCOL_QUEST_IS_IN_PROGRESS						0x2715		// ����Ʈ�� ��������
#define ERR_PROTOCOL_QUEST_IMPOSSIBLE_GIVEUP					0x2716		// ���� �� �� ���� ����Ʈ.

// ���� ���� ����
#define ERR_PROTOCOL_QUEST_SERVICE_PAUSED						0x2740		// ����Ʈ ��� �Ͻ� ������

// GET_INFO ���� ����
#define ERR_PROTOCOL_NO_SUCH_MONSTER_INFO						0x2780
#define ERR_PROTOCOL_NO_SUCH_MAPOBJECT_INFO						0x2781
#define ERR_PROTOCOL_NO_SUCH_QUEST_INFO							0x2782
#define ERR_PROTOCOL_NO_SUCH_ITEM_INFO							0x2783

///////////////////////////////////////////////////////////////////////////////
// Chatting Error (0x2800 ~ 0x28FF)
#define ERR_CHAT_CHARACTER_NAME_NOT_MATCHED				0x2800		// ĳ���� �̸� ����ġ
#define ERR_CHAT_NOT_ALLOWED_STRING						0x2801		// �� ���� �ܾ ����
#define ERR_CHAT_PERMISSION_DENIED						0x2802		// �ش� ä�� ���� ����
#define ERR_CHAT_INVALID_COMMAND						0x2803		// �ش� ä�� ���� ����
#define ERR_CHAT_CHAT_NOT_TRANSFERED					0x2804		// �ش� ä���� ���޵��� �ʾҽ��ϴ�
#define ERR_CHAT_CHAT_BLOCKED							0x2805		// ä�ñ��� ����


// ģ��, �ź� ��� ���� ����
#define ERR_FRIEND_INVALID_CHARACTER_NAME				0x2900		// ĳ�����̸��� ����ְų� ��ȿ���� �ʴ�
#define ERR_FRIEND_REGISTERED_PEER_REJECTLIST			0x2901		// ���� �źθ���Ʈ�� ��ϵǾ� ����
#define ERR_FRIEND_ALREADY_REGISTERED					0x2902		// �̹� ����Ʈ(ģ��, �ź�)�� ��ϵǾ�����
#define ERR_FRIEND_ALREADY_MAX_LIST						0x2903		// �̹� ����Ʈ �ִ��ο��� ��ϵǾ�����
#define ERR_FRIEND_NO_SUCH_CHARACTER_IN_LIST			0x2904		// ����Ʈ���� ĳ�����̸��� ����

// Countdown ���� ����	
#define ERR_COUNTDOWN_INVALID_COUNTDOWN_TYPE			0x2910		// Countdown Type�� ��ȿ���� ����
#define ERR_COUNTDOWN_NOT_ENOUGH_TIME					0x2911		// �ð��� ��� ���� �ʾҴ�
#define ERR_INTERVAL_SYSTEM_SECOND						0x2912		// 2008-08-18 by dhjin, 1�� �� �ý��� ��ȹ��

// ���������� ����
#define ERR_CITYWAR_NO_SUCH_CITYWAR_INFO				0x2A00		// ���������� ���� ������ ����
#define ERR_CITYWAR_NOT_MATCHED_CITY_MAP_INDEX			0x2A01		// ���������� ���� ���� �ƴϴ�
#define ERR_CITYWAR_SETOCCUPYINFO_PERMISSION_DENIED		0x2A02		// ���������� ���� ���� ����
#define ERR_CITYWAR_SETOCCUPYINFO_IMPOSSIBLE_STATE		0x2A03		// ���������� ���� �Ұ��� �����̴�(Nomal ���°� �ƴϴ�)
#define ERR_CITYWAR_SETOCCUPYINFO_IMPOSSIBLE_TIME		0x2A04		// ���� �ð��� ���������� ���� �Ұ��� �ð��̴�
#define ERR_CITYWAR_SETOCCUPYINFO_INVALID_WARTIME		0x2A05		// ���������� ���� �ð��� ��ȿ���� �ʴ�

// MGameMoney/MGameCash ����
#define ERR_CASH_mgQueryMall_ERROR						0x3000		// mgQueryMall���� false�� ������
#define ERR_CASH_mgQueryMall_RESULT_CANNOT_PAYMENT		0x3001		// mgQueryMall���� ����� ����(��ݽ���)
#define ERR_CASH_mgQueryMall_RESULT_NO_ACCOUNT			0x3002		// mgQueryMall���� ����� ����(���� �������� ����)
#define ERR_CASH_NOT_CHARGE_USER						0x3003		// 2006-06-01 by cmkwon, ���� ����ڰ� �ƴϴ�
#define ERR_CASH_INVALID_EXT_ACCOUNTID_NUM				0x3004		// 2006-06-02 by cmkwon
#define ERR_CASH_INVALID_ITEM_INFORMATION				0x3005		// 2006-06-05 by cmkwon
#define ERR_CASH_NORMAL_ERROR							0x3006		// 2006-06-05 by cmkwon
#define ERR_CASH_CASH_SHOP_NO_SERVICE					0x3007		// 2007-01-10 by cmkwon, ���� ���� ���� ����
#define ERR_CASH_LIBRARY_INIT_ERROR						0x3008		// 2007-08-22 by cmkwon, �߱� Yetime ���� ���̺귯�� ���� - ���� �߰�, ���̺귯�� �ʱ�ȭ ����
#define ERR_CASH_INVALID_GIVE_TARGET_ACCOUNT			0x3009		// 2009-08-18 by cmkwon, ���� ĳ���� �� ���� üũ �߰� - ���� �� ����


///////////////////////////////////////////////////////////////////////////////
// 2005-12-02 by cmkwon
#define ERR_INVALID_CHARACTER							0x4000		// Character�� ��ȿ���� �ʴ�(��������, ����)
#define ERR_INVALID_PEER_CHARACTER						0x4001		// �� �ƴ� �ٸ� Character�� ��ȿ���� �ʴ�(��������, ����)
#define ERR_WARPING										0x4002		// ������
#define ERR_IN_PARTY_BATTLE								0x4003		// ��Ƽ����
#define ERR_REQ_WARP_COMPLETIONQUEST_NOT_MATCHED		0x4004		// ���� ��� ����, �ʿ� ����Ʈ�� �Ϸ��ؾ� �Ѵ�
#define ERR_REQ_CHOOSE_INFLUENCE_TYPE					0x4005		// ���� ������ �ʿ��ϴ�
#define ERR_CANNOT_WARP_CONNFLICT_AREA					0x4006		// ���� �������� ���� �Ұ�,// 2006-02-14 by cmkwon
#define ERR_CANNOT_WARP_POSSESSED_CONNFLICT_AREA		0x4007		// ������ ���� �������� ���� �Ұ�,// 2006-02-14 by cmkwon
#define ERR_CANNOT_WARP_BY_TRADING						0x4008		// �ŷ����̹Ƿ� ���� �Ұ�, 2006-03-23 by cmkwon
#define ERR_CANNOT_WARP_BY_SHOPPING						0x4009		// ���� �̿����̹Ƿ� ���� �Ұ�, 2006-03-23 by cmkwon
#define ERR_CANNOT_ATTACHED_USING_PREMIUM_CARD			0x400A		// 2006-03-30 by cmkwon, �� �������� �����̾� ī�� ��� �߿��� ���� �� �� ����
#define ERR_CANNOT_BUY_PREMIUM_CARD_USING_SPEC_ITEM		0x400B		// 2006-03-30 by cmkwon, Ư�� ������ ��� �� ���� �����̾� ī�带 ���� �� �� ����
#define ERR_EXPIRED_ITEM								0x400C		// 2006-03-31 by cmkwon, ��� �ð��� ����� �������̴�
#define ERR_FAILURE_USE_RESTORE_ITEM					0x400D		// 2006-04-10 by cmkwon, ��Ȱ ������(õ���� ��ȣ/����/����) ��� ���� - Ȯ���� ����
#define ERR_DOING_GAMEEVENT								0x400E		// 2006-04-21 by cmkwon, �̹� �����̺�Ʈ ������
#define ERR_INVALID_GAMEUSER							0x400F		// 
#define ERR_INVALID_CALL_WARP_EVENT_ID					0x4010		// 2006-07-21 by cmkwon 
#define ERR_TIMEOVER_CALL_WARP_EVENT					0x4011		// 2006-07-21 by cmkwon 
#define ERR_CANNOT_PUT_ITEM								0x4012		// 2006-07-26 by cmkwon
#define ERR_OVER_COUNT									0x4013		// 2006-07-26 by cmkwon
#define ERR_INVALID_BAZAAR								0x4014		// 2006-07-26 by cmkwon
#define ERR_USING_BAZAAR								0x4015		// 2006-07-26 by cmkwon
#define ERR_INVISIBLE_STATE								0x4016		// 2006-08-03 by cmkwon, ĳ���Ͱ� ���� �����̴�
#define ERR_DOING_SERVER_SHUTDOWN						0x4017		// 2006-08-04 by cmkwon, ���� �ٿ� �������
#define ERR_NO_SEARCH_CHARACTER							0x4018		// 2006-09-15 by dhjin, ĳ���͸� ã�� ��������
#define ERR_NO_MEMBERSHIP_USER							0x4019		// 2006-09-15 by dhjin, �ɹ��� ������ �ƴҶ�
#define ERR_ALREADY_OPEN_OTHER_STORE					0x401A		// 2006-09-15 by cmkwon, �ٸ� â�� ���� �ִ�
#define ERR_ALREADY_LOADING_GUILD_STORE					0x401B		// 2006-09-15 by cmkwon, ���� â�� ������ �ε���
#define ERR_NO_SUCH_GUILD_STORE							0x401C		// 2006-09-25 by cmkwon, ���� UID�� ���� â�� ����
#define ERR_PERMISSION_DENIED							0x401D		// 2006-09-27 by cmkwon, ���� ������ �����ϴ�.
#define ERR_INVALID_EXCUTE_PARAMETER_COUNT				0x401E		// 2006-10-02 by cmkwon, ���� ���� ���� ����
#define ERR_INVALID_EXCUTE_PARAMETER					0x401F		// 2006-10-02 by cmkwon, ���� ���� ����
#define ERR_NOT_RANK_DRAW_GUILD_STORE					0x4020		// 2006-10-09 by dhjin, ���� �̻� ã�� �� �ִ�.
#define ERR_CANNOT_BOOSTER								0x4021		// 2006-10-13 by cmkwon, �ν��� ��� �Ұ�
#define ERR_NOT_INVISIBLE_STATE							0x4022		// 2007-04-02 by cmkwon, ĳ���Ͱ� ���� ���°� �ƴϴ�
#define ERR_JAMBOREE_NO_SUCH_CHARACTER					0x4023		// 2007-04-09 by cmkwon, ��ȸ ������ ĳ���Ͱ� ����, ���� �Ұ�
#define ERR_JAMBOREE_FAIL_CREATE_CHARACTER				0x4024		// 2007-04-09 by cmkwon, ��ȸ ������ ĳ���� ���� �Ұ�
#define ERR_BOSS_STRATEGYPOINT_STATE_SUMMON				0x4025		// 2007-04-26 by dhjin, �����̳� ��������Ʈ�� ��ȯ�Ǿ� �ִ� ����				
#define ERR_CANNOT_WARP_TO_CITY							0x4026		// 2007-05-22 by cmkwon, ���ø����� ���� �Ұ�(�ٸ� ������ ���ø�)
#define ERR_INVALID_WEAPON_INDEX						0x4027		// 2007-06-08 by cmkwon, 2�� ź�� �ε��� ����
#define ERR_INVALID_TUTORIAL							0x4028		// 2007-07-23 by dhjin, Tutorial ������ ã�� �� ����.
#define ERR_CANNOT_USE_SPEAKER_ITEM						0x4029		// 2007-08-24 by cmkwon, ����Ŀ������ ��� ����/���� ���� ��� �߰� - �����߰�
#define ERR_CANNOT_WARP_TO_OUTPOST						0x402A		// 2007-08-28 by dhjin, �������� ������ ���� �Ұ�
#define ERR_CANNOT_SEARCH_OUTPOST						0x402B		// 2007-08-28 by dhjin, �������� ã�� ������ ��
#define ERR_ALREADY_SET_OUTPOST_NEXTWARTIME				0x402C		// 2007-08-28 by dhjin, �������� �ð� ������ �̹� �Ǿ��ִ�.
#define ERR_CANNOT_SEARCH_OUTPOST_NEXTWARTIME			0x402D		// 2007-08-28 by dhjin, �������� �ð� ������ ã�� ������ ��
#define ERR_CONFERENCEROOM_PERMISSION_DENIED			0x402E		// 2007-08-30 by cmkwon, ȸ�Ƿ� �ý��� ���� - ���� �Ұ� ���� �߰�
#define ERR_CANNOT_WARP_TO_OUTPOST_CITY_MAP				0x402F		// 2007-09-12 by dhjin, �������� ���� ������ ���� �Ұ�


#define ERR_ARENA_NO_SUCH_TEAM							0x4030		// 2007-04-23 by dhjin, �Ʒ��� ���ǿ� �´� ���� ã�� �� ����
#define ERR_ARENA_CREATE_TEAM							0x4031		// 2007-04-23 by dhjin, �Ʒ��� �� ���� ����
#define ERR_ARENA_NOT_MATCH_MODE						0x4032		// 2007-04-23 by dhjin, �Ʒ��� �� ��尡 Ʋ����
#define ERR_ARENA_NOT_MATCH_LEVEL						0x4033		// 2007-04-23 by dhjin, �Ʒ��� �� ������ Ʋ����
#define ERR_ARENA_NOT_MATCH_PW							0x4034		// 2007-04-23 by dhjin, �Ʒ��� �� �н����� Ʋ����
#define ERR_ARENA_FULL_TEAMLIST							0x4035		// 2007-04-23 by dhjin, �Ʒ��� ���� �� ���ִ�
#define ERR_ARENA_STATE									0x4036		// 2007-04-23 by dhjin, �Ʒ��� �� ���¿��� ���� �϶�
#define ERR_ARENA_STATE_TEAM_READY						0x4037		// 2007-06-05 by dhjin, �Ʒ��� �� ��Ī���̾ ���� ���� �� �� ������
#define ERR_ARENA_STATE_TEAM_WARING						0x4038		// 2007-04-23 by dhjin, �Ʒ��� �� �������̾ ���� ���� �� �� ������
#define ERR_ARENA_BLOCKED								0x4039		// 2007-07-11 by cmkwon, �Ʒ����� �ý��� ���� - 

#define ERR_NO_SEARCH_CITYLEADER_INFO					0x4040		// 2007-08-22 by dhjin, CityLeader ������ ã�� ������ ��
#define ERR_REQ_NOT_LEADER_CANDIDATE					0x4041		// 2007-10-30 by dhjin, ������ �ĺ� ��� ���ǿ� �������� �ʴ�.
#define ERR_REQ_NOT_POLLDATE_APPLICATION				0x4042		// 2007-10-30 by dhjin, ������ �ĺ� ��� �Ⱓ�� �ƴϴ�.
#define ERR_FAIL_REG_LEADER_CANDIDATE_BY_DB				0x4043		// 2007-10-30 by dhjin, ������ �ĺ� ��Ͽ� ���� DB
#define ERR_FAIL_REG_LEADER_CANDIDATE_BY_REQ			0x4044		// 2007-10-30 by dhjin, ������ �ĺ� ��Ͽ� �䱸 ������ �������� ���� ����
#define ERR_REQ_NOT_POLLDATE_VOTE						0x4045		// 2007-10-30 by dhjin, ��ǥ �Ⱓ�� �ƴϴ�.
#define ERR_REQ_NOT_VOTE								0x4046		// 2007-10-31 by dhjin, ��ǥ ���ǿ� �������� �ʴ�.
#define ERR_ALREADY_VOTE								0x4047		// 2007-10-31 by dhjin, �̹� ��ǥ�� �����̴�.
#define ERR_INVALID_LEADER_CANDIDATE					0x4048		// 2007-10-31 by dhjin, ��ȿ�� ������ �ĺ��� �ƴϴ�.
#define ERR_ALREADY_LEADER_CANDIDATE					0x4049		// 2007-11-01 by dhjin, �̹� ������ �ĺ��̴�.
#define ERR_ALREADY_DELETE_LEADER_CANDIDATE				0x404A		// 2007-11-01 by dhjin, �̹� Ż���� ������ �ĺ��̰ų� Ż�� �Ұ����� �����̴�.
#define ERR_REQ_NOT_POLLDATE_ALL_RANGE					0x404B		// 2007-11-20 by dhjin, ���� �Ⱓ�� �ƴϴ�.
#define ERR_REQ_REG_LEADER_CANDIDATE					0x404C		// 2007-11-20 by dhjin, ������ �ĺ��� ����� �Ǿ��ִ�.

#define ERR_WARING_OUTPOST_TO_OWNMAP					0x404D		// 2007-11-09 by dhjin, ���������� ���� ���̴�.

#define ERR_DELETE_CHARACTER_GUILDCOMMANDER				0x404E		// 2008-10-20 by dhjin, �������� �ɸ��� ���� �Ұ��� ����

///////////////////////////////////////////////////////////////////////////////
// 2007-09-12 by cmkwon, ��Ʈ�� 2���н����� ���� - 2���н����� �ý��� ���� �߰�
#define ERR_SECPASS_NOT_USE_SYSTEM						0x4050		// 2007-09-12 by cmkwon, 2���н����� �ý����� ������� �ʴ´�
#define ERR_SECPASS_PASSWORD_NOT_SETTING				0x4051		// 2007-09-12 by cmkwon, 2���н����尡 �����Ǿ� ���� ����
#define ERR_SECPASS_ALREADY_LOCK						0x4052		// 2007-09-12 by cmkwon, �̹� Lock ������
#define ERR_SECPASS_ALREADY_UNLOCK						0x4053		// 2007-09-12 by cmkwon, �̹� Unlock ������
#define ERR_SECPASS_PASSWORD_NOT_MATCHED				0x4054		// 2007-09-12 by cmkwon, �̹� Unlock ������
#define ERR_SECPASS_NEW_PASSWORD_NOT_SETTING			0x4055		// 2007-09-12 by cmkwon, �ű� �н����尡 �����Ǿ� ���� ����
#define ERR_SECPASS_LOCKED								0x4056		// 2007-09-12 by cmkwon, 2���н����尡 Lock ������

//////////////////////////////////////////////////////////////////////////
// 2008-11-10 by dhjin. ��Ű�ӽ�
#define ERR_LUCKYITEM_INSERT_BUT_COINITEM_DELETE		0x4060		// 2008-11-10 by dhjin, ��Ű�ӽ� �������� �ϳ��� ���޵Ǿ����� �ý��ۿ� ������ �־� ���������� ������ �ʾ��� ���

///////////////////////////////////////////////////////////////////////////////
// ������ ����
#define ERR_INVALID_ARMOR_ITEM							0x4100		// �Ƹ� �������� ��ȿ���� �ʴ�(���ų� ItemKind ����)
#define ERR_ITEM_TRADING								0x4101		// 2005-12-26 by cmkwon, �ŷ����Դϴ�. (�����̿� �Ұ�, â�� �̿� �Ұ�, ...)
#define ERR_USING_SHOP									0x4102		// 2006-05-11 by cmkwon, ���� �̿���(�ŷ� �Ұ�)
#define ERR_NO_SUCH_WEAPON_ITEM							0x4103		// 2007-08-07 by cmkwon, 1��/2�� ���� �Ѿ� ���� ������ ���� - �����ڵ� �߰�
#define ERR_ALREADY_FULL_BULLET							0x4104		// 2007-08-07 by cmkwon, 1��/2�� ���� �Ѿ� ���� ������ ���� - �����ڵ� �߰�
#define ERR_INVALID_ITEMEVENT_UID						0x4105		// 2008-01-10 by cmkwon, ������ �̺�Ʈ �ý��ۿ� �� ���� �ý��� �߰� - 
#define ERR_NOT_ACCOUNT_BLOCKED							0x4106		// 2008-01-31 by cmkwon, ���� ��/���� ��ɾ�� ������ �ý��� ���� - �� ���°� �ƴϴ�
#define ERR_SOLD_OUT_SHOP_ITEM							0x4107		// 2010-01-26 by cmkwon, ĳ�� ������ �����Ǹ� �ý��� ���� - 
#define ERR_NO_SUCH_ENCHANT_INFO						0x4108		// 2010-04-20 by cmkwon, �ű� ��Ű �ӽ� ���� - 
#define ERR_NOT_DISSOLVED_ITEM							0x4109		// 2010-08-31 by shcho&jskim �����ۿ��� �ý��� - ���� �ý��� ��Ŷ ó��
#define ERR_NOT_INSERT_DISSOLVED_ITEMS					0x4128		// 2010-08-31 by shcho&jskim �����ۿ��� �ý��� - ���� �ý��� ��Ŷ ó��

// 2007-10-12 by dhjin, �������� ���� ���� ����
#define ERR_PROTOCOL_SUBLEADER_SET_FAIL					0x4110		// 2007-10-06 by dhjin, �������� ���� ���� 
#define ERR_PROTOCOL_SUBLEADER_SET_ALEADY				0x4111		// 2007-10-06 by dhjin, �������ڰ� �̹� ���� �Ǿ�����

#define ERR_CANNOT_USE_GUILD_STORE						0x4120		// 2009-09-23 by cmkwon, �ʵ�â�� ĳ�� ������ ���� - ����â�� ��� �Ұ�
#define ERR_CANNOT_USE_STORE							0x4121		// 2009-09-23 by cmkwon, �ʵ�â�� ĳ�� ������ ���� - â�� ��� �Ұ�
#define ERR_CANNOT_USE_FIELD_STORE						0x4122		// 2009-09-23 by cmkwon, �ʵ�â�� ĳ�� ������ ���� - �ʵ�â�� ��� �Ұ�
#define ERR_ALREADY_USING_BUILDING						0x4123		// 2009-09-23 by cmkwon, �ʵ�â�� ĳ�� ������ ���� - ���� �̿� ��
#define ERR_NO_SUCH_BUILDINGINDEX						0x4124		// 2009-09-23 by cmkwon, �ʵ�â�� ĳ�� ������ ���� - 
#define ERR_CANNOT_BUY_ITEM								0x4125		// 2009-09-23 by cmkwon, �ʵ�â�� ĳ�� ������ ���� - 
#define ERR_ALREADY_USE_ITEMPARAM						0x4126		// 2010-01-18 by cmkwon, ������ ���� Parameter �ߺ� üũ �ý��� ���� - 


///////////////////////////////////////////////////////////////////////////////
// �� ����
#define ERR_MAP_CHECKSUM_NOT_MATCHED					0x4200		// 2007-04-06 by cmkwon, 

///////////////////////////////////////////////////////////////////////////////
// ĳ���� ����
#define ERR_REQ_CHOOSE_START_CIIY_MAP_INDEX				0x4250		// 2009-10-12 by cmkwon, ������ī ���� ��� ���� - �Ϲݼ����� ���� ���ø� ������ �ʿ��ϴ�


//////////////////////////////////////////////////////////////////////////
// 2007-12-28 by dhjin, �Ʒ��� ���� - 
#define ERR_INVALID_ARENASERVER							0x4300		// 2007-12-28 by dhjin, �Ʒ��� ������ �ƴϴ�.
#define ERR_NO_SUCH_FIELDSERVER							0x4301		// 2007-12-28 by dhjin, �ʵ� ������ ã�� �� ����.
#define ERR_INVALID_MAINSERVER_CHARACTER				0x4302		// 2007-12-28 by dhjin, ��ȿ���� ���� ���� �����̴�.
#define ERR_INVALID_ARENASERVER_CHARACTER				0x4303		// 2007-12-28 by dhjin, ��ȿ���� ���� �Ʒ��� �����̴�.
#define ERR_CANNOT_USE_ARENASERVER						0x4304		// 2008-02-26 by dhjin, �Ʒ��� ���������� ��� �Ұ��̴�.
#define ERR_NOT_CONNECT_TO_ARENASERVER					0x4305		// 2008-03-07 by dhjin, �Ʒ��� ������ ������ �Ǿ� ���� �ʴ�.	

//////////////////////////////////////////////////////////////////////////
// 2008-04-30 by dhjin, EP3 ���� �ý��� -
#define ERR_NO_SUCH_LETTER								0x4310		// 2008-04-30 by dhjin, EP3 ���� �ý��� - ������ ã�� ���Ͽ���.

//////////////////////////////////////////////////////////////////////////
// 2008-04-30 by dhjin, EP3 - ���� ���� ����
#define ERR_ALREADY_REG									0x4320		// 2008-04-30 by dhjin, EP3 - ���� ���� ���� - �ڱ� �Ұ��� ����� �Ǿ��ִ�.
#define ERR_CANNOT_USE_NEW_COMMANDER_BY_CITYLEADER      0x4321		// 2008-06-19 by dhjin, EP3 - ���� ���� ���� - �����ڳ� �������� �������� ������ ���� �Ұ� 
#define ERR_CANNOT_USE_NEW_COMMANDER_BY_POLL		    0x4322		// 2008-06-19 by dhjin, EP3 - ���� ���� ���� - ���ſ� �⸶�� ����� ������ ���� �Ұ�
#define ERR_POSSESS_OUTPOST							    0x4323		// 2009-06-30 by cmkwon, ���� ��ü�� üũ ���� - ���� ������ �����ϰ� �ִ�.

//////////////////////////////////////////////////////////////////////////
// 2008-06-17 by dhjin, EP3 ä�ù� -
#define ERR_INVALID_DATA_FROM_CLIENT					0x4330		// 2008-06-17 by dhjin, EP3 ä�ù� - Ŭ���̾�Ʈ�κ��� ���� �߸��� ����Ÿ
#define ERR_CHATROOM_NO_SUCH_CREATE_NUM					0x4331		// 2008-06-17 by dhjin, EP3 ä�ù� - ���� �� ��ȣ�� ����
#define ERR_CHATROOM_NO_SUCH							0x4332		// 2008-06-17 by dhjin, EP3 ä�ù� - ä�ù��� ����.
#define ERR_CHATROOM_ALREADY_USING						0x4333		// 2008-06-17 by dhjin, EP3 ä�ù� - �̹� ä�ù� �̿����̴�.
#define ERR_CHATROOM_PERMISSION_DENIED					0x4334		// 2008-06-17 by dhjin, EP3 ä�ù� - ������ ����.
#define ERR_CHATROOM_FULL_MEMBER						0x4335		// 2008-06-17 by dhjin, EP3 ä�ù� - ä�ù� �ο��� �����̴�.
#define ERR_CHATROOM_NO_SUCH_NEW_MASTER					0x4336		// 2008-06-17 by dhjin, EP3 ä�ù� - ���ο� ������ ã�� ���ߴ�.
#define ERR_NOT_MATCH_PW								0x4337		// 2008-07-15 by dhjin, EP3 ä�ù� - ��ȣ ����ġ.

//////////////////////////////////////////////////////////////////////////
// 2009-01-12 by dhjin, ���� ����
#define ERR_NO_SUCH_DECLARATION_MSWAR_INFO				0x4340		// 2009-01-12 by dhjin, ���� ���� - ���� ���� ���� ��ã��
#define ERR_NO_MORE_DECLARATION_MSWAR_SET				0x4341		// 2009-01-12 by dhjin, ���� ���� - ���� ���� �ð��� �� �̻� ���� �� �� ����.
#define ERR_INVALID_DECLARATION_MSWAR_TIME				0x4342		// 2009-01-12 by dhjin, ���� ���� - ���� ���� �ð� ������ �߸���.

#define ERR_CANNOT_CHOOSE_INFLUENCE_TYPE				0x4350		// 2009-03-31 by cmkwon, �����ʱ�ȭ �ý��� ���� - �ش� ������ ���� �� �� ����


///////////////////////////////////////////////////////////////////////////////
// 2007-01-05 by cmkwon, �ڵ� ������Ʈ ����
#define ERR_CANNOT_CONNECT_INTERNET						0x5000		// 2007-01-05 by cmkwon, ���ͳ� ���� �ȵ�
#define ERR_CANNOT_CONNECT_AUTO_UPDATE_SERVER			0x5001		// 2007-01-05 by cmkwon, �ڵ�������Ʈ ������ ���� �� �� ����
#define ERR_LOCAL_FILE_CREATE_FAIL						0x5002		// 2007-01-05 by cmkwon, �������� ���� ����
#define ERR_AUTO_UPDATE_SERVER_PERMISSION_DENIED		0x5003		// 2007-01-05 by cmkwon, �ڵ�������Ʈ ���� ���� ���� ����
#define ERR_UPDATE_FILE_NOT_FOUND						0x5004		// 2007-01-05 by cmkwon, ������Ʈ ������ ã�� �� ����
#define ERR_UPDATE_FILE_DOWNLOADING_FAIL				0x5005		// 2007-01-05 by cmkwon, ������Ʈ ���� �ٿ�ε� ����
#define ERR_UPDATE_FILE_DOWNLOADING_CANCEL				0x5006		// 2007-01-05 by cmkwon, ������Ʈ ���� �ٿ�ε� ���
#define ERR_FUNC_HttpOpenRequest						0x5007		// 2007-01-05 by cmkwon, HttpOpenRequest �Լ����� ������ ������
#define ERR_FUNC_HttpSendRequest						0x5008		// 2007-01-05 by cmkwon, HttpSendRequest �Լ����� ������ ������
#define ERR_FUNC_HttpQueryInfo							0x5009		// 2007-01-05 by cmkwon, HttpQueryInfo �Լ����� ������ ������
#define ERR_VERSIONINFO_FILE_NOT_FOUND					0x500A		// 2007-05-09 by cmkwon, 
#define ERR_VERSIONINFO_FILE_CAN_NOT_CREATE				0x500B		// 2007-05-09 by cmkwon, 
#define ERR_NOT_ALLOWED_IP								0x500C		// 2007-10-19 by cmkwon, AllowedIP �ý��� ���� - ���� �㰡�� IP�� �ƴϴ�

////////////////////////////////////////////////////////////////////////////////
// 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - 
#define ERR_DEBUFF_SKILL_APPLYING_SLIENCE				0x6000		// 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - ���Ϸ��� ������� �������̴�.
#define ERR_RELEASE_SKILL_NOT_FIND						0x6001		// 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - ������ ��ų�� ã������ ����.
#define ERR_DEBUFF_SKILL_APPLYING_NOT_HP_RECOVERY		0x6002		// 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - HPȸ�� ����
#define ERR_DEBUFF_SKILL_APPLYING_NOT_DP_RECOVERY		0x6003		// 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - DPȸ�� ����
#define ERR_DEBUFF_SKILL_APPLYING_NOT_SP_RECOVERY		0x6004		// 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - SPȸ�� ����
#define ERR_INFINITY_NO_SUCH_MODE_LIST					0x6005		// 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - ���Ǵ�Ƽ ����Ʈ�� ã�� ������ ���
#define ERR_INFINITY_NO_SUCH_READY_LIST					0x6006		// 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - ���Ǵ�Ƽ ��� ����Ʈ�� ã�� ������ ���
#define ERR_INFINITY_OVER_ENTRANCECOUNT					0x6007		// 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - ���Ǵ�Ƽ ���� ������ ���� �Ѱ��.
#define ERR_INFINITY_CREATE_FAIL						0x6008		// 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - ���Ǵ�Ƽ ���� ����
#define ERR_INFINITY_JOIN_FAIL_SOCKET					0x6009		// 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - ���Ǵ�Ƽ ���� ���� - ���� NULL��
#define ERR_INFINITY_MAX_ADMISSIONCNT					0x600A		// 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - ���Ǵ�Ƽ ���� ���� - �ִ� �ο�
#define ERR_INFINITY_MISMATCH_LEVEL						0x600B		// 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - ���Ǵ�Ƽ - ���� ����
#define ERR_INFINITY_JOIN_FAIL_ENTRANCECOUNT			0x600C		// 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - ���Ǵ�Ƽ ���� ���� - ���� �� ����
#define ERR_INFINITY_MODE								0x600D		// 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - �߸��� ���
#define ERR_INFINITY_CREATEUID							0x600E		// 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - �߸��� ���� ��ȣ
#define ERR_INFINITY_NO_SUCH_MASTER_USER				0x600F		// 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - ���Ǵ�Ƽ ���� ���� - ���� ������
#define ERR_INFINITY_JOIN_FAIL_MASTERUSER_REJECT		0x6010		// 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - ���Ǵ�Ƽ ���� ���� - ���� ��ȣ
#define ERR_INFINITY_NO_SUCH_MEMBER_LIST				0x6011		// 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - ���Ǵ�Ƽ ���� ����Ʈ�� ã�� ������ ���
#define ERR_INFINITY_STATE								0x6012		// 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - ���Ǵ�Ƽ �߸��� ���°�
#define ERR_INFINITY_SAME_MASTER						0x6013		// 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - ���� �ι�!
#define ERR_INFINITY_MASTER								0x6014		// 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - �����Ͱ� �ƴϴ�.
#define ERR_INFINITY_CREATE_MAPCHANNEL					0x6015		// 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - �� ���� �� ä�� ���� ����
#define ERR_INFINITY_NOT_ALL_READY						0x6016		// 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - ��� ������ ���� ���°� �ƴϴ�.
#define ERR_INFINITY_CANNOT_USE_ITEM					0x6017		// 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - ���Ǵ�Ƽ���� ��� �Ұ�
#define ERR_INFINITY_MIN_ADMISSIONCNT					0x6018		// 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - ���� �̿� �ּ� �ο� ����
#define ERR_INFINITY_TENDER_PROCESSING					0x6019		// 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - Tender���̴�.
#define ERR_INFINITY_NOT_PROCESSING_TENDERITEM			0x601A		// 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - Tender�������� �������� �ƴϴ�.
#define ERR_INFINITY_ONLY_USE_ITEM						0x601B		// 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - ���Ǵ�Ƽ������ ��� ����
#define ERR_INFINITY_CANNOT_SUCH_TEAM					0x601C		// 2009-09-09 ~ 2010 by dhjin, ���Ǵ�Ƽ - �ñ� ���� ������ ó��, �����ϴ� ���� ����.
#define ERR_INFINITY_NULL_VALUE							0x601D		// 2009-09-09 ~ 2010-01 by dhjin, ���Ǵ�Ƽ - �ҽ� üũ, NULL�� ����
#define ERR_INFINITY_CANNOT_ALL_START					0x601E		// 2010-04-06 by cmkwon, ����2�� �߰� ���� - 
#define ERR_INFINITY_TENDER_ALREADY_CHOICED				0x601F		// 2010-04-09 by cmkwon, ����2�� �߰� ����(�ܰ躰 ���� �߰�) - �̹� ������ ����
#define ERR_INFINITY_DIFFICLUTY_NOT_FIND				0x6020		// // 2010-05-04 by shcho, ���Ǵ�Ƽ ���̵� ���� - ���̵��� ã�� ������ ��
#define ERR_INFINITY_DIFFICULTY_LEVEL_SAME				0x6021		// 2010. 05. 19 by hsLee ���Ǵ�Ƽ �ʵ� 2�� ���̵� ����. (��ȣó�� + ���� ó��(����) ) - ���� ���̵��� ���� ��û ����.
#define ERR_INFINITY_DIFFICULTY_LEVEL_INVALID			0x6022		// 2010. 05. 19 by hsLee ���Ǵ�Ƽ �ʵ� 2�� ���̵� ����. (��ȣó�� + ���� ó��(����) ) - ��ȿ���� ���� ���̵� ���氪 ��û ����.

#define ERR_INFINITY_MISMATCH_CREATEUID					0x6023		// ���Ǵ�Ƽ - �� ������ȣ ����ġ.	// 2010. 07. 27 by hsLee ���Ǵ�Ƽ 2�� ���� ��� �ó׸� ���� ��ŵ ó��.
#define ERR_INFINITY_PLAYING_STATE						0x6024		// ���Ǵ�Ƽ - ���� ���� ���� �ƴ� ���. ( STATE - PLAYING ~ ���� ) // 2010. 07. 27 by hsLee ���Ǵ�Ƽ 2�� ���� ��� �ó׸� ���� ��ŵ ó��.
#define ERR_INFINITY_ALWAYS_SKIP_ENDINGCINEMA			0x6025		// ���Ǵ�Ƽ - �̹� ���� ��ŵ Ȱ��ȭ �Ǿ� ����. // 2010. 07. 27 by hsLee ���Ǵ�Ƽ 2�� ���� ��� �ó׸� ���� ��ŵ ó��.

#define ERR_KNOWN_ERROR									0x6100		// 2010-04-26 by cmkwon, ���þ� Innva ����/���� �ý��� ���� - 
#define ERR_INVALID_HANDLE								0x6101		// 2010-04-26 by cmkwon, ���þ� Innva ����/���� �ý��� ���� - 

///////////////////////////////////////////////////////////////////////////////
// 2011-01-26 by hskim, ���� ���� ����
#define ERR_PROTOCOL_INVALID_AUTHENTICATION_SERVER_LOGIN_DATA					0x7001		// PreServer �� ���� ���� Data Size�� Authentication Packet Type�� ���� Data Size���� ����
#define ERR_PROTOCOL_INVALID_AUTHENTICATION_SERVER_LOGIN_DB						0x7002		// PreServer �� ���� ��������Ÿ�� ����� ���������� �������� �߰��� ���������� ó������ �ʾҴ�

///////////////////////////////////////////////////////////////////////////////
// ���� ����
#define ERR_SECURITY_NOT_CHECK_VERSION					0xE000		// 
#define ERR_SECURITY_HACKING_GUID						0xE001		// 
#define ERR_SECURITY_HACKING_CRC						0xE002		// 
#define ERR_SECURITY_HACKING_CLIENT						0xE003		// 
#define ERR_SECURITY_ANTICPX_INVALID_HANDLE				0xE004		// 2008-04-03 by cmkwon, �ٽ��� ���� ���� �ý��� ���� - 
#define ERR_SECURITY_CREATE_CLIENT_FAIL					0xE005		// 2008-04-03 by cmkwon, �ٽ��� ���� ���� �ý��� ���� - 

#define ERR_AHNHS_ENGINE_DETECT_GAME_HACK				0xE100
#define ERR_AHNHS_ACTAPC_DETECT_AUTOMOUSE				0xE101
#define ERR_AHNHS_ACTAPC_DETECT_ALREADYHOOKED			0xE102
#define ERR_AHNHS_ACTAPC_DETECT_SPEEDHACK				0xE103
#define ERR_AHNHS_ACTAPC_DETECT_SPEEDHACK_APP			0xE104
#define ERR_AHNHS_ACTAPC_DETECT_KDTRACE					0xE105
#define ERR_AHNHS_ACTAPC_DETECT_KDTRACE_CHANGED			0xE106
#define ERR_AHNHS_ACTAPC_DETECT_DRIVERFAILED			0xE107
#define ERR_AHNHS_ACTAPC_DETECT_HOOKFUNCTION			0xE108
#define ERR_AHNHS_ACTAPC_DETECT_MESSAGEHOOK				0xE109
#define ERR_AHNHS_ACTAPC_DETECT_MODULE_CHANGE			0xE10A
#define ERR_AHNHS_ACTAPC_DETECT_ABNORMAL_MEMORY_ACCESS	0xE10B		// 2007-04-09 by cmkwon
#define ERR_AHNHS_ACTAPC_DETECT_ENGINEFAILED			0xE10C		// 2008-03-24 by cmkwon, �ٽ��� 2.0 ���� - AHNHS_ACTAPC_DETECT_ENGINEFAILED �߰���
#define ERR_AHNHS_ACTAPC_DETECT_AUTOMACRO					0xE10D		// 2009-07-17 by cmkwon, �ٽ��� ��ü ���� ó�� ����Ÿ���߰�(Ŭ���̾�Ʈ�� ���) - 
#define ERR_AHNHS_ACTAPC_DETECT_CODEMISMATCH				0xE10E		// 2009-07-17 by cmkwon, �ٽ��� ��ü ���� ó�� ����Ÿ���߰�(Ŭ���̾�Ʈ�� ���) - 
#define ERR_AHNHS_ACTAPC_DETECT_ABNORMAL_HACKSHIELD_STATUS	0xE10F		// 2009-07-17 by cmkwon, �ٽ��� ��ü ���� ó�� ����Ÿ���߰�(Ŭ���̾�Ʈ�� ���) - 
#define ERR_AHNHS_ACTAPC_DETECT_LMP_FAILED					0xE110		// 2009-07-17 by cmkwon, �ٽ��� ��ü ���� ó�� ����Ÿ���߰�(Ŭ���̾�Ʈ�� ���) - 





///////////////////////////////////////////////////////////////////////////////
// ����ȭ ������ ����
#define ERR_CASH_PREMIUM_CARD_INVALID_ITEMNUM			0xF000		// �����̾�(�Ϲ�, ����, ���׷��̵�) ī�� ItemNum�� �ƴϴ�
#define ERR_CASH_PREMIUM_CARD_ALREADY_USING				0xF001		// �����̾�(�Ϲ�, ����, ���׷��̵�) ī�尡 �̹� �ٸ� ó������
#define ERR_CASH_PREMIUM_CARD_NOT_MATCHED				0xF002		// �����̾�(�Ϲ�, ����, ���׷��̵�) ī�尡 �ٸ� ������
#define ERR_CASH_PREMIUM_CARD_NOT_YET_BUY_STATE			0xF003		// �����̾�(�Ϲ�, ����, ���׷��̵�) ī�尡 �����Ҽ� �ִ� ���°� �ƴϴ�

// start 2011-11-03 by shcho, yedang �˴ٿ��� ����
///////////////////////////////////////////////////////////////////////////////
// ���� �˴ٿ��� 
#define ERR_SHUTDOWNMINORS_USER							0xF004		// 16�� �̸��� ���������� ��ó���� 1���� ���´�.
// end 2011-11-03 by shcho, yedang �˴ٿ��� ����

///////////////////////////////////////////////////////////////////////////////
// String Conversion Functions


#endif // _ATUM_ERROR_H_