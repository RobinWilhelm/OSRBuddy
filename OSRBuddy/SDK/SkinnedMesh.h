// SkinnedMesh.h: interface for the CSkinnedMesh class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SKINNEDMESH_H__75E6AD0E_1348_45B4_8A86_614B206812B1__INCLUDED_)
#define AFX_SKINNEDMESH_H__75E6AD0E_1348_45B4_8A86_614B206812B1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "AtumNode.h"
//#include "GameDataLast.h"

// 2009. 11. 23 by jskim 리소스 로딩 구조 변경
#include "AtumApplication.h"
//end 2009. 11. 23 by jskim 리소스 로딩 구조 변경

#define GXRELEASE(_p) do { if ((_p) != NULL) {(_p)->Release(); (_p) = NULL;} } while (0)

enum METHOD {
    D3DNONINDEXED,
    D3DINDEXED,
    SOFTWARE,
    D3DINDEXEDVS,
    NONE
};

#define OBJECT_ENCODESTRING "dlwlsgk"
#define MAX_DECAL_NUM		5				// 데칼을 적용할수 있는 최대수

struct SMeshContainer
{




    ID3DXMesh* pMesh;	//    D3DXMESHDATA            MeshData;
//	LPD3DXMESH pMeshes[5];

    D3DMATERIAL9* rgMaterials; //pMaterials
    LPDIRECT3DTEXTURE9* pTextures;	//ppTextures
    DWORD cpattr;
    DWORD cMaterials;	//     DWORD                   NumMaterials;
    DWORD iAttrSplit;		//iAttributeSW

    SMeshContainer* pmcNext;
    float fRadius; //세부 메시 반지름	// 2004-10-29 by jschoi
    D3DXVECTOR3 vCenter;	// 중심좌표

    char* szName;	//NAME

    // Skin info
    // 2005-01-03 by jschoi
//    LPD3DXSKINMESH m_pSkinMesh;
    LPD3DXMESH m_pSkinMesh;
    LPD3DXSKININFO m_pSkinMeshInfo;		// pSkinInfo

    D3DXATTRIBUTERANGE* m_pAttrTable;	// pAttributeTable
    D3DXMATRIX** m_pBoneMatrix;			//ppBoneMatrixPtrs
    LPD3DXBUFFER m_pBoneNamesBuf;
    LPD3DXBUFFER m_pBoneOffsetBuf;
    D3DXMATRIX* m_pBoneOffsetMat;		//pBoneOffsetMatrices
    DWORD* m_rgiAdjacency;			//	*pAdjacency
    DWORD m_numBoneComb;
    DWORD m_maxFaceInfl;
    LPD3DXBUFFER m_pBoneCombinationBuf; // pBoneCombinationBuf
    METHOD  m_Method;				// NumInfl
    DWORD m_paletteSize;			// NumPaletteEntries
    BOOL m_bUseSW;					// UseSoftwareVP
    // 2005-01-04 by jschoi
    // SkinMesh info     
//	LPD3DXMESH           m_pOrigMesh;

    SMeshContainer()
        :pMesh(NULL),
        rgMaterials(NULL),
        pTextures(NULL),
        cpattr(0),
        iAttrSplit(0),
        cMaterials(0),
        pmcNext(NULL),
        szName(NULL),
        m_pSkinMesh(NULL),
        m_pSkinMeshInfo(NULL),
        m_pAttrTable(NULL),
        m_pBoneMatrix(NULL),
        m_pBoneNamesBuf(NULL),
        m_pBoneOffsetBuf(NULL),
        m_pBoneOffsetMat(NULL),
        m_rgiAdjacency(NULL),
        m_numBoneComb(0),
        m_maxFaceInfl(0),
        m_pBoneCombinationBuf(NULL),
        m_Method(NONE),
        m_paletteSize(0),
        m_bUseSW(FALSE),
        fRadius(0),
        vCenter(0, 0, 0)
    {
    }

