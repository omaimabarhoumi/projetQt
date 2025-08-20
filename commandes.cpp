#include "commandes.h"
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QDate>

Commandes::Commandes()
{
    id_commande = 0;
    id_client = 0;
    id_livreur = 0;
    date_commande = QDate::currentDate();
    statut = "";
    nom_produit = "";
    type_produit = "";
    prix_totale = 0;
}

Commandes::Commandes(int id_commande, int id_client, int id_livreur, QDate date_commande, QString statut, QString nom_produit,QString type_produit, int prix_totale)
{
    this->id_commande = id_commande;
    this->id_client = id_client;
    this->id_livreur = id_livreur;
    this->date_commande = date_commande;
    this->statut = statut;
    this->nom_produit = nom_produit;
    this->prix_totale = prix_totale;
    this->type_produit=type_produit;
}

Commandes::Commandes( int id_client, int id_livreur, QDate date_commande, QString statut, QString nom_produit,QString type_produit, int prix_totale)
{
    this->id_client = id_client;
    this->id_livreur = id_livreur;
    this->date_commande = date_commande;
    this->statut = statut;
    this->nom_produit = nom_produit;
    this->prix_totale = prix_totale;
    this->type_produit=type_produit;

}

bool Commandes::ajouter()
{
    QSqlQuery query;

    query.prepare("INSERT INTO COMMANDES ( ID_Client, ID_Livreur, Date_Commande, Statut, Nom_Produit, Type_Produit, Prix_Totale) "
                  "VALUES ( :ID_Client, :ID_Livreur, :Date_Commande, :Statut, :Nom_Produit, :Type_Produit, :Prix_Totale)");

    query.bindValue(":ID_Client", id_client);
    query.bindValue(":ID_Livreur", id_livreur);
    query.bindValue(":Date_Commande", date_commande);
    query.bindValue(":Statut", statut);
    query.bindValue(":Nom_Produit", nom_produit);
    query.bindValue(":Type_Produit", type_produit);
    query.bindValue(":Prix_Totale", prix_totale);

    return query.exec();
}

QSqlQueryModel* Commandes::afficher()
{
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM COMMANDES");
    return model;
}

bool Commandes::supprimer(int id)
{
    QSqlQuery query;
    query.prepare("DELETE FROM COMMANDES WHERE ID_Commande = :id");
    query.bindValue(":id", id);
    return query.exec();
}

bool Commandes::idExists(int id)
{
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM COMMANDES WHERE ID_Commande = :id");
    query.bindValue(":id", id);

    if (query.exec() && query.next()) {
        int count = query.value(0).toInt();
        return count > 0;
    }

    return false;
}

bool Commandes::modifier()
{
    QSqlQuery query;

    query.prepare("UPDATE COMMANDES SET ID_Client = :ID_Client, ID_Livreur = :ID_Livreur, Nom_Produit = :Nom_Produit, Type_Produit = :Type_Produit, Prix_Totale = :Prix_Totale WHERE ID_Commande = :ID_Commande");
    query.bindValue(":ID_Commande", id_commande);
    query.bindValue(":ID_Client", id_client);
    query.bindValue(":ID_Livreur", id_livreur);
    query.bindValue(":Nom_Produit", nom_produit);
    query.bindValue(":Type_Produit", type_produit);
    query.bindValue(":Prix_Totale", prix_totale);

    return query.exec();
}

QSqlQueryModel* Commandes::chercher(QString column, QString text)
{
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM COMMANDES WHERE " + column + " LIKE '%" + text + "%'");
    return model;
}

QSqlQueryModel* Commandes::tri(QString column, QString choix)
{
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM COMMANDES ORDER BY " + column + " " + choix);
    return model;
}

int Commandes::countStatut(const QString& statut)
{
    int count = 0;

    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM COMMANDES WHERE Statut = :Statut");
    query.bindValue(":Statut", statut);

    if (query.exec() && query.next()) {
        count = query.value(0).toInt();
    }

    return count;
}

QList<QString> Commandes::Liste_Livreur()
{
QSqlQuery query;
QList<QString> liste;
query.prepare("SELECT nom || ' ' || prenom FROM LIVREURS");
if(query.exec())
{
 while(query.next())
 {
  QString fullName=query.value(0).toString();
  liste.append(fullName);
 }
}
return liste ;

}

int Commandes::chercherIdLivreur(QString FullNameLivreur)
{
    int id=0;

    QSqlQuery query;
    query.prepare("SELECT ID_LIVREUR from LIVREURS where nom || ' ' || prenom   =:FullnameLivreur") ;
    query.bindValue(":FullnameLivreur",FullNameLivreur);
    if(query.exec() && query.next())
    {
        id=query.value(0).toInt();
    }

return id;
}
QString Commandes::chercherNomPrenomById(int ID_livreur)
{
    QString id=0;

    QSqlQuery query;
    query.prepare("SELECT nom || ' ' || prenom  from LIVREURS where  ID_LIVREUR =:ID_livreur") ;
    query.bindValue(":ID_livreur",ID_livreur);
    if(query.exec() && query.next())
    {
        id=query.value(0).toString();
    }

return id;
}
QMap<QString, int> Commandes::statistiquesParSatut() {
    QMap<QString, int> StatutStats;

    QSqlQuery query;
    query.prepare("SELECT STATUT, COUNT(*) as count FROM COMMANDES GROUP BY STATUT");

    if (query.exec()) {
        while (query.next()) {
            QString STATUT= query.value(0).toString();
            int count = query.value(1).toInt();
            StatutStats[STATUT] = count;
        }
    }

    return StatutStats;
}
