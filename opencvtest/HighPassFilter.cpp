#include <iostream>
#include <opencv2/opencv.hpp>

//int main() {
//    cv::Mat original_img, result_img;
//
//    original_img = cv::imread("./tibetfox.bmp", cv::IMREAD_GRAYSCALE);
//    result_img.create(cv::Size(original_img.cols - 2, original_img.rows - 2), CV_8UC1);
//
//    float LPF[3][3] = {
//        {-1, -1, -1},
//        {-1, 8, -1},
//        {-1, -1, -1}
//    };
//
//    for (int y = 0; y < result_img.rows; y++) {
//        for (int x = 0; x < result_img.cols; x++) {
//            float sum = 0;
//            for (int dy = 0; dy <= 2; dy++) {
//                for (int dx = 0; dx <= 2; dx++) {
//                    sum += original_img.at<uchar>(y + dy, x + dx) * LPF[dy][dx];
//                }
//            }
//            result_img.at<uchar>(y, x) = cv::saturate_cast<uchar>(sum);
//        }
//    }
//
//    cv::imshow("original Image", original_img);
//    cv::imshow("result Image", result_img);
//    cv::waitKey(0);
//
//    cv::imwrite("tibetfox_hpf.jpg", result_img);
//
//    return 0;
//
//}
