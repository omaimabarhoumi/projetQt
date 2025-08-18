#include "message.h"
#include <QSqlError>
#include <QDebug>

// Constructeur
Message::Message()
    : senderId(0), receiverId(0), content(""), status("") {}

Message::Message(int senderId, int receiverId, QString content, QString status)
    : senderId(senderId), receiverId(receiverId), content(content), status(status) {}

bool Message::sendMessage() {
    QSqlQuery query;
    query.prepare("INSERT INTO MESSAGE (SENDER_ID, RECEIVER_ID, CONTENT, SENT_AT) "
                  "VALUES (:senderId, :receiverId, :content, CURRENT_TIMESTAMP)");
    query.bindValue(":senderId", senderId);
    query.bindValue(":receiverId", receiverId);
    query.bindValue(":content", content);
    query.bindValue(":status", status);

    if (!query.exec()) {
        qDebug() << "Erreur lors de l'envoi du message:" << query.lastError().text();
        return false;
    }
    return true;
}

// Méthode pour récupérer l'historique des messages d'un utilisateur
QSqlQueryModel* Message::fetchMessages(int userId) {
    QSqlQueryModel* model = new QSqlQueryModel();

        // Requête SQL adaptée pour Oracle : On utilise une jointure explicite pour récupérer les derniers messages
    QString queryStr = R"(
            SELECT M.ID_MSG, M.SENDER_ID, M.RECEIVER_ID, M.CONTENT, M.STATUS, M.SENT_AT
            FROM MESSAGE M
            INNER JOIN (
                SELECT
                    CASE
                        WHEN SENDER_ID < RECEIVER_ID THEN SENDER_ID
                        ELSE RECEIVER_ID
                    END AS User1,
                    CASE
                        WHEN SENDER_ID < RECEIVER_ID THEN RECEIVER_ID
                        ELSE SENDER_ID
                    END AS User2,
                    MAX(SENT_AT) AS LastSentAt
                FROM MESSAGE
                WHERE SENDER_ID = :userId OR RECEIVER_ID = :userId
                GROUP BY
                    CASE
                        WHEN SENDER_ID < RECEIVER_ID THEN SENDER_ID
                        ELSE RECEIVER_ID
                    END,
                    CASE
                        WHEN SENDER_ID < RECEIVER_ID THEN RECEIVER_ID
                        ELSE SENDER_ID
                    END
            ) LatestMessages
            ON ((M.SENDER_ID = LatestMessages.User1 AND M.RECEIVER_ID = LatestMessages.User2) OR
                (M.SENDER_ID = LatestMessages.User2 AND M.RECEIVER_ID = LatestMessages.User1))
            AND M.SENT_AT = LatestMessages.LastSentAt
            ORDER BY M.SENT_AT DESC
        )";

        // Préparation de la requête SQL
        QSqlQuery query;
        query.prepare(queryStr);
        query.bindValue(":userId", userId);

        if (!query.exec()) {
            qDebug() << "Erreur lors de la récupération des derniers messages pour l'utilisateur" << userId
                     << ":" << query.lastError().text();
            delete model;
            return nullptr;
        }

        model->setQuery(query);

        // Vérification des erreurs dans le modèle
        if (model->lastError().isValid()) {
            qDebug() << "Erreur du modèle QSqlQueryModel:" << model->lastError().text();
            delete model;
            return nullptr;
        }

        return model;
    }


// Méthode pour récupérer une conversation spécifique entre deux utilisateurs
QSqlQueryModel* Message::fetchConversation(int userId, int otherUserId) {
    QSqlQueryModel* model = new QSqlQueryModel();
    QSqlQuery query;
    query.prepare("SELECT ID_MSG, SENDER_ID, RECEIVER_ID, CONTENT, STATUS, SENT_AT "
                  "FROM MESSAGE WHERE (SENDER_ID = :userId AND RECEIVER_ID = :otherUserId) "
                  "OR (SENDER_ID = :otherUserId AND RECEIVER_ID = :userId) "
                  "ORDER BY SENT_AT ASC");
    query.bindValue(":userId", userId);
    query.bindValue(":otherUserId", otherUserId);

    if (!query.exec()) {
        qDebug() << "Erreur lors de la récupération de la conversation:" << query.lastError().text();
        delete model;
        return nullptr;
    }

    model->setQuery(query);
    return model;
}

// Méthode pour supprimer un message
bool Message::deleteMessage(int idMsg) {
    QSqlQuery query;
    query.prepare("DELETE FROM MESSAGE WHERE ID_MSG = :idMsg");
    query.bindValue(":idMsg", idMsg);

    if (!query.exec()) {
        qDebug() << "Erreur lors de la suppression du message:" << query.lastError().text();
        return false;
    }
    return true;
}

// Méthode pour marquer un message comme lu
bool Message::markAsRead(int userId,int otherUserId) {
    QSqlQuery query;
    query.prepare("UPDATE MESSAGE SET STATUS = 'readed' WHERE (SENDER_ID = :userId AND RECEIVER_ID = :otherUserId)");
    query.bindValue(":userId",otherUserId );
    query.bindValue(":otherUserId",userId );
    if (!query.exec()) {
        qDebug() << "Erreur lors de la mise à jour du statut du message:" << query.lastError().text();
        return false;
    }
    return true;
}
