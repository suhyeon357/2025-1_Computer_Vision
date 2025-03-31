#include <iostream>
#include "opencv2/opencv.hpp"

// 이미지 반전 코드

//int main(void)
//{
//	
//	cv::Mat image;
//	image = cv::imread("cat.bmp", cv::IMREAD_COLOR);
//
//
//	// 이미지 로드에 실패할 경우를 에러 메세지 반환
//	if (image.empty())
//	{
//		std::cout << "image load fail" << std::endl;
//
//		return -1;
//	}
//
//	for (int y = 0; y < image.rows; y++)
//	{
//		for (int x = 0; x < image.cols; x++)
//		{
//			// image로부터 픽셀값을 읽어옴과 동시에 수정
//			unsigned int b = 255 - image.at<cv::Vec3b>(y, x)[0];
//			unsigned int g = 255 - image.at<cv::Vec3b>(y, x)[1];
//			unsigned int r = 255 - image.at<cv::Vec3b>(y, x)[2];
//
//			image.at<cv::Vec3b>(y, x)[0] = cv::saturate_cast<uchar>(b);
//			image.at<cv::Vec3b>(y, x)[1] = cv::saturate_cast<uchar>(g);
//			image.at<cv::Vec3b>(y, x)[2] = cv::saturate_cast<uchar>(r);
//
//			
//		}
//	}
//
//	// 이미지 출력
//	cv::imshow("Original Image", image);
//	cv::waitKey(0);
//
//	return 0;
//}