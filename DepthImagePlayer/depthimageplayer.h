#ifndef DEPTHIMAGEPLAYER_H
#define DEPTHIMAGEPLAYER_H

#include <QtWidgets/QMainWindow>
#include <qaction.h>
#include <QMenu>
#include <qdir.h>
#include <QMenuBar>
#include <QToolBar>
#include <QMouseEvent>
#include <QStatusBar>
#include <QFileDialog>
#include <QColorDialog>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <qdebug.h>
#include <stdint.h>
#include "ui_depthimageplayer.h"

#include <opencv2/opencv.hpp>

#include "imageProcess.h"


/**
* @brief 类的简单概述
* 类的详细概述
*/
class DepthImagePlayer : public QMainWindow
{
	Q_OBJECT

public:
	DepthImagePlayer(QWidget *parent = Q_NULLPTR);
	~DepthImagePlayer();

public slots:
	void slotPushButtonNext();			//下一张照片槽
	void slotPushButtonLast();			//上一张图片槽
	void slotPushButtonPlayAndPause();	//播放暂停槽
	void slotDataTreeItemSelected(QTreeWidgetItem*, int);	//文件树元素被点击槽
	void slotAlgorithmChecked();		//算法功能槽
	void slotChangeMaxAndMinValue();	//最大小距离改变槽
	void slotChangeTimeValue();			//改变等待时间槽
	void slotUpdateImage(cv::Mat, int);	//更新得到的图像
	

protected:
	bool eventFilter(QObject *, QEvent *);	//过滤图片label点击事件，获取坐标位置


private:
	Ui::DepthImagePlayerClass ui;
	cv::Mat matOri_uint16;				//存储读取到的原始图像，CV_16UC1类型
	QString fileDir;					//文件夹路径
	int indexOfCurrentItem = 0;	//存储当前文件在文件树中位置
	QTreeWidgetItem* currentItem = NULL;	
	ImageProcess process;
	bool runState = 0;					//播放状态
	uint16_t maxValue = 30000;			//伪彩色变换范围
	uint16_t minValue = 0;					


	void open();		//打开文件夹
	void clean();		//清空文件夹

};

#endif // DEPTHIMAGEPLAYER_H
