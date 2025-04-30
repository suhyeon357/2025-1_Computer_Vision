/*
 * ����7: LOG (Laplacian of Gaussian)
 * -> "transformations/filter.hpp" ����
 */

#include "opencv2/opencv.hpp"
#include "filter.hpp"

int main()
{
	cv::Mat original_image, convoluted_image, zerocrossing_image;
	original_image = cv::imread("bucks.jpg", cv::IMREAD_GRAYSCALE);

	double sigma = 2.0; // 0.5, 1.0, 2.0, ...
	LOG logFilter;

	// CreateMask()�� �����ϼ���.
	logFilter.CreateMask(sigma);
	logFilter.Convolute(original_image, convoluted_image);
	// FindZeroCrossing()�� CheckSign()�� �����ϼ���.
	logFilter.FindZeroCrossing(convoluted_image, zerocrossing_image);

	cv::imshow("Original Image", original_image);
	cv::imshow("Convoluted Image", convoluted_image);
	cv::imshow("Zero-Crossing Image", zerocrossing_image);
	cv::waitKey();

	// �̹����� ���Ϸ� �����Ѵ�.
	cv::imwrite("bucks_conv.bmp", convoluted_image);
	cv::imwrite("bucks_zerocrossing.bmp", zerocrossing_image);
	std::cout << "���� ���� �Ϸ�!" << std::endl;
}