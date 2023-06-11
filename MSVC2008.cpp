#include "pch.h"
#include "MSVC2008.h"

BOOL CMSVC2008::SetArguments(int nInstallType)
{
    m_strArguments = L"";

    if (nInstallType & static_cast<int>(eInstallType::eQuiet))
    {
        m_strArguments.append(L"/q ");

    }


    return TRUE;
}