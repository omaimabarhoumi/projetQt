#include "livreurs.h"
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QDate>

livreurs::livreurs()
{
    id_livreur = 0;
    cin = "";
    nom = "";
    prenom = "";
    telephone = "";
    email = "";
    salaire = 0;
    sexe = "";
    date_naissance = QDate::currentDate();
}

livreurs::livreurs(int id_livreur, QString cin, QString nom, QString prenom, QString telephone, QString email, int salaire, QString sexe, QDate date_naissance)
{
    this->id_livreur = id_livreur;
    this->cin = cin;
    this->nom = nom;
    this->prenom = prenom;
    this->telephone = telephone;
    this->email = email;
    this->salaire = salaire;
    this->sexe = sexe;
    this->date_naissance = date_naissance;
}

bool livreurs::ajouter()
{
    QSqlQuery query;

    query.prepare("INSERT INTO LIVREURS (CIN, Nom, Prenom, Telephone, Email, SALAIRE, SEXE, DATE_DE_NAISSANCE) "
                  "VALUES (:CIN, :Nom, :Prenom, :Telephone, :Email, :SALAIRE, :SEXE, :DATE_DE_NAISSANCE)");

    query.bindValue(":CIN", cin);
    query.bindValue(":Nom", nom);
    query.bindValue(":Prenom", prenom);
    query.bindValue(":Telephone", telephone);
    query.bindValue(":Email", email);
    query.bindValue(":SALAIRE", salaire); // Ajout du salaire
    query.bindValue(":SEXE", sexe);
    query.bindValue(":DATE_DE_NAISSANCE", date_naissance);

    return query.exec();
}

QSqlQueryModel* livreurs::afficher()
{
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM LIVREURS");
    return model;
}

bool livreurs::supprimer(int id)
{
    QSqlQuery query;
    query.prepare("DELETE FROM LIVREURS WHERE ID_Livreur = :id");
    query.bindValue(":id", id);
    return query.exec();
}

bool livreurs::idExists(int id)
{
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM LIVREURS WHERE ID_Livreur = :id");
    query.bindValue(":id", id);

    if (query.exec() && query.next()) {
        int count = query.value(0).toInt();
        return count > 0;
    }

    return false;
}

bool livreurs::modifier(int id_livreur, QString cin, QString nom, QString prenom, QString telephone, QString email, int salaire, QString sexe, QDate date_naissance)
{
    QSqlQuery query;

    query.prepare("UPDATE LIVREURS SET CIN = :CIN, Nom = :Nom, Prenom = :Prenom, Telephone = :Telephone, Email = :Email, SALAIRE = :SALAIRE, SEXE = :SEXE, DATE_DE_NAISSANCE = :DATE_DE_NAISSANCE WHERE ID_Livreur = :ID_Livreur");
    query.bindValue(":ID_Livreur", id_livreur);
    query.bindValue(":CIN", cin);
    query.bindValue(":Nom", nom);
    query.bindValue(":Prenom", prenom);
    query.bindValue(":Telephone", telephone);
    query.bindValue(":Email", email);
    query.bindValue(":SALAIRE", salaire); // Mise à jour du salaire
    query.bindValue(":SEXE", sexe);
    query.bindValue(":DATE_DE_NAISSANCE", date_naissance);

    return query.exec();
}

QSqlQueryModel* livreurs::chercher(QString column, QString text)
{
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM LIVREURS WHERE " + column + " LIKE '%" + text + "%'");
    return model;
}

QSqlQueryModel* livreurs::tri(QString column, QString choix)
{
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM LIVREURS ORDER BY " + column + " " + choix);
    return model;
}

int livreurs::countLivreurs()
{
    int count = 0;

    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM LIVREURS");

    if (query.exec() && query.next()) {
        count = query.value(0).toInt();
    }

    return count;
}
