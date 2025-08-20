#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QDate>
#include <QMessageBox>
#include<QDebug>
#include <QFileDialog>
#include"message.h"

#include <QVBoxLayout>
#include <QLabel>
#include <QTimer>
#include <QObject>
#include<QtCharts>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QChart>
#include <QIntValidator>
#include <QRegularExpressionValidator>
#include <QPrinter>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //lors du l'execution  , forcement , on a juste tab login !

        int index_employer=ui->QTabWidget_2->indexOf(ui->tab_19);
        int index_client=ui->QTabWidget_2->indexOf(ui->CLIENT);
        int index_commande=ui->QTabWidget_2->indexOf(ui->Commande);
        ui->QTabWidget_2->setTabVisible(index_employer,false);
        ui->QTabWidget_2->setTabVisible(index_client,false);
        ui->QTabWidget_2->setTabVisible(index_commande,false);

        //lors du l'exuction , en applique un condition sur ui->cin_client  et ui->telephone_client   juste chiffre

        QIntValidator *intValidator = new QIntValidator(0, 1000000000, this); // Only allows integers from 0 to 100000
          ui->cin_client->setValidator(intValidator);
          ui->telephone_client->setValidator(intValidator);
          ui->prix_totale->setValidator(intValidator);

//lors du l'execution , en applique un condition sur ui->nom_client et ui->prenom_client juste charactere
          QRegularExpressionValidator *charValidator = new QRegularExpressionValidator(QRegularExpression("[A-Za-z]*"), this);
ui->prenom_client->setValidator(charValidator);
ui->nom_client->setValidator(charValidator);



ui->tableView_client->setModel(c.afficher());

QStringList gouvernorats = {
    "Tunis", "Ariana", "Ben Arous", "Manouba", "Bizerte", "Beja", "Jendouba",
    "Kef", "Siliana", "Zaghouan", "Nabeul", "Sousse", "Monastir", "Mahdia",
    "Sfax", "Kairouan", "Kasserine", "Sidi Bouzid", "Gafsa", "Tozeur",
    "Kebili", "Gabès", "Medenine", "Tataouine"
};

// Remplir le QComboBox
ui->gouvernorat_client->addItems(gouvernorats);



//commandes

remplir_comboBox_livreur();
remplir_comboBox_client();
ui->tableView_commande->setModel(co.afficher());

ui->id_commande->hide();
ui->id_client->hide();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_addButton_2_clicked()
{
    QString name=ui->nameEdit_2->text();
    QString surname=ui->lineEdit_16->text();
    QDate datebr=ui->dateEdit_2->date();
    double salery=ui->doubleSpinBox->value();
    QString password=ui->lineEdit_18->text();
    QString deppartement=ui->comboBox->currentText();
    QString post=ui->positionEdit_2->text();
    QString cin =ui->lineEdit_55->text();
    Employer emp (name,surname,datebr,salery,password,deppartement,post,cin);

    QMessageBox::StandardButton Confirmation;
    Confirmation = QMessageBox::question(this, "Confirmation", "Voulez-vous vraiment ajouter cette emploiyeé?",
                                    QMessageBox::Yes | QMessageBox::No);
    if (Confirmation == QMessageBox::Yes) {
         Employer emp (name,surname,datebr,salery,password,deppartement,post,cin);
        bool test = emp.ajouter();


    if(test){

          ui->tableView_2->setModel(empo.afficher());
        QMessageBox::information (nullptr, QObject::tr("OK"),
                                   QObject::tr("Ajout effectué \n"
                                  "Click Cancel to exit."), QMessageBox::Ok);
    }
    else{
        QMessageBox::information (nullptr, QObject::tr("Not OK"),
                                   QObject::tr("Ajout non effectué \n"
                                  "Click Cancel to exit."), QMessageBox::Cancel);}
    }
}
void MainWindow::on_updateButton_2_clicked()
{
    QString name=ui->nameEdit_2->text();
    QString surname=ui->lineEdit_16->text();
    QDate datebr=ui->dateEdit_2->date();
    double salery=ui->doubleSpinBox->value();
    QString password=ui->lineEdit_18->text();
    QString deppartement=ui->comboBox->currentText();
    QString post=ui->positionEdit_2->text();
    QString cin =ui->lineEdit_55->text();

    QMessageBox::StandardButton Confirmation;
    Confirmation = QMessageBox::question(this, "Confirmation", "Voulez-vous vraiment modifier cette emploiyeé?",
                                    QMessageBox::Yes | QMessageBox::No);
    if (Confirmation == QMessageBox::Yes) {
         Employer emp (name,surname,datebr,salery,password,deppartement,post,cin);
         int id=ui->labid->text().toInt();
        bool test = emp.modifier(id);


    if(test){

          ui->tableView_2->setModel(empo.afficher());
        QMessageBox::information (nullptr, QObject::tr("OK"),
                                   QObject::tr("Modification effectué \n"
                                  "Click Cancel to exit."), QMessageBox::Ok);
    }
    else{
        QMessageBox::information (nullptr, QObject::tr("Not OK"),
                                   QObject::tr("Modification non effectué \n"
                                  "Click Cancel to exit."), QMessageBox::Cancel);}
    }
}

