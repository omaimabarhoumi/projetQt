#ifndef CLIENTS_H
#define CLIENTS_H

#include <QString>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QDate>

class clients
{
public:
    clients();
    clients(int, QString, QString, QString, QString, QString, QString, QString, QDate,QString,QString);
    clients(QString, QString, QString, QString, QString, QString, QString, QDate,QString,QString);

    // Getters et Setters
    int getIdClient() const { return id_client; }
    void setIdClient(int id_client) { this->id_client = id_client; }

    QString getNom() const { return nom; }
    void setNom(QString nom) { this->nom = nom; }

    QString getPrenom() const { return prenom; }
    void setPrenom(QString prenom) { this->prenom = prenom; }

    QString getEmail() const { return email; }
    void setEmail(QString email) { this->email = email; }

    QString getTelephone() const { return telephone; }
    void setTelephone(QString telephone) { this->telephone = telephone; }

    QString getAdresse() const { return adresse; }
    void setAdresse(QString adresse) { this->adresse = adresse; }

    QString getGouvernorat() const { return gouvernorat; }
    void setGouvernorat(QString gouvernorat) { this->gouvernorat = gouvernorat; }

    QString getDelegation() const { return delegation; }
    void setDelegation(QString delegation) { this->delegation = delegation; }

    QDate getDateNaissance() const { return date_naissance; }
    void setDateNaissance(QDate date_naissance) { this->date_naissance = date_naissance; }

    QString getRole() const { return role; }
    void setRole(QString role) { this->role = role; }

    QString getSEXE() const { return sexe; }
    void setSEXE(QString sexe) { this->sexe = sexe; }

    // CRUD
    bool ajouter();
    QSqlQueryModel* afficher();
    bool supprimer(int id);
    bool idExists(int id);
    bool modifier();
    //metier
    QSqlQueryModel* chercher(QString column, QString text);
    QSqlQueryModel* tri(QString column, QString choix);
    int CountSEXE(QString sexe);

private:
    int id_client;
    QString nom;
    QString prenom;
    QString email;
    QString telephone;
    QString adresse;
    QString gouvernorat;
    QString delegation;
    QString role;
    QDate date_naissance;
    QString sexe;

};

#endif // CLIENTS_H
