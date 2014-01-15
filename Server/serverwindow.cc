#include "serverwindow.h"
#include "ui_serverwindow.h"
#include "characterdialog.h"
#include "itemdialog.h"
#include <QStringListModel>
#include <QAbstractItemModel>
#include <QDebug>

#include "Story.h"
#include "Character.h"
#include "skillmodel.h"
#include "Item.h"
#include "Skill.h"

ServerWindow::ServerWindow(Story* the_story, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ServerWindow),
    story(the_story)
{
    ui->setupUi(this);


    update_characters();
}



ServerWindow::~ServerWindow()
{
    delete ui;
}

void ServerWindow::on_add_charButton_clicked()
{
    characterDialog charDialog(this);
    charDialog.exec();
}

void ServerWindow::update_characters(int row) {
    //QItemSelectionModel* selection = ui->char_listView->selectionModel();

    QStringList strList;
    if (row == -1) {
        for (Character* character : story->get_characters())
            strList.append(character->get_name());


        ui->char_listView->setModel(new QStringListModel(strList));
        ui->char_listView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    }
    //ui->char_listView->setSelectionModel(new QItemSelectionModel(selection->model()));


    if (ui->char_listView->selectionModel()->selectedRows().size() != 0){


        Character* character = story->get_characters().at(ui->char_listView->selectionModel()->selectedRows().at(0).row());

        ui->char_nameLabel->setText(character->get_name());
        ui->max_weightLabel->setText(QString::number(character->inventory.get_max_weight()));
        ui->curr_weightLabel->setText(QString::number(character->inventory.get_weight()));

        SkillModel* skills_model = new SkillModel(character->get_skills());
        ui->skills_listView->setModel(skills_model);

        ui->attr_tableWidget->setRowCount(character->get_attributes().size());
        for (int i{0}; i< character->get_attributes().size(); ++i) {
            ui->attr_tableWidget->setItem(i,0,new QTableWidgetItem(character->get_attributes().keys().at(i)));
            ui->attr_tableWidget->setItem(i,1,new QTableWidgetItem(QString::number(character->get_attributes().values().at(i))));
        }
        ui->attr_tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

        strList.clear();
        for (quint16 id : character->inventory.get_items()) {
            strList.append(story->get_item(id)->get_name());
        }
        ui->item_listView->setModel(new QStringListModel(strList));
        ui->item_listView->setEditTriggers(QAbstractItemView::NoEditTriggers);

        strList.clear();
        for (quint16 id : story->get_items().keys()) {
            strList.append(story->get_item(id)->get_name());
        }
        ui->item_comboBox->setModel(new QStringListModel(strList));
    }


}

void ServerWindow::on_newCharacter()
{
    update_characters();
}

void ServerWindow::on_char_listView_clicked(const QModelIndex &index)
{

    update_characters(index.row());

}

void ServerWindow::on_edit_charButton_clicked()
{
    if(ui->char_listView->currentIndex().isValid()){
        characterDialog charDialog(story->get_characters().at(ui->char_listView->currentIndex().row()),this);
        charDialog.exec();
    }
}

void ServerWindow::on_pushButton_clicked()
{
    QModelIndexList rows = ui->char_listView->selectionModel()->selectedRows();
    if (rows.size() != 0) {
        Character* character = story->get_characters().at(rows.at(0).row());
        if (character != nullptr) {
            character->add_item(story->get_items().values().at(ui->item_comboBox->currentIndex())->get_id());
        }
        update_characters();
    }
}

void ServerWindow::on_remove_itemButton_clicked()
{
    Character* character = story->get_characters().at(ui->char_listView->selectionModel()->selectedRows().at(0).row());
    QModelIndexList rows = ui->item_listView->selectionModel()->selectedRows();
    if (rows.size() != 0) {
        character->remove_item(story->get_items().values().at(rows.at(0).row())->get_id());
    }
    update_characters();
}


void ServerWindow::on_item_listView_clicked(const QModelIndex &index)
{
    qDebug() << index.row();

    QList<quint16> inventory_items = story->get_characters().at(ui->
                                                                char_listView->selectionModel()->
                                                                selectedRows().at(0).row())->inventory.get_items();
    if (inventory_items.size() != ui->item_listView->model()->rowCount())
        return;
    Item* item  = story->get_item(inventory_items.at(index.row()));

    if (item != nullptr) {
        int i{0};
        ui->entity_tableWidget->setRowCount(item->get_modifiers().size());
        for (QString key : item->get_modifiers().keys()) {
            ui->entity_tableWidget->setItem(i, 0, new QTableWidgetItem(key));
            ui->entity_tableWidget->setItem(i, 1, new QTableWidgetItem(QString::number(item->get_modifiers().value(key))));
            ++i;
        }
        ui->entity_tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

        i = 0;
        ui->tableWidget->setRowCount(item->get_attributes().size());
        for (QString key : item->get_attributes().keys()) {
            ui->tableWidget->setItem(i,0,new QTableWidgetItem(key));
            ui->tableWidget->setItem(i,1,new QTableWidgetItem(QString::number(item->get_attribute(key))));
        }
        ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

    }


}

void ServerWindow::on_skills_listView_clicked(const QModelIndex &index)
{
    Skill* skill = story->get_characters().at(ui->char_listView->selectionModel()->selectedRows().at(0).row())->get_skills().at(index.row());
    if (skill != nullptr) {
        int i{0};
        ui->entity_tableWidget->setRowCount(skill->get_modifiers().size());
        for (QString key : skill->get_modifiers().keys()) {
            ui->entity_tableWidget->setItem(i, 0, new QTableWidgetItem(key));
            ui->entity_tableWidget->setItem(i, 1, new QTableWidgetItem(QString::number(skill->get_modifier(key))));
            ++i;
        }
        ui->entity_tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    }
}

void ServerWindow::on_pushButton_2_clicked()
{
    itemDialog dialog(this);
    dialog.exec();
    update_characters();
}

void ServerWindow::on_item_modButton_clicked()
{
    if (ui->char_listView->currentIndex().isValid() && ui->item_listView->currentIndex().isValid()) {


    itemDialog mod_dialog(story->get_item(
                              story->get_characters().at(
                                  ui->char_listView->currentIndex().row())
                              ->inventory.get_items().at(
                                  ui->item_listView->currentIndex().row())),
                          this);
    mod_dialog.exec();

    update_characters();
    }
}
