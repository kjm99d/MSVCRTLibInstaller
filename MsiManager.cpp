#include "pch.h"
#include "MsiManager.h"

CMsiManager::CMsiManager() : m_hInstall(NULL)
{
}

CMsiManager::CMsiManager(std::wstring strFilePath)
{
    SetFilePath(strFilePath);
}

CMsiManager::~CMsiManager()
{
    Close();
}

BOOL CMsiManager::Open()
{
    BOOL bResult = FALSE;
    if (m_strFilePath.length() > 0)
    {
        // MSI 파일 열기
        if (ERROR_SUCCESS == MsiOpenPackageW(m_strFilePath.c_str(), &m_hInstall) && 0 != m_hInstall) 
        {
            bResult = TRUE;
        }
    }

    return bResult;
}

BOOL CMsiManager::SetInstallOption()
{
    BOOL bResult = FALSE;
    if (ERROR_SUCCESS == MsiSetPropertyA(m_hInstall, "UILevel", "2"))
        bResult = TRUE;

    return bResult;
}

BOOL CMsiManager::Install()
{
    BOOL bResult = FALSE;
    UINT nResult = MsiInstallProductW(m_strFilePath.c_str(), L"");
    if (ERROR_SUCCESS == nResult)
    {
        bResult = TRUE;
    }
    else
    {
        DWORD dwErr = GetLastError();
        WCHAR szMsg[1024] = { 0, };
        swprintf_s(szMsg, _countof(szMsg), L"ProductW [%d], Last Error [%d]", nResult, szMsg);
        OutputDebugString(szMsg);
    }

    return bResult;
}

void CMsiManager::SetProgressCallback(INSTALLUI_HANDLERA handler)
{
    MsiSetExternalUIA(handler, INSTALLLOGMODE_PROGRESS | INSTALLLOGMODE_VERBOSE, nullptr);
}

void CMsiManager::Close()
{
    if (m_hInstall)
        MsiCloseHandle(m_hInstall);
}

void CMsiManager::SetFilePath(std::wstring strFilePath)
{
    m_strFilePath = strFilePath;
}

std::wstring CMsiManager::GetFilePath()
{
    return std::wstring();
}
