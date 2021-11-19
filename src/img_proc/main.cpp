#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace std;
using namespace cv;

Mat g_srcImage, g_templateImage, g_resultImage;
int g_nMatchMethod;
int g_nMaxTrackbarNum = 5;

void on_matching(int, void*) {
	Mat srcImage;
	g_srcImage.copyTo(srcImage);
	int res_cols = g_srcImage.cols - g_templateImage.cols + 1;
	int res_rows = g_srcImage.rows - g_templateImage.rows + 1;
	g_resultImage.create(res_cols, res_rows, CV_32FC1);

	matchTemplate(g_srcImage, g_templateImage, g_resultImage, g_nMatchMethod);
	normalize(g_resultImage, g_resultImage, 0, 1, NORM_MINMAX, -1, Mat());
	double minval, maxval;
	Point minloc, maxloc, matchloc;
	minMaxLoc(g_resultImage, &minval, &maxval, &minloc, &maxloc);

	if (g_nMatchMethod == TM_SQDIFF || g_nMatchMethod == TM_SQDIFF_NORMED) {
		matchloc = minloc;
	}
	else {
		matchloc = maxloc;
	}

	rectangle(srcImage, matchloc, Point(matchloc.x + g_templateImage.cols, matchloc.y + g_templateImage.rows), Scalar(0, 0, 255), 2, 8, 0);
	rectangle(g_resultImage, matchloc, Point(matchloc.x + g_templateImage.cols, matchloc.y + g_templateImage.rows), Scalar(0, 0, 255), 2, 8, 0);
	
	imshow("raw_pic", srcImage);
	imshow("res_pic", g_resultImage);
}

int main() {
	g_srcImage = imread("src.png");
	g_templateImage = imread("tmp.png");

	imshow("src", g_srcImage);
	imshow("template", g_templateImage);

	namedWindow("raw", WINDOW_AUTOSIZE);
	namedWindow("res", WINDOW_AUTOSIZE);
	createTrackbar("method", "res", &g_nMatchMethod, g_nMaxTrackbarNum, on_matching);

	on_matching(0, NULL);

	waitKey(0);
	return 0;

}


