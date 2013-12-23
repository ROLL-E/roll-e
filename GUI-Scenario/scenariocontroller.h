#ifndef SCENARIOCONTROLLER_H
#define SCENARIOCONTROLLER_H

#include <QObject>
#include <QString>
#include <QDebug>
#include <QMap>
#include <QStringList>

#include "Scenario.h"
#include "Character.h"
#include "Item.h"
#include "itemmodel.h"


class ScenarioController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool showEditor READ showEditor WRITE set_showEditor NOTIFY editorChanged)
    Q_PROPERTY(QVariant all_characters READ all_characters NOTIFY character_list_changed)

public:
    ScenarioController();
    ScenarioController(Scenario*);
    ScenarioController(Character* primary_character, QList<Character*> all_characters);

    Q_INVOKABLE void print(QString msg) {qDebug() << msg;}


    // functions invokable in QML
    Q_INVOKABLE void set_active_block_number(int number) {qDebug() << "active block is set to number " << number; active_block_number_ = number;}

    Q_INVOKABLE void edit_valueblock(QString stat, bool intent, int blocknr);
    Q_INVOKABLE void edit_damageblock(QString, bool, int);
    Q_INVOKABLE void edit_compareblock(QString, bool, int);

    Q_INVOKABLE void add_block(int number, QString type);

    Q_INVOKABLE void set_active_block_side(QString side) { active_block_side_ = side;}
    Q_INVOKABLE void set_block_value(int blocknr);

    // settings for valueblock

    // TODO: implement functionality

    // don't get why or how the keys for these are used
    // will probably need access to all skills and items
    Q_INVOKABLE void add_skill_valueblock(QString skill, int blocknr);
    Q_INVOKABLE void remove_skill_valueblock(QString skill, int blocknr) {qDebug() << "Skill, remove" << skill << blocknr;}
    Q_INVOKABLE void add_item_valueblock(QString item, int blocknr);
    Q_INVOKABLE void remove_item_valueblock(QString item, int blocknr) {qDebug() << "Item, remove" << item << blocknr;}

    // will need access to all characters
    Q_INVOKABLE void set_damegeblock_target(QString character, int blocknr);

    // DONE
    Q_INVOKABLE void set_valueblock_value(int value, int blocknr);
    Q_INVOKABLE void set_valueblock_roll(int sides, int number, int blocknr);
    Q_INVOKABLE void add_attribute_valueblock(QString attribute, int blocknr);
    Q_INVOKABLE void remove_attribute_valueblock(QString attribute, int blocknr);


    //QML READ functions
    bool showEditor() const {return showEditor_;}
    QVariant all_characters() const { return QVariant::fromValue(character_list_);}

    //QML WRITE functions
    void set_showEditor(const bool showEditor) { showEditor_ = showEditor; emit editorChanged();}



public slots:
    void oklart(QString msg) {qDebug() << msg;}



private:
    // variables
    bool showEditor_;

    Scenario* current_scenario_;

    int active_block_number_;
    QString active_block_side_;

    QMap<int, LogicBlock*> block_map_;

    Character* primary_character_;
    QList<Character*> all_characters_;
    QStringList character_list_;
    QMap<QString, Character*> character_map_;

    QMap<QString, Item*> item_map_;
    QList<ItemModel*> item_model_;


    void update_characters();
    void update_items();


signals:
    void blocknumberChanged();
    void editorChanged();
    void character_list_changed();

};

#endif // SCENARIOCONTROLLER_H