    ~SMeshContainer()
    {
        delete[]rgMaterials;
        rgMaterials = NULL;

        if (pTextures)
        {
            for (DWORD i = 0; i < cMaterials; ++i)
            {
                GXRELEASE(pTextures[i]);
            }
            delete[]pTextures;//by dhkwon
            pTextures = NULL;
        }

        // 2005-02-04 by jschoi - 메모리 누수 
        GXRELEASE(m_pSkinMeshInfo);
        delete[] m_pBoneOffsetMat;
        m_pBoneOffsetMat = NULL;

        GXRELEASE(pMesh);
        //		if(pMeshes)
        //		{
        //			for(DWORD i=0;i<5;i++)
        //				GXRELEASE(pMeshes[i]);
        //		}
        GXRELEASE(m_pSkinMesh);
        GXRELEASE(m_pBoneNamesBuf);
        GXRELEASE(m_pBoneOffsetBuf);
        GXRELEASE(m_pBoneCombinationBuf);

        delete[] m_pBoneMatrix;
        m_pBoneMatrix = NULL;

        delete[] m_pAttrTable;
        m_pAttrTable = NULL;

        delete[] szName;
        szName = NULL;

        delete[] m_rgiAdjacency;
        m_rgiAdjacency = NULL;

        delete pmcNext;
        pmcNext = NULL;
    }
};

// X File formation rotate key
struct SRotateKeyXFile
{
    DWORD			dwTime;
    DWORD			dwFloats;
    float			w;
    float			x;
    float			y;
    float			z;
};

struct SScaleKeyXFile
{
    DWORD	dwTime;
    DWORD	dwFloats;
    D3DXVECTOR3	vScale;
};


struct SPositionKeyXFile
{
    DWORD	dwTime;
    DWORD	dwFloats;
    D3DXVECTOR3	vPos;
};

struct SMatrixKeyXFile
{
    DWORD	dwTime;
    DWORD	dwFloats;
    D3DXMATRIX	mat;
};

// in memory versions

struct SRotateKey
{
    DWORD			dwTime;
    D3DXQUATERNION	quatRotate;
};

struct SPositionKey
{
    DWORD	dwTime;
    D3DXVECTOR3	vPos;
};

struct SScaleKey
{
    DWORD	dwTime;
    D3DXVECTOR3	vScale;
};

struct SMatrixKey
{
    DWORD	dwTime;
    D3DXMATRIXA16	mat;
};

struct SFrame
{

    //	D3DXVECTOR3 m_vCurrentPos;
    SMeshContainer* pmcMesh;
    D3DXMATRIXA16 matRot;
    D3DXMATRIXA16 matTrans;
    D3DXMATRIXA16 matRotOrig;
    D3DXMATRIXA16 matCombined;
                   
 

    // animation information
    SPositionKey* m_pPositionKeys;
    UINT m_cPositionKeys;
    SRotateKey* m_pRotateKeys;
    UINT m_cRotateKeys;
    SScaleKey* m_pScaleKeys;
    UINT m_cScaleKeys;

    SMatrixKey* m_pMatrixKeys;
    char pad[8];
    UINT m_cMatrixKeys;

   

    SFrame* pframeAnimNext;
    SFrame* pframeToAnimate;

    SFrame* pframeSibling;
    SFrame* pframeFirstChild;

    bool bAnimationFrame;
    char* szName;

    SFrame()
        :
        pmcMesh(NULL),
        m_pPositionKeys(NULL),
        m_cPositionKeys(0),
        m_pScaleKeys(NULL),
        m_cScaleKeys(0),
        m_pRotateKeys(NULL),
        m_cRotateKeys(0),
        m_pMatrixKeys(NULL),
        m_cMatrixKeys(0),
        pframeAnimNext(NULL),
        pframeToAnimate(NULL),
        pframeSibling(NULL),
        pframeFirstChild(NULL),
        bAnimationFrame(false),
        szName(NULL)
        //			m_vCurrentPos(0,0,0)
    {
        D3DXMatrixIdentity(&matRot);
        D3DXMatrixIdentity(&matRotOrig);
        D3DXMatrixIdentity(&matTrans);
    }

    ~SFrame()
    {
        delete[]szName;
        szName = NULL;
        delete pmcMesh;
        pmcMesh = NULL;
        delete pframeFirstChild;
        pframeFirstChild = NULL;
        delete pframeSibling;
        pframeSibling = NULL;

        delete[]m_pPositionKeys;
        m_pPositionKeys = NULL;
        delete[]m_pRotateKeys;
        m_pRotateKeys = NULL;
        delete[]m_pScaleKeys;
        m_pScaleKeys = NULL;
        delete[]m_pMatrixKeys;
        m_pMatrixKeys = NULL;

        // do NOT delete pframeAnimNext
        // do NOT delete pframeToAnimate
    }

