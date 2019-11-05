/********************************************************************************
** Form generated from reading UI file 'depthimageplayer.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DEPTHIMAGEPLAYER_H
#define UI_DEPTHIMAGEPLAYER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDockWidget>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DepthImagePlayerClass
{
public:
    QAction *actionOpen;
    QAction *actionClean;
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_3;
    QLabel *labelImageOri;
    QLabel *lableImageRst;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButtonLast;
    QPushButton *pushButtonPlayAndPause;
    QPushButton *pushButtonNext;
    QSpacerItem *horizontalSpacer_2;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;
    QDockWidget *dockWidgetFiles;
    QWidget *dockWidgetContents;
    QVBoxLayout *verticalLayout_3;
    QTreeWidget *dataTreeFiles;
    QDockWidget *dockWidgetParameters;
    QWidget *dockWidgetContents_2;
    QVBoxLayout *verticalLayout_4;
    QGridLayout *gridLayout;
    QLineEdit *lineEditMax;
    QLineEdit *lineEditTimes;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLineEdit *lineEditMin;
    QCheckBox *checkBoxAlgorithm;

    void setupUi(QMainWindow *DepthImagePlayerClass)
    {
        if (DepthImagePlayerClass->objectName().isEmpty())
            DepthImagePlayerClass->setObjectName(QStringLiteral("DepthImagePlayerClass"));
        DepthImagePlayerClass->resize(895, 613);
        actionOpen = new QAction(DepthImagePlayerClass);
        actionOpen->setObjectName(QStringLiteral("actionOpen"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/DepthImagePlayer/Resources/icon/open.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionOpen->setIcon(icon);
        actionClean = new QAction(DepthImagePlayerClass);
        actionClean->setObjectName(QStringLiteral("actionClean"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/DepthImagePlayer/Resources/icon/clean.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionClean->setIcon(icon1);
        centralWidget = new QWidget(DepthImagePlayerClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        horizontalLayout_2 = new QHBoxLayout(centralWidget);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(-1, -1, -1, 0);
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        labelImageOri = new QLabel(centralWidget);
        labelImageOri->setObjectName(QStringLiteral("labelImageOri"));

        horizontalLayout_3->addWidget(labelImageOri);

        lableImageRst = new QLabel(centralWidget);
        lableImageRst->setObjectName(QStringLiteral("lableImageRst"));

        horizontalLayout_3->addWidget(lableImageRst);


        verticalLayout_2->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer);

        pushButtonLast = new QPushButton(centralWidget);
        pushButtonLast->setObjectName(QStringLiteral("pushButtonLast"));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/DepthImagePlayer/Resources/icon/last.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButtonLast->setIcon(icon2);
        pushButtonLast->setIconSize(QSize(30, 30));

        horizontalLayout_4->addWidget(pushButtonLast);

        pushButtonPlayAndPause = new QPushButton(centralWidget);
        pushButtonPlayAndPause->setObjectName(QStringLiteral("pushButtonPlayAndPause"));
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/DepthImagePlayer/Resources/icon/play.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButtonPlayAndPause->setIcon(icon3);
        pushButtonPlayAndPause->setIconSize(QSize(30, 30));

        horizontalLayout_4->addWidget(pushButtonPlayAndPause);

        pushButtonNext = new QPushButton(centralWidget);
        pushButtonNext->setObjectName(QStringLiteral("pushButtonNext"));
        QIcon icon4;
        icon4.addFile(QStringLiteral(":/DepthImagePlayer/Resources/icon/next.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButtonNext->setIcon(icon4);
        pushButtonNext->setIconSize(QSize(30, 30));

        horizontalLayout_4->addWidget(pushButtonNext);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_2);


        verticalLayout_2->addLayout(horizontalLayout_4);


        horizontalLayout_2->addLayout(verticalLayout_2);

        DepthImagePlayerClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(DepthImagePlayerClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 895, 23));
        DepthImagePlayerClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(DepthImagePlayerClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        DepthImagePlayerClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(DepthImagePlayerClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        DepthImagePlayerClass->setStatusBar(statusBar);
        dockWidgetFiles = new QDockWidget(DepthImagePlayerClass);
        dockWidgetFiles->setObjectName(QStringLiteral("dockWidgetFiles"));
        dockWidgetFiles->setMinimumSize(QSize(200, 140));
        dockWidgetContents = new QWidget();
        dockWidgetContents->setObjectName(QStringLiteral("dockWidgetContents"));
        verticalLayout_3 = new QVBoxLayout(dockWidgetContents);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        dataTreeFiles = new QTreeWidget(dockWidgetContents);
        dataTreeFiles->setObjectName(QStringLiteral("dataTreeFiles"));
        dataTreeFiles->setMinimumSize(QSize(0, 100));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font.setPointSize(9);
        dataTreeFiles->setFont(font);
        dataTreeFiles->setContextMenuPolicy(Qt::CustomContextMenu);

        verticalLayout_3->addWidget(dataTreeFiles);

        dockWidgetFiles->setWidget(dockWidgetContents);
        DepthImagePlayerClass->addDockWidget(static_cast<Qt::DockWidgetArea>(1), dockWidgetFiles);
        dockWidgetParameters = new QDockWidget(DepthImagePlayerClass);
        dockWidgetParameters->setObjectName(QStringLiteral("dockWidgetParameters"));
        dockWidgetParameters->setMinimumSize(QSize(200, 136));
        dockWidgetContents_2 = new QWidget();
        dockWidgetContents_2->setObjectName(QStringLiteral("dockWidgetContents_2"));
        verticalLayout_4 = new QVBoxLayout(dockWidgetContents_2);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        lineEditMax = new QLineEdit(dockWidgetContents_2);
        lineEditMax->setObjectName(QStringLiteral("lineEditMax"));

        gridLayout->addWidget(lineEditMax, 2, 1, 1, 1);

        lineEditTimes = new QLineEdit(dockWidgetContents_2);
        lineEditTimes->setObjectName(QStringLiteral("lineEditTimes"));

        gridLayout->addWidget(lineEditTimes, 1, 1, 1, 1);

        label = new QLabel(dockWidgetContents_2);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 2, 0, 1, 1);

        label_2 = new QLabel(dockWidgetContents_2);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        label_3 = new QLabel(dockWidgetContents_2);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout->addWidget(label_3, 3, 0, 1, 1);

        lineEditMin = new QLineEdit(dockWidgetContents_2);
        lineEditMin->setObjectName(QStringLiteral("lineEditMin"));

        gridLayout->addWidget(lineEditMin, 3, 1, 1, 1);


        verticalLayout_4->addLayout(gridLayout);

        checkBoxAlgorithm = new QCheckBox(dockWidgetContents_2);
        checkBoxAlgorithm->setObjectName(QStringLiteral("checkBoxAlgorithm"));

        verticalLayout_4->addWidget(checkBoxAlgorithm);

        dockWidgetParameters->setWidget(dockWidgetContents_2);
        DepthImagePlayerClass->addDockWidget(static_cast<Qt::DockWidgetArea>(1), dockWidgetParameters);

        mainToolBar->addAction(actionOpen);
        mainToolBar->addAction(actionClean);

        retranslateUi(DepthImagePlayerClass);

        QMetaObject::connectSlotsByName(DepthImagePlayerClass);
    } // setupUi

    void retranslateUi(QMainWindow *DepthImagePlayerClass)
    {
        DepthImagePlayerClass->setWindowTitle(QApplication::translate("DepthImagePlayerClass", "DepthImagePlayer", 0));
        actionOpen->setText(QApplication::translate("DepthImagePlayerClass", "Open", 0));
        actionClean->setText(QApplication::translate("DepthImagePlayerClass", "clean", 0));
        labelImageOri->setText(QApplication::translate("DepthImagePlayerClass", "TextLabel", 0));
        lableImageRst->setText(QApplication::translate("DepthImagePlayerClass", "TextLabel", 0));
        pushButtonLast->setText(QString());
        pushButtonPlayAndPause->setText(QString());
        pushButtonNext->setText(QString());
        dockWidgetFiles->setWindowTitle(QApplication::translate("DepthImagePlayerClass", "Files", 0));
        QTreeWidgetItem *___qtreewidgetitem = dataTreeFiles->headerItem();
        ___qtreewidgetitem->setText(0, QApplication::translate("DepthImagePlayerClass", "Files", 0));
        dockWidgetParameters->setWindowTitle(QApplication::translate("DepthImagePlayerClass", "Parameters", 0));
        lineEditMax->setText(QApplication::translate("DepthImagePlayerClass", "30000", 0));
        lineEditTimes->setText(QApplication::translate("DepthImagePlayerClass", "0", 0));
        label->setText(QApplication::translate("DepthImagePlayerClass", "Max:", 0));
        label_2->setText(QApplication::translate("DepthImagePlayerClass", "Times:", 0));
        label_3->setText(QApplication::translate("DepthImagePlayerClass", "Min:", 0));
        lineEditMin->setText(QApplication::translate("DepthImagePlayerClass", "0", 0));
        checkBoxAlgorithm->setText(QApplication::translate("DepthImagePlayerClass", "Run Algorithm", 0));
    } // retranslateUi

};

namespace Ui {
    class DepthImagePlayerClass: public Ui_DepthImagePlayerClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DEPTHIMAGEPLAYER_H
