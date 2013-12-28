/********************************************************************************
** Form generated from reading UI file 'itemdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.1.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ITEMDIALOG_H
#define UI_ITEMDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>

QT_BEGIN_NAMESPACE

class Ui_itemDialog
{
public:
    QDialogButtonBox *buttonBox;
    QTableWidget *tableWidget;
    QLineEdit *lineEdit;
    QLabel *label;
    QPushButton *pushButton;
    QTableWidget *tableWidget_2;
    QPushButton *pushButton_2;

    void setupUi(QDialog *itemDialog)
    {
        if (itemDialog->objectName().isEmpty())
            itemDialog->setObjectName(QStringLiteral("itemDialog"));
        itemDialog->resize(699, 376);
        buttonBox = new QDialogButtonBox(itemDialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(20, 330, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        tableWidget = new QTableWidget(itemDialog);
        if (tableWidget->columnCount() < 2)
            tableWidget->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));
        tableWidget->setGeometry(QRect(30, 70, 281, 241));
        tableWidget->horizontalHeader()->setDefaultSectionSize(138);
        lineEdit = new QLineEdit(itemDialog);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(140, 20, 113, 21));
        label = new QLabel(itemDialog);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(70, 20, 62, 19));
        pushButton = new QPushButton(itemDialog);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(30, 310, 115, 32));
        tableWidget_2 = new QTableWidget(itemDialog);
        if (tableWidget_2->columnCount() < 2)
            tableWidget_2->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget_2->setHorizontalHeaderItem(0, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget_2->setHorizontalHeaderItem(1, __qtablewidgetitem3);
        tableWidget_2->setObjectName(QStringLiteral("tableWidget_2"));
        tableWidget_2->setGeometry(QRect(380, 70, 261, 241));
        pushButton_2 = new QPushButton(itemDialog);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(380, 320, 115, 32));

        retranslateUi(itemDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), itemDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), itemDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(itemDialog);
    } // setupUi

    void retranslateUi(QDialog *itemDialog)
    {
        itemDialog->setWindowTitle(QApplication::translate("itemDialog", "Dialog", 0));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("itemDialog", "Attribute", 0));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("itemDialog", " Value", 0));
        label->setText(QApplication::translate("itemDialog", "Name", 0));
        pushButton->setText(QApplication::translate("itemDialog", "Add attribute", 0));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget_2->horizontalHeaderItem(0);
        ___qtablewidgetitem2->setText(QApplication::translate("itemDialog", "Modifier", 0));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget_2->horizontalHeaderItem(1);
        ___qtablewidgetitem3->setText(QApplication::translate("itemDialog", "Value", 0));
        pushButton_2->setText(QApplication::translate("itemDialog", "Add modifier", 0));
    } // retranslateUi

};

namespace Ui {
    class itemDialog: public Ui_itemDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ITEMDIALOG_H
