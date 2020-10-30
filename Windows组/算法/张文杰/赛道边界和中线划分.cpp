#include <iostream>
#include <opencv2/opencv.hpp>

#include <opencv2/core/core.hpp>   
#include<opencv2/highgui/highgui.hpp>   
#include<opencv2/imgproc/imgproc.hpp> 

using namespace cv;
using namespace std;

void removePepperNoise(Mat& mask);
Mat MarkMat(Mat a, Mat& c);
int main()
{
	Mat A,B;
	A = imread("赛道.png",0);
    B = imread("赛道.png");
	Mat rst;
	threshold(A ,rst, 127, 255, THRESH_OTSU);

    imshow("二值图像", rst);
    removePepperNoise(rst);

    imshow("灰度图像", A);
    imshow("去噪二值图像", rst);
    Mat src(B);
    Mat rst2 = MarkMat(rst, src);


    imshow("标记二值图像", rst2);
    imshow("彩色图像", src);
	waitKey(0);
	return 0;
}

void removePepperNoise(Mat& mask)
{
    for (int y = 2; y < mask.rows - 2; ++y)
    {
        uchar* pThis = mask.ptr(y);
        uchar* pUp1 = mask.ptr(y - 1);
        uchar* pUp2 = mask.ptr(y - 2);
        uchar* pDown1 = mask.ptr(y + 1);
        uchar* pDown2 = mask.ptr(y + 2);

        pThis += 2; pUp1 += 2; pUp2 += 2; pDown1 += 2; pDown2 += 2;

        int x = 2;
        while (x < mask.cols - 2)
        {
            uchar v = *pThis;
            // 当前点为黑色
            if (v == 0)
            {
                // 5 * 5 邻域的外层
                bool allAbove = *(pUp2 - 2) && *(pUp2 - 1) && *(pUp2) && *(pUp2 + 1) && *(pUp2 + 2);
                bool allBelow = *(pDown2 - 2) && *(pDown2 - 1) && *(pDown2) && *(pDown2 + 1) && *(pDown2 + 2);
                bool allLeft = *(pUp1 - 2) && *(pThis - 2) && *(pDown1 - 2);
                bool allRight = *(pUp1 + 2) && *(pThis + 2) && *(pDown1 + 2);
                bool surroundings = allAbove && allBelow && allLeft && allRight;

                if (surroundings)
                {
                    // 5*5 邻域的内层（3*3的小邻域）
                    *(pUp1 - 1) = *(pUp1) = *(pUp1 + 1) = 255;
                    *(pThis - 1) = *pThis = *(pThis + 1) = 255;
                    *(pDown1 - 1) = *pDown1 = *(pDown1 + 1) = 255;
                    // 0 ⇒ 255
                }
                pUp2 += 2; pUp1 += 2; pThis += 2; pDown1 += 2; pDown2 += 2;
                x += 2;
            }
            ++pThis; ++pUp2; ++pUp1; ++pDown1; ++pDown2; ++x;
        }
    }
}

Mat MarkMat(Mat a, Mat &c) {
    int m=0, n=0;
    for (int y= a.rows/3; y < a.rows; ++y) {
        for (int x = a.cols / 2; x < a.cols; ++x) {

            if (a.at<uchar>(y, x) == 0) {
                m = x;
                c.at<Vec3b>(y, x)[0] = 0;
                c.at<Vec3b>(y, x)[1] = 0;
                c.at<Vec3b>(y, x)[2] = 255;
                break;
            }
        }
        for (int x = a.cols / 2; x >=0; --x) {
            if (a.at<uchar>(y, x) == 0) {
                n = x;
                c.at<Vec3b>(y, x)[0] = 0;
                c.at<Vec3b>(y, x)[1] = 0;
                c.at<Vec3b>(y, x)[2] = 255;
                break;
            }
        }
        a.at<uchar>(y, (m + n) / 2) = 0;
        c.at<Vec3b>(y, (m + n) / 2)[0] = 0;
        c.at<Vec3b>(y, (m + n) / 2)[1] = 0;
        c.at<Vec3b>(y, (m + n) / 2)[2] = 255;
    }
    return a;
}
