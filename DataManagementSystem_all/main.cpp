#include"ManageMent_gui.h"
#include"widgets/Window.h"
#include"widgets/Table.h"
#include"widgets/Timer.h"


int main()
{
	Window w(1024, 768, EX_SHOWCONSOLE);//界面类的实例化
	w.setWindowTitle("工业数据分析与文件管理系统");//设置窗口的名称

	ManageMent m;//管理系统类
	m.run();

	return w.exec();//关闭窗口
}