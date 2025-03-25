#include <iostream>
#include "opencv2/opencv.hpp"

// 이진화 구현
int main(void)
{
	
	cv::Mat image;
	image = cv::imread("cat.bmp", cv::IMREAD_GRAYSCALE);


	// 이미지 로드에 실패할 경우를 에러 메세지 반환
	if (image.empty())
	{
		std::cout << "image load fail" << std::endl;

		return -1;
	}


	for (int y = 0; y < image.rows; y++)
	{
		for (int x = 0; x < image.cols; x++)
		{
			int tmp = image.at<uchar>(y, x);

			if (image.at<uchar>(y, x) >= 128)
			{				
				tmp = 255;
			}
			else
			{
				tmp = 0;
			}

			image.at<uchar>(y, x) = cv::saturate_cast<uchar>(tmp);
			
			

		}
	}

	// 이미지 출력
	cv::imshow("Original Image", image);
	cv::waitKey(0);

	return 0;
}