void MainWindow::on_deleteButton_2_clicked()
{
    Employer emp;
    int id = ui->labid->text().toInt();
    QMessageBox::StandardButton Confirmation;
    Confirmation = QMessageBox::question(this, "Confirmation", "Voulez-vous vraiment modifier cette réservation?" ,
                                    QMessageBox::Yes | QMessageBox::No);
    if (Confirmation == QMessageBox::Yes) {
    bool test = emp.supprimer(id);
    if (test) {
        ui->tableView_2->setModel(emp.afficher());
        QMessageBox::information(nullptr, QObject::tr("OK"), QObject::tr("Suppression effectuée"), QMessageBox::Cancel);
    } else {
        QMessageBox::information(nullptr, QObject::tr("Not OK"), QObject::tr("Suppression non effectuée"), QMessageBox::Cancel);
    }
    }

}
void MainWindow::on_lineEdit_74_textChanged(const QString &arg1)
{
    if(arg1.isEmpty()){

        ui->tableView_2->setModel(empo.afficher());

    }

    else{

    Employer emp;
if(ui->comboBox_2->currentText()=="ID"){

    emp.rechercheByID(arg1.toInt());
    if(emp.getNom().isNull()){
        QMessageBox::information(nullptr, QObject::tr("Not OK"), QObject::tr("inserer un id valid"), QMessageBox::Cancel);
    }
    else{
        ui->labid->setText(QString::number(emp.getId()));
        ui->nameEdit_2->setText(emp.getNom());
        ui->lineEdit_16->setText(emp.getPrenom());
        ui->dateEdit_2->setDate(emp.getDateNaissance());
        ui->doubleSpinBox->setValue(emp.getSalaire());
        ui->lineEdit_18->setText(emp.getMotDePasse());
        ui->comboBox->setCurrentText(emp.getDepartement());
        ui->positionEdit_2->setText(emp.getPoste());
        ui->lineEdit_55->setText(emp.getCin());


    }

}
else{
    ui->tableView_2->setModel(emp.recherche(ui->comboBox_2->currentText(),arg1));

}
    }
}





void MainWindow::on_pushButton_42_clicked()
{
     ui->tableView_2->setModel(empo.trier(ui->comboBox_2->currentText(),true));
}

void MainWindow::on_pushButton_9_clicked()
{
    QString cin=ui->lineEdit_13->text();
    QString pass=ui->lineEdit_15->text();
    Idconnected=empo.connexion(cin,pass);

   if(Idconnected >0){

       QMessageBox::information (nullptr, QObject::tr("OK"),
                                  QObject::tr("Connection effectué  avec succee\n"
                                 "Click Cancel to exit."), QMessageBox::Ok);
       int index_login = ui->QTabWidget_2->indexOf(ui->tab_12);
       if (index_login != -1) {
           ui->QTabWidget_2->setTabVisible(index_login, false);

           int index_employer=ui->QTabWidget_2->indexOf(ui->tab_19);
           int index_client=ui->QTabWidget_2->indexOf(ui->CLIENT);
           int index_commande=ui->QTabWidget_2->indexOf(ui->Commande);
           ui->QTabWidget_2->setTabVisible(index_employer,true);
           ui->QTabWidget_2->setTabVisible(index_client,true);
           ui->QTabWidget_2->setTabVisible(index_commande,true);

           ui->tableView_2->setModel(empo.afficher());
           gethistoriquemessage(Idconnected);
           getcontacte(empo.afficher());
           timer = new QTimer(this);
           timer->start(10000);
       }






}

   else{
       QMessageBox::information (nullptr, QObject::tr("warning"),
                                  QObject::tr("verifier votre corrdonait\n"
                                 "Click Cancel to exit."), QMessageBox::Ok);
       }

}

void MainWindow::on_pushButton_clicked()
{
    Employer emp;
    ui->tableView_2->setModel(emp.trier(ui->comboBox_2->currentText(),true));

}

void MainWindow::on_pushButton_40_clicked()
{

}
void MainWindow::gethistoriquemessage(int userId){
    Message msg;
    Employer emp;
    QScrollArea* scrollArea = ui->scrollArea_3;
       QWidget* scrollContent = new QWidget();
       QVBoxLayout* layout = new QVBoxLayout(scrollContent);
       layout->setAlignment(Qt::AlignTop);

       // Récupérer les messages
       QSqlQueryModel* model = msg.fetchMessages(userId);
       if (!model) {
           QLabel* errorLabel = new QLabel("Erreur : Impossible de récupérer les messages.");
           layout->addWidget(errorLabel);
           scrollArea->setWidget(scrollContent);
           return;
       }

       // Parcourir les messages et les afficher
       for (int row = 0; row < model->rowCount(); ++row) {

           QString senderId = model->data(model->index(row, 1)).toString();
           QString receiverId = model->data(model->index(row, 2)).toString();
           QString content = model->data(model->index(row, 3)).toString();
           QString etat=model->data(model->index(row,4)).toString();
           QString sentAt = model->data(model->index(row, 5)).toString();
           QTextDocument doc;
           doc.setHtml(content);
           QString plainText = doc.toPlainText();
            QString messageText ;
           if(senderId.toInt()==Idconnected){

               emp.rechercheByID(receiverId.toInt());
           // Construire un format lisible pour le message
            messageText = QString(" %1\n     Vous: %2\n                 %3")
                                     .arg(emp.getNom()+" "+emp.getPrenom())
                                     .arg(plainText)
                                     .arg(sentAt);
           }
           else{
               emp.rechercheByID(senderId.toInt());
           // Construire un format lisible pour le message
            messageText = QString(" %1\n     %2\n                    %3")
                                     .arg(emp.getNom()+" "+emp.getPrenom())
                                     .arg(plainText)
                                     .arg(sentAt);
           }

           QLabel* messageLabel = new QLabel(messageText);
           messageLabel->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum);
           messageLabel->setContentsMargins(0, 0, 0, 0);
           messageLabel->setWordWrap(true);
           if(etat=="unread" && receiverId.toInt()==Idconnected ){
               messageLabel->setStyleSheet(
                           "border: 1px solid #1DB954; "
                           "background-color: #121212; "
                           "color: #ffffff; "
                           "padding: 10px; "
                           "margin: 5px; "
                           "border-radius: 5px; "
                           "font-size: 14px; "
                           "line-height: 1.5;"
                           "font-weight: bold;"


                           );

           }
            else{
           messageLabel->setStyleSheet(
                       "border: 1px solid #1DB954; "
                       "background-color: #121212; "
                       "color: #ffffff; "
                       "padding: 10px; "
                       "margin: 5px; "
                       "border-radius: 5px; "
                       "font-size: 14px; "
                       "line-height: 1.5;"
                   );}

           if(senderId.toInt()==Idconnected){
               messageLabel->setProperty("idautheruser", receiverId.toInt());
           }
           else{

                   messageLabel->setProperty("idautheruser", senderId.toInt());
           }
           messageLabel->installEventFilter(this);

        layout->addWidget(messageLabel);
       }

       // Configurer le QScrollArea avec le nouveau contenu
       scrollContent->setLayout(layout);
       scrollArea->setWidget(scrollContent);}


