#pragma once
#include <opencv2/opencv.hpp>  
#include <opencv2/core/core.hpp>  
#include <opencv2/highgui/highgui.hpp>  
#include <opencv2/imgproc.hpp> 
#include <iostream>
#include <cmath>


class FunctionPlotter
{
private:
    cv::Mat image; // 存储图像
    int width;     // 图像宽度
    int height;    // 图像高度
    int origin_x;  // X 轴原点
    int origin_y;  // Y 轴原点
public:
    FunctionPlotter(int width, int height);
    void drawAxes();
    void plotFunction(double (*func)(double), double x_start, double x_end, double step);
    void plotFunction(std::vector<double> values, double step);
    void showImage(const std::string& window_name);
    void saveImage(const std::string& filename);
    void clear();
};
