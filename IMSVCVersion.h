#pragma once
#include <Windows.h>
#include <string>

enum class eInstallType {
	eInstall = 0x1,
	eRepair = 0x2,
	eUnInstall = 0x4,
	eLayout = 0x8,
	ePassive = 0x10,
	eQuiet = 0x20,
	eNoRestart = 0x40,
};

class IMSVCVersion
{
public:
	virtual std::wstring GetArguments();
	virtual BOOL SetArguments(int nInstallType) = 0;
	virtual BOOL Install();
	virtual BOOL Install(std::wstring strUrl);

public:
	virtual BOOL SetInstallURLx86(std::wstring strUrl);
	virtual BOOL SetInstallURLx64(std::wstring strUrl);

protected:
	std::wstring m_strUrlInstallx86;
	std::wstring m_strUrlInstallx64;
	std::wstring m_strArguments;
};