void MainWindow::getdesscution(int autherid) {
    Message msg;
    Employer emp;

    QScrollArea* scrollArea = ui->scrollArea;
    QWidget* scrollContent = new QWidget();
    QVBoxLayout* layout = new QVBoxLayout(scrollContent);

    // Récupérer les messages
    QSqlQueryModel* model = msg.fetchConversation(Idconnected, autherid);
    if (!model) {
        QLabel* errorLabel = new QLabel("Erreur : Impossible de récupérer les messages.");
        layout->addWidget(errorLabel);
        scrollArea->setWidget(scrollContent);
        return;
    }

    // Parcourir les messages et les afficher
    for (int row = 0; row < model->rowCount(); ++row) {
        QString senderId = model->data(model->index(row, 1)).toString();
        QString receiverId = model->data(model->index(row, 2)).toString();
        QString content = model->data(model->index(row, 3)).toString();
        QString etat = model->data(model->index(row, 4)).toString();
        QString sentAt = model->data(model->index(row, 5)).toString();

        QString messageText = QString(" %1").arg(content);

        // Créer un QLabel pour le message
        QLabel* messageLabel = new QLabel(messageText);
        messageLabel->setWordWrap(true);
        messageLabel->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum);
        messageLabel->setContentsMargins(0, 0, 0, 0);
        // Créer un QHBoxLayout pour chaque message
        QHBoxLayout* messageLayout = new QHBoxLayout();

        // Si l'expéditeur est l'utilisateur connecté, aligner à droite
        if (senderId.toInt() == Idconnected) {
            messageLayout->addWidget(messageLabel);
            messageLayout->setAlignment(Qt::AlignRight);
        } else {
            messageLayout->addWidget(messageLabel);
            messageLayout->setAlignment(Qt::AlignLeft);
        }

        // Style pour le QLabel
        messageLabel->setStyleSheet(
            "border: 1px solid #1DB954; "
            "background-color: #121212; "
            "color: #ffffff; "
            "padding: 10px; "
            "margin: 5px; "
            "border-radius: 5px; "
            "font-size: 14px; "
            "line-height: 1.5;"
        );

        // Ajouter le QHBoxLayout contenant le QLabel au QVBoxLayout
        layout->addLayout(messageLayout);
    }

    // Configurer le QScrollArea avec le nouveau contenu
    scrollContent->setLayout(layout);
    scrollArea->setWidget(scrollContent);
    msg.markAsRead(Idconnected, autherid);
    timer->start(10000);
}

bool MainWindow::eventFilter(QObject* obj, QEvent* event) {

    if (event->type() == QEvent::MouseButtonPress) {
        QLabel* label = qobject_cast<QLabel*>(obj);
        if (label) {
            Employer emp;
            int idautheruser = label->property("idautheruser").toInt();
            getdesscution(idautheruser);
            emp.rechercheByID(idautheruser);
            ui->groupBox_2->setTitle(emp.getNom()+" "+emp.getPrenom());
            ui->groupBox_2->setProperty("idautheruser",idautheruser);
            gethistoriquemessage(Idconnected);
            return true;
        }
    }
    return QObject::eventFilter(obj, event);
}

void MainWindow::on_sendbtn_clicked()
{
    int autheruserid=ui->groupBox_2->property("idautheruser").toInt();
    Message msg(Idconnected,autheruserid,ui->textEdit->toHtml(),"unreaded");
   bool etat= msg.sendMessage();
    if(etat){
        getdesscution(autheruserid);
        ui->textEdit->clear();
        gethistoriquemessage(Idconnected);
    }
    else{
        QMessageBox::warning(this, "Erreur", "Le message n'est pas envoyer !");

    }

}


