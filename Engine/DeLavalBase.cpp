#include "pch.h"
#include "DeLavalBase.h"

DeLavalBase::DeLavalBase()
{
}

BOOL DeLavalBase::Create(const RECT& rect, CWnd* pParentWnd, UINT nID)
{
    return CWnd::Create(nullptr, _T(""), WS_CHILD | WS_VISIBLE, rect, pParentWnd, nID);
}

BOOL DeLavalBase::Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID)
{
    return 1;
}
