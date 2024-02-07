#pragma once
#include"FileData.h"

class DataGraph:public File_
{
public:	
	static void showdata(double dataX[], double dataY[], int n, long color, PLOTAREA p);
	static void showhisto(double result[], int n, PLOTAREA area);
	static void showpinfo(class File_* f, PLOTAREA farea);
	static double fx(double x, double coeffs[], int degree);
};

