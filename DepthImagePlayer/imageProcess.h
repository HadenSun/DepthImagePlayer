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
	void setTimes(uint16_t time);		//������ʱʱ��
	bool getRunState();					//��ȡ����״̬
	void stop();						//ֹͣ����
	void setFilesList(QStringList list);//�����ļ��б�
	void setDir(QString dir);			//�����ļ���
	void setCurrentIndex(int index);	//���õ�ǰ���

signals:
	void updateImage(cv::Mat, int);		//���´򿪵�ͼ��  ��ǰ�ļ���ţ�ʧ��-1��
	void updateResult(cv::Mat, int);	//�����㷨���

protected:
	void run();							//�̳���QThread���߳����к���

private:
	bool isRun = 0;
	uint16_t time = 0;					//ѭ����ʱʱ��
	QStringList files;					//�ļ��б�
	QString		dir;					//�ļ���Ŀ¼
	int currentIndex = 0;			//��ǰ�ļ����
};

