#pragma once

#include <Windows.h>
#include <string>

/* 用于查询窗口属性的结构体 */
class QueryStruct {
public:
	HWND hwnd;
	PCSTR title;
	QueryStruct() : hwnd(NULL), title("") {}
	QueryStruct(PCSTR t) : hwnd(NULL), title(t) {}
};

class WinController {
private:
	HWND hwnd;
	PCSTR title;
	BOOL is_valid();
public:
	WinController() : hwnd(NULL), title("") {}
	WinController(HWND h) :hwnd(h), title("") {}
	WinController(PCSTR);
	static QueryStruct find_window_hwnd(PCSTR);
	HWND get_hwnd() { return this->hwnd; }
	PCSTR get_title() { return this->title; }
	BOOL reset_hwnd(HWND new_hwnd) { this->hwnd = new_hwnd; }
	BOOL click_at_pos(UINT x, UINT y);
};




