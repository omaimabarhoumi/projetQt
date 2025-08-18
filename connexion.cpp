#include "mainwindow.h"

#include <QApplication>
#include <QMessageBox>
#include <QDebug>
#include "connexion.h"
#include <QObject>


Connexion::Connexion()
{

}

bool Connexion::createconnexion()
{bool test=false;
QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
db.setDatabaseName("SOURCE_projet2A");
db.setUserName("aymen");//inserer nom de l'utilisateur
db.setPassword("esprit18");//inserer mot de passe de cet utilisateur

if (db.open())
test=true;
    return  test;
}

void Connexion::fermerConnexion()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    db.close();
}
