/**
* @file depthimageplayer.cpp
* @brief The main UI handle function.
* @details Include the function handle the UI action.
* @mainpage DetpthImagePlayer
* @author Oliver Sun
* @email admin@sunhx.cn
* @version 1.0.0
* @date 2019-11-8
*/

#include "depthimageplayer.h"

/**
* @brief 构造函数
* @details 完成UI界面初始化和信号槽的连接
*
* @param parent 父类指针
* @return void
* @note
*/
DepthImagePlayer::DepthImagePlayer(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	//默认不启用算法，隐藏算法结果框
	ui.lableImageRst->hide();

	//图像点击事件
	ui.labelImageOri->installEventFilter(this); //label点击事件会调用eventFilter函数

	//按钮槽
	QObject::connect(ui.actionOpen, &QAction::triggered, this, &DepthImagePlayer::open);
	QObject::connect(ui.actionClean, &QAction::triggered, this, &DepthImagePlayer::clean);
	QObject::connect(ui.pushButtonLast, SIGNAL(clicked()), this, SLOT(slotPushButtonLast()));
	QObject::connect(ui.pushButtonNext, SIGNAL(clicked()), this, SLOT(slotPushButtonNext()));
	QObject::connect(ui.pushButtonPlayAndPause, SIGNAL(clicked()), this, SLOT(slotPushButtonPlayAndPause()));
	QObject::connect(ui.checkBoxAlgorithm, SIGNAL(clicked()), this, SLOT(slotAlgorithmChecked()));
	QObject::connect(ui.lineEditMax, SIGNAL(editingFinished()), this, SLOT(slotChangeMaxAndMinValue()));
	QObject::connect(ui.lineEditMin, SIGNAL(editingFinished()), this, SLOT(slotChangeMaxAndMinValue()));
	QObject::connect(ui.lineEditTimes, SIGNAL(editingFinished()), this, SLOT(slotChangeTimeValue()));
	QObject::connect(ui.labelImageOri, SIGNAL(clicked()), this, SLOT(slotLabelClicked()));
	//文件树相关槽
	QObject::connect(ui.dataTreeFiles, SIGNAL(itemDoubleClicked(QTreeWidgetItem*, int)), this, SLOT(slotDataTreeItemSelected(QTreeWidgetItem*, int)));
	

}

/**
* @brief 析构函数
* @details 类析构时调用
*
* @param void
* @return void
* @note
*/
DepthImagePlayer::~DepthImagePlayer()
{

}

/**
* @brief 打开文件夹
* @details 根据用户选择打开文件夹，并将文件夹内png图片在文件树中显示
*
* @param void
* @return void
* @note 暂时没有考虑文件量比较大的情况下打开慢的问题
*/
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

/**
* @brief 清除文件树区域
* @details 回到启动初始状态
*
* @param void
* @return void
* @note 
*/
void DepthImagePlayer::clean()
{
	fileDir.clear();
	ui.dataTreeFiles->clear();

	//状态栏显示结果
	ui.statusBar->showMessage(tr("Clean"), 3000);
}

/**
* @brief 上一幅图像按钮按下槽
* @details 加载上一幅图像并在界面上显示
*
* @param void
* @return void
* @note 
*/
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

/**
* @brief 下一幅图像按钮按下槽
* @details 加载下一幅图像并在界面上显示
*
* @param void
* @return void
* @note 
*/
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

/**
* @brief 播放暂停按钮按下槽
* @details 开启子线程负责循环读取图片文件，暂停文件读取。
*
* @param void
* @return void
* @note 
*/
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

