#ifndef LIVREURS_H
#define LIVREURS_H

#include <QString>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QDate>

class livreurs
{
public:
    livreurs();
    livreurs(int, QString, QString, QString, QString, QString, int, QString, QDate);

    // Getters et Setters
    int getIdLivreur() const { return id_livreur; }
    void setIdLivreur(int id_livreur) { this->id_livreur = id_livreur; }

    QString getCIN() const { return cin; }
    void setCIN(QString cin) { this->cin = cin; }

    QString getNom() const { return nom; }
    void setNom(QString nom) { this->nom = nom; }

    QString getPrenom() const { return prenom; }
    void setPrenom(QString prenom) { this->prenom = prenom; }

    QString getTelephone() const { return telephone; }
    void setTelephone(QString telephone) { this->telephone = telephone; }

    QString getEmail() const { return email; }
    void setEmail(QString email) { this->email = email; }

    int getSalaire() const { return salaire; }
    void setSalaire(int salaire) { this->salaire = salaire; }

    QString getSexe() const { return sexe; }
    void setSexe(QString sexe) { this->sexe = sexe; }

    QDate getDateNaissance() const { return date_naissance; }
    void setDateNaissance(QDate date_naissance) { this->date_naissance = date_naissance; }

    // CRUD
    bool ajouter();
    QSqlQueryModel* afficher();
    bool supprimer(int id);
    bool idExists(int id);
    bool modifier(int, QString, QString, QString, QString, QString, int, QString, QDate);
    //metier
    QSqlQueryModel* chercher(QString column, QString text);
    QSqlQueryModel* tri(QString column, QString choix);
    int countLivreurs();

private:
    int id_livreur;
    QString cin;
    QString nom;
    QString prenom;
    QString telephone;
    QString email;
    int salaire;
    QString sexe;
    QDate date_naissance;
};

#endif // LIVREURS_H
