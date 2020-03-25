#include "stdafx.h"
#include "debugtrace.h"
#include "helpers.h"

extern "C" IMAGE_DOS_HEADER __ImageBase;
HWINEVENTHOOK g_hEventHook;

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
	switch (ul_reason_for_call)
	{
		case DLL_PROCESS_ATTACH:
		case DLL_THREAD_ATTACH:
		case DLL_THREAD_DETACH:
		case DLL_PROCESS_DETACH:
		break;
    }
    return TRUE;
}

////////////////////////////////////////////////////////////////////////////////
void CALLBACK WinEventProcCallback(HWINEVENTHOOK hook, DWORD dwEvent, HWND hwnd, LONG idObject,
								   LONG idChild, DWORD dwEventThread, DWORD dwmsEventTime)
{
	//if (idObject == OBJID_WINDOW)
	//{
		//if (GetParent(GetParent(hwnd)) == NULL) //savefile dlg is main (top) window class
		//{
			//event is fired multiple times until window is visible  //child savefile dlg
			//if (IsWindowVisible(hwnd) && IsWindowClass(hwnd, _T("#32770")))
			//{
				DBGTRACE("#32770  EVENT_SYSTEM_DIALOGSTART\n");
				DBGTRACE("GetFocus=0x%x\n", GetFocus());
				HWND hwOkBtn = FindChildWindow(hwnd, WC_BUTTON, FALSE, BS_DEFPUSHBUTTON);
				DBGTRACE("BS_DEFPUSHBUTTON=0x%x\n", hwOkBtn);
				if (GetFocus() != hwOkBtn) SetFocus(hwOkBtn); //this should work for all dialogs where focus is not set on default button
			//}
		//}
	//}
}

/////////////////////////////////////////////////////////////////////////////////////

bool __stdcall pn_init_extension(int iface_version, /*extensions::IPN*/ void* pn)
{
	DBGTRACE("pn_init_extension\n");
	g_hEventHook = SetWinEventHook(EVENT_SYSTEM_DIALOGSTART, EVENT_SYSTEM_DIALOGSTART, (HINSTANCE)&__ImageBase, 
									WinEventProcCallback, GetCurrentProcessId(), 0, WINEVENT_INCONTEXT);
	
	if (g_hEventHook)
	{
		DBGTRACE("SetWinEventHook\n");
	}

return true;
}

void __declspec(dllexport) __stdcall pn_get_extension_info(/*PN::BaseString&*/void* name, /*PN::BaseString&*/void* version)
{
}

void __declspec(dllexport) __stdcall pn_exit_extension()
{
	DBGTRACE("pn_exit_extension\n");
	//remove event hooks
	_ASSERTE(g_hEventHook);
	if (g_hEventHook)
	{
		UnhookWinEvent(g_hEventHook);
		g_hEventHook=NULL;
		DBGTRACE("UnhookWinEvent\n");
	}
}