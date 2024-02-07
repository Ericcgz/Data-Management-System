#include "ManageMent_gui.h"
#include<sstream>
#include<fstream>
#include<string>
#include<iostream>
#include<algorithm>
#include"widgets/Window.h"
#include<conio.h>
#include"widgets/Timer.h"
#include<sstream>
#include"DataGraph.h"
#include<cstdio>
#include <filesystem>

using namespace std;

ManageMent::ManageMent():m_key(0)
{
	nowFileNumber = 10;//当前文件数量
	tableHeader = "\t文件名\t均值\t方差\t数据条数\t处理状态\t最佳拟合阶数\t";//表头

	m_bk = Image("./images/bk.jpg",Window::width(),Window::height());//加载背景图片
	m_bk2 = Image("./images/bk2.jpg", Window::width(), Window::height());//加载二级背景图片
	
	//主页面按钮放置
	menu_btns.push_back(new PushButton("处理数据文件"));
	menu_btns.push_back(new PushButton("新建数据文件"));
	menu_btns.push_back(new PushButton("删除数据文件"));
	menu_btns.push_back(new PushButton("查找和修改数据文件"));
	menu_btns.push_back(new PushButton("文件分类统计显示"));
	menu_btns.push_back(new PushButton("退出系统"));

	for (int i = 0; i < menu_btns.size(); i++)//按钮居中放置在主界面
	{
		menu_btns[i]->setFixedSize(250, 50);//设置按钮的大小
		menu_btns[i]->setHover(RGB(174, 215, 245));//设置按钮响应之后颜色

		int x = (Window::width() - menu_btns[i]->width()) / 2; //按钮水平居中
		int topMargin = (Window::height() - menu_btns.size() * (menu_btns[0]->height())) / 2+45; //按钮最高的位置
		int y = topMargin + i * (menu_btns[i]->height()+5); //按钮垂直位置
		menu_btns[i]->move(x,y);//将按钮移动到对应位置
	}
	//返回按钮
	ReturnBtn.setFixedSize(300, 40);
	ReturnBtn.setText("返回到主界面(ESC)");
	ReturnBtn.move(Window::width() - ReturnBtn.width(), Window::height() - ReturnBtn.height());
	//文件名按钮
	menu_fileBtns.push_back(new PushButton("sinn.txt"));
	menu_fileBtns.push_back(new PushButton("sinno.txt"));
	menu_fileBtns.push_back(new PushButton("squaren.txt"));
	menu_fileBtns.push_back(new PushButton("squareu.txt"));
	menu_fileBtns.push_back(new PushButton("sawn.txt"));
	menu_fileBtns.push_back(new PushButton("sawu.txt"));
	menu_fileBtns.push_back(new PushButton("sinu.txt"));
	menu_fileBtns.push_back(new PushButton("sinuo.txt"));
	menu_fileBtns.push_back(new PushButton("randn.txt"));
	menu_fileBtns.push_back(new PushButton("randu.txt"));
	//按钮居中放置在主界面 目前menu_fileBtns.size() = 9；
	for (int i = 0; i < menu_fileBtns.size(); i++)
	{
		menu_fileBtns[i]->setFixedSize(250, 50);//设置按钮的大小
		menu_fileBtns[i]->setHover(RGB(174, 215, 245));//设置按钮响应之后颜色

		int x = (Window::width() - menu_fileBtns[i]->width()) / 2; //按钮水平居中
		int topMargin = (Window::height() - menu_fileBtns.size() * (menu_fileBtns[0]->height())) / 2 -50; //按钮最高的位置
		int y = topMargin + i * (menu_fileBtns[i]->height() + 5); //按钮垂直位置
		menu_fileBtns[i]->move(x, y);//将按钮移动到对应位置
	}
	//文件的加载 初始化
	vec_files.push_back(new File_("sinn.txt"));
	vec_files.push_back(new File_("sinno.txt"));
	vec_files.push_back(new File_("squaren.txt"));
	vec_files.push_back(new File_("squareu.txt"));
	vec_files.push_back(new File_("sawn.txt"));
	vec_files.push_back(new File_("sawu.txt"));
	vec_files.push_back(new File_("sinu.txt"));
	vec_files.push_back(new File_("sinuo.txt"));
	vec_files.push_back(new File_("randn.txt"));
	vec_files.push_back(new File_("randu.txt"));
	for (int i = 0; i < vec_files.size(); i++) {
		vec_files[i]->ProcessData_();
	}
	//返回按钮
	LastBtn.setFixedSize(100, 40);
	LastBtn.setText("返回");
	LastBtn.move(0, Window::height() - LastBtn.height());
	//设置最佳拟合阶数按钮
	SetOptBtn.setFixedSize(240, 40);
	SetOptBtn.setText("设置最佳拟合阶数");
	SetOptBtn.move(0, Window::height() - LastBtn.height()-60);


	//初始化查看各个文件信息的表格
	m_insertTable.setHeader(tableHeader);//设置表头
	m_insertTable.move((Window::width()-m_insertTable.width())/2, 100);//让表格居中 设置表格左上角纵坐标
	m_insertTable.setRowCount(13);//设置表格的行数
	
	Font font = m_insertTable.font();//Fond类的实例化
	font.setItalic(false);
	m_insertTable.setFont(font);
	updateTableData();//更新文件统计界面的表格

	MeanSortBtn.setFixedSize(200, 30);
	varianceSortBtn.setFixedSize(200, 30);
	MeanSortBtn.move(Window::width() / 2 - 275, Window::height() - 80);
	varianceSortBtn.move(Window::width() / 2 + 150, Window::height() - 80);
	MeanSortBtn.setText("按均值排序");
	varianceSortBtn.setText("按方差排序");

	//添加页面
	m_insertEdit.setFixedSize(400, 30);
	m_insertEdit.move((Window::width() - m_insertEdit.width()) / 2, (Window::height() - m_insertEdit.height()) / 2);//编辑条
	m_insertBtn.setFixedSize(50, 30);
	m_insertBtn.move(m_insertEdit.x() + m_insertEdit.width()+20, m_insertEdit.y());
	m_insertBtn.setText("确定");//确定按钮


	//查找和修改页面
	m_modifyEdit = new LineEdit(0, 0, 400, 30);//修改页面修改编辑框
	m_modifyEdit->move((Window::width() - m_modifyEdit->width()) / 2, Window::height() / 2-100);//将编辑框移动
	
	searchTable = new Table;
	searchTable->setRowCount(5);
	searchTable->setHeader(tableHeader);
	searchTable->move((Window::width() - searchTable->width()) / 2, m_modifyEdit->y() + 120);
	int width = 140;	//修改页表格宽度
	int w = width * 6;
	int vspace = (Window::width() - w) / 2;
	for (int i = 0; i < 6; i++)
	{
		m_fileEdits.push_back(new LineEdit(vspace+ i* width, m_modifyEdit->y()+120, width, 40));
		m_fileEdits[i]->setCursorHide(true);	//隐藏光标
	}
	m_fileEdits[0]->setInputBoxTitle("请输入文件名");
	m_fileEdits[1]->setInputBoxTitle("请输入均值");
	m_fileEdits[2]->setInputBoxTitle("请输入方差");
	m_fileEdits[3]->setInputBoxTitle("请输入数据条数");
	m_fileEdits[4]->setInputBoxTitle("请输入处理状态");
	m_fileEdits[5]->setInputBoxTitle("请输入最佳拟合阶数");

	//删除页面
	delEdit = new LineEdit(0, 0, 500, 30);
	delBtn = new PushButton("删除", 0, 0, 100, 30);
	delEdit->setInputBoxTitle("请输入文件名：");
	delEdit->move((Window::width() - (delEdit->width()*2)) / 2+200, Window::height() / 2);
	delBtn->move(delEdit->x() + delEdit->width()+80, Window::height() / 2);
}
//运行中心
void ManageMent::run()
{
	Window::beginDraw();
	while (true)
	{		
		Window::clear();
		drawBackground();//绘制首页的背景
		ReturnBtn.show();
		
		if (Window::hasMsg())//获取鼠标和按键信息 
		{
			m_msg = Window::getMsg();

			ReturnBtn.eventLoop(m_msg);
			if (ReturnBtn.isin()) {
				if (ReturnBtn.isClicked()) {
					opt = 66;
				}
			}
			
			switch (m_msg.message)
			{		
			case WM_KEYDOWN:		//按键消息
				switch (m_msg.vkcode)
				{
				case VK_ESCAPE:		//ESC 退出
					opt = 66;
					break;
				}
				break;
			default:			  //其他的都是鼠标消息了
				this->eventLoop();//进入鼠标信息的选择
				break;
			}
		}

		switch (opt)
		{
		case 66:
			opt = mainMenu(m_msg);
			break;
		case ManageMent::ShowAll:
			displayAll();
			break;
		case ManageMent::Insert:
			insert();
			break;
		case ManageMent::Erase:
			erase();
			break;
		case ManageMent::ModifyAndFind:
			modify();
			break;
		case ManageMent::Stactics:
			stactics();
			break;
		case ManageMent::Exit:
			exit(666);
		
		case ManageMent::DarwFileData:
			showdata(filepage);
			break;
		
		default:
			break;
		}	
		Window::flushDraw();
	}
	Window::endDraw();
}
//主菜单按钮显示
void ManageMent::menu()
{
	for (int i = 0; i < menu_btns.size(); i++)
	{
		menu_btns[i]->show();
	}
}

