#include "window_controller.h"
#define MYPRINT(...) {char output[512]; sprintf_s(output, __VA_ARGS__);  OutputDebugString(output);}

BOOL WinController::is_valid() {
	if (this->self_hwnd > 0) {
		return TRUE;
	}
	return FALSE;
}

HWND WinController::find_window_hwnd(PCSTR title_part) {
	QueryStruct query = QueryStruct(title_part);

    HWND find_hwnd = NULL;
    EnumWindows(  // 遍历窗口
		[](HWND hwnd, LPARAM lParam) -> BOOL {
			if (!IsWindowVisible(hwnd)) { return TRUE; }
			if (IsIconic(hwnd)) { return TRUE; }
			int length = GetWindowTextLength(hwnd);
			if (length == 0) { return TRUE; }

			//TCHAR buffer[128];
			//SendMessage(hwnd, WM_GETTEXT, 128, (LPARAM)(void*)buffer);
		
			LPSTR buffer = new CHAR[256];
			GetWindowText(hwnd, buffer, length + 1);
			std::string title_part = std::string(reinterpret_cast<QueryStruct*>(lParam)->title);
			MYPRINT("\n\n\n\n wdnmd!!!!!!!!!!!!!!!!!!\n");
			MYPRINT(buffer);
			MYPRINT("\n\n titlte part:::::\n");
			MYPRINT("title part: %s", title_part);
			if (std::string(buffer).find(title_part) != std::string::npos) {
				reinterpret_cast<QueryStruct*>(lParam)->hwnd = hwnd;
				reinterpret_cast<QueryStruct*>(lParam)->title = buffer;
				return FALSE;
			}
			return TRUE;
		},
		reinterpret_cast<LPARAM>(&query)
	);
    return find_hwnd;
}

WinController::WinController() {
	this->num = 0;
	this->self_hwnd = HWND();
}

WinController::WinController(HWND hwnd) {
	this->num = 0;
	this->self_hwnd = hwnd;
}

WinController::WinController(PCSTR title_str) {
	this->num = 1;
    PCSTR astr = "student";
    std::string kk = "dd haha 你好 stdio stupid";
    std::string hs = "haha";
    if (kk.find(hs) != std::string::npos) {
    }
    else {
    }
}

BOOL WinController::click_at_pos(UINT x, UINT y) {
	return TRUE;
}

HWND GetTheWindowHwnd() {
    HWND find_hwnd = NULL;
    EnumWindows(  // 遍历窗口
		[](HWND hwnd, LPARAM lParam) -> BOOL {
			if (!IsWindowVisible(hwnd)) { return TRUE; }
			if (IsIconic(hwnd)) { return TRUE; }
			int length = GetWindowTextLength(hwnd);
			if (length == 0) { return TRUE; }

			TCHAR buffer[512];
			SendMessage(hwnd, WM_GETTEXT, 512, (LPARAM)(void*)buffer);

			*(reinterpret_cast<HWND*>(lParam)) = hwnd;
			return TRUE;
		},
		reinterpret_cast<LPARAM>(&find_hwnd)
	);
    // if (find_hwnd != NULL) { MYPRINT("\n This is fucking insane: %d", find_hwnd); }
    return find_hwnd;
}


