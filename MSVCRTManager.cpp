#include "pch.h"
#include "MSVCRTManager.h"

CMSVCRTManager::CMSVCRTManager(std::wstring strFilePath)
{
    m_strFilePath = strFilePath;
}

CMSVCRTManager::~CMSVCRTManager()
{
}

BOOL CMSVCRTManager::Install()
{
    if (FALSE == PathFileExistsW(m_strFilePath.c_str()))
        return ERROR_FILE_NOT_FOUND;

    SHELLEXECUTEINFOW info = { 0 };
    info.cbSize = sizeof(SHELLEXECUTEINFOW);
    info.fMask = SEE_MASK_NOCLOSEPROCESS;
    info.lpFile = m_strFilePath.c_str();            // 설치 파일 경로
    info.lpParameters = m_strArguments.c_str();     // 설치 옵션 (예: /q는 조용히 설치)
    info.nShow = SW_SHOWDEFAULT;                    // 설치 중에 표시할 창 종류
    if (ShellExecuteExW(&info))
    {
        WaitForSingleObject(info.hProcess, INFINITE); // 설치가 완료될 때까지 대기
        CloseHandle(info.hProcess);
        
        return TRUE;
    }

    return FALSE;
}

void CMSVCRTManager::SetInstallOption(int typeMask)
{
    m_strArguments = L"";

    if (typeMask & static_cast<int>(CMSVCRTManager::eInstallType::eInstall))
    {
        m_strArguments.append(L"/Install ");
    }
    
    if (typeMask & static_cast<int>(CMSVCRTManager::eInstallType::eRepair))
    {
        m_strArguments.append(L"/repair ");

    }
    
    if (typeMask & static_cast<int>(CMSVCRTManager::eInstallType::eUnInstall))
    {
        m_strArguments.append(L"/uninstall ");

    }
    
    if (typeMask & static_cast<int>(CMSVCRTManager::eInstallType::eLayout))
    {
        m_strArguments.append(L"/layout ");

    }
    
    if (typeMask & static_cast<int>(CMSVCRTManager::eInstallType::ePassive))
    {
        m_strArguments.append(L"/passive ");

    }
    
    if (typeMask & static_cast<int>(CMSVCRTManager::eInstallType::eQuiet))
    {
        m_strArguments.append(L"/quiet ");

    }
    
    if (typeMask & static_cast<int>(CMSVCRTManager::eInstallType::eNoRestart))
    {
        m_strArguments.append(L"/norestart ");

    }
}
