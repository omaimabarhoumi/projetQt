#include "clients.h"
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QDate>
#include <QList>
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
    cin="";
}

clients::clients(int id_client, QString nom, QString prenom, QString email, QString telephone, QString adresse, QString gouvernorat, QString delegation, QDate date_naissance,QString role,QString sexe,QString cin)
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
    this->cin=cin;
}

clients::clients( QString nom, QString prenom, QString email, QString telephone, QString adresse, QString gouvernorat, QString delegation, QDate date_naissance,QString role,QString sexe,QString cin)
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
    this->cin=cin;
}

bool clients::ajouter()
{
    QSqlQuery query;

    query.prepare("INSERT INTO CLIENTS (Nom, Prenom, Email, Telephone, Adresse, DATE_DE_NAISSANCE,Gouvernorat, Delegation,SEXE,CIN) "
                  "VALUES (:Nom, :Prenom, :Email, :Telephone, :Adresse, :DATE_DE_NAISSANCE, :Gouvernorat, :Delegation,:SEXE,:CIN)");

    query.bindValue(":Nom", nom);
    query.bindValue(":Prenom", prenom);
    query.bindValue(":Email", email);
    query.bindValue(":Telephone", telephone);
    query.bindValue(":Adresse", adresse);
    query.bindValue(":Gouvernorat", gouvernorat);
    query.bindValue(":Delegation", delegation);
    query.bindValue(":DATE_DE_NAISSANCE", date_naissance);
    query.bindValue(":SEXE", sexe);
    query.bindValue(":CIN", cin);

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

    query.prepare("UPDATE CLIENTS SET Nom = :Nom, Prenom = :Prenom, Email = :Email, Telephone = :Telephone, Adresse = :Adresse, DATE_DE_NAISSANCE = :DATE_DE_NAISSANCE , Gouvernorat = :Gouvernorat, Delegation = :Delegation,SEXE= :SEXE,CIN=:CIN WHERE ID_Client = :ID_Client");
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
    query.bindValue(":CIN", cin);

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


QMap<QString, int> clients::statistiquesParGouvernorat() {
    QMap<QString, int> GouvernoratStats;

    QSqlQuery query;
    query.prepare("SELECT Gouvernorat, COUNT(*) as count FROM CLIENTS GROUP BY Gouvernorat");

    if (query.exec()) {
        while (query.next()) {
            QString Gouvernorat= query.value(0).toString();
            int count = query.value(1).toInt();
            GouvernoratStats[Gouvernorat] = count;
        }
    }

    return GouvernoratStats;
}


QList<QString> clients::Liste_Client()
{
QSqlQuery query;
QList<QString> liste;
query.prepare("SELECT nom || ' ' || prenom FROM Clients");
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


int clients::chercherIdClient(QString FullNameClient)
{
    int id=0;

    QSqlQuery query;
    query.prepare("SELECT ID_CLIENT from CLIENTS where nom || ' ' || prenom   =:FullNameClient") ;
    query.bindValue(":FullNameClient",FullNameClient);
    if(query.exec() && query.next())
    {
        id=query.value(0).toInt();
    }

return id;
}

QString clients::chercherNomPrenomById(int ID_client)
{
    QString id;

    QSqlQuery query;
    query.prepare("SELECT nom || ' ' || prenom  from CLIENTS where  ID_CLIENT =:ID_client") ;
    query.bindValue(":ID_client",ID_client);
    if(query.exec() && query.next())
    {
        id=query.value(0).toString();
    }

return id;
}

QString clients::connexion(QString email, QString cin) { // oumaima.barhoumi@esprit.tn    ::  87654321
    QSqlQuery query;


    query.prepare("SELECT CIN, ROLE FROM CLIENTS WHERE EMAIL = :email AND ROLE != 'CLIENT'");
    query.bindValue(":email", email);

    if (query.exec() && query.next()) {
        //CIN= 87654321

        QString storedPassword = query.value("CIN").toString();

        // Check if the password matches
        if (cin == storedPassword) {
            return query.value("ROLE").toString(); // Return the role
            //ROLE=CLIENT
        }
    }

    //livreur
    query.prepare("SELECT CIN FROM LIVREURS WHERE EMAIL = :email");
    query.bindValue(":email", email);

    if (query.exec() && query.next()) {
        //CIN= 87654321

        QString storedPassword = query.value("CIN").toString();

        // Check if the password matches
        if (cin == storedPassword) {
            return "LIVREUR"; // Return the role
        }
    }

    return QString(); // Return null (empty QString) if login fails
}

QMap<QString, QString> clients::GetNomAndPrenom(QString email, QString cin, QString ROLE) {
    QSqlQuery query;
    QMap<QString, QString> liste;

    if (ROLE == "LIVREUR") {
        query.prepare("SELECT NOM, PRENOM FROM LIVREURS WHERE EMAIL = :email AND CIN = :cin");
    } else {
        query.prepare("SELECT NOM, PRENOM FROM CLIENTS WHERE EMAIL = :email AND CIN = :cin");
    }

    query.bindValue(":email", email);
    query.bindValue(":cin", cin);

    if (query.exec() && query.next()) {
        QString nom = query.value(0).toString();
        QString prenom = query.value(1).toString();

        liste.insert("nom", nom);
        liste.insert("prenom", prenom);
    }

    return liste;
}