void ManageMent::eventLoop()
{
	//if (opt == ShowAll){m_insertTable.eventLoop(m_msg);//表格类展示四个按钮}
	if (opt == ShowAll) 
	{
		for (int i = 0; i < menu_fileBtns.size(); i++) {
			menu_fileBtns[i]->eventLoop(m_msg);//文件按钮
		}
	}
	else if (opt == Insert)
	{
		m_insertBtn.eventLoop(m_msg);//新建文件确认按钮
		m_insertEdit.eventLoop(m_msg);//新建文件编辑条按钮
	}
	else if (opt == Erase)
	{
		delBtn->eventLoop(m_msg);//删除确认按钮
		delEdit->eventLoop(m_msg);//删除编辑条按钮
	}
	else if (opt == ModifyAndFind)
	{
		m_modifyEdit->eventLoop(m_msg);//修改编辑条
		if (haveFile)//如果找到了文件
		{
			for (int i = 0; i < 6; i++)
			{
				m_fileEdits[i]->eventLoop(m_msg);//修改编辑条
			}
		}
	}
	else if (opt == Stactics)
	{
		updateTableData();
		MeanSortBtn.eventLoop(m_msg);
		varianceSortBtn.eventLoop(m_msg);
		m_insertTable.eventLoop(m_msg);
	}
	else if (opt == DarwFileData)
	{
		LastBtn.eventLoop(m_msg);//选择文件后的返回按钮
		SetOptBtn.eventLoop(m_msg);//设置最佳拟合阶数按钮
		m_insertTable.eventLoop(m_msg); //表格类展示四个按钮
	}

}

