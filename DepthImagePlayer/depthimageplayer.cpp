#include "depthimageplayer.h"

DepthImagePlayer::DepthImagePlayer(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	//默认不启用算法，隐藏算法结果框
	ui.lableImageRst->hide();

	//按钮槽
	QObject::connect(ui.actionOpen, &QAction::triggered, this, &DepthImagePlayer::open);
	QObject::connect(ui.actionClean, &QAction::triggered, this, &DepthImagePlayer::clean);
	QObject::connect(ui.pushButtonLast, SIGNAL(clicked()), this, SLOT(slotPushButtonLast()));
	QObject::connect(ui.pushButtonNext, SIGNAL(clicked()), this, SLOT(slotPushButtonNext()));
	QObject::connect(ui.pushButtonPlayAndPause, SIGNAL(clicked()), this, SLOT(slotPushButtonPlayAndPause()));
	QObject::connect(ui.checkBoxAlgorithm, SIGNAL(stateChanged()), this, SLOT(slotAlgorithmChecked()));
	QObject::connect(ui.lineEditMax, SIGNAL(editingFinished()), this, SLOT(slotChangeMaxAndMinValue()));
	QObject::connect(ui.lineEditMin, SIGNAL(editingFinished()), this, SLOT(slotChangeMaxAndMinValue()));
	QObject::connect(ui.lineEditTimes, SIGNAL(editingFinished()), this, SLOT(slotChangeTimeValue()));
	//文件树相关槽
	QObject::connect(ui.dataTreeFiles, SIGNAL(itemDoubleClicked(QTreeWidgetItem*, int)), this, SLOT(slotDataTreeItemSelected(QTreeWidgetItem*, int)));
	

}

DepthImagePlayer::~DepthImagePlayer()
{

}


void DepthImagePlayer::open()
{
	bool flag = 0;	//标记是否已经有文件夹打开
	if (!fileDir.isEmpty())
		flag = 1;

	QString dirfile = QFileDialog::getExistingDirectory(this, tr("Open files dir"));
	if (dirfile.isEmpty())
		return;		//没有选择文件夹，直接结束

	//如果已经有文件夹打开，先清空
	if (flag)
	{
		clean();
	}

	fileDir = dirfile;

	//打开文件夹
	QDir dir(fileDir);
	QStringList filter;		//创建过滤器
	filter << "*.png";
	QStringList files = dir.entryList(filter, QDir::Files | QDir::Readable, QDir::Name);

	//设置线程类
	process.setDir(fileDir);
	process.setFilesList(files);


	//更新资源树
	for (int i = 0; i < files.size(); i++)
	{
		QString name = files.at(i);
		QTreeWidgetItem *child = new QTreeWidgetItem(QStringList() << name);
		ui.dataTreeFiles->addTopLevelItem(child);
	}

	//状态栏显示结果
	ui.statusBar->showMessage(tr("Open ") + fileDir, 3000);

}

void DepthImagePlayer::clean()
{
	fileDir.clear();
	ui.dataTreeFiles->clear();

	//状态栏显示结果
	ui.statusBar->showMessage(tr("Clean"), 3000);
}

void DepthImagePlayer::slotPushButtonLast()
{
	if (fileDir.isEmpty())
		return;		//如果没有开文件夹

	if (indexOfCurrentItem == 0)
		return;		//当前已经是第一张
	
	if (currentItem == NULL)
		return;

	QTreeWidgetItem* item = ui.dataTreeFiles->itemAbove(currentItem);	
	slotDataTreeItemSelected(item,0);
}

void DepthImagePlayer::slotPushButtonNext()
{
	if (fileDir.isEmpty())
		return;		//如果没有开文件夹

	if (indexOfCurrentItem == 0)
		return;		//当前已经是第一张

	if (currentItem == NULL)
		return;

	QTreeWidgetItem* item = ui.dataTreeFiles->itemBelow(currentItem);
	slotDataTreeItemSelected(item, 0);
}

