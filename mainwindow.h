#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QObject>
#include "clients.h"
#include "commandes.h"
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



    void on_pushButton_9_clicked();

   void on_addButton_client_clicked();

   void on_gouvernorat_client_currentTextChanged(const QString &arg1);

   void on_tableView_client_clicked(const QModelIndex &index);

   void on_updateButton_client_clicked();

   void on_deleteButton_client_clicked();

   void on_bt_tri_client_clicked();

   void on_chercher_client_textChanged(const QString &arg1);

   void on_pdf_client_clicked();

   void on_stat_client_clicked();

   void remplir_comboBox_livreur();

   void remplir_comboBox_client();
   void on_addButton_commande_clicked();

   void on_tableView_commande_clicked(const QModelIndex &index);

   void on_updateButton_commande_clicked();

   void on_deleteButton_commande_clicked();

   void on_tri_commande_clicked();

   void on_chercher_commande_textChanged(const QString &arg1);

   void on_pdf_commande_clicked();

   void on_stat_commande_clicked();

   void on_bt_client_log_out_clicked();

   void on_bt_commande_log_out_clicked();

   void on_QrCode_commande_clicked();

private:
    Ui::MainWindow *ui;
    QWidget gestemp;
    QString Role;
    QTimer* timer;

    clients c;
    Commandes co;
};
#endif // MAINWINDOW_H
