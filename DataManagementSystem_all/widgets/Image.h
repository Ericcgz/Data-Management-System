#pragma once
#include"Configure.h"
class Image :public IMAGE
{
public:
	Image();
	//加载图片 输入图片位置，放置起点，初始起点为（0，0）
	Image(const std::string& imgPath,int w = 0,int h =0);
	//example: Image("./res/images/jumpMask.jpg","./res/images/jumpSrc.jpg")
	
	Image(const std::string& maskImgPath, const std::string& srcImgPath,int w = 0,int h =0);
	//example: Image("./res/images/","jumpMask.jpg","jumpSrc.jpg")
	
	Image(const std::string& prefixPath,const std::string& maskImgPath, const std::string& srcImgPath,int w = 0,int h = 0);
	
	void draw();//绘制图片
	void draw(DWORD maskdwRop, DWORD srcdwRop);//绘制透明贴图的封装
	void move(int x, int y);//移动图片起点

	void save(const std::string& savePath);//保存图片到当前
	static void save(const std::string& savePath, Image* img);//保存图片到img
	Image* getimage(int x, int y, int w, int h);//获取图片的数据

	DWORD* ImageBuffer();			// 获取绘图设备的显存指针
	
private:
	void SetDefault() override;						// 设置为默认状态
	static void putimage_alapha(int x, int y, IMAGE* src);

	int x;
	int y;
private://使用掩码图透明贴图
	Image *pMaskImg;
};

