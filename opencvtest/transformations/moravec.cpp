#include <algorithm>
#include "moravec.hpp"

transformations::Moravec::Moravec(cv::InputArray& original_image)
{
	cv::Mat src = original_image.getMat();
	confidence_map.create(src.size(), CV_32FC1);

	// �ܰ� 2�� �ȼ��� Confidence�� 0���� ����
	for (int w = 0; w < src.cols; ++w)
	{
		confidence_map.at<float>(0, w) = 0.0;
		confidence_map.at<float>(1, w) = 0.0;
		confidence_map.at<float>(src.rows - 1, w) = 0.0;
		confidence_map.at<float>(src.rows - 2, w) = 0.0;
	}

	for (int h = 0; h < src.rows; ++h)
	{
		confidence_map.at<float>(h, 0) = 0.0;
		confidence_map.at<float>(h, 1) = 0.0;
		confidence_map.at<float>(h, src.cols - 1) = 0.0;
		confidence_map.at<float>(h, src.cols - 2) = 0.0;
	}
}


void transformations::Moravec::FindConfidenceMap(cv::InputArray& original_image)
{
	cv::Mat src = original_image.getMat();
	
	/**
	 * src�� �̿��Ͽ� ��� �˰����� Confidence�� ����� ��
	 * �̸� confidence_map�� �����ϼ���.
	 * (confidence_map�� Ŭ���� ��� ������ ����Ǿ� �ֽ��ϴ�.)
	 */
	// ** ���ݺ��� �ڵ带 �ۼ��ϼ���. �� ���� ����ø� �� �˴ϴ� **

	// ** ������� �ڵ带 �ۼ��ϼ���. �� ���� ����ø� �� �˴ϴ� **
}


void transformations::Moravec::DrawFeature(cv::OutputArray& result_image)
{
	cv::Mat dst = result_image.getMat();

	for (int h = 0; h < confidence_map.rows; ++h)
	{
		for (int w = 0; w < confidence_map.cols; ++w)
		{
			if (confidence_map.at<float>(h, w) >= 15000)
			{
				cv::circle(dst, cv::Point(w, h), 3, cv::Scalar(255, 0, 0));
			}
		}
	}
}