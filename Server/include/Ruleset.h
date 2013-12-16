#ifndef RULESET_H
#define RULESET_H
#include <QList>
#include <QString>
#include <QMap>

class Scenario;
class Skill;

class Ruleset {

private:
    QList<QString> allowed_attributes;
    QList<Skill*> allowed_skills;
    QList<Scenario*> scenarios;

public:
    QMap<quint16, Skill*> skill_id_map;

    Ruleset(QList<QString>);
    Ruleset(const Ruleset&);
    QList<Scenario*> get_scenarios() const;
    QList<Skill*> get_skills() const;

    void add_scenario(Scenario*);
    void add_skill(Skill*);

    void remove_scenario(Scenario*);
    void remove_skill(Skill*);
};

#endif
