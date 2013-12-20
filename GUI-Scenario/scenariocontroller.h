#ifndef SCENARIOCONTROLLER_H
#define SCENARIOCONTROLLER_H

#include <QObject>
#include <QString>
#include <QDebug>
#include <QMap>

#include "Scenario.h"

class ScenarioController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool showEditor READ showEditor WRITE set_showEditor NOTIFY editorChanged)

public:
    ScenarioController();
    ScenarioController(Scenario*);

    //QML READ functions
    bool showEditor() const {return showEditor_;}

    //QML WRITE functions
    void set_showEditor(const bool showEditor) { showEditor_ = showEditor; emit editorChanged();}



public slots:
    void oklart(QString msg) {qDebug() << msg;}
    void add_block(int number, QString type);

    void set_active_block_number_(int number) {qDebug() << "active block is set to number " << number; active_block_number_ = number;}
    void set_active_block_side(QString side) { active_block_side_ = side;}

    void edit_valueblock(QString stat, bool intent, int blocknr);
    void edit_damageblock(QString, bool, int);
    void edit_compareblock(QString, bool, int);

    void set_compareblock_value(int blocknr);

private:
    // variables
    bool showEditor_;

    Scenario* current_scenario_;

    int active_block_number_;
    QString active_block_side_;

    QMap<int, LogicBlock*> block_map_;


signals:
    void blocknumberChanged();
    void editorChanged();

};

#endif // SCENARIOCONTROLLER_H
