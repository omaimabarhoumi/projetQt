#ifndef MESSAGEBOX_H
#define MESSAGEBOX_H

#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>

class Message {
public:
    // Constructeur
    Message();
    Message( int  , int , QString ,QString  );

    // Méthodes CRUD
    bool sendMessage();                              // Créer un message
    QSqlQueryModel* fetchMessages(int userId);       // Lire l'historique de tous les messages d'un utilisateur
    QSqlQueryModel* fetchConversation(int userId, int otherUserId); // Lire une conversation spécifique
    bool deleteMessage(int idMsg);                  // Supprimer un message
    bool markAsRead(int userId,int otherUserId);                     // Marquer un message comme lu

private:
    // Attributs privés
    int idMsg;             // ID du message
    int senderId;          // ID de l'expéditeur
    int receiverId;        // ID du destinataire
    QString content;       // Contenu du message
    QString status;        // Statut (unread, read)
    QString sentAt;        // Date/heure d'envoi
};

#endif // MESSAGEBOX_H
