#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

void dissolveImages(const string& image1Path, const string& image2Path, float alpha, const string& outputPath) {
    // 이미지 읽기
    Mat img1 = imread(image1Path);
    Mat img2 = imread(image2Path);

    if (img1.empty() || img2.empty()) {
        cerr << "Error: Could not open or find the images!" << endl;
        return;
    }

    // 두 이미지가 동일한 크기인지 확인
    if (img1.size() != img2.size()) {
        cerr << "Error: Images must be the same size!" << endl;
        return;
    }

    // 디졸브 수행
    Mat result;
    addWeighted(img1, alpha, img2, 1 - alpha, 0.0, result);

    // 결과 저장
    imwrite(outputPath, result);

    cv::imshow("Original Image", result); 
    cout << "Saved: " << outputPath << endl;
}

//int main() {
//    string image1 = "cat.bmp";
//    string image2 = "tibetfox.bmp";
//
//    // 𝛼 = 0.3
//    dissolveImages(image1, image2, 0.3, "dissolve_3.bmp");
//
//    // 𝛼 = 0.7
//    dissolveImages(image1, image2, 0.7, "dissolve_7.bmp");
//
//    return 0;
//}
