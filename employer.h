#ifndef EMPLOYER_H
#define EMPLOYER_H

#include <QString>
#include <QDate>
#include <QSqlQueryModel>

class Employer
{
    QString nom, prenom, departement, poste,cin,motDePasse;
    QDate dateNaissance;
    double salaire;
    int id;

public:
    Employer();
    Employer(QString, QString, QDate, double, QString, QString, QString, QString);

    int getId() const { return id; }
    QString getCin() const { return cin; }
    QString getNom() const { return nom; }
    QString getPrenom() const { return prenom; }
    QDate getDateNaissance() const { return dateNaissance; }
    double getSalaire() const { return salaire; }
    QString getMotDePasse() const { return motDePasse; }
    QString getDepartement() const { return departement; }
    QString getPoste() const { return poste; }

    void setCin(QString c) { cin = c; }
    void setNom(QString n) { nom = n; }
    void setPrenom(QString p) { prenom = p; }
    void setDateNaissance(QDate date) { dateNaissance = date; }
    void setSalaire(double s) { salaire = s; }
    void setMotDePasse(QString mdp) { motDePasse = mdp; }
    void setDepartement(QString d) { departement = d; }
    void setPoste(QString p) { poste = p; }

    bool ajouter();
    bool supprimer(int id);
    bool modifier(int id);
    QSqlQueryModel* afficher();
    QSqlQueryModel* trier(QString condition, bool ascendant);
    void rechercheByID(int id);
    QSqlQueryModel* recherche(QString critere,QString valeur);
    QMap<QString, int> statistiquesParDepartement();
    int connexion(QString cin, QString motDePasse);
};

#endif // EMPLOYER_H
