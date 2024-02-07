#pragma once
#include<vector>
#include<map>
#include"widgets/pushButton.h"
#include"widgets/Table.h"
#include"widgets/LineEdit.h"
#include"FileData.h"

class ManageMent
{
	enum Operator//枚举选择，界面的切换
	{
		ShowAll,
		Insert,
		Erase,
		ModifyAndFind,
		Stactics,
		Exit,
		DarwFileData = 7,
	};

public:
	ManageMent();
	void run();
	//显示主菜单按钮
	void menu();

	void eventLoop();
	void drawBackground();

	int mainMenu(const ExMessage& msg);

	void updateTableData();	//插入和删除数据时，更新一下表格
	void updateFileMenu(); //插入文件时，更新文件和按钮
	void displayAll();	    //处理数据文件
	void insert();	        //新建数据文件
	void erase();	        //删除数据文件
	void modify();	        //修改数据文件
	void stactics();	    //文件分类统计
	
private:
	//保存文件信息到文件
	void writeData(const std::string& fileName,int number);

public:
	std::string tableHeader;	//表头
	
	int nowFileNumber;

	std::vector<PushButton*> menu_btns;//动态按钮类数组 主菜单的按钮
	
	int opt = 66;		//当前所在页
	ExMessage m_msg;
	ExMessage m_keymsg;
	int m_key;
public:
	Image m_bk;//背景图片
	Image m_bk2;//背景图片2

public://显示文件数据页 
	Table		m_insertTable;      //表格类 包含四个按钮
	PushButton  MeanSortBtn;		//按均值排序按钮
	PushButton  varianceSortBtn;   //按方差排序按钮

public://返回主界面按钮
	PushButton   ReturnBtn;

public://处理数据文件页
	std::vector<PushButton*> menu_fileBtns;//文件按钮数组
	std::vector<File_*> vec_files;//文件类数据数组
	PushButton LastBtn;//返回按钮
	void showdata(int filepage);//显示数据界面
	int filepage;
	PushButton SetOptBtn;//设置最佳拟合阶数按钮

public://添加文件数据页
	LineEdit	m_insertEdit;//添加文件和数据编辑框
	PushButton	m_insertBtn;//添加文件确认按钮

public://删除文件页面
	LineEdit*   delEdit;
	PushButton* delBtn;

public://查找和修改文件页
	
	LineEdit*       m_modifyEdit;//添加文件名编辑框
	std::vector<LineEdit*> m_fileEdits;//各个编辑条按钮
	File_* m_modifyit;//指向要修改的文件的指针
	File_  tempfile;//储存修改文件信息

	bool haveFile = false;//是否有要修改的文件
	bool isfirst = true;//是不是第一次查找	
	Table* searchTable;//文件数据显示表格
};
