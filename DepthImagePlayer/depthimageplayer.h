#ifndef DEPTHIMAGEPLAYER_H
#define DEPTHIMAGEPLAYER_H

#include <QtWidgets/QMainWindow>
#include <qaction.h>
#include <QMenu>
#include <qdir.h>
#include <QMenuBar>
#include <QToolBar>
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

class DepthImagePlayer : public QMainWindow
{
	Q_OBJECT

public:
	DepthImagePlayer(QWidget *parent = Q_NULLPTR);
	~DepthImagePlayer();

public slots:
	void slotPushButtonNext();			//��һ����Ƭ��
	void slotPushButtonLast();			//��һ��ͼƬ��
	void slotPushButtonPlayAndPause();	//������ͣ��
	void slotDataTreeItemSelected(QTreeWidgetItem*, int);	//�ļ���Ԫ�ر������
	void slotAlgorithmChecked();		//�㷨���ܲ�
	void slotChangeMaxAndMinValue();	//���С����ı��
	void slotChangeTimeValue();			//�ı�ȴ�ʱ���
	void slotUpdateImage(cv::Mat, int);	//���µõ���ͼ��
	

private:
	Ui::DepthImagePlayerClass ui;
	QString fileDir;					//�ļ���·��
	int indexOfCurrentItem = 0;	//�洢��ǰ�ļ����ļ�����λ��
	QTreeWidgetItem* currentItem = NULL;	
	ImageProcess process;
	bool runState = 0;					//����״̬
	uint16_t maxValue = 30000;			//α��ɫ�任��Χ
	uint16_t minValue = 0;					


	void open();		//���ļ���
	void clean();		//����ļ���

};

#endif // DEPTHIMAGEPLAYER_H
