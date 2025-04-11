/*
 * ����5: Weight Pyramid and Sobel Mask
 */

#include "opencv2/opencv.hpp"

void getSimpleDownscaledPyramid(const int Q, const cv::InputArray& input_image, std::vector<cv::Mat>& output_vector)
{
	cv::Mat input_mat = input_image.getMat();
	int width = input_mat.cols;
	int height = input_mat.rows;

	cv::Mat temp;
	input_mat.copyTo(temp);

	for (int q = 0; q < Q; ++q)
	{
		cv::Mat dst(cv::Size(width / 2, height / 2), CV_8UC1);

		for (int h = 0; h < dst.rows; ++h)
		{
			for (int w = 0; w < dst.cols; ++w)
			{
				dst.at<uchar>(h, w) = temp.at<uchar>(h * 2, w * 2);
			}
		}
		output_vector.push_back(dst);
		dst.copyTo(temp);

		width = width / 2;
		height = height / 2;
	}
}

void getWeightPyramid(const int Q, const cv::InputArray& input_image, std::vector<cv::Mat>& output_vector)
{
	cv::Mat input_mat = input_image.getMat();
	int width = input_mat.cols;
	int height = input_mat.rows;

	double weight[5][5] = {
		0.0025, 0.0125, 0.02, 0.0125, 0.0025,
		0.0125, 0.0625, 0.1, 0.0625, 0.0125,
		0.02, 0.1, 0.16, 0.1, 0.02,
		0.0125, 0.0625, 0.1, 0.0625, 0.0125,
		0.0025, 0.0125, 0.02, 0.0125, 0.0025
	};


	/**
	 * Weight Pyramid�� �����մϴ�.
	 * ���� �־��� weight kernel�� �̿��Ͽ� Convolution ������ �����մϴ�.
	 * �����Ͽ� ������� ��� �̹����� output_vector�� �����մϴ�.
	 *
	 * Q�� ��� �Ƕ�̵� �̹����� �����Դϴ�. Q����ŭ �ٿ���ϸ��� �����ϸ� �˴ϴ�.
	 */
	 // ** ���ݺ��� �ڵ带 �ۼ��ϼ���. �� ���� ����ø� �� �˴ϴ� **
	cv::Mat temp;
	input_mat.copyTo(temp);

	for (int q = 0; q < Q; ++q) {
		cv::Mat dst(cv::Size(width / 2, height / 2), CV_8UC1);

		for (int h = 0; h < dst.rows; ++h) {
			for (int w = 0; w < dst.cols; ++w) {

				double sum = 0;
				for (int mY = -2; mY < 3; ++mY) {
					int idxY = (h * 2) + mY;
					if (idxY < 0)
						idxY = 0;
					if (idxY >= temp.rows)
						idxY = temp.rows - 1;

					for (int mX = -2; mX < 3; ++mX) {

						int idxX = (w * 2) + mX;
						if (idxX < 0)
							idxX = 0;
						if (idxX >= temp.cols)
							idxX = temp.cols - 1;

						sum += (temp.at<uchar>(idxY, idxX) * weight[2 + mY][2 + mX]);

					}
				}
				dst.at<uchar>(h, w) = cv::saturate_cast<uchar>(sum);
			}
		}
		output_vector.push_back(dst);
		dst.copyTo(temp);

		width = width / 2;
		height = height / 2;
	}
	
	// ** ������� �ڵ带 �ۼ��ϼ���. �� ���� ����ø� �� �˴ϴ� **
}

int main()
{
	std::vector<cv::Mat> octave_image;
	cv::Mat original_image;
	original_image = cv::imread("cat.bmp", cv::IMREAD_GRAYSCALE);

	getSimpleDownscaledPyramid(4, original_image, octave_image);  // ó���� �ּ�ó���Ǿ� �־���, �ּ�ó�� ���� �� �ٽ� �غ�
	getWeightPyramid(4, original_image, octave_image);

	int idx = 0;
	for (auto& v : octave_image)
	{
		std::string str = std::to_string(idx++);
		cv::namedWindow(str.c_str(), cv::WINDOW_NORMAL);
		cv::imshow(str.c_str(), v);
		cv::resizeWindow(str.c_str(), cv::Size(640, 360));

		// �̹����� ���Ϸ� �����Ѵ�.
		cv::imwrite("cat_q" + std::to_string(idx) + ".bmp", v);
	}
	cv::waitKey();

	return 0;

};