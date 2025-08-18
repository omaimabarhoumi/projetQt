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



//refresh lel tableView
ui->tableView_client->setModel(c.afficher());
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
    if(!c.idExists(id))
    {
        QMessageBox::critical(nullptr, QObject::tr(""),
                                   QObject::tr("id n'existe pas ."), QMessageBox::Cancel);
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

         }
         else
             {QMessageBox::critical(nullptr, QObject::tr(""),
                                    QObject::tr("echec de suppresion."), QMessageBox::Cancel);}

    }
}

