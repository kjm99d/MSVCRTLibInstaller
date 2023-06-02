#pragma once
#include <Windows.h>
#include <msi.h>
#include <msiquery.h>
#include <string>
#pragma comment(lib, "Msi.lib")

//typedef UINT (*WINAPI FP_ProgressCallback)(MSIHANDLE hInstall, UINT iMessageType, LPCTSTR szMessage, DWORD_PTR /*dwMessage*/);

class CMsiManager
{
public:
	CMsiManager();
	CMsiManager(std::wstring strFilePath);
	~CMsiManager();

public:
	BOOL Open();
	BOOL SetInstallOption();
	BOOL Install();
	
	void SetProgressCallback(INSTALLUI_HANDLERA handler);
private:
	void Close();

private:
	void SetFilePath(std::wstring strFilePath);
	std::wstring GetFilePath();

private:
	std::wstring m_strFilePath;

	MSIHANDLE m_hInstall;
};

