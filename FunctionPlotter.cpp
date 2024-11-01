#include "FunctionPlotter.h"

FunctionPlotter::FunctionPlotter(int width, int height)
{
    // 初始化图像大小
    image = cv::Mat::zeros(height, width, CV_8UC3); // 创建黑色图像
    this->width = width;
    this->height = height;
    // 设置坐标系中线的中心位置
    origin_x = width / 2;
    origin_y = height / 2;
    image.setTo(cv::Scalar(255, 255, 255));//set image to white
}
void FunctionPlotter::drawAxes()
{
    // 绘制 X 轴
    cv::line(image, cv::Point(0, origin_y), cv::Point(width, origin_y), cv::Scalar(0, 0, 0), 1);
    // 绘制 Y 轴
    cv::line(image, cv::Point(origin_x, 0), cv::Point(origin_x, height), cv::Scalar(0, 0, 0), 1);
}
void FunctionPlotter::plotFunction(double (*func)(double), double x_start, double x_end, double step)
{
    for (double x = x_start; x <= x_end; x += step) {
        double y = func(x);
        int x_pixel = static_cast<int>(origin_x + x * 20); // 缩放 x 值
        int y_pixel = static_cast<int>(origin_y - y * 20); // 缩放 y 值，注意Y轴反向

        if (x_pixel >= 0 && x_pixel < width && y_pixel >= 0 && y_pixel < height) {
            image.at<cv::Vec3b>(y_pixel, x_pixel) = cv::Vec3b(0, 255, 0); // 绘制点（红色）
        }
    }
    drawAxes();
}
void FunctionPlotter::plotFunction(std::vector<double> values, double step) {
    for (int i = 0; i < values.size(); i++) {
        double y = values[i];
        int x_pixel = static_cast<int>(origin_x + i * step); // 缩放 x 值
        int y_pixel = static_cast<int>(origin_y - y); // 缩放 y 值，注意Y轴反向

        if (x_pixel >= 0 && x_pixel < width && y_pixel >= 0 && y_pixel < height) {
            image.at<cv::Vec3b>(y_pixel, x_pixel) = cv::Vec3b(255, 0, 0); // 绘制点（红色）
        }
    }
    drawAxes();
};
void FunctionPlotter::showImage(const std::string& window_name)
{
    cv::imshow(window_name, image);
    cv::waitKey(0);
}
void FunctionPlotter::saveImage(const std::string& filename) 
{
    cv::imwrite(filename, image);
}
void FunctionPlotter::clear() {
    image = cv::Mat::zeros(height, width, CV_8UC3); // 重置图像
    drawAxes();
}
