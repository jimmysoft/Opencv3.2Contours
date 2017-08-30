
#include <iostream>
#include <opencv2\core.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2/imgcodecs/imgcodecs.hpp>
#include "opencv2/imgproc.hpp"
using namespace std;
using namespace cv;
int main()
{
cv::Mat image = cv::imread("c:\\jimmy\\my.bmp", IMREAD_GRAYSCALE);
if (image.empty())
{
cout << "이미지를 찾을 수 없습니다." << endl;
}
else
{
//load image
cv::namedWindow("Original Image");
cv::Mat result;

cv::imshow("Original Image", image);
std::vector<std::vector<cv::Point>> contours;


//threshold
//cv::threshold(image, image, 1, 255, cv::THRESH_BINARY);
//cv::imshow("threshold", image);

//Canny edge 캐니를 해야지 뭉쳐있는 와중에도 외곽선을 추출할 수 있다.
cv::Canny(image, result, 100, 200, 5);
cv::imshow("canny", result);


//contours
cv::findContours(image, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);

// Get the moments
vector<Moments> mu(contours.size());
for (int i = 0; i < contours.size(); i++)
{
mu[i] = moments(contours[i], false);
}
//  Get the mass centers:
vector<Point2f> mc(contours.size());
for (int i = 0; i < contours.size(); i++)
{
mc[i] = Point2f(mu[i].m10 / mu[i].m00, mu[i].m01 / mu[i].m00);
}
//contours to point iterator
std::vector<std::vector<cv::Point>>::iterator it = contours.begin();
int i=0;
//change color gray -> CV_8UC3
Mat drawing = Mat::zeros(image.size(), CV_8UC3);
//draw line and center
while (it != contours.end())
{
	//poly vector
	std::vector<cv::Point> poly;
	//get poly vector from points (poly line length)
	cv::approxPolyDP(*it, poly, 10, true);
	//is it square?
	//if (poly.size() == 4)
	//if (poly.size() >= 4 && fabs(contourArea(Mat(poly))) > 1000 && isContourConvex(Mat(poly)))
	if (poly.size() >= 4 && isContourConvex(Mat(poly)))
	{
	//draw lines
	//cv:polylines(result, poly, true, Scalar(255,255,0), 30);
	cv:polylines(drawing, poly, true, Scalar(255, 255, 0), 5);

	//cv::rectangle(drawing, poly[0], poly[2], CV_RGB(0, 255, 0), 2);

	//draw centers
	circle(drawing, mc[i], 4, Scalar(100, 200, 0), -1, 8, 0);
}
++it;
i++;
}
//show the result
cv::imshow("contour poly size >=4 result", drawing);
}
cv::waitKey(0);
return 0;
}

