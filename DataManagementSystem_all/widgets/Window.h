#pragma once
#include"Configure.h"
#include<conio.h>


class Window
{
public:
	Window(int w, int h,int flag = 0);
	~Window();
	void setWindowTitle(const std::string& title);
	static void setWindowColor(COLORREF c);
	//设置鼠标光标的形状
	void setCursor(LPSTR curSorStyle);
	//关闭窗口
	inline int exec() { system("pause"); return 0; };

public://static 常用函数简化
	static int width();
	static int height();
	static void clear();
	static void beginDraw();
	static void flushDraw();
	static void endDraw();

	inline static bool hasMsg() { return peekmessage(&s_message, EX_MOUSE | EX_KEY); }//获取当前窗口的信息 鼠标和键盘
	inline static const ExMessage& getMsg() { return s_message; }

private:
	HWND handle;	//当前窗口句柄
	static ExMessage s_message;
};


/*@setCursor光标样式名字
	IDC_ARROW,   //正常
	IDC_IBEAM,	//工
	IDC_WAIT,    //○
	IDC_CROSS,   //十
	IDC_UPARROW, //↑
	IDC_SIZE,	//????
	IDC_ICON,    //????
	IDC_SIZENWSE,//左上角缩放
	IDC_SIZENESW,//右上角缩放
	IDC_SIZEWE,	//左右
	IDC_SIZENS,	//上下
	IDC_SIZEALL,	//带箭头的十
	IDC_NO		//(X)
*/
