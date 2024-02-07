#define _use_CRT_SECURE_NO_WARNINGS
#include "DataGraph.h"
#include"FileData.h"
#include<easyx.h>
#include<algorithm>
#include<string>

int COLOR[16] = { BLACK,BLUE,GREEN,CYAN,RED,MAGENTA,BROWN,LIGHTGRAY,DARKGRAY,LIGHTBLUE,LIGHTGREEN,LIGHTCYAN,LIGHTRED,LIGHTMAGENTA,YELLOW,WHITE };

//绘制折线图
void DataGraph::showdata(double dataX[], double dataY[], int n, long color, PLOTAREA p)
{
	int i;
	int x0, y1, height, width;
	double minX, scaleX, minY, scaleY;//获取x和y轴的坐标

	//  find the min and scale of the input array
	minX = arraymin(dataX, n);											
	scaleX = arrayscale(dataX, n);//确定x的最小值，确定x的取值范围		
	minY = arraymin(dataY, n);
	scaleY = arrayscale(dataY, n);//确定y的最小值，确定y的取值范围

	// Set the plot area; 设置绘图区域
	x0 = p.x0;y1 = p.y1;
	height = p.y1 - p.y0;width = p.x1 - p.x0;
	// Plot the graph
	setlinecolor(color);
	setlinestyle(PS_SOLID | PS_JOIN_BEVEL, 2);
	for (i = 0; i < n - 1 ; i++)
	{
		line(x0 + (dataX[i] - minX) / scaleX * width, y1 - (dataY[i] - minY) / scaleY * height, x0 + (dataX[i + 1] - minX) / scaleX * width, y1 - (dataY[i + 1] - minY) / scaleY * height);
	}

}

//绘制直方图
void DataGraph::showhisto(double result[], int n, PLOTAREA area)
{
	int i;
	double max;
	float xscale, yscale;
	max = result[1];
	for (i = 1; i < n; i++)
		if (max < result[i]) max = result[i];
	xscale = (area.x1 - area.x0) / (float)n;
	yscale = (area.y1 - area.y0) / (float)max;
	for (i = 1; i <= n; i++)
	{
		setfillcolor(COLOR[i + 1]);
		solidrectangle(area.x0 + i * xscale, area.y1, area.x0 + (i + 1) * xscale, area.y1 - result[i] * yscale);
	}
}

void DataGraph::showpinfo(class File_* f, PLOTAREA farea)
{
	// need to set the project properties to MBCS	
	settextcolor(WHITE);
	outtextxy(farea.x0, farea.y0, "Filename: ");
	outtextxy(textwidth("Filename: "), farea.y0, f->filename_.c_str());
	
	outtextxy(farea.x0, farea.y0 + 30, "Row of Data: ");
	char str[20]; 
	sprintf_s(str, "%d", f->row_);
	outtextxy(textwidth("Row of Data: "), farea.y0 + 30, str);
	
	sprintf_s(str, "%d", f->OptiOrder_);
	outtextxy(farea.x0, farea.y0 + 60, "Default OptiOrder is: ");
	outtextxy(textwidth("Default OptiOrder is: "), farea.y0 + 60, str);
	
	sprintf_s(str, "%lf", f->fitError_[f->OptiOrder_]);
	outtextxy(farea.x0, farea.y0 + 90, "Overall fiterrror is: ");
	outtextxy(farea.x0, farea.y0 + 120,str);
}

double DataGraph::fx(double x, double coeffs[], int degree)
{
	double result = 0;
	int i;
	for (i = 0; i <= degree; ++i) {
		result += coeffs[i] * pow(x, degree - i);
	}
	return result;
}


