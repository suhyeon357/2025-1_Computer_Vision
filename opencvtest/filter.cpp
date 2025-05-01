/*
 * ����9: LOG (Laplacian of Gaussian)
 */

#include "filter.hpp"

Filter::~Filter()
{
	if (mask != nullptr)
	{
		for (int i = 0; i < maskSize; ++i)
		{
			delete[] mask[i];
		}
		delete[] mask;
	}
}

void Filter::AllocateMask()
{
	mask = new double* [maskSize];

	for (int i = 0; i < maskSize; ++i)
	{
		mask[i] = new double[maskSize] { 0.0, };
	}
}

void Filter::Convolute(cv::InputArray& input_image, cv::OutputArray& output_image)
{
	output_image.create(input_image.size(), CV_32FC1);

	cv::Mat input_mat = input_image.getMat();
	cv::Mat output_mat = output_image.getMat();

	int halfSize = maskSize / 2;
	for (int y = halfSize; y < input_mat.rows - halfSize; y++)
	{
		for (int x = halfSize; x < input_mat.cols - halfSize; x++)
		{
			double sum = 0;

			for (int dy = -halfSize; dy <= halfSize; ++dy)
				for (int dx = -halfSize; dx <= halfSize; ++dx)
					sum += input_mat.at<uchar>(y + dy, x + dx) * mask[dy + halfSize][dx + halfSize];

			output_mat.at<float>(y, x) = sum;
		}
	}
}

void LOG::CreateMask()
{
	CreateMask(2.0);
}

void LOG::CreateMask(double sigma)
{
	maskSize = 6 * sigma;
	if (maskSize % 2 == 0)
		++maskSize;

	AllocateMask();

	/**
	 * LOG ���͸� �����մϴ�.
	 * �־��� sigma ���� ���� maskSize * maskSize ũ���� ���͸� �����մϴ�.
	 * ���ϴ� ����� PPT�� ���� p.124~130�� �����ϼ���.
	 */
	// ** ���ݺ��� �ڵ带 �ۼ��ϼ���. �� ���� ����ø� �� �˴ϴ� **
	int half = maskSize / 2;
	double sigma2 = sigma * sigma;
	double sigma4 = sigma2 * sigma2;
	double pi = 3.141592;

	for (int y = -half; y <= half; ++y)
	{
		for (int x = -half; x <= half; ++x)
		{
			double r2 = x * x + y * y;
			double value = (r2 - 2 * sigma2) / sigma4;
			value *= exp(-r2 / (2 * sigma2));
			value /= (pi * sigma4);

			mask[y + half][x + half] = value;
		}
	}
	// ** ������� �ڵ带 �ۼ��ϼ���. �� ���� ����ø� �� �˴ϴ� **
}

void LOG::FindZeroCrossing(cv::InputArray& input_image, cv::OutputArray& output_image)
{
	output_image.create(input_image.size(), CV_8UC1);

	cv::Mat input_mat = input_image.getMat();
	cv::Mat output_mat = output_image.getMat();
	output_mat.setTo(cv::Scalar(0));

	/**
	 * ������ �˰����� �����ϼ���.
	 * �־��� n0�� ����, n1~n7������ �����ϰ�
	 * ��ȣ�� Ȯ���Ͽ� cnt���� ������ŵ�ϴ�.
	 * 
	 * cnt���� �Ӱ�ġ�� 2�� �ΰ�, �Ӱ�ġ �̻��� ��� ���� output_mat�� 255�� �Ҵ��ϼ���.
	 */
	// ** ���ݺ��� �ڵ带 �ۼ��ϼ���. �� ���� ����ø� �� �˴ϴ� **
	for (int y = 1; y < input_mat.rows - 1; ++y)
	{
		for (int x = 1; x < input_mat.cols - 1; ++x)
		{
			int cnt = 0;
			float n0 = input_mat.at<float>(y, x + 1);

			float n1 = input_mat.at<float>(y + 1, x + 1);
			float n2 = input_mat.at<float>(y + 1, x);
			float n3 = input_mat.at<float>(y + 1, x - 1);

			float n4 = input_mat.at<float>(y, x - 1);

			float n5 = input_mat.at<float>(y - 1, x - 1);
			float n6 = input_mat.at<float>(y - 1, x);
			float n7 = input_mat.at<float>(y - 1, x + 1);

			if (CheckSign(n0) != CheckSign(n4))
				if (CheckSign(n0) != 0 && CheckSign(n4) != 0)
					cnt++;

			if (CheckSign(n1) != CheckSign(n5))
				if (CheckSign(n1) != 0 && CheckSign(n5) != 0)
					cnt++;

			if (CheckSign(n2) != CheckSign(n6))
				if (CheckSign(n2) != 0 && CheckSign(n6) != 0)
					cnt++;

			if (CheckSign(n3) != CheckSign(n7))
				if (CheckSign(n3) != 0 && CheckSign(n7) != 0)
					cnt++;

			if (cnt >= 2)
				output_mat.at<uchar>(y, x) = 255;
		}
	}
	// ** ������� �ڵ带 �ۼ��ϼ���. �� ���� ����ø� �� �˴ϴ� **
}

int LOG::CheckSign(const float& value)
{
	/**
	 * value�� ��ȣ�� �����ϴ� �ڵ带 �ۼ��ϼ���.
	 * ���� 0�� ��쵵, 0���� return�ϵ��� �ϼ���.
	 */
	// ** ���ݺ��� �ڵ带 �ۼ��ϼ���. �� ���� ����ø� �� �˴ϴ� **
	if (value == 0)
		return 0;
	else if (value > 0)
		return 1;
	else
		return -1;
	// ** ������� �ڵ带 �ۼ��ϼ���. �� ���� ����ø� �� �˴ϴ� **
}