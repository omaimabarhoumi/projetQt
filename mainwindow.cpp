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
#include "QrCode.hpp"
#include "email.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //lors du l'execution  , forcement , on a juste tab login !
    ui->lineEdit_15->setEchoMode(QLineEdit::Password);

        int index_client=ui->QTabWidget_2->indexOf(ui->CLIENT);
        int index_commande=ui->QTabWidget_2->indexOf(ui->Commande);
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





void MainWindow::on_pushButton_9_clicked()
{
    QString email=ui->lineEdit_13->text();
    QString cin=ui->lineEdit_15->text();
    Role=c.connexion(email,cin);
    //"" CLIENT ADMIN LOGISTIQUE
   if(Role !=""){


        qDebug()<<Role;
        QMap<QString,QString> lise=c.GetNomAndPrenom( email, cin, Role);
        qDebug()<<lise;
        QString nom = lise.value("nom");
        QString prenom = lise.value("prenom");

        QString message = QString("%1 %2").arg(nom, prenom); // Using arg for formatting
            QString welcomeMessage = QObject::tr("Bienvenu ") + Role + " \n" + message + "\n.";

            if (Role == "LIVREUR" || Role == "ADMIN" || Role == "GESTIONNAIRE LOGISTIQUE") {
                QMessageBox::information(nullptr, QObject::tr("OK"), welcomeMessage, QMessageBox::Ok);
            }

       int index_login = ui->QTabWidget_2->indexOf(ui->login);
       if (index_login != -1) {
           ui->QTabWidget_2->setTabVisible(index_login, false);

           int index_client=ui->QTabWidget_2->indexOf(ui->CLIENT);
           int index_commande=ui->QTabWidget_2->indexOf(ui->Commande);
           ui->QTabWidget_2->setTabVisible(index_client,true);
           ui->QTabWidget_2->setTabVisible(index_commande,true);


        }
if(Role=="LIVREUR")
{
ui->pdf_commande->hide();
ui->pdf_client->hide();

ui->addButton_client->hide();
ui->addButton_commande->hide();

ui->updateButton_client->hide();
ui->updateButton_commande->hide();

ui->deleteButton_client->hide();
ui->deleteButton_commande->hide();

ui->stat_client->hide();
ui->stat_commande->hide();



}
else
{
    ui->pdf_commande->show();
    ui->pdf_client->show();

    ui->addButton_client->show();
    ui->addButton_commande->show();

    ui->updateButton_client->show();
    ui->updateButton_commande->show();

    ui->deleteButton_client->show();
    ui->deleteButton_commande->show();

    ui->stat_client->show();
    ui->stat_commande->show();
}


}

   else{
       QMessageBox::information (nullptr, QObject::tr("warning"),
                                  QObject::tr("verifier votre coordonait\n"
                                 "Click Cancel to exit."), QMessageBox::Ok);
       }

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

QString message =
"Bonjour " + prenom+" "+nom + ",\n\n"
"Votre commande est prête à être livrée.\n"
"Afin d’organiser la livraison dans les meilleures conditions, nous vous invitons à confirmer vos informations :\n\n"
"📦 Informations de livraison enregistrées :\n"
"- Nom : " + prenom+" "+nom  + "\n"
"- Gouvernorat : " + gouvernorat + "\n"
"- Delegation : " + delegation + "\n"
"- Adresse : " + adresse + "\n"
"- Téléphone : " + telephone + "\n\n"
"✅ Merci de confirmer que ces informations sont correctes afin que nous puissions procéder à la livraison.\n"
"En cas de modification, contactez-nous dès que possible à omaimabarhoumi2@gmail.com \n"
"Nous restons à votre disposition pour toute question.\n\n"
"Cordialement,\n"
"L’équipe MIMI DELIVERY";
QString objet = "Merci de confirmer votre livraison";


mailer::sendEmail(email, objet,message);

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


void MainWindow::on_bt_client_log_out_clicked()
{
    int index_client=ui->QTabWidget_2->indexOf(ui->CLIENT);
    int index_commande=ui->QTabWidget_2->indexOf(ui->Commande);
    int index_login=ui->QTabWidget_2->indexOf(ui->login);

    ui->QTabWidget_2->setTabVisible(index_client,false);
    ui->QTabWidget_2->setTabVisible(index_commande,false);
    ui->QTabWidget_2->setTabVisible(index_login,true);
    Role="";
}


void MainWindow::on_bt_commande_log_out_clicked()
{
    int index_client=ui->QTabWidget_2->indexOf(ui->CLIENT);
    int index_commande=ui->QTabWidget_2->indexOf(ui->Commande);
    int index_login=ui->QTabWidget_2->indexOf(ui->login);

    ui->QTabWidget_2->setTabVisible(index_client,false);
    ui->QTabWidget_2->setTabVisible(index_commande,false);
    ui->QTabWidget_2->setTabVisible(index_login,true);
    Role="";
}


void MainWindow::on_QrCode_commande_clicked()
{
    QString type = ui->type_produit->text();
    QString nom = ui->nom_produit->text();
    QString prix = ui->prix_totale->text();
    QString FullNameLivreur = ui->comboBox_livreur->currentText();
    QString FullNameClient = ui->comboBox_client->currentText();
    QString id_commande = ui->id_commande->text();

    // Create QR code text
    QString text = QString("ID Commande: %1\nFullNameLivreur: %2\nFullNameClient: %3\nType produit: %4\nNom produit: %5\nPrix: %6\n")
                    .arg(id_commande, FullNameLivreur, FullNameClient, type, nom, prix);

    using namespace qrcodegen;
    QrCode qr = QrCode::encodeText(text.toUtf8().data(), QrCode::Ecc::MEDIUM);

    // Create the QR code image
    qint32 sz = qr.getSize();
    QImage im(sz, sz, QImage::Format_RGB32);
    QRgb black = qRgb(0, 0, 0);
    QRgb white = qRgb(255, 255, 255);

    for (int y = 0; y < sz; y++) {
        for (int x = 0; x < sz; x++) {
            im.setPixel(x, y, qr.getModule(x, y) ? black : white);
        }
    }

    // Create a QDialog for display later on it QrCode
    QDialog *chartDialog = new QDialog(this);
    chartDialog->setWindowTitle("Qr Code");
    chartDialog->setFixedSize(600, 400);

    // Create a layout for the dialog
    QVBoxLayout *layout = new QVBoxLayout(chartDialog);

    // Create a QLabel to display the QR code
    QLabel *qrCodeLabel = new QLabel(chartDialog);
    QPixmap pixmap = QPixmap::fromImage(im.scaled(200, 200, Qt::KeepAspectRatio, Qt::FastTransformation));
    qrCodeLabel->setPixmap(pixmap);

    // Add the QR code label to the layout
    layout->addWidget(qrCodeLabel);

    // Set the layout for the dialog
    chartDialog->setLayout(layout);

    // Show the dialog
    chartDialog->exec();
}


