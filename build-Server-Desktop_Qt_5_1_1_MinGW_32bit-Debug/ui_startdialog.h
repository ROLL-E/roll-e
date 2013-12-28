/********************************************************************************
** Form generated from reading UI file 'startdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.1.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STARTDIALOG_H
#define UI_STARTDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>

QT_BEGIN_NAMESPACE

class Ui_startDialog
{
public:
    QDialogButtonBox *buttonBox;
    QPushButton *loadButton;
    QPushButton *pushButton_2;
    QLabel *label;
    QLabel *label_2;
    QTableWidget *tableWidget;

    void setupUi(QDialog *startDialog)
    {
        if (startDialog->objectName().isEmpty())
            startDialog->setObjectName(QStringLiteral("startDialog"));
        startDialog->resize(400, 300);
        buttonBox = new QDialogButtonBox(startDialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(30, 240, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        loadButton = new QPushButton(startDialog);
        loadButton->setObjectName(QStringLiteral("loadButton"));
        loadButton->setGeometry(QRect(230, 60, 131, 81));
        pushButton_2 = new QPushButton(startDialog);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(20, 250, 115, 32));
        label = new QLabel(startDialog);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(60, 10, 331, 19));
        label_2 = new QLabel(startDialog);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(60, 30, 181, 19));
        tableWidget = new QTableWidget(startDialog);
        if (tableWidget->columnCount() < 1)
            tableWidget->setColumnCount(1);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));
        tableWidget->setGeometry(QRect(20, 70, 111, 171));

        retranslateUi(startDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), startDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), startDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(startDialog);
    } // setupUi

    void retranslateUi(QDialog *startDialog)
    {
        startDialog->setWindowTitle(QApplication::translate("startDialog", "Dialog", 0));
        loadButton->setText(QApplication::translate("startDialog", "Load from file", 0));
        pushButton_2->setText(QApplication::translate("startDialog", "Add attribute", 0));
        label->setText(QApplication::translate("startDialog", "Either enter the allowed attributes for a new story", 0));
        label_2->setText(QApplication::translate("startDialog", "or load a saved game", 0));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("startDialog", "Attribute", 0));
    } // retranslateUi

};

namespace Ui {
    class startDialog: public Ui_startDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STARTDIALOG_H
