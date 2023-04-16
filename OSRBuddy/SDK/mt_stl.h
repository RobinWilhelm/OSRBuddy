/******************************************************************************

	For MT-SAFE and/or Easy Use of STL Classes

******************************************************************************/

#ifndef __MT_STL_H__
#define __MT_STL_H__

#pragma warning(disable:4786)
#include <windows.h>
#include <map>
#include <set>
#include <list>
#include <vector>
#include <queue>
#include <string>
#include <algorithm>
#include <functional>
//#include "DebugAssert.h"

using namespace std;

class mt_lock
{
public:
	mt_lock()
	{
		InitializeCriticalSection(&m_lock);
	}

	~mt_lock()
	{
		EnterCriticalSection(&m_lock);	// �ٸ� ������ �̹� lock�� ��Ҵٸ� ó�� �ϷḦ ��ٸ��� ����
		LeaveCriticalSection(&m_lock);
		DeleteCriticalSection(&m_lock);
	}

	inline void lock()
	{
#ifdef _DEBUG
		// 2005-08-01 by cmkwon
		//		if (m_lock.LockCount < -1 || m_lock.LockCount > 100)
		//		{
		//			ASSERT_NEVER_GET_HERE();
		//			return;
		//		}
#endif
		EnterCriticalSection(&m_lock);
	}

#if (_WIN32_WINNT >= 0x0400)
	inline BOOL tryLock()
	{
		/*
		BOOL TryEnterCriticalSection(LPCRITICAL_SECTION lpCriticalSection);

		Return Values
			- If the critical section is successfully entered or the current
			thread already owns the critical section, the return value is nonzero.
			- If another thread already owns the critical section,
			the return value is zero.
		 */
		return TryEnterCriticalSection(&m_lock);
	}
#endif	// (_WIN32_WINNT >= 0x0400)_endif

	inline void unlock()
	{
#ifdef _DEBUG
		// 2005-08-01 by cmkwon
		//		if (m_lock.LockCount < -1 || m_lock.LockCount > 100)
		//		{
		//			ASSERT_NEVER_GET_HERE();
		//			return;
		//		}
#endif
		LeaveCriticalSection(&m_lock);
	}

public:
	CRITICAL_SECTION		m_lock;
};

// mt_auto_lock ���� ���� ��, scope�� ���������� ����
// mt_lock�� invalidate�Ǵ� ��� cancel_unlock_on_exit()�� �ݵ�� ȣ���ؾ���.
class mt_auto_lock
{
public:
	mt_auto_lock(mt_lock* i_pMTLock)
	{
		m_pMTLock = i_pMTLock;
		m_pMTLock->lock();
	}

	~mt_auto_lock()
	{
		if (m_pMTLock != NULL)
		{
			m_pMTLock->unlock();
		}
	}

	void auto_unlock_cancel(void)
	{
		if (m_pMTLock)
		{
			m_pMTLock->unlock();
		}
		m_pMTLock = NULL;
	}

public:
	mt_lock* m_pMTLock;
};

 
template<class _K, class _Ty, class _Pr = less<_K>, class _A = allocator<_Ty> >
class mt_map : public std::map< _K, _Ty, _Pr, _A >, public mt_lock
{
public:

};

template<class _K, class _Ty, class _Pr = less<_K>, class _A = allocator<_Ty> >
class mt_multimap : public std::multimap< _K, _Ty, _Pr, _A >, public mt_lock
{
public:
	
};

template<class _K, class _Pr = less<_K>, class _A = allocator<_K> >
class mt_set : public std::set<_K, _Pr, _A>, public mt_lock
{
public:
	
};

typedef set<std::string>				setString;			// 2007-05-04 by cmkwon, �߰���
typedef mt_set<std::string>			mtsetString;		// 2007-05-04 by cmkwon, �߰���



template<class _Ty, class _A = allocator<_Ty> >
class mt_list : public std::list<_Ty, _A>, public mt_lock
{
public:
	
};

template<class _Ty, class _A = allocator<_Ty> >
class mt_vector : public std::vector<_Ty, _A>, public mt_lock
{
public:

};

template<class _Ty, class _C = deque<_Ty> >
class mt_queue : public std::queue<_Ty, _C>, public mt_lock
{
public:

};

template<class _K, class _Ty, class _Pr = less<_K>, class _A = allocator<_Ty> >
class ez_map : public std::map< _K, _Ty, _Pr, _A >
{
public:

};

template<class _K, class _Pr = less<_K>, class _A = allocator<_K> >
class ez_set : public std::set<_K, _Pr, _A>
{
public:
	
};

template<class _Ty, class _A = allocator<_Ty> >
class ez_list : public std::list<_Ty, _A>
{

};


typedef vector<std::string>		vectstring;	// 2007-05-28 by cmkwon
#endif