void ManageMent::drawBackground()
{
	m_bk.draw();//绘制背景
}
int ManageMent::mainMenu(const ExMessage& msg)
{
	settextcolor(RGB(174, 215, 245));
	settextstyle(60, 0, "华文中宋");
	char title[50] = "工业数据分析与文件管理系统";
	outtextxy((Window::width() - textwidth(title)) / 2, 80, title);

	for (auto btn : menu_btns)
	{
		btn->show();//绘制按钮
	}

	for (size_t i = 0; i < menu_btns.size(); i++)
	{
		menu_btns[i]->eventLoop(msg);
		if (menu_btns[i]->isClicked() && Timer::startTimer(200, 0))//设置时间防止多次信息
		{
			return i;//处理按钮点击 进入相应的页面
		}
	}
	return 66;
}

//更新文件表格的数据
void ManageMent::updateTableData()
{
	m_insertTable.clear();
	for (int i = 0;i<vec_files.size();i++)
	{
		m_insertTable.insert(vec_files[i]->file_formatInfo());
	}
}

void ManageMent::stactics() 
{
	m_bk2.draw();
	ReturnBtn.show();
	m_insertTable.show();
	MeanSortBtn.show();
	varianceSortBtn.show();
	if (MeanSortBtn.isClicked() && Timer::startTimer(200, 0)) 
	{
		for (int i = 0; i < vec_files.size(); i++) {
			for (int j = i + 1; j < vec_files.size(); j++) {
				if (vec_files[i]->mean_ < vec_files[j]->mean_) {
					std::string  t0 = vec_files[i]->filename_; vec_files[i]->filename_ = vec_files[j]->filename_; vec_files[j]->filename_ = t0;
					double t1 = vec_files[i]->mean_; vec_files[i]->mean_ = vec_files[j]->mean_; vec_files[j]->mean_ = t1;
					double t2 = vec_files[i]->variance_; vec_files[i]->variance_ = vec_files[j]->variance_; vec_files[j]->variance_ = t2;
				}
			}
		}
		updateTableData();
	}
	if (varianceSortBtn.isClicked() && Timer::startTimer(200, 0)) 
	{
		for (int i = 0; i < vec_files.size(); i++) {
			for (int j = i + 1; j < vec_files.size(); j++) {
				if (vec_files[i]->variance_ < vec_files[j]->variance_) {
					std::string  t0 = vec_files[i]->filename_; vec_files[i]->filename_ = vec_files[j]->filename_; vec_files[j]->filename_ = t0;
					double t1 = vec_files[i]->mean_; vec_files[i]->mean_ = vec_files[j]->mean_; vec_files[j]->mean_ = t1;
					double t2 = vec_files[i]->variance_; vec_files[i]->variance_ = vec_files[j]->variance_; vec_files[j]->variance_ = t2;
				}
			}
		}
		updateTableData();
	}
}

