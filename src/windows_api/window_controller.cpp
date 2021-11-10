#include "window_controller.h"

BOOL WinController::is_valid() {
	if (this->hwnd > 0) {
		return TRUE;
	}
	return FALSE;
}

/* �������ҵ���һ��ƥ��ؼ��ֵĴ��ڣ����������һ�鴰�ڲ��� */
QueryStruct WinController::find_window_hwnd(PCSTR title_part) {
	QueryStruct query = QueryStruct(title_part);

    EnumWindows(  // ��������
		[](HWND hwnd, LPARAM lParam) -> BOOL {
			if (!IsWindowVisible(hwnd)) { return TRUE; }
			//if (IsIconic(hwnd)) { return TRUE; }  // ��С���Ĵ���
			int length = GetWindowTextLength(hwnd);
			if (length == 0) { return TRUE; }

			LPSTR buffer = new CHAR[256];
			GetWindowText(hwnd, buffer, length + 1);  // ���ڱ���
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
    return query;
}

WinController::WinController(PCSTR title_part) {
	QueryStruct res = WinController::find_window_hwnd(title_part);
	this->hwnd = res.hwnd;
	this->title = res.title;
}

BOOL WinController::click_at_pos(UINT x, UINT y) {
	return TRUE;
}

