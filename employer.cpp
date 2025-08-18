#include "employer.h"
#include <QSqlQuery>
#include <QSqlQueryModel>
#include<QDebug>
#include <QSqlError>


Employer::Employer() {}

Employer::Employer(QString nom, QString prenom, QDate dateNaissance, double salaire, QString motDePasse, QString departement, QString poste, QString cin)
    : nom(nom), prenom(prenom), dateNaissance(dateNaissance), salaire(salaire), motDePasse(motDePasse), departement(departement), poste(poste), cin(cin) {}

bool Employer::ajouter() {

    QSqlQuery query;
    query.prepare("INSERT INTO EMPLOYER (NOM, PRENOM, DATE_NAISSANCE, SALAIRE, MOT_DE_PASSE, DEPARTEMENT, POSTE, CIN) "
                  "VALUES (:NOM, :PRENOM, :DATE_NAISSANCE, :SALAIRE, :MOT_DE_PASSE, :DEPARTEMENT, :POSTE, :CIN)");
    query.bindValue(":NOM", nom);
    query.bindValue(":PRENOM", prenom);
    query.bindValue(":DATE_NAISSANCE", dateNaissance);
    query.bindValue(":SALAIRE", salaire);
    query.bindValue(":MOT_DE_PASSE", motDePasse);
    query.bindValue(":DEPARTEMENT", departement);
    query.bindValue(":POSTE", poste);
    query.bindValue(":CIN", cin);

    if (!query.exec()) {
        qDebug() << "Erreur lors de l'ajout de l'employé:" << query.lastError().text();
        return false;
    }

    return true;
}


bool Employer::modifier(int id) {
    QSqlQuery query;
    query.prepare("UPDATE EMPLOYER SET NOM = :NOM, PRENOM = :PRENOM, DATE_NAISSANCE = :DATE_NAISSANCE, SALAIRE = :SALAIRE, "
                  "MOT_DE_PASSE = :MOT_DE_PASSE, DEPARTEMENT = :DEPARTEMENT, POSTE = :POSTE, CIN = :CIN WHERE ID= :ID");
    query.bindValue(":ID", id);
    query.bindValue(":CIN", cin);
    query.bindValue(":NOM", nom);
    query.bindValue(":PRENOM", prenom);
    query.bindValue(":DATE_NAISSANCE", dateNaissance);
    query.bindValue(":SALAIRE", salaire);
    query.bindValue(":MOT_DE_PASSE", motDePasse);
    query.bindValue(":DEPARTEMENT", departement);
    query.bindValue(":POSTE", poste);


    return query.exec();

}

bool Employer::supprimer(int id) {
    QSqlQuery query;
    query.prepare("DELETE FROM EMPLOYER WHERE ID = :ID");
    query.bindValue(":ID", id);
    return query.exec();
}

QSqlQueryModel* Employer::afficher() {
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM EMPLOYER");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Id"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prenom"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Date Naissance"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Salaire"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Mot de Passe"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("Departement"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("Poste"));
    model->setHeaderData(8, Qt::Horizontal, QObject::tr("CIN"));
    return model;
}

QSqlQueryModel* Employer::trier(QString condition, bool ascendant) {
    QSqlQueryModel* model = new QSqlQueryModel();
    QString order = ascendant ? "ASC" : "DESC";


    QSqlQuery query;

    QString queryString = "SELECT * "
                          "FROM EMPLOYER ORDER BY " + condition + " "+order;

    query.prepare(queryString);

    if (!query.exec()) {
        delete model;
        return nullptr;
    }

    model->setQuery(query);
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Id"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prenom"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Date Naissance"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Salaire"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Mot de Passe"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("Departement"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("Poste"));
    model->setHeaderData(8, Qt::Horizontal, QObject::tr("CIN"));

    return model;
}

void Employer::rechercheByID(int idr) {
    QSqlQuery query;
    query.prepare("SELECT * FROM EMPLOYER WHERE ID = :ID");
    query.bindValue(":ID", idr);

    if (query.exec() && query.next()) {
        id=query.value("ID").toInt();
        nom = query.value("NOM").toString();
        prenom = query.value("PRENOM").toString();
        dateNaissance = query.value("DATE_NAISSANCE").toDate();
        salaire = query.value("SALAIRE").toDouble();
        motDePasse = query.value("MOT_DE_PASSE").toString();
        departement = query.value("DEPARTEMENT").toString();
        poste = query.value("POSTE").toString();
        cin=query.value("CIN").toString();
    }
}

QSqlQueryModel* Employer::recherche(QString critere, QString valeur) {
    QSqlQueryModel* model = new QSqlQueryModel();
    QSqlQuery query;

    QString queryString = "SELECT * "
                          "FROM EMPLOYER WHERE " + critere + " LIKE :valeur";

    query.prepare(queryString);
    query.bindValue(":valeur", "%" + valeur + "%");

    if (!query.exec()) {
        delete model;
        return nullptr;
    }

    model->setQuery(query);
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Id"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prenom"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Date Naissance"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Salaire"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Mot de Passe"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("Departement"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("Poste"));
    model->setHeaderData(8, Qt::Horizontal, QObject::tr("CIN"));

    return model;
}


QMap<QString, int> Employer::statistiquesParDepartement() {
    QMap<QString, int> stats;
    QSqlQuery query("SELECT DEPARTEMENT, COUNT(*) FROM EMPLOYER GROUP BY DEPARTEMENT");
    while (query.next()) {
        QString dept = query.value(0).toString();
        int count = query.value(1).toInt();
        stats[dept] = count;
    }
    return stats;
}

int Employer::connexion(QString cin, QString motDePasse) {
    QSqlQuery query;

    // Préparer la requête pour récupérer l'ID de l'utilisateur correspondant au CIN et mot de passe
    query.prepare("SELECT ID FROM EMPLOYER WHERE CIN = :cin AND MOT_DE_PASSE = :motDePasse");
    query.bindValue(":cin", cin);
    query.bindValue(":motDePasse", motDePasse);

    // Exécution de la requête
    if (!query.exec()) {
        qDebug() << "Erreur lors de l'exécution de la requête de connexion : " << query.lastError();
        return -1; // Retourne -1 en cas d'erreur
    }

    // Vérifier si un résultat est disponible
    if (query.next()) {
        int id = query.value(0).toInt(); // Récupérer l'ID de l'utilisateur
        return id;
    }

    return -1; // Retourne -1 si aucun utilisateur n'est trouvé
}
