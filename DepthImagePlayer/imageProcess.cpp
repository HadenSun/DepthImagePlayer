﻿/**
* @file imageProcess.cpp
* @brief New thread for open image continue.
* @details Handle for image open continuly and leave a port for running algorithm.
* @mainpage ImageProcess
* @author Oliver admin@sunhx.cn
* @version 1.0.0
* @date 2019-11-8
*/

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
		currentIndex++;

		//检查是否到最后
		if (currentIndex < files.size())
		{
			//打开文件
			QString fileFullName = dir + "/" + files.at(currentIndex);
			cv::Mat img = cv::imread(fileFullName.toLocal8Bit().toStdString(), CV_LOAD_IMAGE_ANYCOLOR | CV_LOAD_IMAGE_ANYDEPTH);


			//算法代码执行
			algorithm->runAlgorithm();

			//发送代码执行结果
			//cv::Mat rst = algorithm->getResult();
			//emit updataResult(rst.clone(), currentIndex);

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

void ImageProcess::setAlgorithm(MyAlgorithm* algorithm)
{
	this->algorithm = algorithm;
}