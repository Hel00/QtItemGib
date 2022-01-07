#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QtDebug>
#include <QString>
#include <string>

#include "items.h"

int listLength = 0;

void initList(Ui::MainWindow *ui)
{
    listLength = 0;
    ui->itemList->clear();

    for ( QString &item : itemArr)
    {
        ui->itemList->addItem( item );
        listLength++;
    }
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    initList(ui);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_itemList_activated(const QModelIndex &index)
{
    qDebug() << "Activated " << ui->itemList->item(index.row())->text();
}

void MainWindow::on_itemFilter_textChanged(const QString &arg1)
{
    QString insertedText = ui->itemFilter->text();
    QList<QListWidgetItem*> itemsFound = ui->itemList->findItems(insertedText, Qt::MatchFlag::MatchContains);

    for (int itemIndex = 0; itemIndex < ui->itemList->count(); itemIndex++)
    {
        //qDebug() << ui->itemList->item(itemIndex)->text();

        if (!itemsFound.contains(ui->itemList->item(itemIndex)))
        {
            //qDebug() << ui->itemList->item(itemIndex)->text();
            ui->itemList->item(itemIndex)->setHidden(true);
        }
        else
        {
            ui->itemList->item(itemIndex)->setHidden(false);
        }
    }
}


void MainWindow::on_attachDks_clicked()
{
    system("injector.exe");
}

