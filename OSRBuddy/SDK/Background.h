// Background.h: interface for the CBackground class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BACKGROUND_H__7699F556_5513_4782_B433_E68C5F32BBC0__INCLUDED_)
#define AFX_BACKGROUND_H__7699F556_5513_4782_B433_E68C5F32BBC0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "AtumNode.h"

class CGameData;
class CINFImage;
class CQuadGround;
class CSkinnedMesh;
class DataHeader;

class CBackground : public CAtumNode
{
public:
	CBackground(PROJECTINFO info);//,int n);
	virtual ~CBackground();
	virtual HRESULT InitDeviceObjects();
	virtual HRESULT RestoreDeviceObjects();
	virtual HRESULT InvalidateDeviceObjects();
	virtual HRESULT DeleteDeviceObjects();
	virtual void Render();
	virtual void Tick(float fElapsedTime);

public:
	D3DLIGHT9					m_lightSupport[4];				// ���� ���� ����Ʈ
	D3DMATERIAL9				m_mtrl;
	D3DXMATRIX					m_mat;
	TILEINFOCLIENT* m_pTileInfo;				// �������� �����ϴ� Ÿ�Ϲ�ȣ, N x M �� 
	BOOL* m_bTileRender;
	VERTEXINFO* m_pTileVertexArray;
	//	LPDIRECT3DVERTEXBUFFER8	*	m_pVBRender;				//[m_projectInfo.m_sYSize];
	INT							m_nCreateTexNumber;
	int							m_nObjectNumber;
	FLOAT						m_fCheckWaterTime;
	MapInfo						m_info;
	MAP_INFO* m_pMapInfo;

	PROJECTINFO					m_projectInfo;
	CGameData* m_pBackgroundData;						// ����Ÿ���� (������)
	CGameData* m_pTextureData;				// Texture ( 512x512, 16��)
	D3DXMATRIX					m_mMatrix;

	BOOL						m_bBazaar;					// 2006-07-21 by ispark, ���������
	////////////////////////////////////////////////////////
	CAtumNode** m_ppObjectList;
	CAtumNode* m_pBigObject;				// ū ������Ʈ ����Ÿ
	CAtumNode* m_pWaterObject;				// �� ������Ʈ 
	CAtumNode* m_pObjectEvent;				// �̺�Ʈ ������Ʈ ����Ÿ
	CAtumNode* m_pObjectMonster;			// ������Ʈ ���� ����Ÿ

//	CINFImage	*				m_pMinimap;
//	CSkinnedMesh*				m_pMeshMinimap;				// 2005-09-12 by ispark ���� ó��
	/////////////// Water Render //////////////////////
	LPDIRECT3DTEXTURE9			m_pWaterTexture[WATER_TEXTURE_COUNT];			// Water Texture
	LPDIRECT3DVERTEXBUFFER9* m_pVBWater;
	WATERINFO* m_bWaterRender;
	FLOAT						m_fCheckWaterTexAniTime;
	BYTE						m_bWaterTexCont;

	CQuadGround* m_pQuad;						// ���� Ʈ��

	map<INT, EFFECTINFOCLIENT*>			m_mapEffectList;		// ���� �� �ε��� * (00~99) <- ����Ʈ ��(��������)
	vector<MONSTERINFO*>				m_vecMonsterResList;	// ���� �� �ε��� * (00~99) <- ����Ʈ ��(��������)


	///////////////////////////////////////////////////////////////////////////////
	// 2004-06-04, cmkwon, Object Render�� ����

	float						m_fSizeMap_X;				// ���� X�� Size�� ������ ����������
	float						m_fSizeMap_Z;				// ���� Z�� Size�� ������ ����������
	int							m_NUM_BLOCK_X;
	int							m_NUM_BLOCK_Z;

	//////////////////////////////////////////////////////////////////////////
	// 2005-09-06 by ispark �̴ϸ�
	BOOL						m_bMiniMap;
	CINFImage* m_pMiniBigMapImage;
	CINFImage* m_pMiniBigMapCityImage;			// 2006-04-08 by ispark, ���� ���� �̹���
	DataHeader* m_pMiniMapDataHeader;
	DataHeader* m_pMiniMapCityDataHeader;

	int							m_nMapNumber;					// �ʹ�ȣ

	//////////////////////////////////////////////////////////////////////////
	LPDIRECT3DTEXTURE9			m_pDetailMap;					// ������


	// 2008. 12. 11 by ckPark ��������
	LPDIRECT3DVERTEXBUFFER9		m_pToRenderWaterVB;				// ���������� ���ļ� �׸� �� ���ؽ� ����
	// end 2008. 12. 11 by ckPark ��������
};

#endif // !defined(AFX_BACKGROUND_H__7699F556_5513_4782_B433_E68C5F32BBC0__INCLUDED_)
