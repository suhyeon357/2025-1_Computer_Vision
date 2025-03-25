#include "opencv2/opencv.hpp"

// ��� ��ȯ
// 
// �����ð� �ۼ� �ڵ�
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
	
	// ����� �̹����� ������ result���� �� dog.jpg�� �о� �Ҵ��մϴ�.
	cv::Mat result_image, image;
	image = cv::imread("cat.bmp", cv::IMREAD_COLOR);

	// �̹����� result�� ����
	image.copyTo(result_image);

	// �̹��� �ε忡 ������ ��츦 ���� �޼��� ��ȯ
	if (image.empty())
	{
		std::cout << "image load fail" << std::endl;

		return -1;
	}

	// �̹����� ��ü ��� ���� 75 �����.
	for (int y = 0; y < image.rows; y++)
	{
		for (int x = 0; x < image.cols; x++)
		{
			// image�κ��� �ȼ����� �о�Ȱ� ���ÿ� ����
			int b = image.at<cv::Vec3b>(y, x)[0] - 75;
			int g = image.at<cv::Vec3b>(y, x)[1] - 75;
			int r = image.at<cv::Vec3b>(y, x)[2] - 75;

			// ���� 0~255 ������ �°� clip�Ͽ� result_image�� �Ҵ�
			result_image.at<cv::Vec3b>(y, x)[0] = cv::saturate_cast<uchar>(b);
			result_image.at<cv::Vec3b>(y, x)[1] = cv::saturate_cast<uchar>(g);
			result_image.at<cv::Vec3b>(y, x)[2] = cv::saturate_cast<uchar>(r);
		}
	}

	// �̹����� ���� ��
	cv::imshow("Original Image", image);
	cv::imshow("Result image", result_image);
	cv::waitKey(0);

	return 0;
}