    void SetTime(float fGlobalTime)
    {
        UINT iKey;
        UINT dwp2;
        UINT dwp3;
        D3DXMATRIXA16 matResult;
        D3DXMATRIXA16 matTemp;
        float fTime1;
        float fTime2;
        float fLerpValue;
        D3DXVECTOR3 vScale;
        D3DXVECTOR3 vPos;
        D3DXQUATERNION quat;
        BOOL bAnimate = false;
        float fTime;

        if (m_pMatrixKeys)
        {
            fTime = (float)fmod(fGlobalTime, m_pMatrixKeys[m_cMatrixKeys - 1].dwTime);

            for (iKey = 0; iKey < m_cMatrixKeys; iKey++)
            {
                if ((float)m_pMatrixKeys[iKey].dwTime > fTime)
                {
                    dwp3 = iKey;

                    if (iKey > 0)
                    {
                        dwp2 = iKey - 1;
                    }
                    else  // when iKey == 0, then dwp2 == 0
                    {
                        dwp2 = iKey;
                    }

                    break;
                }
            }
            fTime1 = (float)m_pMatrixKeys[dwp2].dwTime;
            fTime2 = (float)m_pMatrixKeys[dwp3].dwTime;

            if ((fTime2 - fTime1) == 0)
                fLerpValue = 0;
            else
                fLerpValue = (fTime - fTime1) / (fTime2 - fTime1);

            if (fLerpValue > 0.5)
            {
                iKey = dwp3;
            }
            else
            {
                iKey = dwp2;
            }

            pframeToAnimate->matRot = m_pMatrixKeys[iKey].mat;
        }
        else
        {
            D3DXMatrixIdentity(&matResult);

            if (m_pScaleKeys)
            {
                dwp2 = dwp3 = 0;

                fTime = (float)fmod(fGlobalTime, m_pScaleKeys[m_cScaleKeys - 1].dwTime);

                for (iKey = 0; iKey < m_cScaleKeys; iKey++)
                {
                    if ((float)m_pScaleKeys[iKey].dwTime > fTime)
                    {
                        dwp3 = iKey;

                        if (iKey > 0)
                        {
                            dwp2 = iKey - 1;
                        }
                        else  // when iKey == 0, then dwp2 == 0
                        {
                            dwp2 = iKey;
                        }

                        break;
                    }
                }
                fTime1 = (float)m_pScaleKeys[dwp2].dwTime;
                fTime2 = (float)m_pScaleKeys[dwp3].dwTime;

                if ((fTime2 - fTime1) == 0)
                    fLerpValue = 0;
                else
                    fLerpValue = (fTime - fTime1) / (fTime2 - fTime1);

                D3DXVec3Lerp(&vScale,
                    &m_pScaleKeys[dwp2].vScale,
                    &m_pScaleKeys[dwp3].vScale,
                    fLerpValue);


                D3DXMatrixScaling(&matTemp, vScale.x, vScale.y, vScale.z);

                D3DXMatrixMultiply(&matResult, &matResult, &matTemp);

                bAnimate = true;
            }

            //check rot keys
            if (m_pRotateKeys)
            {
                int i1 = 0;
                int i2 = 0;

                fTime = (float)fmod(fGlobalTime, m_pRotateKeys[m_cRotateKeys - 1].dwTime);

                for (iKey = 0; iKey < m_cRotateKeys; iKey++)
                {
                    if ((float)m_pRotateKeys[iKey].dwTime > fTime)
                    {
                        i1 = (iKey > 0) ? iKey - 1 : 0;
                        i2 = iKey;
                        break;
                    }
                }

                fTime1 = (float)m_pRotateKeys[i1].dwTime;
                fTime2 = (float)m_pRotateKeys[i2].dwTime;

                if ((fTime2 - fTime1) == 0)
                    fLerpValue = 0;
                else
                    fLerpValue = (fTime - fTime1) / (fTime2 - fTime1);
                D3DXQuaternionSlerp(&quat, &m_pRotateKeys[i1].quatRotate, &m_pRotateKeys[i2].quatRotate, fLerpValue);

                quat.w = -quat.w;
                D3DXMatrixRotationQuaternion(&matTemp, &quat);
                D3DXMatrixMultiply(&matResult, &matResult, &matTemp);

                bAnimate = true;
            }

            if (m_pPositionKeys)
            {
                dwp2 = dwp3 = 0;

                fTime = (float)fmod(fGlobalTime, m_pPositionKeys[m_cPositionKeys - 1].dwTime);

                for (iKey = 0; iKey < m_cPositionKeys; iKey++)
                {
                    if ((float)m_pPositionKeys[iKey].dwTime > fTime)
                    {
                        dwp3 = iKey;

                        if (iKey > 0)
                        {
                            dwp2 = iKey - 1;
                        }
                        else  // when iKey == 0, then dwp2 == 0
                        {
                            dwp2 = iKey;
                        }

                        break;
                    }
                }
                fTime1 = (float)m_pPositionKeys[dwp2].dwTime;
                fTime2 = (float)m_pPositionKeys[dwp3].dwTime;

                if ((fTime2 - fTime1) == 0)
                    fLerpValue = 0;
                else
                    fLerpValue = (fTime - fTime1) / (fTime2 - fTime1);


                D3DXVec3Lerp((D3DXVECTOR3*)&vPos,
                    &m_pPositionKeys[dwp2].vPos,
                    &m_pPositionKeys[dwp3].vPos,
                    fLerpValue);

                //			m_vCurrentPos = vPos;
                D3DXMatrixTranslation(&matTemp, vPos.x, vPos.y, vPos.z);

                D3DXMatrixMultiply(&matResult, &matResult, &matTemp);
                bAnimate = true;
            }
            else
            {
                D3DXMatrixTranslation(&matTemp, pframeToAnimate->matRotOrig._41, pframeToAnimate->matRotOrig._42, pframeToAnimate->matRotOrig._43);

                D3DXMatrixMultiply(&matResult, &matResult, &matTemp);
            }

            if (bAnimate)
            {
                pframeToAnimate->matRot = matResult;
            }
        }
    }

