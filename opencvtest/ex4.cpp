/*
 * ����4: Rotation using Homogeneous Matrix
 */

#include "opencv2/opencv.hpp"
#include "geometry.hpp"

int main()
{
	cv::Mat original_image, forward_result_image, backward_result_image;
	original_image = cv::imread("cat.bmp", cv::IMREAD_GRAYSCALE);

	GeometryTransformator transformator;

	// ȸ�� ���� ����� �����Ѵ�.
	// geometry.cpp�� Geometry::SetRotateMatrix �Լ��� �����ϼ���.
	double degree = -10.0;
	transformator.SetRotateMatrix(degree);

	// Q1. ���� ���� ��ȯ�� �����Ѵ�.
	// geometry.cpp�� Geometry::ForwardTransformation �Լ��� �����ϼ���.
	transformator.ForwardTransformation(original_image, forward_result_image);

	// Q2. �Ĺ� ���� ��ȯ�� �����Ѵ�.
	// geometry.cpp�� Geometry::BackwardTransformation �Լ��� �����ϼ���.
	transformator.BackwardTransformation(original_image, backward_result_image);

	cv::imshow("Original Image", original_image);
	cv::imshow("Forward Result Image", forward_result_image);
	cv::imshow("Backward Result Image", backward_result_image);
	cv::waitKey(0); // �ƹ� Ű�� ������ ����Ѵ�.

	// �̹����� ���Ϸ� �����Ѵ�.
	cv::imwrite("cat_forward.bmp", forward_result_image);
	cv::imwrite("cat_backward.bmp", backward_result_image);
	std::cout << "���� ���� �Ϸ�!" << std::endl;

	return 0;
}

