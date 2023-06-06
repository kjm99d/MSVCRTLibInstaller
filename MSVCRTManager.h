/*****************************************************************//**
 * \file   MSVCRTManager.h
 * \brief  Microsoft Visual C/C++ Runtime Package 설치 지원에 대한 클래스입니다.
 * 
 * \author Administrator
 * \date   June 2023
 *********************************************************************/

#pragma once
#include <string>



class CMSVCRTManager
{
public:
	enum class eInstallType {
		eInstall	= 0x1,
		eRepair		= 0x2,
		eUnInstall	= 0x4,
		eLayout		= 0x8,
		ePassive	= 0x10,
		eQuiet		= 0x20,
		eNoRestart	= 0x40,
	};
public:
	CMSVCRTManager(std::wstring strFilePath);
	~CMSVCRTManager();

public:
	BOOL Install();
	void SetInstallOption(int typeMask);

private:
	std::wstring m_strFilePath;
	std::wstring m_strArguments;
};

