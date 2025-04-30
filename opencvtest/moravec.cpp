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
	std::vector<cv::Point> directions = {
		{0, 1}, 
		{0, -1}, 
		{1, 0},
		{-1, 0} 
	};

	for (int y = 1; y < src.rows - 1; ++y)
	{
		for (int x = 1; x < src.cols - 1; ++x)
		{
			float min_ssd = FLT_MAX;

			for (const auto& dir : directions)
			{
				float ssd = 0.0f;

				for (int dy = -1; dy <= 1; ++dy)
				{
					for (int dx = -1; dx <= 1; ++dx)
					{
						int yy = y + dy;
						int xx = x + dx;
						int yy_shift = yy + dir.y;
						int xx_shift = xx + dir.x;

						if (yy_shift < 0 || yy_shift >= src.rows || xx_shift < 0 || xx_shift >= src.cols)
							continue;

						float diff = src.at<uchar>(yy, xx) - src.at<uchar>(yy_shift, xx_shift);
						ssd += diff * diff;
					}
				}

				min_ssd = std::min(min_ssd, ssd);
			}

			confidence_map.at<float>(y, x) = min_ssd;
		}
	}

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