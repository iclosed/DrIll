#pragma once

#include <Windows.h>
#include <string>

class QueryStruct {
public:
	HWND hwnd;
	PCSTR title;
	QueryStruct() : hwnd(NULL), title("") {}
	QueryStruct(PCSTR title) : hwnd(NULL) { this->title = title; }
};

class WinController {
private:
	UINT num;
	HWND self_hwnd;
	BOOL is_valid();
public:
	WinController();
	WinController(HWND hwnd);
	WinController(PCSTR title_str);
	static HWND find_window_hwnd(PCSTR title);
	HWND get_hwnd() { return this->self_hwnd; }
	BOOL reset_hwnd(HWND new_hwnd) { this->self_hwnd = new_hwnd; }
	BOOL click_at_pos(UINT x, UINT y);
};




