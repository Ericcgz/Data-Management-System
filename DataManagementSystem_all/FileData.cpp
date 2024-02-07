#include "FileData.h"
#include"DataGraph.h"
#include<fstream>
#include<string>
#include<sstream>
#include<iostream>

using namespace std;


File_::File_():row_(1000), MaxOrder_(9), OptiOrder_(6), mean_(0), variance_(0),maxData_x(0), maxData_y(0), minData_x(0), minData_y(0)
{
}

File_::File_(std::string filename) :filename_(filename)
		,row_(1000),MaxOrder_(9),OptiOrder_(6),mean_(0), variance_(0)
	    ,maxData_x(0), maxData_y(0), minData_x(0), minData_y(0)
{
	this->status_ = "N";
	memset(this->data_, 0, sizeof(double) * 1000);
}

void File_::display()
{
	cout<< this->filename_ << "\t" << this->mean_ << "\t" << this->variance_ << "\t" << this->row_ << "\t" << this->status_ << "\t" << this->OptiOrder_ << endl;
}

std::string File_::file_formatInfo()
{
	std::stringstream ff;
	ff << this->filename_ << "\t" << this->mean_ << "\t" << this->variance_ << "\t" << this->row_ << "\t" << this->status_ << "\t" << this->OptiOrder_ << endl;
	return ff.str();
}

void File_::readData()
{
	std::ifstream fin;
	fin.open(this->filename_, std::ios::in);
	if (!fin.is_open()) {
		cout << "无法找到文件:"<<this->filename_ << endl;
		return;
	}
	int i = 0;
	long double buf = 0;
	while (fin >> buf) //文件数据的读取
	{
		//cout << buf << endl;
		this->data_[i] = buf;
		i++;
	}
	this->row_ = i;
	fin.close();
}

void File_::ProcessData_()
{
	readData();//数据读取正常
	for (int i = 0; i < row_; i+=2) //将数据分为横纵坐标 x,y
	{
		this->data_x[(int)i / 2] = this->data_[i];
		this->data_y[(int)i / 2] = this->data_[i + 1];
	}
	PositionSort_(this->data_x, this->data_y, row_ / 2);

	this->mean_ = mean(data_, 1000);
	this->variance_ = variance(data_, row_);
	
	this->maxData_x = arraymax(data_x, row_/2);
	this->minData_x = arraymin(data_x, row_/2);
	this->maxData_y = arraymax(data_y, row_/2);
	this->minData_y = arraymin(data_y, row_/2);
	
	for (int order = 1; order <= this->MaxOrder_; order++)
	{
		File_::polyfit(this->row_ / 2, this->data_x, this->data_y, order, this->polyCoeff_[order]);
	}
	
	for (int order = 1; order <= this->MaxOrder_; order++)
	{
		double fity[1000] = { 0 };
		double fiterror = 0;
		for (int i = 0; i < this->row_ / 2; i++)
		{
			fity[i] = DataGraph::fx(this->data_x[i], this->polyCoeff_[order], order);//拟合点的纵坐标
			fiterror += (fity[i] - this->data_y[i]) * (fity[i] - this->data_y[i]);
		}
		this->fitError_[order] = fiterror;
	}

}

void File_::PositionSort_(double x[],double y[], int n)
{
	double t1 = 0,t2 = 0;
	for (int i = 0; i < n; i++) {
		for (int j = i+1; j < n; j++) {
			if (x[i] > x[j]) {
				t1 = x[i]; x[i] = x[j]; x[j] = t1;
				t2 = y[i]; y[i] = y[j]; y[j] = t2;
			}
		}
	}
}

double File_::mean(double a[], int n)
{
	double sum = 0; int i;
	for (i = 0; i < n; i++){
		sum = sum + a[i];
	}
	return sum / n;
}
double File_::variance(double a[], int n)
{
	float M, sum = 0;int i;
	M = mean(a, n);              //先算均值
	for (i = 0; i < n; i++){
		sum = sum + (a[i] - M) * (a[i] - M);
	}
	return sum / n;
}
double File_::arraymax(double a[], int n)
{
	double max;
	int i;
	max = a[0];
	for (i = 1; i < n; i++)
	{
		if (max < a[i]) max = a[i];
	}
	return max;
}
double File_::arraymin(double a[], int n)
{
	double min;
	int i;
	min = a[0];
	for (i = 1; i < n; i++)
	{
		if (min > a[i]) min = a[i];
	}
	return min;
}

