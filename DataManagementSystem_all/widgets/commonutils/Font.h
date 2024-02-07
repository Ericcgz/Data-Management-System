#pragma once
#include"TypeDefine.h"
#include<string>
#include"Color.h"
class Font//文本类
{
public:
    Font();//文字类的空构造
    Font(const std::string& family, int Weight = 0, bool italic = false);//文字类 字体、粗细、是否斜体的构造

    void setHeight(int height);               //设置字符的高度
    void setWidth(int width);                 //设置字符的宽度
    void setBold(bool enable);
    void setItalic(bool enable);              //设置是否斜体
    void setWeight(int weight);               //设置笔画粗细
    void setQuality(int Quality);             //指定文字的输出质量；
    void setFamily(const std::string& family);//设置字体
    void setColor(const Color& color);        //设置字体颜色

    const Color& color();

    int Height();        //获取高度
    int Width();         //获取宽度
    bool Bold();         
    bool Italic();       //获取是否斜体
    int Weight();        //获取笔画粗细
    int Quality();       //获取文字输出质量
    std::string Family();//获取字体

private:
    int32      lfHeight = 0;            //字符的平均高度
    int32      lfWidth = 0;             //字符的平均宽度(0 表示自适应)
    int32      lfEscapement = 0;        //字符串的书写角度(单位 0.1 度)；
    int32      lfOrientation = 0;       //每个字符的书写角度(单位 0.1 度)；
    int32      lfWeight = 0;            //字符的笔画粗细(0 表示默认粗细)；
    Byte      lfItalic = 0;             //是否斜体；
    Byte      lfUnderline = 0;          //是否下划线；
    Byte      lfStrikeOut = 0;          //是否删除线
    Byte      lfCharSet = 0;            //指定字符集；
    Byte      lfOutPrecision = 0;       //指定文字的输出精度；
    Byte      lfClipPrecision = 0;      //指定文字的剪辑精度；
    Byte      lfQuality = 0;            //指定文字的输出质量；
    Byte      lfPitchAndFamily = 0;     //指定以常规方式描述字体的字体系列。
    char      lfFaceName[32] = { 0 };   //字体名称
    Color     lfcolor;                  //color类 字体的颜色
};