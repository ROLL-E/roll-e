/********************************************************************************
** Form generated from reading UI file 'characterdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.1.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHARACTERDIALOG_H
#define UI_CHARACTERDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>

QT_BEGIN_NAMESPACE

class Ui_characterDialog
{
public:
    QDialogButtonBox *buttonBox;
    QLineEdit *nameLineEdit;
    QLabel *label;
    QListView *skillListView;
    QLabel *label_2;
    QPushButton *addSkillButton;
    QLineEdit *lineEdit;
    QLabel *label_4;
    QLabel *label_5;
    QComboBox *skillsComboBox;
    QTableWidget *attr_tableWidget;

    void setupUi(QDialog *characterDialog)
    {
        if (characterDialog->objectName().isEmpty())
            characterDialog->setObjectName(QStringLiteral("characterDialog"));
        characterDialog->resize(558, 456);
        buttonBox = new QDialogButtonBox(characterDialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(20, 410, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        nameLineEdit = new QLineEdit(characterDialog);
        nameLineEdit->setObjectName(QStringLiteral("nameLineEdit"));
        nameLineEdit->setGeometry(QRect(120, 10, 113, 21));
        label = new QLabel(characterDialog);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(10, 10, 62, 19));
        skillListView = new QListView(characterDialog);
        skillListView->setObjectName(QStringLiteral("skillListView"));
        skillListView->setGeometry(QRect(270, 30, 221, 331));
        label_2 = new QLabel(characterDialog);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(280, 10, 62, 19));
        addSkillButton = new QPushButton(characterDialog);
        addSkillButton->setObjectName(QStringLiteral("addSkillButton"));
        addSkillButton->setGeometry(QRect(270, 370, 91, 32));
        lineEdit = new QLineEdit(characterDialog);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(120, 40, 113, 21));
        label_4 = new QLabel(characterDialog);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(10, 40, 91, 19));
        label_5 = new QLabel(characterDialog);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(10, 80, 91, 19));
        skillsComboBox = new QComboBox(characterDialog);
        skillsComboBox->setObjectName(QStringLiteral("skillsComboBox"));
        skillsComboBox->setGeometry(QRect(360, 370, 141, 26));
        attr_tableWidget = new QTableWidget(characterDialog);
        if (attr_tableWidget->columnCount() < 2)
            attr_tableWidget->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        attr_tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        attr_tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        attr_tableWidget->setObjectName(QStringLiteral("attr_tableWidget"));
        attr_tableWidget->setGeometry(QRect(10, 111, 201, 201));

        retranslateUi(characterDialog);
        QObject::connect(buttonBox, SIGNAL(rejected()), characterDialog, SLOT(reject()));
        QObject::connect(buttonBox, SIGNAL(accepted()), characterDialog, SLOT(accept()));

        QMetaObject::connectSlotsByName(characterDialog);
    } // setupUi

    void retranslateUi(QDialog *characterDialog)
    {
        characterDialog->setWindowTitle(QApplication::translate("characterDialog", "Dialog", 0));
        label->setText(QApplication::translate("characterDialog", "Name", 0));
        label_2->setText(QApplication::translate("characterDialog", "Skills", 0));
        addSkillButton->setText(QApplication::translate("characterDialog", "Add Skill", 0));
        label_4->setText(QApplication::translate("characterDialog", "Max Weight", 0));
        label_5->setText(QApplication::translate("characterDialog", "Attributes", 0));
        QTableWidgetItem *___qtablewidgetitem = attr_tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("characterDialog", "Attribute", 0));
        QTableWidgetItem *___qtablewidgetitem1 = attr_tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("characterDialog", "Value", 0));
    } // retranslateUi

};

namespace Ui {
    class characterDialog: public Ui_characterDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHARACTERDIALOG_H
