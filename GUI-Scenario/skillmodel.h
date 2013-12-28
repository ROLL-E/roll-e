#ifndef SKILLMODEL_H
#define SKILLMODEL_H

#include <QObject>


class SkillModel : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString name READ name WRITE set_name  NOTIFY nameChanged)
    Q_PROPERTY(QString modifier READ modifier WRITE set_modifier  NOTIFY modifierChanged)
    Q_PROPERTY(int skill READ skill WRITE set_skill NOTIFY skillChanged)
public:
    SkillModel(QObject* parent=0);
    SkillModel(const QString &name, const QString &modifier, int skill, QObject* parent=0);

    QString name() const;
    void set_name(const QString &name);

    QString modifier() const;
    void set_modifier(const QString &modifier);

    int skill() const;
    void set_skill(int skill);

signals:
    void nameChanged();
    void modifierChanged();
    void skillChanged();


private:
    QString name_;
    QString modifier_;
    int skill_;

};

#endif // SKILLMODEL_H