void DepthImagePlayer::slotPushButtonPlayAndPause()
{
	if (fileDir.isEmpty())
		return;		//如果没有开文件夹

	if (indexOfCurrentItem == 0)
		return;		//当前已经是第一张

	//TODO 自动从第一张播放
	if (currentItem == NULL)
		return;

	if (process.getRunState())
	{
		//正在运行，停止
		process.stop();
		QObject::disconnect(&process, SIGNAL(updateImage(cv::Mat, int)), this, SLOT(slotUpdateImage(cv::Mat, int)));

		//UI界面处理
		ui.pushButtonPlayAndPause->setIcon(QIcon(":/DepthImagePlayer/Resources/icon/play.png"));
	}
	else
	{
		//图像更新槽
		QObject::connect(&process, SIGNAL(updateImage(cv::Mat, int)), this, SLOT(slotUpdateImage(cv::Mat, int)));

		//UI界面更新
		ui.pushButtonPlayAndPause->setIcon(QIcon(":/DepthImagePlayer/Resources/icon/pause.png"));

		//启动准备
		process.setCurrentIndex(indexOfCurrentItem);
		process.start();
	}

}

void DepthImagePlayer::slotDataTreeItemSelected(QTreeWidgetItem* item, int i)
{
	QString imageName = fileDir + "/"+item->text(0);
	indexOfCurrentItem = ui.dataTreeFiles->indexOfTopLevelItem(item);
	currentItem = item;

	//加载图片
	cv::Mat img = cv::imread(imageName.toLocal8Bit().toStdString(), CV_LOAD_IMAGE_ANYCOLOR | CV_LOAD_IMAGE_ANYDEPTH);
	if (img.type() != CV_16U)
		ui.statusBar->showMessage(tr("Image is not CV_16U, may cause error!"), 3000);

	cv::Mat zip;
	cv::Mat colorMap;
	img.convertTo(zip, CV_8U, 256.0/(maxValue-minValue),-(double)minValue/(maxValue-minValue));	//空间压缩
	cv::applyColorMap(zip, colorMap, cv::COLORMAP_JET);											//伪彩色化
	cv::cvtColor(colorMap, colorMap, CV_BGR2RGB);												//颜色空间转换
	QImage qimg = QImage((const unsigned char*)(colorMap.data), colorMap.cols, colorMap.rows, QImage::Format_RGB888);
	ui.labelImageOri->setPixmap(QPixmap::fromImage(qimg));

	//状态栏更新
	ui.statusBar->showMessage(tr("Open ") + imageName, 3000);
}

void DepthImagePlayer::slotAlgorithmChecked()
{
	//获取选框状态
	int state = ui.checkBoxAlgorithm->checkState();
	qDebug() << state;


	if (state)
	{
		//启用
		ui.lableImageRst->show();
		//TODO process设置
	}
	else
	{
		//不启用
		ui.lableImageRst->hide();
		//TODO process设置
	}
}

void DepthImagePlayer::slotChangeMaxAndMinValue()
{
	//获取结果
	maxValue = ui.lineEditMax->text().toUShort();
	minValue = ui.lineEditMin->text().toUShort();

	//防止异常
	ui.lineEditMax->setText(QString::number(maxValue));
	ui.lineEditMin->setText(QString::number(minValue));

	//如果没有在播放
	//重新加载一下当前图片
	if (!process.getRunState())
	{
		slotDataTreeItemSelected(currentItem, 0);
	}
		
}

void DepthImagePlayer::slotChangeTimeValue()
{
	uint16_t time = ui.lineEditTimes->text().toUShort();
	ui.lineEditTimes->setText(QString::number(time));

	//设置延时
	process.setTimes(time);
}

void DepthImagePlayer::slotUpdateImage(cv::Mat img, int rst)
{
	qDebug() << rst;
	if (rst < 0)
	{
		QObject::disconnect(&process, SIGNAL(updateImage(cv::Mat, int)), this, SLOT(slotUpdateImage(cv::Mat, int)));
		
		//UI异常处理
		ui.pushButtonPlayAndPause->setIcon(QIcon(":/DepthImagePlayer/Resources/icon/play.png"));
			
		return;
	}
	qDebug() << img.type();
	indexOfCurrentItem = rst;
	cv::Mat zip;
	cv::Mat colorMap;
	img.convertTo(zip, CV_8U, 256.0 / (maxValue - minValue), -(double)minValue / (maxValue - minValue));	//空间压缩
	cv::applyColorMap(zip, colorMap, cv::COLORMAP_JET);											//伪彩色化
	cv::cvtColor(colorMap, colorMap, CV_BGR2RGB);												//颜色空间转换
	QImage qimg = QImage((const unsigned char*)(colorMap.data), colorMap.cols, colorMap.rows, QImage::Format_RGB888);
	ui.labelImageOri->setPixmap(QPixmap::fromImage(qimg));
}