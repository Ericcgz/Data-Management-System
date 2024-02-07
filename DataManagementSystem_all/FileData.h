#pragma once
#include <vector>
#include<iostream>
#include"widgets/pushButton.h"
#include"widgets/BasicWidget.h"

class File_
{
public:
	std::string filename_;     //�ļ���
	int row_;                  //���ݵ�����
	double polyCoeff_[10][10]; //��ͬ�״ζ���ʽ���
	double fitError_[10];      //��ͬ�״ζ���ʽ������
	int MaxOrder_;             //�����Ͻ���-�û�����
	int OptiOrder_;			   //�����Ͻ���
	double mean_;			   //��ֵ
	double variance_;		   //����
	std::string status_;			   //״̬
	double data_[1100];        //��������
	double data_x[550];	   //���ݺ�����
	double data_y[550];       //����������
	double maxData_x;          //���ݺ���������ֵ
	double maxData_y;		   //��������������ֵ
	double minData_x;          //���ݺ��������Сֵ
	double minData_y;          //�������������Сֵ

	//���캯��
	File_();
	File_(std::string filename);
	void display();

	std::string file_formatInfo();
	
	//�ļ����ݵĶ�ȡ
	void readData();
	//�������ݵĴ���
	void ProcessData_();
	//�������������������
	void PositionSort_(double x[],double y[],int n);
	//ƽ��
	void mafilter(double a[], int n, int size);

	void SetOptiOrder_(int n);

public:	//�����������
	static double mean(double a[], int n);//���ݵľ�ֵ       
	static double variance(double a[], int n);//���ݷ���	  
	static void arraycopy(double target[], double source[], int n);//���鿽�� 	
	static void arraysub(double x[], double y[], double z[], int n);// z=x-y;	
	static double arraymax(double a[], int n);//�������ֵ
	static double arraymin(double a[], int n);//������Сֵ
	static double arrayscale(double a[], int n);//�������ֵ��Χ
public:
	static void polyfit(int n, double x[], double y[], int poly_n, double p[]);
/*============================================================*/
    //��˹��Ԫ������õ�	n �ζ���ʽ��ϵ��
    //n: ϵ���ĸ���
    //ata: ���Ծ���
    //sumxy: ���Է������Yֵ
    //p: ������ϵĽ��
/*============================================================*/
	static void gauss_solve(int n, double A[], double x[], double b[]);
	static void reverseP(double arr[], int size);
};

typedef struct
{
	int x0, y0, x1, y1;  // top left point and the bottom right point
}PLOTAREA; //��ͼ����