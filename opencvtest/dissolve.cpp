#include <iostream>
#include <opencv2/opencv.hpp>

//int main() {
//	cv::Mat dissolve_from, dissolve_to, result_image;
//
//	dissolve_from = cv::imread("./cat.bmp", cv::IMREAD_COLOR);
//	dissolve_to = cv::imread("./tibetfox.bmp", cv::IMREAD_COLOR);
//
//	if (dissolve_from.empty() || dissolve_to.empty()) {
//		std::cerr << "fail" << std::endl;
//		return -1;
//	}
//
//	if (dissolve_from.size() != dissolve_to.size()) {
//		cv:resize(dissolve_to, dissolve_to, dissolve_from.size());
//	}
//
//	result_image.create(cv::Size(dissolve_from.cols, dissolve_from.rows), CV_8UC3);
//
//	float alpha;
//
//	for (int alpha_ten_iteration = 10; alpha_ten_iteration >= 0; alpha_ten_iteration--) {
//		alpha = float(alpha_ten_iteration) / 10.0;
//
//		for (int y = 0; y < dissolve_from.rows; y++) {
//			for (int x = 0; x < dissolve_from.cols; x++) {
//				cv::Vec3b from_pixel = dissolve_from.at<cv::Vec3b>(y, x);
//				cv::Vec3b to_pixel = dissolve_to.at<cv::Vec3b>(y, x);
//
//				cv::Vec3b& result_pixel = result_image.at<cv::Vec3b>(y, x);
//				for (int c = 0; c < 3; ++c) {
//					result_pixel[c] = cv::saturate_cast<uchar>(alpha * from_pixel[c] + (1.0 - alpha) * to_pixel[c]);
//				}
//			}
//		}
//
//		std::cout << "alpha = " << alpha << std::endl;
//		cv::imshow("Result Image", result_image);
//		cv::waitKey(500);
//
//		if (alpha_ten_iteration == 7 || alpha_ten_iteration == 3) {
//			cv::imwrite("dissolve_" + std::to_string(alpha_ten_iteration) + ".jpg", result_image);
//		}
//
//	}
//
//	return 0;
//
//}