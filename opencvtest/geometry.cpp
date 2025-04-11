/*
 * ����4: Rotation using Homogeneous Matrix
 */

#include "geometry.hpp"
#include "opencv2\opencv.hpp"

void GeometryTransformator::ForwardTransformation(cv::InputArray& srcMat, cv::OutputArray& dstMat)
{
    if (!hasMatrixSet)
        throw "���� ����� ���ǵ��� �ʾҽ��ϴ�. ���� ����� ���� �������ּ���.";

    cv::Mat input_image, output_image;

    // ���ڷκ��� Mat �̹��� �ε�
    input_image = srcMat.getMat();
    if (dstMat.empty())
        dstMat.create(input_image.size(), input_image.type());
    output_image = dstMat.getMat();

    /**
     * input_image�� �̹����� Forward Tranformation�ϴ� �ڵ带 �����ϼ���.
     * input_image�� H ������ �̿��Ͽ� Transformation�ϰ�, ����� output_image�� �����ϼ���.
     */
     // ** ���ݺ��� �ڵ带 �ۼ��ϼ���. �� ���� ����ø� �� �˴ϴ� **
    int y_target, x_target = 0;
    float cord_array[3];
    for (int y = 0; y < input_image.rows; y++) {
        for (int x = 0; x < input_image.cols; x++) {
            y_target = 0;
            x_target = 0;

            cord_array[0] = y;
            cord_array[1] = x;
            cord_array[2] = 1;

            for (int dx = 0; dx < 3; dx++) {
                y_target += cord_array[dx] * H[dx][0];
                x_target += cord_array[dx] * H[dx][1];
            }

            if (0 <= x_target && x_target < output_image.cols &&
                0 <= y_target && y_target < output_image.rows) {
                output_image.at<uchar>(y_target, x_target) = input_image.at<uchar>(y, x);
            }
        }
    }

    // ** ������� �ڵ带 �ۼ��ϼ���. �� ���� ����ø� �� �˴ϴ� **

}

void GeometryTransformator::BackwardTransformation(cv::InputArray& srcMat, cv::OutputArray& dstMat)
{
    if (!hasMatrixSet)
        throw "���� ����� ���ǵ��� �ʾҽ��ϴ�. ���� ����� ���� �������ּ���.";

    cv::Mat input_image, output_image;

    // ���ڷκ��� Mat �̹��� �ε�
    input_image = srcMat.getMat();
    if (dstMat.empty())
        dstMat.create(input_image.size(), input_image.type());
    output_image = dstMat.getMat();

    double H_inverse[3][3] = {};
    InverseHmatrix(H_inverse);

    /**
     * input_image�� �̹����� Backward Tranformation�ϴ� �ڵ带 �����ϼ���.
     * input_image�� H_inverse ������ �̿��Ͽ�
     * GeometryTransformator::ForwardTransformation�� �����ϰ� �����ϸ� �˴ϴ�.
     */
     // ** ���ݺ��� �ڵ带 �ۼ��ϼ���. �� ���� ����ø� �� �˴ϴ� **


    int y_target, x_target = 0;
    float cord_array[3];
    for (int y = 0; y < input_image.rows; y++) {
        for (int x = 0; x < input_image.cols; x++) {
            y_target = 0;
            x_target = 0;

            cord_array[0] = y;
            cord_array[1] = x;
            cord_array[2] = 1;

            for (int dx = 0; dx < 3; dx++) {
                y_target += cord_array[dx] * H_inverse[dx][0];
                x_target += cord_array[dx] * H_inverse[dx][1];
            }

            if (0 <= x_target && x_target < input_image.cols &&
                0 <= y_target && y_target < input_image.rows) {
                output_image.at<uchar>(y, x) = input_image.at<uchar>(y_target, x_target);
            }
        }
    }
    // ** ������� �ڵ带 �ۼ��ϼ���. �� ���� ����ø� �� �˴ϴ� **
}

void GeometryTransformator::SetMoveMatrix(double y, double x)
{
    ClearMatrix();

    H[0][0] = 1;
    H[1][1] = 1;
    H[2][0] = y;
    H[2][1] = x;
    H[2][2] = 1;

    hasMatrixSet = true;
}

void GeometryTransformator::SetRotateMatrix(double degree)
{
    ClearMatrix();

    /**
     * 3*3 ��� ���� H�� �̵� ���� ����� �ۼ��ϼ���.
     * ������ ���ڸ��� ���� �Ҵ��ϸ� �˴ϴ�.
     * cos() �Լ��� sin() �Լ��� ���ڴ� degree�� �ƴ� radian�� �Է¹޴� ���� �����ϰ�
     * PI ������ Ȱ���Ͽ� ��ȯ�մϴ�.
     */

     // ** ���ݺ��� �ڵ带 �ۼ��ϼ���. �� ���� ����ø� �� �˴ϴ� **
    H[0][0] = cos(degree * PI / 180.0);
    H[0][1] = -sin(degree * PI / 180.0);
    H[1][0] = sin(degree * PI / 180.0);
    H[1][1] = cos(degree * PI / 180.0);
    H[2][2] = 1;

    // ** ������� �ڵ带 �ۼ��ϼ���. �� ���� ����ø� �� �˴ϴ� **

    hasMatrixSet = true;
}

void GeometryTransformator::InverseHmatrix(double result[3][3])
{
    double determinant = 0;

    for (int i = 0; i < 3; i++)
        determinant += (H[0][i] * (H[1][(i + 1) % 3] * H[2][(i + 2) % 3] - H[1][(i + 2) % 3] * H[2][(i + 1) % 3]));

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            result[i][j] = (
                (H[(j + 1) % 3][(i + 1) % 3] * H[(j + 2) % 3][(i + 2) % 3]) -
                (H[(j + 1) % 3][(i + 2) % 3] * H[(j + 2) % 3][(i + 1) % 3])
                ) / determinant;
        }
    }
}

void GeometryTransformator::ClearMatrix()
{
    memset(H, 0, sizeof(H));
    hasMatrixSet = false;
}
