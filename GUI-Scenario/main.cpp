#include <QtGui/QGuiApplication>
#include <QtQml>
#include "qtquick2applicationviewer.h"

#include "scenariocontroller.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QtQuick2ApplicationViewer viewer;
    viewer.setMainQmlFile(QStringLiteral("qml/GUI-Scenario/main.qml"));
    viewer.showExpanded();

    // create a controller
    ScenarioController controller{new Scenario{}};

    //connect signals from QML

    QObject::connect((QObject*)viewer.rootObject(), SIGNAL(testSignal(QString)),&controller, SLOT(oklart(QString)));
    QObject::connect((QObject*)viewer.rootObject(), SIGNAL(setDropAreaParent(int)),&controller, SLOT(set_active_block_number_(int)));
    QObject::connect((QObject*)viewer.rootObject(), SIGNAL(setDropAreaSide(QString)),&controller, SLOT(set_active_block_side(QString)));
    QObject::connect((QObject*)viewer.rootObject(), SIGNAL(add_block(int, QString)),&controller, SLOT(add_block(int,QString)));
    QObject::connect((QObject*)viewer.rootObject(), SIGNAL(editValueBlock(QString, bool, int)),&controller, SLOT(edit_valueblock(QString, bool, int)));
    QObject::connect((QObject*)viewer.rootObject(), SIGNAL(setCompareBlockValue(int)),&controller, SLOT(set_compareblock_value(int)));

    //TODO: complete signals below
     //QObject::connect((QObject*)viewer.rootObject(), SIGNAL(editDamageBlock(QString, bool, int)),&controller, SLOT(edit_damageblock(QString, bool, int)));




    // export instance to qml
    QQmlContext *ctxt = viewer.rootContext();
    //ctxt->setContextProperty("sController", &controller);

    return app.exec();
}
