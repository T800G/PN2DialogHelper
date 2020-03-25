#ifndef _HELPERS_307E652D_183C_44D1_A7CA_A53239B0C476_
#define _HELPERS_307E652D_183C_44D1_A7CA_A53239B0C476_

BOOL IsWindowClass(HWND hWnd, LPCTSTR pszClsName)
{
	TCHAR strBuf[256];
return ((GetClassName(hWnd, strBuf, 256) && lstrcmp(strBuf, pszClsName) == 0));
}

inline BOOL HasWindowStyle(HWND hw, LONG lStyle) {return (GetWindowLongPtr(hw, GWL_STYLE) & lStyle);}
inline BOOL HasWindowExStyle(HWND hw, LONG lExStyle) {return (GetWindowLongPtr(hw, GWL_EXSTYLE) & lExStyle);}

HWND FindChildWindow(HWND hwParent, LPCTSTR lpszChildClass, BOOL bVisibleOnly, LONG lWndStyle = 0, LONG lWndExStyle = 0)
{
	HWND hwChild = FindWindowEx(hwParent, NULL, lpszChildClass, NULL);
	while (hwChild)
	{
		if (!(bVisibleOnly && !IsWindowVisible(hwChild)))
		{
			if (!(lWndStyle && !HasWindowStyle(hwChild, lWndStyle)))
			{
				if (!(lWndExStyle && !HasWindowExStyle(hwChild, lWndExStyle)))
				{
					return hwChild;
				}
			}
		}
		hwChild = FindWindowEx(hwParent, hwChild, lpszChildClass, NULL);
	}
return NULL;
}

#endif//_HELPERS_307E652D_183C_44D1_A7CA_A53239B0C476_
