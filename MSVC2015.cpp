#include "pch.h"
#include "MSVC2015.h"

BOOL CMSVC2015::SetArguments(int nInstallType)
{
    m_strArguments = L"";

    if (nInstallType & static_cast<int>(eInstallType::eInstall))
    {
        m_strArguments.append(L"/Install ");
    }

    if (nInstallType & static_cast<int>(eInstallType::eRepair))
    {
        m_strArguments.append(L"/repair ");

    }

    if (nInstallType & static_cast<int>(eInstallType::eUnInstall))
    {
        m_strArguments.append(L"/uninstall ");

    }

    if (nInstallType & static_cast<int>(eInstallType::eLayout))
    {
        m_strArguments.append(L"/layout ");

    }

    if (nInstallType & static_cast<int>(eInstallType::ePassive))
    {
        m_strArguments.append(L"/passive ");

    }

    if (nInstallType & static_cast<int>(eInstallType::eQuiet))
    {
        //m_strArguments.append(L"/q ");
        m_strArguments.append(L"/quiet ");

    }

    if (nInstallType & static_cast<int>(eInstallType::eNoRestart))
    {
        m_strArguments.append(L"/norestart ");

    }

    return TRUE;
}