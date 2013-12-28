#include <QtGui/QGuiApplication>
#include <QtQml>
#include "qtquick2applicationviewer.h"
#include <QList>

#include "scenariocontroller.h"
#include "Character.h"
#include "Item.h"
#include "Story.h"
#include "Skill.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

//    QtQuick2ApplicationViewer viewer;
//    viewer.setMainQmlFile(QStringLiteral("qml/GUI-Scenario/main.qml"));
//    viewer.showExpanded();


    //temp for testing


//    Story* story;
//    Item* hammer = new Item{"hammer"};
//    //story->add_item(hammer);
//    QMap<QString, qint16> attributes;
//    attributes["hp"] = 10;

//    Character player1{};//attributes, 5, story};

////    player1.set_name("player1");
////    player1.add_to_attribute("hp", 10);

//    Character player2;

//      player2.set_name("player2");
////    player2.add_to_attribute("hp", 13);
//    //player1.add_item(1); does not work for some reasaon LOOK IT UP!!!!!

//    QList<Character*> characterlist;

//    //characterlist.append(&player1);
//    characterlist.append(&player2);

//    QMap<quint16, Item*> items;
//    items[1] = hammer;

////    qDebug() << "before add";
////    player1.add_item(1);
////    qDebug() << "after add";
///
///

    //from other main

    QList<QString> attr_list{"health", "armor", "strength"};
    Ruleset rs(attr_list);

    Story* main_story = new Story(rs);

    QMap<QString, qint16> attr_map{{"health", 10}, {"armor", 2}, {"strength", 5}};
    main_story->add_character(new Character(attr_map, 50, main_story));

    Character* bob = main_story->get_characters().front();
    bob->set_name("BOB!");


    try {
      Item* hammer1 = new Item("Hammer of doom");
      main_story->add_item(hammer1);
      hammer1->set_attribute("Weight", 20);

      Item* hammer2 = new Item("nicer hammah");
      main_story->add_item(hammer2);
      hammer2->set_attribute("Weight", 20);
      hammer2->set_attribute("bonk", 50);
      hammer2->set_attribute("smash", 3000);

      bob->add_item(hammer1->get_id());
      bob->add_item(hammer2->get_id());


      qDebug() << "Bob's stuff:";
      for (auto item_id : bob->inventory.get_items()) {
        qDebug() << main_story->get_items().value(item_id)->get_name();
      }
    }
    catch (const std::out_of_range& e) {
      qDebug() << "out_of_range exception: " << e.what();
    }


    Character* herman = new Character(attr_map, 10, main_story);
    main_story->add_character(herman);
    herman->set_name("Herr Man");

    rs.add_skill(new Skill("Break those cuffs"));
    rs.add_skill(new Skill("Eat horse"));
    rs.get_skills().at(0)->set_modifier("int", 10);
    rs.get_skills().at(0)->set_modifier("str", 11);
    rs.get_skills().at(1)->set_modifier("int" , 5);
    rs.get_skills().at(1)->set_modifier("str", 25);
    bob->add_skill(rs.get_skills().at(0));
    bob->add_skill(rs.get_skills().at(1));


    herman->add_skill(rs.get_skills().at(1));


    // create a controller
    ScenarioController controller{herman, main_story->get_characters(),main_story->get_items(),rs.get_skills(),rs.get_attributes()};

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

//    QStringList dataList;
//    dataList.append("Item 1");
//    dataList.append("Item 2");
//    dataList.append("Item 3");
//    dataList.append("Item 4");
//    dataList.append("Item 1");
//    dataList.append("Item 2");
//    dataList.append("Item 3");
//    dataList.append("Item 4");
//    dataList.append("Item 1");
//    dataList.append("Item 2");
//    dataList.append("Item 3");
//    dataList.append("Item 4");
//    dataList.append("Item 1");
//    dataList.append("Item 2");
//    dataList.append("Item 3");
//    dataList.append("Item 4");

//    // export instance to qml
//    QQmlContext *ctxt = viewer.rootContext();
//    ctxt->setContextProperty("controller", &controller);

    //ctxt->setContextProperty("dataList", QVariant::fromValue(dataList));

    //ctxt->setContextProperty("sController", &controller);

    //QML

    QtQuick2ApplicationViewer viewer;

    // export instance to qml
    QQmlContext *ctxt = viewer.rootContext();
    ctxt->setContextProperty("controller", &controller);


    viewer.setMainQmlFile(QStringLiteral("qml/GUI-Scenario/main.qml"));
    viewer.showExpanded();




    return app.exec();
}
