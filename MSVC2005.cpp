#include "pch.h"
#include "MSVC2005.h"

BOOL CMSVC2005::SetArguments(int nInstallType)
{
    m_strArguments = L"";


    if (nInstallType & static_cast<int>(eInstallType::eQuiet))
    {
        m_strArguments.append(L"/Q ");

    }

    return TRUE;
}