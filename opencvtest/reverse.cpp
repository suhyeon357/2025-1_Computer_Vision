#include <iostream>
#include "opencv2/opencv.hpp"

// �̹��� ���� �ڵ�

//int main(void)
//{
//	
//	cv::Mat image;
//	image = cv::imread("cat.bmp", cv::IMREAD_COLOR);
//
//
//	// �̹��� �ε忡 ������ ��츦 ���� �޼��� ��ȯ
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
//			// image�κ��� �ȼ����� �о�Ȱ� ���ÿ� ����
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
//	// �̹��� ���
//	cv::imshow("Original Image", image);
//	cv::waitKey(0);
//
//	return 0;
//}