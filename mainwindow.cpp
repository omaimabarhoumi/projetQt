#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_bt_ajouter_clicked()
{
    QMessageBox::information(nullptr, QObject::tr("database is  open"),
                QObject::tr("connection succefull.\n"
                            "Click Cancel to exit."), QMessageBox::Cancel);
}
