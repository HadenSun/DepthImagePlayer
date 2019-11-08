/**
* @file main.cpp
* @brief The main function file.
* @details This is the entry of this program.
* @mainpage Mainpage
* @author Oliver Sun
* @email admin@sunhx.cn
* @version 1.0.0
* @date 2019-11-8
*/



#include "depthimageplayer.h"
#include <QtWidgets/QApplication>


/**
* @brief 主函数
* @details 程序唯一入口
*
* @param argc 命令参数个数
* @param argv 命令参数指针数组
* @return 程序执行成功与否
*     @retval 0 程序执行成功
*     @retval 1 程序执行失败
* @note 
*/
int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	DepthImagePlayer w;
	w.show();
	return a.exec();
}
