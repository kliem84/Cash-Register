#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <iostream>
#include <QMainWindow>
#include "caisse.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    void charger();
    ~MainWindow();
public slots:
    void actualiser();
    void ajouter();
    void retirer();

private:
    Ui::MainWindow *ui;
    Caisse caisse_;
};
#endif // MAINWINDOW_H
