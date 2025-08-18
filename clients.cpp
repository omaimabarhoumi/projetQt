#include "clients.h"
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QDate>

clients::clients()
{
    id_client = 0;
    nom = "";
    prenom = "";
    email = "";
    telephone = "";
    adresse = "";
    gouvernorat = "";
    delegation = "";
    date_naissance = QDate::currentDate();
}

clients::clients(int id_client, QString nom, QString prenom, QString email, QString telephone, QString adresse, QString gouvernorat, QString delegation, QDate date_naissance,QString role,QString sexe)
{
    this->id_client = id_client;
    this->nom = nom;
    this->prenom = prenom;
    this->email = email;
    this->telephone = telephone;
    this->adresse = adresse;
    this->gouvernorat = gouvernorat;
    this->delegation = delegation;
    this->date_naissance = date_naissance;
    this->role = role;
    this->sexe=sexe;
}

clients::clients( QString nom, QString prenom, QString email, QString telephone, QString adresse, QString gouvernorat, QString delegation, QDate date_naissance,QString role,QString sexe)
{
    this->nom = nom;
    this->prenom = prenom;
    this->email = email;
    this->telephone = telephone;
    this->adresse = adresse;
    this->gouvernorat = gouvernorat;
    this->delegation = delegation;
    this->date_naissance = date_naissance;
    this->role = role;
    this->sexe=sexe;
}

bool clients::ajouter()
{
    QSqlQuery query;

    query.prepare("INSERT INTO CLIENTS (Nom, Prenom, Email, Telephone, Adresse, DATE_DE_NAISSANCE,Gouvernorat, Delegation,SEXE) "
                  "VALUES (:Nom, :Prenom, :Email, :Telephone, :Adresse, :DATE_DE_NAISSANCE, :Gouvernorat, :Delegation,:SEXE)");

    query.bindValue(":Nom", nom);
    query.bindValue(":Prenom", prenom);
    query.bindValue(":Email", email);
    query.bindValue(":Telephone", telephone);
    query.bindValue(":Adresse", adresse);
    query.bindValue(":Gouvernorat", gouvernorat);
    query.bindValue(":Delegation", delegation);
    query.bindValue(":DATE_DE_NAISSANCE", date_naissance);
    query.bindValue(":SEXE", sexe);

    return query.exec();
}

QSqlQueryModel* clients::afficher()
{
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM CLIENTS");
    return model;
}

bool clients::supprimer(int id)
{
    QSqlQuery query;
    query.prepare("DELETE FROM CLIENTS WHERE ID_Client = :id");
    query.bindValue(":id", id);
    return query.exec();
}

bool clients::idExists(int id)
{
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM CLIENTS WHERE ID_Client = :id");
    query.bindValue(":id", id);

    if (query.exec() && query.next()) {
        int count = query.value(0).toInt();
        return count > 0;
    }

    return false;
}

bool clients::modifier()
{
    QSqlQuery query;

    query.prepare("UPDATE CLIENTS SET Nom = :Nom, Prenom = :Prenom, Email = :Email, Telephone = :Telephone, Adresse = :Adresse, DATE_DE_NAISSANCE = :DATE_DE_NAISSANCE , Gouvernorat = :Gouvernorat, Delegation = :Delegation,SEXE= :SEXE WHERE ID_Client = :ID_Client");
    query.bindValue(":ID_Client", id_client);
    query.bindValue(":Nom", nom);
    query.bindValue(":Prenom", prenom);
    query.bindValue(":Email", email);
    query.bindValue(":Telephone", telephone);
    query.bindValue(":Adresse", adresse);
    query.bindValue(":Gouvernorat", gouvernorat);
    query.bindValue(":Delegation", delegation);
    query.bindValue(":DATE_DE_NAISSANCE", date_naissance);
    query.bindValue(":SEXE", sexe);

    return query.exec();
}

QSqlQueryModel* clients::chercher(QString column, QString text)
{
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM CLIENTS WHERE " + column + " LIKE '%" + text + "%'");
    return model;
}

QSqlQueryModel* clients::tri(QString column, QString choix)
{
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM CLIENTS ORDER BY " + column + " " + choix);
    return model;
}

int clients::CountSEXE(QString sexe)
{
    
    int count = 0;

    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM CLIENTS WHERE SEXE=:sexe");
    query.bindValue(":sexe",sexe);

    if (query.exec() && query.next()) {
        count = query.value(0).toInt();
    }

    return count;
    
}




