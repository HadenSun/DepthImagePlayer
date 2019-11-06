#include "depthimageplayer.h"

DepthImagePlayer::DepthImagePlayer(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	//Ĭ�ϲ������㷨�������㷨�����
	ui.lableImageRst->hide();

	//��ť��
	QObject::connect(ui.actionOpen, &QAction::triggered, this, &DepthImagePlayer::open);
	QObject::connect(ui.actionClean, &QAction::triggered, this, &DepthImagePlayer::clean);
	QObject::connect(ui.pushButtonLast, SIGNAL(clicked()), this, SLOT(slotPushButtonLast()));
	QObject::connect(ui.pushButtonNext, SIGNAL(clicked()), this, SLOT(slotPushButtonNext()));
	QObject::connect(ui.pushButtonPlayAndPause, SIGNAL(clicked()), this, SLOT(slotPushButtonPlayAndPause()));
	QObject::connect(ui.checkBoxAlgorithm, SIGNAL(stateChanged()), this, SLOT(slotAlgorithmChecked()));
	QObject::connect(ui.lineEditMax, SIGNAL(editingFinished()), this, SLOT(slotChangeMaxAndMinValue()));
	QObject::connect(ui.lineEditMin, SIGNAL(editingFinished()), this, SLOT(slotChangeMaxAndMinValue()));
	QObject::connect(ui.lineEditTimes, SIGNAL(editingFinished()), this, SLOT(slotChangeTimeValue()));
	//�ļ�����ز�
	QObject::connect(ui.dataTreeFiles, SIGNAL(itemDoubleClicked(QTreeWidgetItem*, int)), this, SLOT(slotDataTreeItemSelected(QTreeWidgetItem*, int)));
	

}

DepthImagePlayer::~DepthImagePlayer()
{

}


void DepthImagePlayer::open()
{
	bool flag = 0;	//����Ƿ��Ѿ����ļ��д�
	if (!fileDir.isEmpty())
		flag = 1;

	QString dirfile = QFileDialog::getExistingDirectory(this, tr("Open files dir"));
	if (dirfile.isEmpty())
		return;		//û��ѡ���ļ��У�ֱ�ӽ���

	//����Ѿ����ļ��д򿪣������
	if (flag)
	{
		clean();
	}

	fileDir = dirfile;

	//���ļ���
	QDir dir(fileDir);
	QStringList filter;		//����������
	filter << "*.png";
	QStringList files = dir.entryList(filter, QDir::Files | QDir::Readable, QDir::Name);

	//�����߳���
	process.setDir(fileDir);
	process.setFilesList(files);


	//������Դ��
	for (int i = 0; i < files.size(); i++)
	{
		QString name = files.at(i);
		QTreeWidgetItem *child = new QTreeWidgetItem(QStringList() << name);
		ui.dataTreeFiles->addTopLevelItem(child);
	}

	//״̬����ʾ���
	ui.statusBar->showMessage(tr("Open ") + fileDir, 3000);

}

void DepthImagePlayer::clean()
{
	fileDir.clear();
	ui.dataTreeFiles->clear();

	//״̬����ʾ���
	ui.statusBar->showMessage(tr("Clean"), 3000);
}

void DepthImagePlayer::slotPushButtonLast()
{
	if (fileDir.isEmpty())
		return;		//���û�п��ļ���

	if (indexOfCurrentItem == 0)
		return;		//��ǰ�Ѿ��ǵ�һ��
	
	if (currentItem == NULL)
		return;

	QTreeWidgetItem* item = ui.dataTreeFiles->itemAbove(currentItem);	
	slotDataTreeItemSelected(item,0);
}

void DepthImagePlayer::slotPushButtonNext()
{
	if (fileDir.isEmpty())
		return;		//���û�п��ļ���

	if (indexOfCurrentItem == 0)
		return;		//��ǰ�Ѿ��ǵ�һ��

	if (currentItem == NULL)
		return;

	QTreeWidgetItem* item = ui.dataTreeFiles->itemBelow(currentItem);
	slotDataTreeItemSelected(item, 0);
}

