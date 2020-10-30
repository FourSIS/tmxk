#include <opencv2/opencv.hpp>


using namespace cv;

int main() {
	Mat src;
	src = imread("2.jpg");

	double k1 = -0.00000080;
	double k2 = -0.00000080;	

	Mat src2 = imread("2.jpg");
	
	for (int i = 0; i < src.rows; i++) {
		double y = i - round(src.rows / 2);
		for (int j = 0; j < src.cols; j++) {
			double x = j - round(src.cols / 2);

			double x1 = round(x * (1 + k1 * x * x + k2 * y * y ));
			double y1 = round(y * (1 + k1 * x * x + k2 * y * y ));

			y1 = y1 + round(src.rows / 2);
			x1 = x1 + round(src.cols / 2);

			src2.at<Vec3b>(i, j)[0] = src.at<Vec3b>(y1, x1)[0];
			src2.at<Vec3b>(i, j)[1] = src.at<Vec3b>(y1, x1)[1];
			src2.at<Vec3b>(i, j)[2] = src.at<Vec3b>(y1, x1)[2];
		}
	}

	imshow("Ô­Í¼",src);
	imshow("½ÃÕýºó", src2);

	waitKey(0);
	return 0;
}