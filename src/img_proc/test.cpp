#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <Windows.h>

using namespace std;

HWND hpopo;

BITMAPINFOHEADER createBitmapHeader(int width, int height) {
	BITMAPINFOHEADER bi;

	bi.biSize = sizeof(BITMAPINFOHEADER);
	bi.biWidth = width;
	bi.biHeight = -height;
	bi.biPlanes = 1;
	bi.biBitCount = 32;
	bi.biCompression = BI_RGB;
	bi.biSizeImage = 0;
	bi.biXPelsPerMeter = 0;
	bi.biYPelsPerMeter = 0;
	bi.biClrUsed = 0;
	bi.biClrImportant = 0;

	return bi;
}

cv::Mat captureScreenMat(HWND hwnd) {
	cv::Mat src;

	// get handles to a device context (DC)
	HDC hwindowDC = GetDC(hwnd);
	HDC hwindowCompatibleDC = CreateCompatibleDC(hwindowDC);
	SetStretchBltMode(hwindowCompatibleDC, COLORONCOLOR);
	// This is the best stretch mode:
	//SetStretchBltMode(hdcWindow, HALFTONE);
	
	// define scale, height and width
	//int screenx = GetSystemMetrics(SM_XVIRTUALSCREEN);
	//int screeny = GetSystemMetrics(SM_YVIRTUALSCREEN);
	//int width = GetSystemMetrics(SM_CXVIRTUALSCREEN);
	//int height = GetSystemMetrics(SM_CYVIRTUALSCREEN);

	RECT r;
	GetWindowRect(hwnd, &r);
	int window_x = r.left;
	int window_y = r.top;
	int width = r.right - r.left;
	int height = r.bottom - r.top;

	// create mat object
	src.create(height, width, CV_8UC4);

	// create a bitmap
	HBITMAP hbwindow = CreateCompatibleBitmap(hwindowDC, width, height);
	BITMAPINFOHEADER bi = createBitmapHeader(width, height);

	// use the previously created device context with the bitmap
	SelectObject(hwindowCompatibleDC, hbwindow);


	// copy from the window device context to the bitmap device context
	StretchBlt(hwindowCompatibleDC, 0, 0, width, height, hwindowDC, 0, 0, width, height, SRCCOPY);  //change SRCCOPY to NOTSRCCOPY for wacky colors !
	//BitBlt(hwindowCompatibleDC, 0, 0, width, height, hwindowDC, 0, 0, SRCCOPY);
	GetDIBits(hwindowCompatibleDC, hbwindow, 0, height, src.data, (BITMAPINFO*)&bi, DIB_RGB_COLORS);            //copy from hwindowCompatibleDC to hbwindow

	// avoid memory leak
	DeleteObject(hbwindow);
	DeleteDC(hwindowCompatibleDC);
	ReleaseDC(hwnd, hwindowDC);
	
	cv::Mat dst;
	dst.create(height, width, CV_8UC3);
	cv::cvtColor(src, dst, cv::COLOR_BGRA2BGR);
	return dst;
}

void on_matching(char* src, char* tmp) {
	int matchMethod = cv::TM_SQDIFF_NORMED;
	cv::Mat srcImage, tmpImage, g_resultImage;
	//srcImage = cv::imread(src);
	//tmpImage = cv::imread(tmp);

	EnumWindows(
		[](HWND hwnd, LPARAM lParam) -> BOOL {
			if (!IsWindowVisible(hwnd)) { return TRUE; }
			//if (IsIconic(hwnd)) { return TRUE; }  // 最小化的窗口
			int length = GetWindowTextLength(hwnd);
			if (length == 0) { return TRUE; }

			LPSTR buffer = new CHAR[256];
			GetWindowText(hwnd, buffer, length + 1);  // 窗口标题
			if (std::string(buffer).find("网易") != std::string::npos) {
				hpopo = hwnd;
				return FALSE;
			}
			return TRUE;
		}, NULL
	);


	srcImage = captureScreenMat(hpopo);
	//srcImage = captureScreenMat(GetDesktopWindow());
	tmpImage = cv::imread("tmp.png");
	matchTemplate(srcImage, tmpImage, g_resultImage, matchMethod);

	// find best match point(matchloc)
	double minval, maxval;
	cv::Point minloc, maxloc, matchloc;
	cv::minMaxLoc(g_resultImage, &minval, &maxval, &minloc, &maxloc);
	matchloc = (matchMethod == cv::TM_SQDIFF || matchMethod == cv::TM_SQDIFF_NORMED) ? minloc : maxloc;

	std::cout << "Matching... min_val:" << minval << "max_val:" << maxval << std::endl;

	cv::rectangle(srcImage, matchloc, cv::Point(matchloc.x + tmpImage.cols, matchloc.y + tmpImage.rows), cv::Scalar(0, 0, 255), 2, 8, 0);
	cv::imshow("raw_pic", srcImage);
}
 
int main() {
	on_matching("src.png", "tmp.png");
	//HWND hwnd = GetDesktopWindow();
	//cv::Mat src = captureScreenMat(hwnd);

	//cv::imshow("oops", src);
	cv::waitKey(0);
	return 0;
}


