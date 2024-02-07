#pragma once
#include"BasicWidget.h"
#include<thread>
#pragma comment(lib,"Imm32.lib")
class LineEdit:public BasicWidget//编辑窗口 BasicWidget的子类
{
public:
	LineEdit(int x = 0, int y = 0, int w = 100, int h = 30);//编辑窗口的基础设置
	void show();//绘制一个文本框

	void eventLoop(const ExMessage& msg);//判断是否需要弹出输入框

	//弹出数据输入框
	void popInputBox();
	void setInputBoxTitle(const std::string& title);
	void setText(const std::string&text);
	std::string text();
	void clear();
	void setCursorHide(bool isHide);
	//文本是否改变了
	bool textChanged();
private:
	std::string m_pretext;	//上一次的文字
	std::string m_text;		//行编辑器中的文字
	int textw;

	std::string m_title;	//行编辑器弹出窗标题
	bool m_hideCursor = false;		//是否显示光标
	bool m_isPopUp;	//是否弹出
};

