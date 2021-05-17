// ObjRender.h: interface for the CObjRender class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_OBJRENDER_H__7E16B046_BEDE_45DA_A99E_D42C15F7EFDF__INCLUDED_)
#define AFX_OBJRENDER_H__7E16B046_BEDE_45DA_A99E_D42C15F7EFDF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MeshRender.h"

class CObjectChild;
class CUnitData;
class CSkinnedMesh;
class CObjRender : public CMeshRender
{
public:
	CObjRender();
	virtual ~CObjRender();

	virtual void	RenderShadow(CAtumNode* pNode);
	virtual void	Render(CObjectChild* pObj);
	virtual void	Tick(float fElapsedTime);	// ¾È¾¸.

	virtual HRESULT InitDeviceObjects();
	virtual HRESULT RestoreDeviceObjects();
	virtual HRESULT InvalidateDeviceObjects();
	virtual HRESULT DeleteDeviceObjects();
};

#endif // !defined(AFX_OBJRENDER_H__7E16B046_BEDE_45DA_A99E_D42C15F7EFDF__INCLUDED_)