void File_::mafilter(double a[], int n, int size)
{
	int i, j;
	float sum;
	for (i = size / 2; i < n - size / 2; i++){
		sum = 0;
		for (j = i - size / 2; j <= i + size / 2; j++){
			sum = sum + a[j];
		}
		a[i] = sum / size;
	}
}

void File_::SetOptiOrder_(int n)
{
	this->OptiOrder_ = n;
}

void File_::arraycopy(double target[], double source[], int n)
{
	int i;
	for (i = 0; i < n; i++){
		target[i] = source[i];
	}
}
void File_::arraysub(double x[], double y[], double z[], int n)
{
	int i;
	for (i = 0; i < n; i++){
		z[i] = x[i] - y[i];
	}
}
double File_::arrayscale(double a[], int n)
{
	return arraymax(a, n) - arraymin(a, n);
}

//n为数据一共多少个点 x[]为横坐标数组 y[]为纵坐标数组 poly_n为拟合的阶数，最高次阶数 p[]存到每个阶次的系数
void File_::polyfit(int n, double x[], double y[], int poly_n, double p[])
{
	int i, j;
	double* tempx, * tempy, * sumxx, * sumxy, * ata;

	tempx = (double*)calloc(n, sizeof(double));
	sumxx = (double*)calloc((poly_n * 2 + 1), sizeof(double));
	tempy = (double*)calloc(n, sizeof(double));
	sumxy = (double*)calloc((poly_n + 1), sizeof(double));
	ata = (double*)calloc((poly_n + 1) * (poly_n + 1), sizeof(double));

	for (i = 0; i < n; i++)
	{
		tempx[i] = 1;
		tempy[i] = y[i];
	}
	for (i = 0; i < 2 * poly_n + 1; i++)
	{
		for (sumxx[i] = 0, j = 0; j < n; j++)
		{
			sumxx[i] += tempx[j];
			tempx[j] *= x[j];
		}
	}
	for (i = 0; i < poly_n + 1; i++)
	{
		for (sumxy[i] = 0, j = 0; j < n; j++)
		{
			sumxy[i] += tempy[j];
			tempy[j] *= x[j];
		}
	}
	for (i = 0; i < poly_n + 1; i++)
	{
		for (j = 0; j < poly_n + 1; j++)
		{
			ata[i * (poly_n + 1) + j] = sumxx[i + j];
		}
	}
	
	gauss_solve(poly_n + 1, ata, p, sumxy);
	reverseP(p, poly_n);

	free(tempx);free(sumxx);free(tempy);free(sumxy);free(ata);	//释放动态分配的内存。	
}
//n表示需要解出来的系数个数，比多项式的最高次大1，A[]表示线性矩阵（ata），x[]表示解出来的系数结果，b[]表示线性方程组的Y值。
void File_::gauss_solve(int n, double A[], double x[], double b[])
{
	int i, j, k, r;
	double max;
	for (k = 0; k < n - 1; k++)
	{
		max = fabs(A[k * n + k]);			// find maxmum 
		r = k;
		for (i = k + 1; i < n - 1; i++)
		{
			if (max < fabs(A[i * n + i]))
			{
				max = fabs(A[i * n + i]);
				r = i;
			}
		}
		if (r != k)
		{
			for (i = 0; i < n; i++)		//change array:A[k]&A[r]
			{
				max = A[k * n + i];
				A[k * n + i] = A[r * n + i];
				A[r * n + i] = max;
			}
			max = b[k];                    //change array:b[k]&b[r]
			b[k] = b[r];
			b[r] = max;
		}                                  //为了使用列主元消去法，在第k步消元前，先找出k行下所有第k列元素最大的非零元素ar,k，将第r行与第k行进行整行交换

		for (i = k + 1; i < n; i++)
		{
			for (j = k + 1; j < n; j++)
				A[i * n + j] -= A[i * n + k] * A[k * n + j] / A[k * n + k];
			b[i] -= A[i * n + k] * b[k] / A[k * n + k];
		}
	}
	for (i = n - 1; i >= 0; x[i] /= A[i * n + i], i--)
	{
		for (j = i + 1, x[i] = b[i]; j < n; j++)
			x[i] -= A[i * n + j] * x[j];
	}
}
// 将多项式的系数变为最高次在首位 首尾互换
void File_::reverseP(double arr[], int size)
{
	double temp;
	int i;
	for (i = 0; i <= size / 2; i++)
	{
		temp = arr[i]; arr[i] = arr[size - i]; arr[size - i] = temp;
	}
}


