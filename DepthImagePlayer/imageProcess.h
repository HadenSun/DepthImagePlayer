#pragma once

#include <qthread.h>
#include <qdebug.h>
#include <stdint.h>
#include <opencv2/opencv.hpp>

class ImageProcess :
	public QThread
{
	Q_OBJECT

public:
	ImageProcess();
	~ImageProcess();
	void setTimes(uint16_t time);		//设置延时时间
	bool getRunState();					//获取运行状态
	void stop();						//停止运行
	void setFilesList(QStringList list);//设置文件列表
	void setDir(QString dir);			//设置文件夹
	void setCurrentIndex(int index);	//设置当前序号

signals:
	void updateImage(cv::Mat, int);		//传新打开的图像  当前文件序号（失败-1）
	void updateResult(cv::Mat, int);	//更新算法结果

protected:
	void run();							//继承自QThread，线程运行函数

private:
	bool isRun = 0;
	uint16_t time = 100;					//循环延时时间
	QStringList files;					//文件列表
	QString		dir;					//文件夹目录
	int currentIndex = 0;			//当前文件序号
};