//显示所有文件选择页
void ManageMent::displayAll()
{
	m_bk2.draw();
	ReturnBtn.show();

	for (int i = 0; i < menu_fileBtns.size(); i++) 
	{
		menu_fileBtns[i]->show();
		if (menu_fileBtns[i]->isClicked() && Timer::startTimer(200, 0)) 
		{
			filepage = i;
			opt = DarwFileData;
		}
	}
}
//显示具体文件数据页
void ManageMent::showdata(int filepage)
{
	int COLOR[16] = { BLUE,GREEN,CYAN,RED,MAGENTA,BROWN,LIGHTGRAY,DARKGRAY,LIGHTBLUE,LIGHTGREEN,LIGHTCYAN,LIGHTRED,LIGHTMAGENTA,YELLOW,WHITE,BLACK };

	PLOTAREA  parea = { 200,400,824,700 }; // 直方图显示区域，
	PLOTAREA  farea = { 10,400,300,700 };   // 文字显示区域 
	PLOTAREA dataarea = { 10,10,1000,300 }; // 数据曲线显示区域
	
	int order = 1;
	double fiterror = 0;

	Window::setWindowColor(BLACK);
	settextcolor(WHITE);
	
	LastBtn.show();
	SetOptBtn.show();

	if (LastBtn.isClicked() && Timer::startTimer(100, 0)) {
		opt = ShowAll;
	}//返回按钮

	if (SetOptBtn.isClicked() && Timer::startTimer(200, 0)) {
		char Option[10];
		InputBox(Option, 10, NULL, "请输入最佳拟合阶数", "输入1到9", 400, false);
		int choice = atoi(Option);

		if (choice >= 1 && choice <= 9){vec_files[filepage]->SetOptiOrder_(choice);}
		else 
		{
			InputBox(NULL, 0, "输入错误！","警告", "输入错误！", 400, 0);
		}
	}

	//数据折线图的绘制 原始数据
	DataGraph::showdata(vec_files[filepage]->data_x, vec_files[filepage]->data_y, vec_files[filepage]->row_/2, RED, dataarea);
	
	//计算内容不能都放在这里，一直计算减慢程序速度
	
	// 计算并记录拟合误差，画出拟合曲线。
	for (int order = 1; order <= this->vec_files[filepage]->MaxOrder_; order++)
	{
		double fity[1000] = { 0 };
		double fiterror = 0;
		for (int i = 0; i < this->vec_files[filepage]->row_ / 2; i++)
		{
			fity[i] = DataGraph::fx(vec_files[filepage]->data_x[i], vec_files[filepage]->polyCoeff_[order], order);//拟合点的纵坐标
		}
		DataGraph::showdata(vec_files[filepage]->data_x, fity, vec_files[filepage]->row_/2, COLOR[order], dataarea);
	}
	// 用直方图表示不同阶次的拟合误差。
	DataGraph::showhisto(vec_files[filepage]->fitError_, 9, parea); // 在parea 显示直方图
	//显示文件信息
	DataGraph::showpinfo(this->vec_files[filepage], farea);
}

