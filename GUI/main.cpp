#include <QtGui/QGuiApplication>
#include "qtquick2applicationviewer.h"
#include "Story.h"
#include "GameSave.h"

#include <QtQml>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    GameSave gamesave;
    QtQuick2ApplicationViewer viewer;
    viewer.setMainQmlFile(QStringLiteral("qml/ROLLE_UI/main.qml"));
    viewer.showExpanded();

    Story* main_story = new Story(Ruleset({"strength"}));
    QQmlContext* ctxt = viewer.rootContext();

    ctxt->setContextProperty("story", main_story);
    ctxt->setContextProperty("gamesave", &gamesave);
    return app.exec();
}