void MainWindow::getcontacte(QSqlQueryModel* model){
    QScrollArea* scrollArea = ui->scrollArea_2;
       QWidget* scrollContent = new QWidget();
       QVBoxLayout* layout = new QVBoxLayout(scrollContent);
       layout->setAlignment(Qt::AlignTop);

       // Récupérer les messages
       if (!model) {
           QLabel* errorLabel = new QLabel("Erreur : Impossible de récupérer les messages.");
           layout->addWidget(errorLabel);
           scrollArea->setWidget(scrollContent);
           return;
       }

       // Parcourir les messages et les afficher
       for (int row = 0; row < model->rowCount(); ++row) {
           int idcontacte = model->data(model->index(row, 0)).toInt();
           QString nom = model->data(model->index(row, 1)).toString();
           QString prenom = model->data(model->index(row, 2)).toString();

            QString messageText ;


            messageText = QString(" %1")
                                     .arg(nom+" "+prenom);



           QLabel* messageLabel = new QLabel(messageText);
           messageLabel->setWordWrap(true);



           messageLabel->setStyleSheet(
                       "border: 1px solid #1DB954; "
                       "background-color: #121212; "
                       "color: #ffffff; "
                       "padding: 10px; "
                       "margin: 5px; "
                       "border-radius: 5px; "
                       "font-size: 14px; "
                       "line-height: 1.5;"
                       "font-weight: bold;"
                   );

               messageLabel->setProperty("idautheruser", idcontacte);



           messageLabel->installEventFilter(this);
        if(Idconnected !=idcontacte){
        layout->addWidget(messageLabel);}
       }

       // Configurer le QScrollArea avec le nouveau contenu
       scrollContent->setLayout(layout);
       scrollArea->setWidget(scrollContent);}

void MainWindow::on_lineEdit_textChanged(const QString &arg1)
{

    getcontacte(empo.recherche("nom",arg1));
}


void MainWindow::on_pushButton_60_clicked()
{
        QMap<QString, int> stats = empo.statistiquesParDepartement();

        QPieSeries *series = new QPieSeries();
        for (auto it = stats.begin(); it != stats.end(); ++it) {
            series->append(it.key(), it.value());
        }

        QChart *chart = new QChart();
        chart->addSeries(series);
        chart->setTitle("Statistiques des Employer par deppartement");

        QChartView *chartView = new QChartView(chart);
        chartView->setRenderHint(QPainter::Antialiasing);

        QDialog *chartDialog = new QDialog(this);
        chartDialog->setWindowTitle("Graphique des Statistiques");
        chartDialog->setFixedSize(480, 240);
        QVBoxLayout *layout = new QVBoxLayout();
        layout->addWidget(chartView);
        chartDialog->setLayout(layout);

        chartDialog->exec();
}

void MainWindow::on_addButton_client_clicked()
{
    //Etape1:Recupération du donné d'apres ui (design)
    QString nom=ui->nom_client->text();
    QString prenom=ui->prenom_client->text();
    QDate naissance=ui->naissance_client->date();
    QString email=ui->email_client->text();
    QString telephone=ui->telephone_client->text();
    QString cin=ui->cin_client->text();
    QString adresse=ui->adresse_client->text();
    QString sexe=ui->sexe_client->currentText();
    QString gouvernorat=ui->gouvernorat_client->currentText();
    QString delegation=ui->delegation_client->currentText();

    //Etape2:Controle de Saisie
if(nom==""||prenom==""||telephone==""||cin==""||email==""||adresse=="")
{
    QMessageBox::warning(this, "Erreur", "Tu dois remplir tous les champs !");
    return;

}

if(telephone.length()!=8)
{
    QMessageBox::warning(this, "Erreur", "Le numero de telephone doit etre 8 chiffre !");
    return;
}
QRegularExpression emailRegex(R"(^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$)");//aa@aa.aa
// Check if the email is valid
          if (!emailRegex.match(email).hasMatch()) {
              QMessageBox::critical(nullptr, QObject::tr(""),
                                    QObject::tr("L'adresse email est invalide"), QMessageBox::Cancel);
              return;
  }

    //Etape3:  appel du fonction ajout();
 clients c(nom,  prenom,  email,  telephone,  adresse,  gouvernorat,  delegation,naissance, "Client", sexe, cin);
 bool test =c.ajouter();

    //Etape4:Message resultat  , avec succes ou échoué  (ajout)
if(test)
{

    QMessageBox::information(nullptr, QObject::tr(""),
                          QObject::tr("Ajout avec succés"), QMessageBox::Cancel);

ui->nom_client->clear();
ui->prenom_client->clear();
ui->naissance_client->clear();
ui->email_client->clear();
ui->telephone_client->clear();
ui->cin_client->clear();
ui->adresse_client->clear();
ui->id_client->clear();
//refresh lel tableView
ui->tableView_client->setModel(c.afficher());

remplir_comboBox_client();
}
else
{
    QMessageBox::warning(nullptr, QObject::tr(""),
                          QObject::tr("Ajout echoué"), QMessageBox::Cancel);
}
}




