#include "skillmodel_QML.h"

SkillModelQML::SkillModelQML(QObject* parent) : QObject(parent)
{
}

SkillModelQML::SkillModelQML(const QString &name, const QString &modifier, int skill, QObject *parent)
    : QObject{parent}, name_{name}, modifier_{modifier}, skill_{skill}
{
}

QString SkillModelQML::name() const
{
    return name_;
}

void SkillModelQML::set_name(const QString &name)
{
    if (name != name_) {
        name_ = name;
        emit nameChanged();
    }
}

QString SkillModelQML::modifier() const
{
    return modifier_;
}

void SkillModelQML::set_modifier(const QString &modifier)
{
    if (modifier != modifier_) {
        modifier_ = modifier;
        emit modifierChanged();
    }
}

int SkillModelQML::skill() const
{
    return skill_;
}

void SkillModelQML::set_skill(int skill)
{
    if (skill != skill_){
        skill_ = skill;
        emit skillChanged();
    }
}
