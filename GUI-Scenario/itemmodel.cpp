#include "itemmodel.h"

ItemModel::ItemModel(QObject* parent) : QObject(parent)
{
}

ItemModel::ItemModel(const QString &name, const QString &attribute, const int item_id,  QObject *parent)
    : QObject{parent}, name_{name}, attribute_{attribute}, item_id_{item_id}
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

int ItemModel::item_id() const
{
    return item_id_;
}

void ItemModel::set_item_id(const int &item_id)
{
    if (item_id != item_id_){
        item_id_ = item_id;
        emit itemIdChanged();
    }
}
