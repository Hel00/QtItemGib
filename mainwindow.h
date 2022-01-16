#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include <tchar.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_itemList_activated(const QModelIndex &index);

    void on_itemFilter_textChanged(const QString &arg1);

    void on_attachDks_clicked();

private:
    HANDLE hMapFile;
    LPCTSTR pBuf;

    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