/**
* @brief 文件树元素双击相应槽
* @details 获取双击的文件树元素，打开并显示图片文件，并存标记为当前元素。
*
* @param item 双击元素的指针
* @param i 第i列元素
* @return void
* @note 
*/
void DepthImagePlayer::slotDataTreeItemSelected(QTreeWidgetItem* item, int i)
{
	QString imageName = fileDir + "/"+item->text(0);
	indexOfCurrentItem = ui.dataTreeFiles->indexOfTopLevelItem(item);
	currentItem = item;

	//加载图片
	cv::Mat img = cv::imread(imageName.toLocal8Bit().toStdString(), CV_LOAD_IMAGE_ANYCOLOR | CV_LOAD_IMAGE_ANYDEPTH);
	if (img.type() != CV_16U)
		ui.statusBar->showMessage(tr("Image is not CV_16U, may cause error!"), 3000);

	matOri_uint16 = img.clone();
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

/**
* @brief 算法复选框点击槽
* @details 通知子线程，在循环读取的时候是否要调用相应算法类
*
* @param void
* @return void
* @note 暂时没有考虑单张读取时的算法调用
*/
void DepthImagePlayer::slotAlgorithmChecked()
{
	//获取选框状态
	int state = ui.checkBoxAlgorithm->checkState();


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

/**
* @brief 改变伪彩色变换时范围的最大最小值
* @details 深度图像转为伪彩色图像时需要进行深度缩放，value = (depth - min) / (max - min) * 255。
*
* @param void
* @return void
* @note
*/
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

/**
* @brief 修改子线程文件读取间隔事件
* @details 为了避免子线程读取速度过快造成主线程无响应，每次读取图像之间加入延时。
*
* @param void
* @return void
* @note 
*/
void DepthImagePlayer::slotChangeTimeValue()
{
	uint16_t time = ui.lineEditTimes->text().toUShort();
	ui.lineEditTimes->setText(QString::number(time));

	//设置延时
	process.setTimes(time);
}

/**
* @brief 更新图片槽
* @details 接收子线程读取图片完成后发送的完成信号，完成图像在UI上的显示。
*
* @param img 子线程传来的读取图像
* @param rst 当前读取到的图像序号，-1异常
* @return void
* @note 
*/
void DepthImagePlayer::slotUpdateImage(cv::Mat img, int rst)
{
	qDebug() << rst;
	if (rst < 0)
	{
		matOri_uint16 = img.clone();
		QObject::disconnect(&process, SIGNAL(updateImage(cv::Mat, int)), this, SLOT(slotUpdateImage(cv::Mat, int)));
		
		//UI异常处理
		ui.pushButtonPlayAndPause->setIcon(QIcon(":/DepthImagePlayer/Resources/icon/play.png"));
			
		return;
	}
	qDebug() << img.type();
	indexOfCurrentItem = rst;
	matOri_uint16 = img;
	cv::Mat zip;
	cv::Mat colorMap;
	img.convertTo(zip, CV_8U, 256.0 / (maxValue - minValue), -(double)minValue / (maxValue - minValue));	//空间压缩
	cv::applyColorMap(zip, colorMap, cv::COLORMAP_JET);											//伪彩色化
	cv::cvtColor(colorMap, colorMap, CV_BGR2RGB);												//颜色空间转换
	QImage qimg = QImage((const unsigned char*)(colorMap.data), colorMap.cols, colorMap.rows, QImage::Format_RGB888);
	ui.labelImageOri->setPixmap(QPixmap::fromImage(qimg));
}

/**
* @brief 事件过滤器
* @details 过滤图像点击事件，并获取点击坐标，在UI上显示点击点坐标、LSB和深度距离。
*
* @param obj 事件元素指针
* @param e 事件类
* @return void
* @note 
*/
bool DepthImagePlayer::eventFilter(QObject* obj, QEvent* e)
{
	//获取鼠标点击事件
	if (e->type() == QEvent::MouseButtonPress)
	{
		QMouseEvent* env = static_cast<QMouseEvent*>(e);
		//判断事件对象
		if (ui.labelImageOri == obj)
		{
			//获取坐标
			int img_x = env->x();
			int img_y = env->y();

			//判断是否有图像
			if (!matOri_uint16.empty())
			{
				ushort value = matOri_uint16.at<ushort>(img_y, img_x);
				double depth = value * 1250.0 / 30000;

				ui.lineEditX->setText(QString::number(img_x));
				ui.lineEditY->setText(QString::number(img_y));
				ui.lineEditValue->setText(QString::number(value));

				//无效点显示
				if (value > 30000)
					ui.lineEditDepth->setText("NULL");
				else
					ui.lineEditDepth->setText(QString::number(depth));
			}
			
			return true;
		}
	}

	return false;		//其他事件不处理，继续传递
}