//插入数据页
void ManageMent::insert()
{
	m_bk2.draw();
	ReturnBtn.show();
	settextstyle(60, 0, "楷体");
	char title[50] = "新建文件数据";
	outtextxy((Window::width() - textwidth(title)) / 2, 80, title);
	m_insertEdit.show();
	m_insertBtn.show();
	settextstyle(40, 0, "华文中宋");
	outtextxy(m_insertEdit.x() +20, m_insertEdit.y() - 150, "请输入新建文件的名称");

	static int nowFile = 10;
	//点一次会触发多次，所以用定时器来延迟一下
	if (m_insertBtn.isClicked() && Timer::startTimer(200,0))
	{
		std::string newData = m_insertEdit.text();
		if (newData.empty()) /*|| std::count(newData.begin(),newData.end(),' ')!=5*/
		{
			printf("插入失败，字符串为空，或格式不满足\n");
			return;
		}
		char data[1024];
		menu_fileBtns.push_back(new PushButton(newData));
		vec_files.push_back((new File_(newData)));
		std::cout << vec_files.size();
		updateFileMenu();
		InputBox(data, 1000, "2-1100个", "请输入新建文件总数据数量(偶数)",NULL, 400, 0);
		int int_data = atoi(data);
		for (int i = 0; i < int_data; i++) {
			char number[1024];
			InputBox(number, 1024,NULL, "请输入数据", NULL, 400, 0);
			int a = atoi(number);
			vec_files[nowFile]->data_[i] = a;
		}
		nowFile++;
		m_insertEdit.clear();
		printf("插入成功啦\n");
		updateFileMenu();
		writeData(newData, int_data);
	}
}
//写入文件数据
void ManageMent::writeData(const std::string& fileName,int number)
{
	fstream write(fileName.c_str(), ios::trunc | ios::out);//写文件 覆盖写（配合out使用）
	if (!write.is_open())
	{
		cerr << fileName << " file open failed [save]";
		return;
	}
	int i = 0;
	for (i = 0; i < vec_files.size(); i++) {
		if (vec_files[i]->filename_ == fileName) {
			break;
		}
	}
	for (int j = 0; j < number; j++) {
		write << vec_files[i]->data_[j]<<" ";
	}
	write.close();
}
//更新文件主菜单 添加文件后
void ManageMent::updateFileMenu()
{
	for (int i = 0; i < menu_fileBtns.size(); i++)//按钮居中放置在主界面
	{
		menu_fileBtns[i]->setFixedSize(250, 50);//设置按钮的大小
		menu_fileBtns[i]->setHover(RGB(174, 215, 245));//设置按钮响应之后颜色

		int x = (Window::width() - menu_fileBtns[i]->width()) / 2; //按钮水平居中
		int topMargin = (Window::height() - menu_fileBtns.size() * (menu_fileBtns[0]->height())) / 2 - 50; //按钮最高的位置
		int y = topMargin + i * (menu_fileBtns[i]->height() + 5); //按钮垂直位置
		menu_fileBtns[i]->move(x, y);//将按钮移动到对应位置
	}
	for (int i = 0; i < vec_files.size(); i++) {
		vec_files[i]->ProcessData_();
	}
}
//删除文件页
void ManageMent::erase()
{
	m_bk2.draw();
	ReturnBtn.show();
	settextstyle(60, 0, "楷体");
	char title[50] = "删除文件";
	outtextxy((Window::width() - textwidth(title)) / 2, 80, title);

	settextstyle(40, 0, "华文中宋");
	outtextxy(m_insertEdit.x() + 20, m_insertEdit.y() - 150, "请输入删除文件的名称");

	delEdit->show();
	delBtn->show();

	static std::string deltefilename;
	if (delEdit->textChanged())//判断编辑条的文字改变
	{
		int isDeleteFileBtnFlag = 1;
		
		deltefilename = delEdit->text();
		if (deltefilename.empty())
			return;
		std::ifstream file(deltefilename);
		if (file.is_open()) {
			InputBox(0, 0, "已经找到该文件", "提示", "已经找到该文件");
		}
		else {
			InputBox(0, 0, "没有找到该文件", "提示", "没有找到该文件");
		}
	}
	//删除按钮按下
	if (delBtn->isClicked() &&  Timer::startTimer(200, 0))
	{
		if (std::filesystem::remove(deltefilename.c_str()) != 0) { // 尝试删除文件
			std::cout << deltefilename << " " << "Failed to delete file." << endl;
			InputBox(0, 0, "删除文件成功，重启系统生效", "提示", "删除成功");
		}
	}
}
//查找和修改
void ManageMent::modify()
{
	static int flag;
	m_bk2.draw();
	ReturnBtn.show();
	settextstyle(60, 0, "楷体");
	char title[50] = "查找和修改文件";
	outtextxy((Window::width() - textwidth(title)) / 2, 80, title);

	settextstyle(40, 0, "华文中宋");
	outtextxy(m_insertEdit.x() -60, m_insertEdit.y() - 150, "请输入需要查找或修改文件的名称");

	searchTable->show();
	m_modifyEdit->show();//显示输入文件名编辑条
	
	static int clock = 1;
	if (m_modifyEdit->textChanged())
	{
		clock = 1;
		std::string res = m_modifyEdit->text();//接收输入的文件名

		for (int i = 0; i < vec_files.size(); i++) {
			if (res == vec_files[i]->filename_) 
			{
				haveFile = true;
				m_modifyit = vec_files[i];
				tempfile.filename_ = vec_files[i]->filename_;
				tempfile.mean_ = vec_files[i]->mean_;
				tempfile.variance_ = vec_files[i]->variance_;
				tempfile.row_ = vec_files[i]->row_;
				tempfile.status_ = vec_files[i]->status_;
				tempfile.OptiOrder_ = vec_files[i]->OptiOrder_;
				flag = i;
				break;
			}
			else {
				haveFile = false;
			}
		}
	}
	if (haveFile)
	{
		settextstyle(18, 0, "黑体");
		setfillcolor(RGB(194, 195, 201));
		solidrectangle(m_fileEdits[0]->x(), m_fileEdits[0]->y() -75, m_fileEdits[0]->x() + 6 * 120, m_fileEdits[0]->y()-50);
		outtextxy(m_fileEdits[0]->x(), m_fileEdits[0]->y() - 70, "成功找到该文件！   请点击下方信息直接编辑");
		
		while (clock) 
		{
			m_fileEdits[0]->setText(tempfile.filename_);
			m_fileEdits[1]->setText(to_string(tempfile.mean_));
			m_fileEdits[2]->setText(to_string(tempfile.variance_));
			m_fileEdits[3]->setText(to_string(tempfile.row_));
			m_fileEdits[4]->setText(tempfile.status_);
			m_fileEdits[5]->setText(to_string(tempfile.OptiOrder_));
			clock = 0;
		}//只设置一次，防止重新设置使得变化失效

		for (int i = 0; i < 6; i++)
		{
			m_fileEdits[i]->show();//文件信息编辑按钮
		}

		//如果修改了文件信息
		for (int i = 0; i < 6; i++)
		{
			if (m_fileEdits[i]->textChanged())
			{
				switch (i)
				{
				case 0:		//修改了文件名
					m_modifyit-> filename_= m_fileEdits[i]->text();
					break;
				case 1:		//修改了均值
					m_modifyit->mean_	= atoi(m_fileEdits[i]->text().data());
					break;
				case 2:		//修改了方差
					m_modifyit->variance_ = atoi(m_fileEdits[i]->text().data());
					break;
				case 3:		//修改了数据条数
					m_modifyit->row_ = atoi(m_fileEdits[i]->text().data());
					break;
				case 4:		//修改了处理状态
					m_modifyit->status_ = atoi(m_fileEdits[i]->text().data());
					break;
				case 5:		//修改了最佳拟合阶数
					m_modifyit->OptiOrder_ = atoi(m_fileEdits[i]->text().data());
					break;
				}
			}
		}
	}
	else if(!isfirst)
	{
		settextstyle(18, 0, "黑体");
		setfillcolor(RGB(194, 195, 201));
		solidrectangle(m_fileEdits[0]->x(), m_fileEdits[0]->y()-75, m_fileEdits[0]->x() + 6 * 120, m_fileEdits[0]->y() - 50);
		outtextxy(m_fileEdits[0]->x(), m_fileEdits[0]->y()-70, "未找到你要修改的学生，请查证后重试~");
	}
	else
	{
		settextstyle(18, 0, "黑体");
		setfillcolor(RGB(194, 195, 201));
		solidrectangle(m_fileEdits[0]->x(), m_fileEdits[0]->y()-75, m_fileEdits[0]->x() + 6 * 120, m_fileEdits[0]->y()  - 50);
		outtextxy(m_fileEdits[0]->x(), m_fileEdits[0]->y() - 70, "请在上方输入框中输入要查找的学生学号，然后点击下方信息直接编辑");
	}
}