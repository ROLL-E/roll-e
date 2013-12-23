#include "itemmodel.h"

ItemModel::ItemModel(QObject* parent) : QObject(parent)
{
}

ItemModel::ItemModel(const QString &name, const QString &attribute, QObject *parent)
    : QObject{parent}, name_{name}, attribute_{attribute}
{
}

QString ItemModel::name() const
{
    return name_;
}

void ItemModel::set_name(const QString &name)
{
    if (name != name_) {
        name_ = name;
        emit nameChanged();
    }
}

QString ItemModel::attribute() const
{
    return attribute_;
}

void ItemModel::set_attribute(const QString &attribute)
{
    if (attribute != attribute_) {
        attribute_ = attribute;
        emit attributeChanged();
    }
}


