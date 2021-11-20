#include <img_proc.h>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;

bool match_img(char* src, char* tmp) {
	int matchMethod = cv::TM_SQDIFF;
	cv::Mat srcImage, tmpImage, g_resultImage;
	srcImage = cv::imread(src);
	tmpImage = cv::imread(tmp);

	matchTemplate(srcImage, tmpImage, g_resultImage, matchMethod);

	// find best match point(matchloc)
	double minval, maxval;
	cv::Point minloc, maxloc, matchloc;
	cv::minMaxLoc(g_resultImage, &minval, &maxval, &minloc, &maxloc);
	matchloc = (matchMethod == cv::TM_SQDIFF || matchMethod == cv::TM_SQDIFF_NORMED) ? minloc : maxloc;

	cv::rectangle(srcImage, matchloc, cv::Point(matchloc.x + tmpImage.cols, matchloc.y + tmpImage.rows), cv::Scalar(0, 0, 255), 2, 8, 0);
	cv::imshow("raw_pic", srcImage);
	cv::waitKey(0);
	return true;
}


