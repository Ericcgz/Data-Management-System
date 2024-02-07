/*pushButton 按钮类*/
#ifndef __PUSHBUTTON_H_
#define __PUSHBUTTON_H_
#include"Configure.h"
#include"image.h"
#include"BasicWidget.h"

class PushButton:public BasicWidget//放置按钮类 BasicWidget的子类
{
public:
	PushButton(std::string text ="PushButton",int x=0,int y=0,int w =100,int h = 30);//初始化按钮 设置按钮的文本，初始坐标和长度，高度
	//显示按钮
	void show();
	//设置按钮的文本
	void setText(std::string text);
	//设置按钮的图片
	void setBackgroundImage(std::string imgPath);
	//设置按钮的颜色
	void setBackgroundColor(Color color);
	//设置按钮改变后颜色
	void setHover(COLORREF c);
	//设置按钮改变后图片
	void setHover(std::string imgPath);
	//事件循环,按钮悬停后变化
	void eventLoop(const ExMessage&);

	//鼠标是否在按钮上面
	bool isin();
	//鼠标是否点击了按钮
	bool isClicked();
	

	~PushButton();

public:
	std::string text;
	bool  isshow = false;			//显示状态
	ExMessage _msg;					//鼠标消息
public:	//current 当前颜色
	Image* cur_img = nullptr;
	COLORREF cur_color = RGB(232, 232, 236);

public:	//normal 正常颜色
	Image* nor_img = nullptr;
	COLORREF nor_color = RGB(232, 232, 236);

public:	//hover
	Image* h_img = nullptr;
	COLORREF h_color = RGB(194, 195, 201);
	//COLORREF h_color = RGB(165, 165, 165);
};
#endif