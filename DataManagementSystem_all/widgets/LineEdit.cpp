﻿#include "LineEdit.h"
#include"Window.h"
#include<conio.h>

LineEdit::LineEdit(int x, int y, int w, int h)
	:BasicWidget(x, y, w, h), textw(2), m_isPopUp(false)
	, m_title("请输入")
{
	
}

void LineEdit::show()
{
	BasicWidget::show();//设置字体和颜色,初始化
	setfillcolor(RGB(232, 232, 236));
	fillrectangle(m_x, m_y, m_x+m_w, m_y+m_h);

	if (!m_hideCursor)
	{
		//闪烁的小竖线
		setlinecolor(RED);
		line(m_x + textw + 2 +10, m_y + 2, m_x + textw + 2+10, m_y + m_h - 2);
	}
	//把文字靠左输出到edit上
	outtextxy(m_x+10, m_y+(m_h - textheight(m_text.c_str())) / 2+5,m_text.c_str());

	if (m_isPopUp)
	{
		m_pretext = m_text;
		popInputBox();
		m_isPopUp = false;
	}
}
void LineEdit::eventLoop(const ExMessage& msg)//判断是否需要弹出输入框
{
	if (msg.x > m_x && msg.x < m_x + m_w && msg.y > m_y && msg.y < m_y + m_h
		&& msg.message == WM_LBUTTONDOWN)
	{
		m_isPopUp = true;
	}//如果鼠标在文本框内并且按下，弹出文本框
}
void LineEdit::popInputBox()
{
	char str[128] = { 0 };
	InputBox(str, 128, nullptr,m_title.c_str(),m_text.c_str());
	m_text = str;//把信息传入
	textw = ::textwidth(m_text.c_str());//更新文字的宽度
}
void LineEdit::setInputBoxTitle(const std::string& title)
{
	m_title = title;
}

void LineEdit::setText(const std::string& text)
{
	m_text = text;
	textw = ::textwidth(m_text.c_str());
}

std::string LineEdit::text()
{
	return m_text;
}

void LineEdit::clear()
{
	m_text.clear();
	textw = 0;
}

void LineEdit::setCursorHide(bool isHide)
{
	m_hideCursor = isHide;
}

bool LineEdit::textChanged()
{
	if (m_pretext == m_text)
	{
		return false;
	}
	m_pretext = m_text;	//更新,通知一次文本改变即可
	return true;
}
