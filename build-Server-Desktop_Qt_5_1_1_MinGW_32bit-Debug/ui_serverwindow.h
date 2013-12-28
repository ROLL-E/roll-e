/********************************************************************************
** Form generated from reading UI file 'serverwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.1.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SERVERWINDOW_H
#define UI_SERVERWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ServerWindow
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *ServerWindow)
    {
        if (ServerWindow->objectName().isEmpty())
            ServerWindow->setObjectName(QStringLiteral("ServerWindow"));
        ServerWindow->resize(400, 300);
        menuBar = new QMenuBar(ServerWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        ServerWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(ServerWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        ServerWindow->addToolBar(mainToolBar);
        centralWidget = new QWidget(ServerWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        ServerWindow->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(ServerWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        ServerWindow->setStatusBar(statusBar);

        retranslateUi(ServerWindow);

        QMetaObject::connectSlotsByName(ServerWindow);
    } // setupUi

    void retranslateUi(QMainWindow *ServerWindow)
    {
        ServerWindow->setWindowTitle(QApplication::translate("ServerWindow", "ServerWindow", 0));
    } // retranslateUi

};

namespace Ui {
    class ServerWindow: public Ui_ServerWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SERVERWINDOW_H
