#include "etudiant.h"
#include <QSqlQuery>
#include <QtDebug>
#include <QObject>
#include <QMessageBox>

Etudiant::Etudiant(){
    id=1;
    nom=" ";
    prenom="";
}
Etudiant::Etudiant(int id ,QString nom, QString prenom,int id_professeur)
{
    this->id=id;
    this->nom=nom;
    this->prenom=prenom;
    this->id_professeur=id_professeur;
}
//Getters
QString Etudiant:: getNom(){return nom;}
QString Etudiant:: getPrenom(){return prenom;}
int Etudiant:: getid(){return id;}
int Etudiant:: getid_professeur(){return id_professeur;}


//Setter

void Etudiant:: setNom(QString n){nom=n;}
void Etudiant:: setPrenom(QString p){prenom=p;}
void Etudiant:: setid(int id){this->id=id;}
void Etudiant:: setid_professeur(int id_professeur){this->id_professeur=id_professeur;}
bool Etudiant:: ajouter(){


    QSqlQuery query;
    QString id_string= QString::number(id);
          query.prepare("INSERT INTO etudiant (id, nom, prenom,id_professeur) "
                        "VALUES (:id, :nom, :prenom, :id_professeur)");
          query.bindValue(":id", id_string);
          query.bindValue(":nom", nom);
          query.bindValue(":prenom", prenom);
          query.bindValue(":id_professeur", id_professeur);
          return query.exec();





}
bool Etudiant::supprimer(int id){
    if (!etudiantExiste(id)) {
        qDebug() << "Échec de la suppression : Étudiant avec l'ID" << id << "n'existe pas.";
        return false;
    }

    QSqlQuery query;
    QString id_string = QString::number(id);
    query.prepare("DELETE FROM etudiant WHERE id = :id");
    query.bindValue(":id", id_string);

    return query.exec();
}

QSqlQueryModel* Etudiant::afficher(){
/*
    QMessageBox msgBox;
    msgBox.setText("AAAAAAAAAAAAAAAAAAAAAA !");
    msgBox.exec(); */

    QSqlQueryModel* model=new QSqlQueryModel();


          model->setQuery("select * FROM etudiant");
          model->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
          model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
          model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom"));



    return model;


}
bool Etudiant::etudiantExiste(int id) {
    QSqlQuery query;
    query.prepare("SELECT id FROM etudiant WHERE id = :id");
    query.bindValue(":id", id);
    if (query.exec() && query.next()) {
        return true; // L'étudiant existe
    }
    return false; // L'étudiant n'existe pas
}

bool Etudiant::modifier() {
    if (!etudiantExiste(id)) {
        qDebug() << "Échec de la modification : Étudiant avec l'ID" << id << "n'existe pas.";
        return false;
    }

    QSqlQuery query;
    query.prepare("UPDATE etudiant SET nom = :nom, prenom = :prenom WHERE id = :id");
    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":id", id);

    return query.exec();
}
Etudiant Etudiant::getEtudiantById(int id) {
    QSqlQuery query;
    query.prepare("SELECT * FROM etudiant WHERE id = :id");
    query.bindValue(":id", id);

    if (query.exec() && query.next()) {
        int fetchedId = query.value(0).toInt();
        int fetchedId_professeur = query.value(0).toInt();
        QString fetchedNom = query.value(1).toString();
        QString fetchedPrenom = query.value(2).toString();

        Etudiant etudiant(fetchedId, fetchedNom, fetchedPrenom, fetchedId_professeur);
        return etudiant;
    } else {
        // Gérer le cas où l'étudiant n'a pas pu être trouvé
        Etudiant etudiant; // Vous pouvez définir un étudiant "vide" ou retourner une valeur spéciale
        return etudiant;
    }
}




