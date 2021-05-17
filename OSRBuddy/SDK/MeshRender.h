// MeshRender.h: interface for the CMeshRender class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MESHRENDER_H__28791450_5BD7_4A28_9A2B_736B3B0E6ED0__INCLUDED_)
#define AFX_MESHRENDER_H__28791450_5BD7_4A28_9A2B_736B3B0E6ED0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "AtumNode.h"
#include "SkinnedMesh.h"

class CMeshRender : public CAtumNode
{
public:
	CMeshRender();
	virtual ~CMeshRender();
	// 2009. 11. 23 by jskim ���ҽ� �ε� ���� ����
	//virtual CSkinnedMesh*	InitData(int nMeshIndex);
	virtual CSkinnedMesh* InitData(int nMeshIndex, int nType);
	//end 2009. 11. 23 by jskim ���ҽ� �ε� ���� ����
	virtual void			DeleteData(int nMeshIndex);
	virtual void			RenderShadow(CAtumNode* pNode);
	virtual void			Render();
	virtual void			Tick(float fElapsedTime);
	virtual HRESULT			InitDeviceObjects();
	virtual HRESULT			RestoreDeviceObjects();
	virtual HRESULT			InvalidateDeviceObjects();
	virtual HRESULT			DeleteDeviceObjects();


	map<int, CSkinnedMesh*>		m_mapSkinnedMesh;		// index  : 12030100 ( 12 : degree, 03 : amor, 01 : unitKind )

protected:
	vector<int>					m_vecLoadMeshIndex;		// render�߿� �ε��� ���� ���� ��� ���⿡ �ְ� Tick���� �ε��Ѵ�.
//	DWORD						m_dwNormalStateBlock;
//	DWORD						m_dwAlphaBlendStateBlock;

};


#endif // !defined(AFX_MESHRENDER_H__28791450_5BD7_4A28_9A2B_736B3B0E6ED0__INCLUDED_)
