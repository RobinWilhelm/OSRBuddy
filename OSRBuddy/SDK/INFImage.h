// INFImage.h: interface for the CINFImage class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_INFIMAGE_H__7B409C14_93C0_4282_B7B5_8367FF326F11__INCLUDED_)
#define AFX_INFIMAGE_H__7B409C14_93C0_4282_B7B5_8367FF326F11__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "AtumNode.h"

class CINFImage : public CAtumNode
{

public:
	CINFImage();
	virtual ~CINFImage();

	virtual HRESULT InitDeviceObjects(char* pData, int nSize);
	virtual HRESULT InitDeviceObjectsEx();										// 2005-09-29 by ispark
	virtual HRESULT RestoreDeviceObjects();
	virtual HRESULT RestoreDeviceObjectsEx(int nImageSizeX, int nImageSizeY);	// 2005-09-29 by ispark
	virtual HRESULT DeleteDeviceObjects();
	virtual HRESULT InvalidateDeviceObjects();
	virtual void Render();

	LPDIRECT3DTEXTURE9	m_pTexture;
	LPD3DXSPRITE		m_pd3dxSprite;
	D3DXVECTOR2			m_v2Scaling, m_v2Rcenter, m_v2Trans;
	RECT* m_pRect;
	BOOL				m_bSpriteCrate;
	float				m_fAngle;
	char* m_pData;
	int					m_nDataSize;
	D3DCOLOR			m_dwColor;
	POINT				m_poImgSize;
};

#endif // !defined(AFX_INFIMAGE_H__7B409C14_93C0_4282_B7B5_8367FF326F11__INCLUDED_)