void MainWindow::on_gouvernorat_client_currentTextChanged(const QString &gouvernorat)
{
    QStringList delegations;

    switch (gouvernorat.toStdString()[0]) {
        case 'T':
            if (gouvernorat == "Tunis") {
                delegations << "Tunis" << "La Marsa" << "Carthage" << "El Mourouj" << "Le Bardo" << "El Kabaria";
            } else if (gouvernorat == "Tozeur") {
                delegations << "Tozeur" << "Nefta" << "Degache" << "Tozeur Nord" << "Tozeur Sud";
            } else if (gouvernorat == "Tataouine") {
                delegations << "Tataouine" << "Ghadames" << "Remada" << "Tataouine Nord" << "Tataouine Sud";
            }
            break;

        case 'A':
            if (gouvernorat == "Ariana") {
                delegations << "Ariana" << "Raoued" << "Ezzahra" << "Mnihla" << "Kalaat El Andalous" << "Borj El Amri";
            }
            break;

        case 'B':
            if (gouvernorat == "Ben Arous") {
                delegations << "Ben Arous" << "Mourouj" << "Fouchana" << "Sidi Hassine";
            } else if (gouvernorat == "Bizerte") {
                delegations << "Bizerte" << "Menzel Bourguiba" << "Mateur" << "Tinja" << "Sidi Ali Ben Aoun";
            } else if (gouvernorat == "Beja") {
                delegations << "Beja" << "Bousalem" << "Teboursouk" << "Medjez El Bab" << "Nefza";
            }
            break;

        case 'J':
            if (gouvernorat == "Jendouba") {
                delegations << "Jendouba" << "Bizerte" << "Fernana" << "Ghardimaou" << "Ain Draham";
            }
            break;

        case 'K':
            if (gouvernorat == "Kef") {
                delegations << "Kef" << "Dahmani" << "Jerissa";
            } else if (gouvernorat == "Kairouan") {
                delegations << "Kairouan" << "El Alia" << "Haffouz";
            } else if (gouvernorat == "Kasserine") {
                delegations << "Kasserine" << "Thala" << "Sbeitla";
            } else if (gouvernorat == "Kebili") {
                delegations << "Kebili" << "Douz" << "Sabria";
            }
            break;

        case 'M':
            if (gouvernorat == "Manouba") {
                delegations << "Manouba" << "Douar Hicher" << "Oued Ellil" << "La Soukra";
            } else if (gouvernorat == "Monastir") {
                delegations << "Monastir" << "Moknine" << "Bembla";
            } else if (gouvernorat == "Mahdia") {
                delegations << "Mahdia" << "Chebba" << "El Jem";
            } else if (gouvernorat == "Medenine") {
                delegations << "Medenine" << "Zarzis" << "Ben Guerdane";
            }
            break;

        case 'S':
            if (gouvernorat == "Sidi Bouzid") {
                delegations << "Sidi Bouzid" << "Jelma" << "Meknassy";
            } else if (gouvernorat == "Sfax") {
                delegations << "Sfax" << "Skhira" << "Agareb";
            } else if (gouvernorat == "Sousse") {
                delegations << "Sousse" << "Hammam Sousse" << "Kalaa Seghira";
            } else if (gouvernorat == "Siliana") {
                delegations << "Siliana" << "Bargou" << "Makthar";
            }
            break;

        case 'G':
            if (gouvernorat == "Gafsa") {
                delegations << "Gafsa" << "Moulares" << "Redeyef";
            } else if (gouvernorat == "Gabès") {
                delegations << "Gabès" << "Mareth" << "El Hamma";
            }
            break;

        default:
            break;
    }

    // Update the combo box for delegations
    ui->delegation_client->clear(); // Clear previous entries
    ui->delegation_client->addItems(delegations); // Add new delegations
}

void MainWindow::on_tableView_client_clicked(const QModelIndex &index)
{
    //index du ligne
    QAbstractItemModel* model = ui->tableView_client->model();
    int row=index.row();
//récuperation des case du table d'apres ligne du index !
    QString id_client=model->data(model->index(row,0)).toString();
    QString nom=model->data(model->index(row,1)).toString();
    QString prenom=model->data(model->index(row,2)).toString();
    QString email=model->data(model->index(row,3)).toString();
    QString telephone=model->data(model->index(row,4)).toString();
    QString adresse=model->data(model->index(row,5)).toString();
    QDate naissance=model->data(model->index(row,6)).toDate();
    QString gouvernorat=model->data(model->index(row,7)).toString();
    QString delegation=model->data(model->index(row,8)).toString();
    QString role=model->data(model->index(row,9)).toString();
    QString sexe=model->data(model->index(row,10)).toString();
    QString cin=model->data(model->index(row,11)).toString();


    //insertion dans les lineEdits etc
ui->id_client->setText(id_client);
ui->nom_client->setText(nom);
ui->prenom_client->setText(prenom);
ui->email_client->setText(email);
ui->telephone_client->setText(telephone);
ui->adresse_client->setText(adresse);
ui->naissance_client->setDate(naissance);
ui->gouvernorat_client->setCurrentText(gouvernorat);
ui->delegation_client->setCurrentText(delegation);
ui->sexe_client->setCurrentText(sexe);
ui->cin_client->setText(cin);

}