    SFrame* FindFrame(char* szFrame)
    {
        SFrame* pframe;

        if ((szName != NULL) && (strcmp(szName, szFrame) == 0))
            return this;

        if (pframeFirstChild != NULL)
        {
            pframe = pframeFirstChild->FindFrame(szFrame);
            if (pframe != NULL)
                return pframe;
        }

        if (pframeSibling != NULL)
        {
            pframe = pframeSibling->FindFrame(szFrame);
            if (pframe != NULL)
                return pframe;
        }

        return NULL;
    }

    void ResetMatrix()
    {
        matRot = matRotOrig;
        D3DXMatrixIdentity(&matTrans);

        if (pframeFirstChild != NULL)
        {
            pframeFirstChild->ResetMatrix();
        }

        if (pframeSibling != NULL)
        {
            pframeSibling->ResetMatrix();
        }
    }

    void AddFrame(SFrame* pframe)
    {
        if (pframeFirstChild == NULL)
        {
            pframeFirstChild = pframe;
        }
        else
        {
            pframe->pframeSibling = pframeFirstChild->pframeSibling;
            pframeFirstChild->pframeSibling = pframe;
        }
    }

    void AddMesh(SMeshContainer* pmc)
    {
        pmc->pmcNext = pmcMesh;
        pmcMesh = pmc;
    }
};

struct SDrawElement
{
    SFrame* pframeRoot;

    D3DXVECTOR3 vCenter;
    float fRadius;

    // name of element for selection purposes
    char* szName;

    // animation list
    SFrame* pframeAnimHead;

    // next element in list
    SDrawElement* pdeNext;

    float fCurTime;
    float fMaxTime;

    SDrawElement()
        :vCenter(0.0, 0.0, 0.0),
        fRadius(1.0),
        szName(NULL),
        pframeRoot(NULL),
        pframeAnimHead(NULL),
        pdeNext(NULL)
    {
    }

    ~SDrawElement()
    {
        delete pframeRoot;
        pframeRoot = NULL;
        delete pdeNext;
        pdeNext = NULL;
        delete[] szName;
        szName = NULL;

        // do NOT delete pframeAnimHead;
    }

    void AddAnimationFrame(SFrame* pframeAnim)
    {
        pframeAnim->pframeAnimNext = pframeAnimHead;
        pframeAnimHead = pframeAnim;
    }

    SFrame* FindFrame(char* szName)
    {
        if (pframeRoot == NULL)
            return NULL;
        else
            return pframeRoot->FindFrame(szName);
    }
};

#define MAX_INTERSECTIONS 16
struct D3DVERTEX
{
    D3DXVECTOR3 p;
    D3DXVECTOR3 n;
    FLOAT       tu, tv;
};
struct INTERSECTION
{
    DWORD dwFace;                 // mesh face that was intersected
    FLOAT fBary1, fBary2;         // barycentric coords of intersection
    FLOAT fDist;                  // distance from ray origin to intersection
    FLOAT tu, tv;                 // texture coords of intersection
};

typedef struct _COLLISION_RESULT
{
    int nCollType;
    float fDist;
    D3DXVECTOR3 vNormalVector;
    D3DXVECTOR3 vPicking;
    _COLLISION_RESULT()
    {
        nCollType = COLL_NONE;
        fDist = DEFAULT_COLLISION_DISTANCE;
    }
} COLLISION_RESULT;

