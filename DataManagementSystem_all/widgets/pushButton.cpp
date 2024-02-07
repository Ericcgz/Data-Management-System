#include "pushButton.h"

PushButton::PushButton(std::string text, int x, int y, int w, int h)
	:text(text),BasicWidget(x,y,w,h)
{
	memset(&_msg, 0, sizeof(ExMessage));//初始化消息
}

void PushButton::show()
{
	BasicWidget::show();//设置字体和颜色
	if (cur_img)
	{
		cur_img->draw();//如果按钮是图片，就显示图片
	}
	else//否则就绘制一个圆角矩形
	{
		setlinecolor(BLACK);
		setfillcolor(cur_color);
		::fillroundrect(m_x, m_y, m_x + m_w, m_y + m_h,10,10);
	}
	
	//居中显示文本
	int tx = m_x + (m_w - textwidth(text.data())) / 2;
	int ty = m_y + (m_h - textheight(text.data())) / 2;
	outtextxy(tx, ty, text.data());
}

void PushButton::setText(std::string text)
{
	this->text = text;
}

void PushButton::setBackgroundImage(std::string imgPath)
{
	if(!nor_img)
		nor_img = new Image(imgPath.data(), this->m_w, this->m_h);
	this->cur_img = nor_img;
	this->show();
}

void PushButton::setBackgroundColor(Color color)
{
	this->nor_color = color;
}

void PushButton::setHover(COLORREF c)
{
	h_color = c;
}

void PushButton::setHover(std::string imgPath)
{
	if(!h_img)
		h_img = new Image(imgPath.c_str(),m_w,m_h);
}

void PushButton::eventLoop(const ExMessage& msg)
{
	this->_msg = msg;
	if (isin())
	{
		if (cur_img)
		{
			cur_img = h_img;//如果按钮为图片，进行图片改变
		}
		else
		{
			cur_color = h_color;//颜色变化
		}
	}
	else
	{
		if (cur_img)
		{
			cur_img = nor_img;
		}
		else
		{
			cur_color = nor_color;
		}
	}
	//this->show();
}

bool PushButton::isin()//判断鼠标是否在区域
{
	if (_msg.x >= m_x && _msg.x <= m_x + m_w && _msg.y >= m_y && _msg.y <= m_y+m_h)
	{
		return true;
	}
	return false;
}

bool PushButton::isClicked()//判断是否点击
{
	if (isin())
	{
		switch (_msg.message)
		{
		case WM_LBUTTONDOWN:
			return true;
		}
	}
	return false;
}

PushButton::~PushButton()
{
}
