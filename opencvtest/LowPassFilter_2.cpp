#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

// 3x3 Low Pass Filter 적용 함수
void applyLowPassFilter(const Mat& input, Mat& output) {
    output = input.clone(); // 원본 크기 유지
    int kernel[3][3] = {
        {1, 1, 1},
        {1, 1, 1},
        {1, 1, 1}
    };

    int kernelSize = 3;
    int sumKernel = 9;

    // 가장자리를 제외한 영역에 대해 필터 적용
    for (int y = 1; y < input.rows - 1; y++) {
        for (int x = 1; x < input.cols - 1; x++) {
            Vec3i sum = { 0, 0, 0 };

            // 3x3 필터 적용
            for (int ky = -1; ky <= 1; ky++) {
                for (int kx = -1; kx <= 1; kx++) {
                    Vec3b pixel = input.at<Vec3b>(y + ky, x + kx);
                    sum[0] += pixel[0] * kernel[ky + 1][kx + 1]; // Blue
                    sum[1] += pixel[1] * kernel[ky + 1][kx + 1]; // Green
                    sum[2] += pixel[2] * kernel[ky + 1][kx + 1]; // Red
                }
            }

            // 평균값 적용
            output.at<Vec3b>(y, x) = Vec3b(sum[0] / sumKernel, sum[1] / sumKernel, sum[2] / sumKernel);
        }
    }
}

//int main() {
//    string inputFile = "salt_pepper.bmp";
//    string outputFile = "salt_pepper_lpf.bmp";
//
//    // 이미지 읽기
//    Mat inputImage = imread(inputFile);
//    if (inputImage.empty()) {
//        cerr << "Error: Could not open or find the image!" << endl;
//        return -1;
//    }
//
//    // Low Pass Filter 적용
//    Mat outputImage;
//    applyLowPassFilter(inputImage, outputImage);
//
//    // 결과 저장
//    imwrite(outputFile, outputImage);
//    cout << "Saved: " << outputFile << endl;
//
//    return 0;
//}
