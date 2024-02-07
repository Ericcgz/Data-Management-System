#pragma once
#include"Configure.h"
#include"commonutils/Color.h"
class BasicWidget//基础数据的设置
{
public:
	BasicWidget(int x, int y, int w, int h);
	int width() const;//获取宽度
	int height()const;//获取高度
	void setFixedSize(int w, int h);//设置宽度和高度

	int x()const;//获取起点横坐标
	int y()const;//获取起点纵坐标
	void move(int x, int y);//将起点移动到指定位置 x,y
	

	void setBackgroundColor(const Color& color);//设置背景颜色
	Color BackgroundColor();//获取背景颜色

	void setFont(const Font& font);//设置字体
	const Font& font();//获取字体
	virtual void show();
protected:
	int m_x;//起点横坐标
	int m_y;//起点纵坐标
	int m_w;//宽度
	int m_h;//高度

	Color m_bkColor;	//背景颜色
	Font m_font;		//字体
};