// 2006-04-08 by ispark
typedef struct _COLLISION_OBJ_RESULT
{
    COLLISION_RESULT stCollision;
    CObjectChild* pObject;
    _COLLISION_OBJ_RESULT()
    {
        pObject = NULL;
    }
} COLLISION_OBJ_RESULT;

class CSkinnedMesh : public CAtumNode
{
public:
    CSkinnedMesh();
    CSkinnedMesh(BOOL bProgressiveMesh);
    // 2009. 11. 23 by jskim 리소스 로딩 구조 변경
    //- 생성자를 함수로 따로 구현
    void InitSkinnedMesh();
    //end 2009. 11. 23 by jskim 리소스 로딩 구조 변경

    float GetRaidus() { return m_fRadius; }

    virtual ~CSkinnedMesh();
    virtual HRESULT InitDeviceObjects();
    virtual HRESULT RestoreDeviceObjects();
    virtual HRESULT InvalidateDeviceObjects();
    virtual HRESULT DeleteDeviceObjects();
    virtual void Render(BOOL bMultiTexture = FALSE, DWORD nType = 0);
    virtual void Tick(float fElapsedTime);

    SDrawElement* m_pdeSelected;
    SFrame* m_pframeSelected;
    CGameData* m_pGameDataToDecal;

    DWORD					m_dwFVF;
    LPDIRECT3DDEVICE9		m_pd3dDevice;
    LPD3DXMATRIXA16			m_pBoneMatrices;
    DWORD					m_dwIndexedVertexShader[4];
    DWORD					m_maxBones;
    METHOD					m_method;
    D3DCAPS9				m_d3dCaps;
    D3DXMATRIX				m_mWorld;

    DataHeader* m_pDataHeader;
public:
    float					m_fRadius;
    D3DXVECTOR3				m_vCenter;
    BYTE					m_bTextureNum;
    // 2007-08-29 by bhsohn 최소 프레임시 기본 아머만 로딩하게끔 변경
    //CGameData *				m_pGameData;
    //LPDIRECT3DTEXTURE9	*	m_pTexture;	
    SMeshContainer* m_pmcSelectedMesh;
    SDrawElement* m_pdeHead;
    INT						m_nRenderCount;						// 렌더링이 사용된 횟수(일정시간동안 사용빈도수가 없으면 메모리에서 내림)
    BOOL					m_bMaterial;						// Material 을 적용할것이냐?
    D3DMATERIAL9			m_material;							// Material
    BOOL					m_bCheckBlend;						// 블렌딩을 체크할것이냐?
    FLOAT					m_fCollDist;						// 충돌 지점 거리
    BYTE					m_bProgressiveMesh;					// 메쉬의 폴리곤 수를를 줄일것이냐?
    BYTE					m_bTotalTextureNum;
    BOOL					m_bMultiTexture;
    LPDIRECT3DTEXTURE9		m_pOrderTexture;					// 강제로 맵핑을하여 그릴때
    INTERSECTION			m_Intersection;						// 충돌 처리용

    int						m_nSelectDecalNum[MAX_DECAL_NUM];
    int						m_nDecalCount;
    //	LPDIRECT3DTEXTURE9		*m_pDecalTextures;	//ppTextures (Decal)
    UINT					m_unTexColor;
    UINT					m_unTexSelectColor;
    UINT					m_unUnitTexOld;

    // 2007-08-29 by bhsohn 최소 프레임시 기본 아머만 로딩하게끔 변경
    CGameData* m_pGameData;
    LPDIRECT3DTEXTURE9* m_pTexture;
    BOOL* m_pLoadMem;

    // 2007-11-08 by bhsohn 인벤 이펙트 관련 처리
    char					m_szMeshObjFileName[256];

    // 2009. 11. 23 by jskim 리소스 로딩 구조 변경
    BOOL					m_bIsLoadingFlag;
    LPDIRECTXFILE			pxofapi;
    LPDIRECTXFILEENUMOBJECT pxofenum;
    SDrawElement* pdeMesh;
    LPDXFILELOADMEMORY		pMemory;
    DWORD					dwOptions;
    LPDIRECTXFILEDATA		pxofobjCur;
    DataHeader* pHeader;
    int						m_StartTime;
    //end 2009. 11. 23 by jskim 리소스 로딩 구조 변경
};
#endif // !defined(AFX_SKINNEDMESH_H__75E6AD0E_1348_45B4_8A86_614B206812B1__INCLUDED_)
