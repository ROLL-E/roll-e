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
#include "Skill.h"
#include "itemmodel.h"
#include "skillmodel_QML.h"



class ScenarioController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool showEditor READ showEditor WRITE set_showEditor NOTIFY editorChanged)
    Q_PROPERTY(QVariant all_characters READ all_characters NOTIFY character_list_changed)
    //TODO: add models for attributes
    Q_PROPERTY(QVariant items READ items NOTIFY itemsChanged)
    Q_PROPERTY(QVariant skills READ skills NOTIFY skillsChanged)
    Q_PROPERTY(QVariant attributes READ attributes NOTIFY attributesChanged)


public:
    ScenarioController();
    ScenarioController(Scenario*);
    ScenarioController(Character* primary_character, QList<Character*> all_characters, QMap<quint16, Item*> items, QList<Skill*> skills, QList<QString> attributes);

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

    // we need to decide if one should be able to add more than one "attribute" per skill/item for each value-block
    Q_INVOKABLE void add_skill_valueblock(int skill, QString modifier, int blocknr);
    Q_INVOKABLE void remove_skill_valueblock(int skill, int blocknr);
    Q_INVOKABLE void add_item_valueblock(int id, QString attribute, int blocknr);
    Q_INVOKABLE void remove_item_valueblock(QString item, int id, int blocknr);


    // DONE
    Q_INVOKABLE void set_valueblock_value(int value, int blocknr);
    Q_INVOKABLE void set_valueblock_roll(int sides, int number, int blocknr);
    Q_INVOKABLE void add_attribute_valueblock(QString attribute, int blocknr);
    Q_INVOKABLE void remove_attribute_valueblock(QString attribute, int blocknr);

    Q_INVOKABLE void set_damegeblock_target(QString character, int blocknr);
    Q_INVOKABLE void set_valueblock_intention(QString intention, int blocknr);

    //QML READ functions
    bool showEditor() const { return showEditor_; }
    QVariant all_characters() const { return QVariant::fromValue(character_list_); }
    QVariant items() const { return QVariant::fromValue(item_model_); }
    QVariant skills() const { return QVariant::fromValue(skill_model_); }
    QVariant attributes() const { return QVariant::fromValue(attribute_model_); }

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

    //QMap<QString, Item*> item_map_;
    QMap<quint16, Item*> items_;
    QList<QObject*> item_model_;


    QMap<int, Skill*> skill_map_;
    QList<Skill*> skills_;
    QList<QObject*> skill_model_;

    QList<QString> attributes_;
    QStringList attribute_model_;

    void update_characters();
    void update_items();
    void update_skills();
    void update_attributes();


signals:
    void blocknumberChanged();
    void editorChanged();
    void itemsChanged();
    void skillsChanged();
    void attributesChanged();
    void character_list_changed();

    void nameChanged();

};

#endif // SCENARIOCONTROLLER_H
