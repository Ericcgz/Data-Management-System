#pragma once
#include"BasicWidget.h"
#include"pushButton.h"
#include<vector>

class Table :public BasicWidget//表格类，BasciWidget的子类
{
public:
	Table(int row = 1, int col = 0);
	void setRowCount(int row);
	void setColCount(int col);

	//设置表头 插入以制表符分隔的字符串数据 
	void setHeader(const std::string& data);
	//插入数据在末尾
	void insert(const std::string& data);
	//清除数据并更新
	void clear();
	//四个页码处理按钮
	void eventLoop(const ExMessage& msg);
	//绘制表格
	void show();
	//以指定的方式分隔字符串
	std::vector<std::string> split(std::string str, char separator = '\t');
private:
	//表格线
	void drawTableGrid();
	//填写表格
	void drawTableText();
	//绘制表头
	void drawHeader();
	//更新数据
	void updateData();		
	
	//初始化换页按钮位置 在表格的下方
	void initPageBtnPos();

private:
	size_t m_rows; //表格的行数
	size_t m_cols; //表格的列数

	int m_gridw;//表格的宽度
	int m_gridh;//表格的高度

	std::string m_header;//表头
	std::vector<std::string> m_datas;//表格中的数据
private:	//换页处理
	int m_curPage;	//当前页
	int m_maxPage;	//总页数
	int m_extraData;	//如果不是整数页，那么保存一下最后一页有多少条数据

	PushButton m_prevPageBtn;		//上一页
	PushButton m_nextPageBtn;		//下一页
	PushButton m_beginPageBtn;		//第一页
	PushButton m_endPageBtn;		//末尾页
};

