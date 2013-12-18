#include <QtGui/QGuiApplication>
#include <QtQml>


#include "qtquick2applicationviewer.h"
#include "Story.h"
#include "GameSave.h"

#include <QtQml>

#include "Story.h"
#include "Character.h"

// test
#include <QObject>
#include <QList>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    GameSave gamesave;
    QtQuick2ApplicationViewer viewer;
    viewer.setMainQmlFile(QStringLiteral("qml/ROLLE_UI/main.qml"));
    viewer.showExpanded();





    // test

    QList<QString> attr_list{"health", "armor", "strength"};
    Ruleset rs(attr_list);

    Story* main_story = new Story{rs};


    QMap<QString, qint16> attr_map{{"health", 10}, {"armor", 2}, {"strength", 5}};
    main_story->add_character(new Character(attr_map, 50, main_story));

    Character* bob = main_story->get_characters().front();
    bob->set_name("BOB!");

    // export instance to qml
    QQmlContext *ctxt = viewer.rootContext();;

    ctxt->setContextProperty("story", main_story);
ctxt->setContextProperty("gamesave", &gamesave);
    // characters

    QList<Character*> characters;
    characters = main_story->get_characters();

    QList<QObject*> Qcharacters;
    for (Character* character : characters)
        Qcharacters.append(dynamic_cast<QObject*>(character));

    ctxt->setContextProperty("characters", QVariant::fromValue(Qcharacters));


    return app.exec();
}
