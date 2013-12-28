#include "skillmodel.h"

SkillModel::SkillModel(QObject* parent) : QObject(parent)
{
}

SkillModel::SkillModel(const QString &name, const QString &modifier, int skill, QObject *parent)
    : QObject{parent}, name_{name}, modifier_{modifier}, skill_{skill}
{
}

QString SkillModel::name() const
{
    return name_;
}

void SkillModel::set_name(const QString &name)
{
    if (name != name_) {
        name_ = name;
        emit nameChanged();
    }
}

QString SkillModel::modifier() const
{
    return modifier_;
}

void SkillModel::set_modifier(const QString &modifier)
{
    if (modifier != modifier_) {
        modifier_ = modifier;
        emit modifierChanged();
    }
}

int SkillModel::skill() const
{
    return skill_;
}

void SkillModel::set_skill(int skill)
{
    if (skill != skill_){
        skill_ = skill;
        emit skillChanged();
    }
}
