/*
 * ����6: Moravec
 * -> "transformations/moravec.hpp" ����
 */

#include "moravec.hpp"
#include "opencv2/opencv.hpp"
void main()
{
	/// Load image
	cv::Mat bucks = imread("bucks.jpg", cv::IMREAD_GRAYSCALE);
	
	transformations::Moravec moravaec(bucks);
	moravaec.FindConfidenceMap(bucks);

	cv::Mat result_image;

	cv::cvtColor(bucks, result_image, cv::COLOR_GRAY2BGR);
	moravaec.DrawFeature(result_image);

	cv::imshow("Original Image", bucks);
	cv::imshow("Result Image", result_image);
	cv::waitKey();

}
