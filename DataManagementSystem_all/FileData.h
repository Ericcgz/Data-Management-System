#pragma once
#include <vector>
#include<iostream>
#include"widgets/pushButton.h"
#include"widgets/BasicWidget.h"

class File_
{
public:
	std::string filename_;     //文件名
	int row_;                  //数据的条数
	double polyCoeff_[10][10]; //不同阶次多项式拟合
	double fitError_[10];      //不同阶次多项式拟合误差
	int MaxOrder_;             //最高拟合阶数-用户输入
	int OptiOrder_;			   //最佳拟合阶数
	double mean_;			   //均值
	double variance_;		   //方差
	std::string status_;			   //状态
	double data_[1100];        //总体数据
	double data_x[550];	   //数据横坐标
	double data_y[550];       //数据纵坐标
	double maxData_x;          //数据横坐标的最大值
	double maxData_y;		   //数据纵坐标的最大值
	double minData_x;          //数据横坐标的最小值
	double minData_y;          //数据纵坐标的最小值

	//构造函数
	File_();
	File_(std::string filename);
	void display();

	std::string file_formatInfo();
	
	//文件数据的读取
	void readData();
	//基本数据的处理
	void ProcessData_();
	//对于数据坐标进行排序
	void PositionSort_(double x[],double y[],int n);
	//平滑
	void mafilter(double a[], int n, int size);

	void SetOptiOrder_(int n);

public:	//数组基本处理
	static double mean(double a[], int n);//数据的均值       
	static double variance(double a[], int n);//数据方差	  
	static void arraycopy(double target[], double source[], int n);//数组拷贝 	
	static void arraysub(double x[], double y[], double z[], int n);// z=x-y;	
	static double arraymax(double a[], int n);//数组最大值
	static double arraymin(double a[], int n);//数组最小值
	static double arrayscale(double a[], int n);//数组的数值范围
public:
	static void polyfit(int n, double x[], double y[], int poly_n, double p[]);
/*============================================================*/
    //高斯消元法计算得到	n 次多项式的系数
    //n: 系数的个数
    //ata: 线性矩阵
    //sumxy: 线性方程组的Y值
    //p: 返回拟合的结果
/*============================================================*/
	static void gauss_solve(int n, double A[], double x[], double b[]);
	static void reverseP(double arr[], int size);
};

typedef struct
{
	int x0, y0, x1, y1;  // top left point and the bottom right point
}PLOTAREA; //绘图区域