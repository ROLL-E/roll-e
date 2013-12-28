/********************************************************************************
** Form generated from reading UI file 'skilldialog.ui'
**
** Created by: Qt User Interface Compiler version 5.1.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SKILLDIALOG_H
#define UI_SKILLDIALOG_H

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

class Ui_skillDialog
{
public:
    QDialogButtonBox *buttonBox;
    QLabel *label;
    QLineEdit *lineEdit;
    QTableWidget *tableWidget;
    QPushButton *pushButton;

    void setupUi(QDialog *skillDialog)
    {
        if (skillDialog->objectName().isEmpty())
            skillDialog->setObjectName(QStringLiteral("skillDialog"));
        skillDialog->resize(481, 455);
        buttonBox = new QDialogButtonBox(skillDialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(50, 370, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        label = new QLabel(skillDialog);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(40, 10, 62, 19));
        lineEdit = new QLineEdit(skillDialog);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(120, 10, 113, 21));
        tableWidget = new QTableWidget(skillDialog);
        if (tableWidget->columnCount() < 2)
            tableWidget->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));
        tableWidget->setGeometry(QRect(70, 70, 256, 192));
        pushButton = new QPushButton(skillDialog);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(70, 280, 115, 32));

        retranslateUi(skillDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), skillDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), skillDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(skillDialog);
    } // setupUi

    void retranslateUi(QDialog *skillDialog)
    {
        skillDialog->setWindowTitle(QApplication::translate("skillDialog", "Dialog", 0));
        label->setText(QApplication::translate("skillDialog", "Name", 0));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("skillDialog", "Modifier", 0));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("skillDialog", "Value", 0));
        pushButton->setText(QApplication::translate("skillDialog", "Add Modifier", 0));
    } // retranslateUi

};

namespace Ui {
    class skillDialog: public Ui_skillDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SKILLDIALOG_H
