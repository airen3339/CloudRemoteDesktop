
#ifdef _WIN32
#include "Windows.h"
#endif // _WIN32

#include "CKeyAssistantWin.h"
#include "CKeyHookWin.h"
#include "Command.h"
#include <iostream>
using std::cout;
using std::endl;

HHOOK g_hKeyBoard;

//! bottom keyboard system caller, filter alt+tab
static LRESULT CALLBACK KeyBoardProc(int code, WPARAM wParam, LPARAM lParam)
{

	if (code == HC_ACTION)
	{
		PKBDLLHOOKSTRUCT p;

		switch (wParam)
		{
		case WM_KEYDOWN:
		case WM_SYSKEYDOWN:
		case WM_KEYUP:
		case WM_SYSKEYUP:
			p = (PKBDLLHOOKSTRUCT)lParam;

			{
				//! log
				p->flags;
				p->vkCode;
				p->scanCode;
				p->dwExtraInfo;
				cout << endl;
				cout << __func__ << " flags: " << p->flags << " vkCode: " << p->vkCode
					<< " scanCode: " << p->scanCode << " dwExtraInfo: " << p->dwExtraInfo << endl;
			}

			//! alt + tab
			if ((p->vkCode == VK_TAB) && ((p->flags & LLKHF_ALTDOWN) != 0))
			{
#if 0

				//! <0, down; >0, up
				bool bLAltDown = GetKeyState(VK_LMENU) < 0 ? true : false;
				bool bRAltDown = GetKeyState(VK_RMENU) < 0 ? true : false;

				CMDData cmdData;
				if (bLAltDown) {
					cmdData.SetCMD(CMDTYPE::CMD_KEY_SP_ALTL_TAB);
				}
				else if(bRAltDown) {
					cmdData.SetCMD(CMDTYPE::CMD_KEY_SP_ALTR_TAB);
				}
				
				if (WM_SYSKEYUP == wParam) {
					//! tab release
					cmdData.SetKeyValue(static_cast<int32_t>(CMDTYPE::CMD_KEY_RELEASE));
				}

				cout << __func__ << " catch alt+tab" << " wParam: " << wParam << endl;
				CKeyAssistantWin::Notify(cmdData);
				return 1;

#else

				CkeyHookWinAltTab altTab;
				return altTab.Hook(wParam, lParam);
#endif // 0

			}
			//! left/right win + l, L key value = 0x4C
			else if ((p->vkCode == 0x4C))
			{
#if 0
				//! <0, down; >0, up
				bool bLWinDown = GetKeyState(VK_LWIN) < 0 ? true : false;
				bool bRWinDown = GetKeyState(VK_RWIN) < 0 ? true : false;

				CMDData cmdData;
				if (bLWinDown) {
					cmdData.SetCMD(CMDTYPE::CMD_KEY_SP_WIN_L);
				}
				else if (bRWinDown) {
					cmdData.SetCMD(CMDTYPE::CMD_KEY_SP_WIN_L);
				}

				cout << __func__ << " catch win+L" << endl;
				CKeyAssistantWin::Notify(cmdData);
				return 1;

#else

				CkeyHookWinWinL winL;
				return winL.Hook(wParam, lParam);

#endif // 0

			}

			break;
		}
	}

	return ::CallNextHookEx(g_hKeyBoard, code, wParam, lParam);
}

//! register global hook
static void SetHookEx()
{
	HMODULE hModule = GetModuleHandle("Hook");
	HMODULE hModuleUser = LoadLibrary("user32.dll");
	static_cast<HMODULE>(hModule);
	static_cast<HMODULE>(hModuleUser);
	g_hKeyBoard = SetWindowsHookEx(WH_KEYBOARD_LL, KeyBoardProc, hModuleUser, 0);
	DWORD err = GetLastError();
	cout << __func__ << " err: " << err << endl;
}

//! unregister global hook
static void UnSetHookEx()
{
	if (g_hKeyBoard) {
		UnhookWindowsHookEx(g_hKeyBoard);
		DWORD err = GetLastError();
		cout << __func__ << " err: " << err << endl;
	}

	g_hKeyBoard = NULL;
}

CKeyAssistantWin* CKeyAssistantWin::m_pOwner = nullptr;

CKeyAssistantWin::CKeyAssistantWin()
{
	InitHanlde();
	SetHook();
}

CKeyAssistantWin::~CKeyAssistantWin()
{
	UnSetHook();
	m_pOwner = nullptr;
}

void CKeyAssistantWin::InitHanlde()
{
	m_pOwner = this;
}

void CKeyAssistantWin::Process()
{
	
}

void CKeyAssistantWin::SetHook()
{
	SetHookEx();
}

void CKeyAssistantWin::UnSetHook()
{
	UnSetHookEx();
}

void CKeyAssistantWin::SendKeyMsg(CMDData& cmdData)
{
	if (m_pCb.cb && m_pCb.user) {
		m_pCb.param = static_cast<void*>(&cmdData);
		m_pCb.cb(m_pCb.user, m_pCb.param);
	}
}

void CKeyAssistantWin::Notify(CMDData& cmdData)
{
	cout << __func__ << endl;
	if (m_pOwner) {
		m_pOwner->SendKeyMsg(cmdData);
	}

}
