#include "opencv2/opencv.hpp"

// 밝기 변환
// 
// 수업시간 작성 코드
int main(void)
{
	cv::Mat result_img, src;
	src = cv::imread("./cat.bmp", cv::IMREAD_COLOR);

	src.copyTo(result_img);

	for (int y = 0; y < src.rows; y++)
	{
		for (int x = 0; x < src.cols; x++)
		{
			int b = src.at<cv::Vec3b>(y, x)[0] - 75;
			int g = src.at<cv::Vec3b>(y, x)[1] - 75;
			int r = src.at<cv::Vec3b>(y, x)[2] - 75;

			result_img.at<cv::Vec3b>(y, x)[0] = cv::saturate_cast<uchar>(b);
			result_img.at<cv::Vec3b>(y, x)[1] = cv::saturate_cast<uchar>(g);
			result_img.at<cv::Vec3b>(y, x)[2] = cv::saturate_cast<uchar>(r);

		}
	}

	cv::imshow("image1", src);
	cv::imshow("image2", result_img);

	cv::waitKey();
	return 0;
}

int main(void)
{
	
	// 결과를 이미지를 저장할 result선언 및 dog.jpg를 읽어 할당합니다.
	cv::Mat result_image, image;
	image = cv::imread("cat.bmp", cv::IMREAD_COLOR);

	// 이미지를 result의 복사
	image.copyTo(result_image);

	// 이미지 로드에 실패할 경우를 에러 메세지 반환
	if (image.empty())
	{
		std::cout << "image load fail" << std::endl;

		return -1;
	}

	// 이미지의 전체 밝기 값을 75 낮춘다.
	for (int y = 0; y < image.rows; y++)
	{
		for (int x = 0; x < image.cols; x++)
		{
			// image로부터 픽셀값을 읽어옴과 동시에 수정
			int b = image.at<cv::Vec3b>(y, x)[0] - 75;
			int g = image.at<cv::Vec3b>(y, x)[1] - 75;
			int r = image.at<cv::Vec3b>(y, x)[2] - 75;

			// 값을 0~255 범위에 맞게 clip하여 result_image에 할당
			result_image.at<cv::Vec3b>(y, x)[0] = cv::saturate_cast<uchar>(b);
			result_image.at<cv::Vec3b>(y, x)[1] = cv::saturate_cast<uchar>(g);
			result_image.at<cv::Vec3b>(y, x)[2] = cv::saturate_cast<uchar>(r);
		}
	}

	// 이미지를 서로 비교
	cv::imshow("Original Image", image);
	cv::imshow("Result image", result_image);
	cv::waitKey(0);

	return 0;
}