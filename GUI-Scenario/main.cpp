#include <QtGui/QGuiApplication>
#include <QtQml>
#include "qtquick2applicationviewer.h"
#include <QList>

#include "scenariocontroller.h"
#include "Character.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QtQuick2ApplicationViewer viewer;
    viewer.setMainQmlFile(QStringLiteral("qml/GUI-Scenario/main.qml"));
    viewer.showExpanded();


    //temp for testing

    Character player1;

    player1.set_name("player1");
    player1.add_to_attribute("hp", 10);

    Character player2;

    player2.set_name("player2");
    player2.add_to_attribute("hp", 13);

    QList<Character*> characterlist;

    characterlist.append(&player1);
    characterlist.append(&player2);

    // create a controller
    ScenarioController controller{&player1, characterlist};

    //connect signals from QML

//    QObject::connect((QObject*)viewer.rootObject(), SIGNAL(testSignal(QString)),&controller, SLOT(oklart(QString)));
//    QObject::connect((QObject*)viewer.rootObject(), SIGNAL(setDropAreaParent(int)),&controller, SLOT(set_active_block_number_(int)));
//    QObject::connect((QObject*)viewer.rootObject(), SIGNAL(setDropAreaSide(QString)),&controller, SLOT(set_active_block_side(QString)));
//    QObject::connect((QObject*)viewer.rootObject(), SIGNAL(add_block(int, QString)),&controller, SLOT(add_block(int,QString)));
//    QObject::connect((QObject*)viewer.rootObject(), SIGNAL(editValueBlock(QString, bool, int)),&controller, SLOT(edit_valueblock(QString, bool, int)));
//    QObject::connect((QObject*)viewer.rootObject(), SIGNAL(setCompareBlockValue(int)),&controller, SLOT(set_compareblock_value(int)));
//    QObject::connect((QObject*)viewer.rootObject(), SIGNAL(editDamageBlock(QString, bool, int)),&controller, SLOT(edit_damageblock(QString, bool, int)));

//    //TODO: complete signals below
//    QObject::connect((QObject*)viewer.rootObject(), SIGNAL(editCompareBlock(QString, bool, int)),&controller, SLOT(edit_compareblock(QString, bool, int)));

    QStringList dataList;
    dataList.append("Item 1");
    dataList.append("Item 2");
    dataList.append("Item 3");
    dataList.append("Item 4");
    dataList.append("Item 1");
    dataList.append("Item 2");
    dataList.append("Item 3");
    dataList.append("Item 4");
    dataList.append("Item 1");
    dataList.append("Item 2");
    dataList.append("Item 3");
    dataList.append("Item 4");
    dataList.append("Item 1");
    dataList.append("Item 2");
    dataList.append("Item 3");
    dataList.append("Item 4");

    // export instance to qml
    QQmlContext *ctxt = viewer.rootContext();
    ctxt->setContextProperty("controller", &controller);

    ctxt->setContextProperty("dataList", QVariant::fromValue(dataList));

    //ctxt->setContextProperty("sController", &controller);
    return app.exec();
}
