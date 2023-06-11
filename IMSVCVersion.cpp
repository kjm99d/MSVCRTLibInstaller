#include "pch.h"
#include "IMSVCVersion.h"

std::wstring IMSVCVersion::GetArguments()
{
    return m_strArguments;
}

BOOL IMSVCVersion::Install()
{
    // 경로 정보가 유효하면서
    if (FALSE == m_strUrlInstallx86.empty())
    {
        // 설치에 실패하면
        if (FALSE == Install(m_strUrlInstallx86))
            return FALSE;
    }
        

    // 경로 정보가 유효하면서
    if (FALSE == m_strUrlInstallx64.empty())
    {
        // 설치에 실패하면
        if (FALSE == Install(m_strUrlInstallx64))
            return FALSE;
    }
    
    return TRUE;
}

BOOL IMSVCVersion::Install(std::wstring strUrl)
{
    // 다운로드 URL
    URLDownloadToFileW(NULL, strUrl.c_str(), L"Install.exe", 0, NULL);

    SHELLEXECUTEINFOW info = { 0 };
    info.cbSize = sizeof(SHELLEXECUTEINFOW);
    info.fMask = SEE_MASK_NOCLOSEPROCESS;
    info.lpFile = L"Install.exe";            // 설치 파일 경로
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

BOOL IMSVCVersion::SetInstallURLx86(std::wstring strUrl)
{
    this->m_strUrlInstallx86 = strUrl;
    return TRUE;
}

BOOL IMSVCVersion::SetInstallURLx64(std::wstring strUrl)
{
    this->m_strUrlInstallx86 = strUrl;
    return TRUE;
}
