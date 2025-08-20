#ifndef COMMANDES_H
#define COMMANDES_H

#include <QString>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QDate>

class Commandes
{
public:
    Commandes();
    Commandes(int, int, int, QDate, QString, QString,QString , int);
    Commandes( int, int, QDate, QString, QString,QString , int);

    // Getters et Setters
    int getIdCommande() const { return id_commande; }
    void setIdCommande(int id_commande) { this->id_commande = id_commande; }

    int getIdClient() const { return id_client; }
    void setIdClient(int id_client) { this->id_client = id_client; }

    int getIdLivreur() const { return id_livreur; }
    void setIdLivreur(int id_livreur) { this->id_livreur = id_livreur; }

    QDate getDateCommande() const { return date_commande; }
    void setDateCommande(QDate date_commande) { this->date_commande = date_commande; }

    QString getStatut() const { return statut; }
    void setStatut(QString statut) { this->statut = statut; }

    QString getNomProduit() const { return nom_produit; }
    void setNomProduit(QString nom_produit) { this->nom_produit = nom_produit; }

    QString getTypeProduit() const { return type_produit; }
    void setTypeProduit(QString type_produit) { this->type_produit = type_produit; }

    int getPrixTotale() const { return prix_totale; }
    void setPrixTotale(int prix_totale) { this->prix_totale = prix_totale; }

    // CRUD
    bool ajouter();
    QSqlQueryModel* afficher();
    bool supprimer(int id);
    bool idExists(int id);
    bool modifier();
    //Metier
    QSqlQueryModel* chercher(QString column, QString text);
    QSqlQueryModel* tri(QString column, QString choix);
    int countStatut(const QString& statut);

    QList<QString> Liste_Livreur();
    int chercherIdLivreur(QString FullNameLivreur);
    QString chercherNomPrenomById(int ID_livreur);
    QMap<QString, int> statistiquesParSatut() ;

private:
    int id_commande;
    int id_client;
    int id_livreur;
    QDate date_commande;
    QString statut;
    QString nom_produit;
    QString type_produit;
    int prix_totale;
};

#endif // COMMANDES_H