void MainWindow::on_updateButton_client_clicked()
{
    //Etape1:Recupération du donné d'apres ui (design)
    int id_client=ui->id_client->text().toInt();
    QString nom=ui->nom_client->text();
    QString prenom=ui->prenom_client->text();
    QDate naissance=ui->naissance_client->date();
    QString email=ui->email_client->text();
    QString telephone=ui->telephone_client->text();
    QString cin=ui->cin_client->text();
    QString adresse=ui->adresse_client->text();
    QString sexe=ui->sexe_client->currentText();
    QString gouvernorat=ui->gouvernorat_client->currentText();
    QString delegation=ui->delegation_client->currentText();

    //Etape2:Controle de Saisie
    if(id_client==0)
    {
        QMessageBox::warning(this, "Erreur", "Tu dois chosir une ligne d'apres le tableau !");
        return;
    }
if(nom==""||prenom==""||telephone==""||cin==""||email==""||adresse=="")
{
    QMessageBox::warning(this, "Erreur", "Tu dois remplir tous les champs !");
    return;

}

if(telephone.length()!=8)
{
    QMessageBox::warning(this, "Erreur", "Le numero de telephone doit etre 8 chiffre !");
    return;
}
QRegularExpression emailRegex(R"(^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$)");//aa@aa.aa
// Check if the email is valid
          if (!emailRegex.match(email).hasMatch()) {
              QMessageBox::critical(nullptr, QObject::tr(""),
                                    QObject::tr("L'adresse email est invalide"), QMessageBox::Cancel);
              return;
  }

    //Etape3:  appel du fonction ajout();
 clients c(id_client,nom,  prenom,  email,  telephone,  adresse,  gouvernorat,  delegation,naissance, "Client", sexe, cin);
 bool test =c.modifier();

    //Etape4:Message resultat  , avec succes ou échoué  (ajout)
if(test)
{

    QMessageBox::information(nullptr, QObject::tr(""),
                          QObject::tr("Modification avec succés"), QMessageBox::Cancel);
    remplir_comboBox_client();
    ui->nom_client->clear();
    ui->prenom_client->clear();
    ui->naissance_client->clear();
    ui->email_client->clear();
    ui->telephone_client->clear();
    ui->cin_client->clear();
    ui->adresse_client->clear();
    ui->id_client->clear();

//refresh lel tableView
ui->tableView_client->setModel(c.afficher());
}
else
{
    QMessageBox::warning(nullptr, QObject::tr(""),
                          QObject::tr("Modification echoué"), QMessageBox::Cancel);
}
}


void MainWindow::on_deleteButton_client_clicked()
{
    int id=ui->id_client->text().toInt();

    if(id==0)
    {
        QMessageBox::warning(this, "Erreur", "Tu dois chosir une ligne d'apres le tableau !");
        return;
    }
    else
       {

    bool test=c.supprimer(id);
     QMessageBox msgBox;
    if(test)
    {
        {QMessageBox::information(nullptr, QObject::tr(""),
                               QObject::tr("suppresion avec succes."), QMessageBox::Cancel);}
               ui->tableView_client->setModel(c.afficher());
    remplir_comboBox_client();
    ui->nom_client->clear();
    ui->prenom_client->clear();
    ui->naissance_client->clear();
    ui->email_client->clear();
    ui->telephone_client->clear();
    ui->cin_client->clear();
    ui->adresse_client->clear();
    ui->id_client->clear();

         }
         else
             {QMessageBox::critical(nullptr, QObject::tr(""),
                                    QObject::tr("echec de suppresion."), QMessageBox::Cancel);}

    }
}


void MainWindow::on_bt_tri_client_clicked()
{
    QString ordre=ui->ordre_client->currentText();
    QString choix=ui->choix_client->currentText();
    if(ordre=="ASCENDANT")
    {
ui->tableView_client->setModel(c.tri(choix,"ASC"));
    }
    else
    {
        ui->tableView_client->setModel(c.tri(choix,"DESC"));
    }
}


void MainWindow::on_chercher_client_textChanged(const QString &text)
{
    QString choix=ui->choix_client->currentText();
    ui->tableView_client->setModel(c.chercher(choix,text));

}

