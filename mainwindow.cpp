#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QtDebug>
#include <QString>
#include <string>

#define BUF_SIZE 256

TCHAR szName[] = TEXT("Global\\MyFileMappingObject");
TCHAR szMsg[] = TEXT("Message from first process.");

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

    hMapFile = CreateFileMapping(
                  INVALID_HANDLE_VALUE,    // use paging file
                  NULL,                    // default security
                  PAGE_READWRITE,          // read/write access
                  0,                       // maximum object size (high-order DWORD)
                  BUF_SIZE,                // maximum object size (low-order DWORD)
                  szName);                 // name of mapping object

    if (hMapFile == NULL)
    {
       _tprintf(TEXT("Could not create file mapping object (%d).\n"),
              GetLastError());
       return;
    }
    pBuf = (LPTSTR) MapViewOfFile(hMapFile,   // handle to map object
                         FILE_MAP_ALL_ACCESS, // read/write permission
                         0,
                         0,
                         BUF_SIZE);

    if (pBuf == NULL)
    {
       _tprintf(TEXT("Could not map view of file (%d).\n"),
              GetLastError());

        CloseHandle(hMapFile);

       return;
    }


    CopyMemory((PVOID)pBuf, szMsg, (_tcslen(szMsg) * sizeof(TCHAR)));
}

MainWindow::~MainWindow()
{
    UnmapViewOfFile(pBuf);

    CloseHandle(hMapFile);

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

