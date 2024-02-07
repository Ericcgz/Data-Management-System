#pragma once
#include"TypeDefine.h"
class Color//颜色类
{
public:
	Color(int rgb = 0x000);           //当输入一个值的构造函数
	Color(uint8 r, uint8 g, uint8 b); //输入r,g,b的构造函数
	uint32 toRgb() const ;            //返回当前颜色

	inline operator uint32() const
	{
		return m_color;
	}

	static uint32 rgb(uint8 r, uint8 g, uint8 b);
private:
	uint32 m_color;//私有的颜色参数
public:
	enum ColorDef //颜色枚举
	{
		Black			= 0,
		Blue			= 0xAA0000,
		Green			= 0x00AA00,
		Cyan			= 0xAAAA00,
		Red				= 0x0000AA,
		Magenta			= 0xAA00AA,
		Brown			= 0x0055AA,
		LightGray		= 0xAAAAAA,
		DarkGray		= 0x555555,
		LightBlue		= 0xFF5555,
		LightGreen		= 0x55FF55,
		LightCyan		= 0xFFFF55,
		LightRed		= 0x5555FF,
		LightMagenta	= 0xFF55FF,
		Yellow			= 0x55FFFF,
		White			= 0xFFFFFF,
	};
};