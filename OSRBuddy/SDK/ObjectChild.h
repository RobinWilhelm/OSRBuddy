// ObjectChild.h: interface for the CObjectChild class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_OBJECTCHILD_H__66461ECB_74A2_47DA_BD3A_578ED7698888__INCLUDED_)
#define AFX_OBJECTCHILD_H__66461ECB_74A2_47DA_BD3A_578ED7698888__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "AtumNode.h"

class CSkinnedMesh;
class CCharacterInfo;
class CObjRender;
class CChatMoveData;
class CObjectChild : public CAtumNode
{
public:
	CObjectChild(OBJECTINFOCLIENT objInfo);
	virtual ~CObjectChild();
	virtual void Render();//int min_x,int max_x,int min_z,int max_z);
	virtual void ObjectNameRender();
	virtual void Tick();

	//	float GetObjectSize(int type);

	//	FLOAT			m_fMaxTime;

	//	FLOAT			m_fShadowSizeWidth;		// �׸��� ���� ũ��
	//	FLOAT			m_fShadowSizeHeight;	// �׸��� ���� ũ��
	D3DXVECTOR3			m_vPos;					// ������ ���� ��ǥ
	D3DXVECTOR3			m_vUp;
	D3DXVECTOR3			m_vVel;
	FLOAT				m_fCurrentTime;
	D3DXMATRIX			m_mMatrix;
	INT					m_nObjScreenX;			// ��ũ���� X ��ǥ
	INT					m_nObjScreenY;			// ��ũ���� Y ��ǥ
	INT					m_nObjScreenW;			// ��ũ���� W ��ǥ
	BOOL				m_bCheckBlend;
	//D3DXVECTOR3			m_vShadowPos1;			// �׸��� ��ġ (�պκ� ����)
	//D3DXVECTOR3			m_vShadowPos2;			// �׸��� ��ġ (�պκ� ������)
	//D3DXVECTOR3			m_vShadowPos3;			// �׸��� ��ġ (�޺κ� ������)
	//D3DXVECTOR3			m_vShadowPos4;			// �׸��� ��ġ (�޺κ� ����)
	FLOAT				m_fDistanceCamera;		// ī�޶�κ����� �Ÿ�
	D3DXVECTOR3		m_vOriPos;
	INT				m_nCode;
	BOOL			m_bCheckAttack;
	BOOL			m_bCheckColl;
	BOOL			m_bCheckAni;
	MAPOBJECTINFO* m_pObjectInfo;
	CObjRender* m_pRenderer;
	INT				m_nObjectCont;			// Ŭ���̾�Ʈ���� ������ ������Ʈ �ε���
	BOOL			m_bCheckRenderDist;
	POINT			m_ptBlockPos;

	DWORD			m_dwObjectMonsterUniqueNumber;		// Object Monster �� ������ ���� ����ũ�ѹ�
	BYTE			m_bObjectTexIndex;
	UINT			m_nNextEventIndex;		// �̺�Ʈ�� �����ϱ� ���� �˻��ϴ� �����ε���
//	BYTE			m_bBodyCondition;
	BOOL			m_bIsEvent;
	BYTE			m_bEventType;
	short			m_sEventIndexFrom;		// �̺�Ʈ ������Ʈ�� ���� �ε���
	short			m_sEventIndexTo;
	short			m_sEventIndex3;
	char			m_strEventParam[40];
	CChatMoveData* m_pMoveChat;
	BOOL			m_bEnableObjectMonsterObject;		// ���� ������Ʈ ���Ͷ��, ������Ʈ ���� ������Ʈ�� Ȱ��ȭ ����

	BodyCond_t		m_BodyCondition;					// ����, bit flag ���
	CCharacterInfo* m_pCharacterInfo;
	void LoadCharacterEffect(char* strFileName);
	//	LPDIRECT3DVERTEXBUFFER8 m_pVBShadow;			// Shadow VB
	CSkinnedMesh* m_pObjMesh;
};

#endif // !defined(AFX_OBJECTCHILD_H__66461ECB_74A2_47DA_BD3A_578ED7698888__INCLUDED_)
