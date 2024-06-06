// CircularSplit.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
#include <opencv2/opencv.hpp>  
#include <opencv2/core/core.hpp>  
#include <opencv2/highgui/highgui.hpp>  
#include <opencv2/imgproc.hpp>  
#include<iostream>
#include <cmath>
#include<fstream>
#include <stdio.h>
#include<vector>
#include <ctime>
#include <math.h>
#include <stdlib.h>
#include<assert.h>
#include<vector>
using namespace std;
using namespace cv;

#define Pi 3.141593
#define N 200
#define M 200
#define scale 0.5

struct City
{
    double x;  //x坐标
    double y;  //y坐标
    double angle;    //角度
    double distance; //极径
    double demand;   //需求
    double ready;    //开启时间
    double due;      //关闭时间
    double service;  //服务时间
};

Point p[N];      //绘图坐标点
City city[N];    //存储城市坐标

//**************************************************************************************************************************************************
void drawArrow(cv::Mat& img, cv::Point pStart, cv::Point pEnd, int len, int alpha, cv::Scalar color, int thickness, int lineType)
{
    const double PI = 3.1415926;
    Point arrow;
    //计算 θ 角（最简单的一种情况在下面图示中已经展示，关键在于 atan2 函数，详情见下面）   
    double angle = atan2((double)(pStart.y - pEnd.y), (double)(pStart.x - pEnd.x));

    line(img, pStart, pEnd, color, thickness, lineType);

    //计算箭角边的另一端的端点位置（上面的还是下面的要看箭头的指向，也就是pStart和pEnd的位置） 
    arrow.x = pEnd.x + len * cos(angle + PI * alpha / 180);

    arrow.y = pEnd.y + len * sin(angle + PI * alpha / 180);

    line(img, pEnd, arrow, color, thickness, lineType);

    arrow.x = pEnd.x + len * cos(angle - PI * alpha / 180);

    arrow.y = pEnd.y + len * sin(angle - PI * alpha / 180);

    line(img, pEnd, arrow, color, thickness, lineType);
}
void CreatRoute(vector<int> route) {
    RNG rng(12345);
    int b = rng.uniform(0, 255);
    int g = rng.uniform(0, 255);
    int r = rng.uniform(0, 255);
    Mat src(800, 800, CV_8UC3, cv::Scalar(255, 255, 255));
    for (int i = 0; i < route.size(); i++) {
        circle(src, p[route[i]], 2, Scalar(0, 0, 0), 2);
        //string num = to_string(route[i]);
        //putText(src, num, p[route[i]], FONT_HERSHEY_PLAIN, 1, (255, 255, 255), 1, LINE_AA);
    }
    for (int i = 1; i < route.size(); i++) {
        if (route[i - 1] == 0) {
            b = rng.uniform(0, 255);
            g = rng.uniform(0, 255);
            r = rng.uniform(0, 255);
        }
        //arrowedLine(src, p[route[i - 1]], p[route[i]], Scalar(0, 0, 0), 2);
        drawArrow(src, p[route[i - 1]], p[route[i]], 12, 30, cv::Scalar(b, g, r), 2, 8);
        string num = to_string(route[i]);
        putText(src, num, p[route[i]], FONT_HERSHEY_PLAIN, 1, Scalar(b, g, r), 1, LINE_AA);
    }
    imwrite("src.jpg", src);
    cv::Mat image_fliped;
    cv::flip(src, image_fliped, 0);
    imshow("巡回路径", image_fliped);
    waitKey(0);
}

