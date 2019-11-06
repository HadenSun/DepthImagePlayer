#include "imageProcess.h"


ImageProcess::ImageProcess()
{
	qRegisterMetaType<cv::Mat>("cv::Mat");
}


ImageProcess::~ImageProcess()
{
}

void ImageProcess::run()
{
	isRun = 1;

	while (isRun)
	{
		qDebug() << "run...";
		currentIndex++;

		//检查是否到最后
		if (currentIndex < files.size())
		{
			//打开文件
			QString fileFullName = dir + "/" + files.at(currentIndex);
			cv::Mat img = cv::imread(fileFullName.toLocal8Bit().toStdString(), CV_LOAD_IMAGE_ANYCOLOR | CV_LOAD_IMAGE_ANYDEPTH);


			//TODO 添加算法代码在这里



			emit updateImage(img.clone(), currentIndex);
		}
		else
		{
			currentIndex = 0;
			cv::Mat img;	
			isRun = 0;		//主动停止

			emit updateImage(img, -1);
		}
		

		//处理完延时
		if (time)
			usleep(time * 1000);
	}
}

bool ImageProcess::getRunState()
{
	return isRun;
}

void ImageProcess::stop()
{
	isRun = 0;
}

void ImageProcess::setDir(QString dir)
{
	this->dir = dir;
}

void ImageProcess::setFilesList(QStringList list)
{
	this->files = list;
}

void ImageProcess::setCurrentIndex(int index)
{
	this->currentIndex = index;
}

void ImageProcess::setTimes(uint16_t time)
{
	this->time = time;
}