void DepthImagePlayer::slotPushButtonPlayAndPause()
{
	if (fileDir.isEmpty())
		return;		//���û�п��ļ���

	if (indexOfCurrentItem == 0)
		return;		//��ǰ�Ѿ��ǵ�һ��

	//TODO �Զ��ӵ�һ�Ų���
	if (currentItem == NULL)
		return;

	if (process.getRunState())
	{
		//�������У�ֹͣ
		process.stop();
		QObject::disconnect(&process, SIGNAL(updateImage(cv::Mat, int)), this, SLOT(slotUpdateImage(cv::Mat, int)));

		//UI���洦��
		ui.pushButtonPlayAndPause->setIcon(QIcon(":/DepthImagePlayer/Resources/icon/play.png"));
	}
	else
	{
		//ͼ����²�
		QObject::connect(&process, SIGNAL(updateImage(cv::Mat, int)), this, SLOT(slotUpdateImage(cv::Mat, int)));

		//UI�������
		ui.pushButtonPlayAndPause->setIcon(QIcon(":/DepthImagePlayer/Resources/icon/pause.png"));

		//����׼��
		process.setCurrentIndex(indexOfCurrentItem);
		process.start();
	}

}

void DepthImagePlayer::slotDataTreeItemSelected(QTreeWidgetItem* item, int i)
{
	QString imageName = fileDir + "/"+item->text(0);
	indexOfCurrentItem = ui.dataTreeFiles->indexOfTopLevelItem(item);
	currentItem = item;

	//����ͼƬ
	cv::Mat img = cv::imread(imageName.toLocal8Bit().toStdString(), CV_LOAD_IMAGE_ANYCOLOR | CV_LOAD_IMAGE_ANYDEPTH);
	if (img.type() != CV_16U)
		ui.statusBar->showMessage(tr("Image is not CV_16U, may cause error!"), 3000);

	cv::Mat zip;
	cv::Mat colorMap;
	img.convertTo(zip, CV_8U, 256.0/(maxValue-minValue),-(double)minValue/(maxValue-minValue));	//�ռ�ѹ��
	cv::applyColorMap(zip, colorMap, cv::COLORMAP_JET);											//α��ɫ��
	cv::cvtColor(colorMap, colorMap, CV_BGR2RGB);												//��ɫ�ռ�ת��
	QImage qimg = QImage((const unsigned char*)(colorMap.data), colorMap.cols, colorMap.rows, QImage::Format_RGB888);
	ui.labelImageOri->setPixmap(QPixmap::fromImage(qimg));

	//״̬������
	ui.statusBar->showMessage(tr("Open ") + imageName, 3000);
}

void DepthImagePlayer::slotAlgorithmChecked()
{
	//��ȡѡ��״̬
	int state = ui.checkBoxAlgorithm->checkState();
	qDebug() << state;


	if (state)
	{
		//����
		ui.lableImageRst->show();
		//TODO process����
	}
	else
	{
		//������
		ui.lableImageRst->hide();
		//TODO process����
	}
}

void DepthImagePlayer::slotChangeMaxAndMinValue()
{
	//��ȡ���
	maxValue = ui.lineEditMax->text().toUShort();
	minValue = ui.lineEditMin->text().toUShort();

	//��ֹ�쳣
	ui.lineEditMax->setText(QString::number(maxValue));
	ui.lineEditMin->setText(QString::number(minValue));

	//���û���ڲ���
	//���¼���һ�µ�ǰͼƬ
	if (!process.getRunState())
	{
		slotDataTreeItemSelected(currentItem, 0);
	}
		
}

void DepthImagePlayer::slotChangeTimeValue()
{
	uint16_t time = ui.lineEditTimes->text().toUShort();
	ui.lineEditTimes->setText(QString::number(time));

	//������ʱ
	process.setTimes(time);
}

void DepthImagePlayer::slotUpdateImage(cv::Mat img, int rst)
{
	qDebug() << rst;
	if (rst < 0)
	{
		QObject::disconnect(&process, SIGNAL(updateImage(cv::Mat, int)), this, SLOT(slotUpdateImage(cv::Mat, int)));
		
		//UI�쳣����
		ui.pushButtonPlayAndPause->setIcon(QIcon(":/DepthImagePlayer/Resources/icon/play.png"));
			
		return;
	}
	qDebug() << img.type();
	indexOfCurrentItem = rst;
	cv::Mat zip;
	cv::Mat colorMap;
	img.convertTo(zip, CV_8U, 256.0 / (maxValue - minValue), -(double)minValue / (maxValue - minValue));	//�ռ�ѹ��
	cv::applyColorMap(zip, colorMap, cv::COLORMAP_JET);											//α��ɫ��
	cv::cvtColor(colorMap, colorMap, CV_BGR2RGB);												//��ɫ�ռ�ת��
	QImage qimg = QImage((const unsigned char*)(colorMap.data), colorMap.cols, colorMap.rows, QImage::Format_RGB888);
	ui.labelImageOri->setPixmap(QPixmap::fromImage(qimg));
}