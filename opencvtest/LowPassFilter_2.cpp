#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

// 3x3 Low Pass Filter ���� �Լ�
void applyLowPassFilter(const Mat& input, Mat& output) {
    output = input.clone(); // ���� ũ�� ����
    int kernel[3][3] = {
        {1, 1, 1},
        {1, 1, 1},
        {1, 1, 1}
    };

    int kernelSize = 3;
    int sumKernel = 9;

    // �����ڸ��� ������ ������ ���� ���� ����
    for (int y = 1; y < input.rows - 1; y++) {
        for (int x = 1; x < input.cols - 1; x++) {
            Vec3i sum = { 0, 0, 0 };

            // 3x3 ���� ����
            for (int ky = -1; ky <= 1; ky++) {
                for (int kx = -1; kx <= 1; kx++) {
                    Vec3b pixel = input.at<Vec3b>(y + ky, x + kx);
                    sum[0] += pixel[0] * kernel[ky + 1][kx + 1]; // Blue
                    sum[1] += pixel[1] * kernel[ky + 1][kx + 1]; // Green
                    sum[2] += pixel[2] * kernel[ky + 1][kx + 1]; // Red
                }
            }

            // ��հ� ����
            output.at<Vec3b>(y, x) = Vec3b(sum[0] / sumKernel, sum[1] / sumKernel, sum[2] / sumKernel);
        }
    }
}

//int main() {
//    string inputFile = "salt_pepper.bmp";
//    string outputFile = "salt_pepper_lpf.bmp";
//
//    // �̹��� �б�
//    Mat inputImage = imread(inputFile);
//    if (inputImage.empty()) {
//        cerr << "Error: Could not open or find the image!" << endl;
//        return -1;
//    }
//
//    // Low Pass Filter ����
//    Mat outputImage;
//    applyLowPassFilter(inputImage, outputImage);
//
//    // ��� ����
//    imwrite(outputFile, outputImage);
//    cout << "Saved: " << outputFile << endl;
//
//    return 0;
//}
