#include "window_controller.h"

BOOL WinController::is_valid() {
	if (this->self_hwnd > 0) {
		return TRUE;
	}
	return FALSE;
}

HWND WinController::find_window_hwnd(PCSTR title_part) {
	QueryStruct query = QueryStruct(title_part);

    EnumWindows(  // 遍历窗口
		[](HWND hwnd, LPARAM lParam) -> BOOL {
			if (!IsWindowVisible(hwnd)) { return TRUE; }
			if (IsIconic(hwnd)) { return TRUE; }
			int length = GetWindowTextLength(hwnd);
			if (length == 0) { return TRUE; }

			LPSTR buffer = new CHAR[256];
			GetWindowText(hwnd, buffer, length + 1);  // 窗口标题
			QueryStruct* p = reinterpret_cast<QueryStruct*>(lParam);
			if (std::string(buffer).find(p->title) != std::string::npos) {
				reinterpret_cast<QueryStruct*>(lParam)->hwnd = hwnd;
				reinterpret_cast<QueryStruct*>(lParam)->title = buffer;
				return FALSE;
			}
			return TRUE;
		},
		reinterpret_cast<LPARAM>(&query)
	);
    return query.hwnd;
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
	this->self_hwnd = NULL;
    PCSTR astr = "student";
}

BOOL WinController::click_at_pos(UINT x, UINT y) {
	return TRUE;
}