//ETAPE1:  numero ligne et column du table !
//etape 2: creation du code html et css ! varaibale out !
//etape 3: creation du table dans le html , header !  variable out fih les donnes lkol mta tableau
//etape 4:Qfile Dialog , sna3na fichier pdf et lien
//etpae 5 :  insertion du varaibale out (html) dans le fichier pdf d'apres le lien
void MainWindow::on_pdf_client_clicked()
{
    QString strStream;
    QTextStream out(&strStream);

    const int rowCount = ui->tableView_client->model()->rowCount();
    const int columnCount = ui->tableView_client->model()->columnCount();

    out << "<html>\n"
           "<head>\n"
           "<meta Content=\"Text/html; charset=Windows-1251\">\n"
           "<title>%1</title>\n"
           "<style>\n"
           "table {\n"
           "    width: 100%;\n"
           "    border-collapse: collapse;\n"
           "}\n"
           "th, td {\n"
           "    padding: 8px;\n"
           "    text-align: left;\n"
           "    border-bottom: 1px solid #ddd;\n"
           "}\n"
           "tr:nth-child(even) {\n"
           "    background-color: #f2f2f2;\n"
           "}\n"
           "</style>\n"
           "</head>\n"
           "<body bgcolor=#ffffff link=#5000A0>\n"
           "<center> <H1>Liste des Clients</H1></center><br/><br/>\n"
           "<img src=\"path/to/your/image.jpg\" alt=\"Description of image\" style=\"max-width: 100%; height: auto;\">\n"
           "<table>\n";

    // headers
    out << "<thead><tr bgcolor=#f0f0f0> <th>Numero</th>";
    for (int column = 0; column < columnCount; column++)
    {
        if (!ui->tableView_client->isColumnHidden(column))
        {
            out << QString("<th>%1</th>").arg(ui->tableView_client->model()->headerData(column, Qt::Horizontal).toString());
        }
    }
    out << "</tr></thead>\n";

    // data table
    for (int row = 0; row < rowCount; row++)//ligne
    {
        out << "<tr> <td>" << row + 1 << "</td>";
        for (int column = 0; column < columnCount; column++)
        {
            if (!ui->tableView_client->isColumnHidden(column))
            {
                QString data = ui->tableView_client->model()->data(ui->tableView_client->model()->index(row, column)).toString().simplified();
                out << QString("<td>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
            }
        }
        out << "</tr>\n";
    }



    QString fileName = QFileDialog::getSaveFileName((QWidget *)0, "Sauvegarder en PDF", QString(), "*.pdf");
    if (QFileInfo(fileName).suffix().isEmpty())
    {
        fileName.append(".pdf");
    }

    QPrinter printer(QPrinter::PrinterResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setPageSize(QPageSize::A4);
    printer.setOutputFileName(fileName);

    QTextDocument doc;
    doc.setHtml(strStream);
    doc.print(&printer);

}



void MainWindow::on_stat_client_clicked()
{
    QMap<QString, int> stats = c.statistiquesParGouvernorat();

         QPieSeries *series = new QPieSeries();
         for (auto it = stats.begin(); it != stats.end(); ++it) {
             series->append(it.key(), it.value());
         }

         QChart *chart = new QChart();
         chart->addSeries(series);
         chart->setTitle("Statistiques des clients par gouvernorat");

         QChartView *chartView = new QChartView(chart);
         chartView->setRenderHint(QPainter::Antialiasing);

         QDialog *chartDialog = new QDialog(this);
         chartDialog->setWindowTitle("Graphique des Statistiques");
         chartDialog->setFixedSize(600, 400);
         QVBoxLayout *layout = new QVBoxLayout();
         layout->addWidget(chartView);
         chartDialog->setLayout(layout);

         chartDialog->exec();
}


void MainWindow::remplir_comboBox_livreur()
{
    ui->comboBox_livreur->clear();
    QList<QString> liste = co.Liste_Livreur();

    for (int i = 0; i < liste.length(); i++)
    {
        ui->comboBox_livreur->addItem(liste[i]);
    }
}

void MainWindow::remplir_comboBox_client()
{
    ui->comboBox_client->clear();
    QList<QString> liste = c.Liste_Client();

    for (int i = 0; i < liste.length(); i++)
    {
        ui->comboBox_client->addItem(liste[i]);
    }
}


void MainWindow::on_addButton_commande_clicked()
{
   QString type= ui->type_produit->text();
   QString nom=ui->nom_produit->text();
   int prix=ui->prix_totale->text().toInt();
   QString FullNameLivreur=ui->comboBox_livreur->currentText();
   QString FullNameClient=ui->comboBox_client->currentText();

if(type==""||nom==""||prix==0)
{
    QMessageBox::warning(nullptr, QObject::tr(""),
                          QObject::tr("Tu dois remplir tous les champs"), QMessageBox::Cancel);
    return;
}

if(prix<0)
   {
    QMessageBox::warning(nullptr, QObject::tr(""),
                          QObject::tr("Le prix doit etre positif"), QMessageBox::Cancel);
    return;

}

int id_livreur=co.chercherIdLivreur(FullNameLivreur);
int id_client=c.chercherIdClient(FullNameClient);

Commandes co(  id_client,  id_livreur,  QDate::currentDate(),  "En attente",  nom,type,  prix);
bool test =co.ajouter();

if(test)
{
    QMessageBox::information(nullptr, QObject::tr(""),
                          QObject::tr("Ajout avec succées"), QMessageBox::Cancel);
    ui->tableView_commande->setModel(co.afficher());

    ui->nom_produit->clear();
    ui->type_produit->clear();
    ui->prix_totale->clear();

}
else
{
    QMessageBox::warning(nullptr, QObject::tr(""),
                          QObject::tr("Ajout échoué"), QMessageBox::Cancel);

}
}


void MainWindow::on_tableView_commande_clicked(const QModelIndex &index)
{
    //index du ligne
    QAbstractItemModel* model = ui->tableView_commande->model();
    int row=index.row();
//récuperation des case du table d'apres ligne du index !
    QString id_commande=model->data(model->index(row,0)).toString();
    int id_client=model->data(model->index(row,1)).toInt();
    int id_livreur=model->data(model->index(row,2)).toInt();
    QString date_commande=model->data(model->index(row,3)).toString();
    QString statut=model->data(model->index(row,4)).toString();
    QString nom_produit=model->data(model->index(row,5)).toString();
    QString type_produit=model->data(model->index(row,6)).toString();
    QString prix_totale=model->data(model->index(row,7)).toString();



    //insertion dans les lineEdits etc
ui->id_commande->setText(id_commande);
ui->nom_produit->setText(nom_produit);
ui->type_produit->setText(type_produit);
ui->prix_totale->setText(prix_totale);

QString FullNameLivreur=co.chercherNomPrenomById(id_livreur);
QString FullNameClient=c.chercherNomPrenomById(id_client);
        ui->comboBox_client->setCurrentText(FullNameClient);
        ui->comboBox_livreur->setCurrentText(FullNameLivreur);

}

void MainWindow::on_updateButton_commande_clicked()
{
   QString type= ui->type_produit->text();
   QString nom=ui->nom_produit->text();
   int prix=ui->prix_totale->text().toInt();
   QString FullNameLivreur=ui->comboBox_livreur->currentText();
   QString FullNameClient=ui->comboBox_client->currentText();
   int id_commande=ui->id_commande->text().toInt();

   if(id_commande==0)
   {
       QMessageBox::warning(nullptr, QObject::tr(""),
                             QObject::tr("Tu dois choisir une ligne d'apres le tableau"), QMessageBox::Cancel);
       return;
   }
if(type==""||nom==""||prix==0)
{
    QMessageBox::warning(nullptr, QObject::tr(""),
                          QObject::tr("Tu dois remplir tous les champs"), QMessageBox::Cancel);
    return;
}

if(prix<0)
   {
    QMessageBox::warning(nullptr, QObject::tr(""),
                          QObject::tr("Le prix doit etre positif"), QMessageBox::Cancel);
    return;

}

int id_livreur=co.chercherIdLivreur(FullNameLivreur);
int id_client=c.chercherIdClient(FullNameClient);
Commandes co( id_commande, id_client,  id_livreur,  QDate::currentDate(),  "En attente",  nom,type,  prix);
bool test =co.modifier();

if(test)
{
    QMessageBox::information(nullptr, QObject::tr(""),
                          QObject::tr("Ajout avec succées"), QMessageBox::Cancel);
    ui->tableView_commande->setModel(co.afficher());

    ui->nom_produit->clear();
    ui->type_produit->clear();
    ui->prix_totale->clear();

}
else
{
    QMessageBox::warning(nullptr, QObject::tr(""),
                          QObject::tr("Ajout échoué"), QMessageBox::Cancel);

}
}


void MainWindow::on_deleteButton_commande_clicked()
{
    int id=ui->id_commande->text().toInt();

    if(id==0)
    {
        QMessageBox::warning(this, "Erreur", "Tu dois chosir une ligne d'apres le tableau !");
        return;
    }
    else
       {

    bool test=co.supprimer(id);
     QMessageBox msgBox;
    if(test)
    {
        {QMessageBox::information(nullptr, QObject::tr(""),
                               QObject::tr("suppresion avec succes."), QMessageBox::Cancel);}
               ui->tableView_commande->setModel(co.afficher());

ui->nom_produit->clear();
ui->type_produit->clear();
ui->prix_totale->clear();
         }
         else
             {QMessageBox::critical(nullptr, QObject::tr(""),
                                    QObject::tr("echec de suppresion."), QMessageBox::Cancel);}

    }
}

void MainWindow::on_tri_commande_clicked()
{
    QString ordre=ui->ordre_commande->currentText();
    QString choix=ui->choix_commande->currentText();
    if(ordre=="ASCENDANT")
    {
ui->tableView_commande->setModel(co.tri(choix,"ASC"));
    }
    else
    {
        ui->tableView_commande->setModel(co.tri(choix,"DESC"));
    }
}


void MainWindow::on_chercher_commande_textChanged(const QString &text)
{
    QString choix=ui->choix_commande->currentText();
    ui->tableView_commande->setModel(co.chercher(choix,text));
}


void MainWindow::on_pdf_commande_clicked()
{
    QString strStream;
    QTextStream out(&strStream);

    const int rowCount = ui->tableView_commande->model()->rowCount();
    const int columnCount = ui->tableView_commande->model()->columnCount();

    out << "<html>\n"
           "<head>\n"
           "<meta Content=\"Text/html; charset=Windows-1251\">\n"
           "<title>%1</title>\n"
           "<style>\n"
           "table {\n"
           "    width: 100%;\n"
           "    border-collapse: collapse;\n"
           "}\n"
           "th, td {\n"
           "    padding: 8px;\n"
           "    text-align: left;\n"
           "    border-bottom: 1px solid #ddd;\n"
           "}\n"
           "tr:nth-child(even) {\n"
           "    background-color: #f2f2f2;\n"
           "}\n"
           "</style>\n"
           "</head>\n"
           "<body bgcolor=#ffffff link=#5000A0>\n"
           "<center> <H1>Liste des Commandes</H1></center><br/><br/>\n"
           "<img src=\"path/to/your/image.jpg\" alt=\"Description of image\" style=\"max-width: 100%; height: auto;\">\n"
           "<table>\n";

    // headers
    out << "<thead><tr bgcolor=#f0f0f0> <th>Numero</th>";
    for (int column = 0; column < columnCount; column++)
    {
        if (!ui->tableView_commande->isColumnHidden(column))
        {
            out << QString("<th>%1</th>").arg(ui->tableView_commande->model()->headerData(column, Qt::Horizontal).toString());
        }
    }
    out << "</tr></thead>\n";

    // data table
    for (int row = 0; row < rowCount; row++)//ligne
    {
        out << "<tr> <td>" << row + 1 << "</td>";
        for (int column = 0; column < columnCount; column++)
        {
            if (!ui->tableView_commande->isColumnHidden(column))
            {
                QString data = ui->tableView_commande->model()->data(ui->tableView_commande->model()->index(row, column)).toString().simplified();
                out << QString("<td>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
            }
        }
        out << "</tr>\n";
    }



    QString fileName = QFileDialog::getSaveFileName((QWidget *)0, "Sauvegarder en PDF", QString(), "*.pdf");
    if (QFileInfo(fileName).suffix().isEmpty())
    {
        fileName.append(".pdf");
    }

    QPrinter printer(QPrinter::PrinterResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setPageSize(QPageSize::A4);
    printer.setOutputFileName(fileName);

    QTextDocument doc;
    doc.setHtml(strStream);
    doc.print(&printer);

}


void MainWindow::on_stat_commande_clicked()
{
    QMap<QString, int> stats = co.statistiquesParSatut();

           QPieSeries *series = new QPieSeries();
           for (auto it = stats.begin(); it != stats.end(); ++it) {
               series->append(it.key(), it.value());
           }

           QChart *chart = new QChart();
           chart->addSeries(series);
           chart->setTitle("Statistiques des Commandes par statut");

           QChartView *chartView = new QChartView(chart);
           chartView->setRenderHint(QPainter::Antialiasing);

           QDialog *chartDialog = new QDialog(this);
           chartDialog->setWindowTitle("Graphique des Statistiques");
           chartDialog->setFixedSize(600, 400);
           QVBoxLayout *layout = new QVBoxLayout();
           layout->addWidget(chartView);
           chartDialog->setLayout(layout);

           chartDialog->exec();
}

