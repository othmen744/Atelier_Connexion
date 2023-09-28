#include "professeur.h"
#include <QSqlQuery>
#include <QDebug>
#include <QSqlError>

Professeur::Professeur(){
    id_professeur=0;
    nom_professeur=" ";
    prenom_professeur="";
}
Professeur::Professeur(int id_professeur, QString nom_professeur, QString prenom_professeur) {
    this->id_professeur = id_professeur;
    this->nom_professeur = nom_professeur;
    this->prenom_professeur = prenom_professeur;
}

//Getters
int Professeur::getid_professeur() {
    return id_professeur;
}

QString Professeur::getnom_professeur() {
    return nom_professeur;
}

QString Professeur::getprenom_professeur() {
    return prenom_professeur;
}


//Setter

void Professeur::setid_professeur(int id_professeur) {
    this->id_professeur = id_professeur;
}

void Professeur::setnom_professeur(QString &nom_professeur) {
    this->nom_professeur = nom_professeur;
}

void Professeur::setprenom_professeur(QString &prenom_professeur) {
    this->prenom_professeur = prenom_professeur;
}
bool Professeur::ajouterprof() {
    QSqlQuery query;
    query.prepare("INSERT INTO Professeur (id_professeur, nom_professeur, prenom_professeur) "
                  "VALUES (:id_professeur, :nom_professeur, :prenom_professeur)");
    query.bindValue(":id_professeur", id_professeur);
    query.bindValue(":nom_professeur", nom_professeur);
    query.bindValue(":prenom_professeur", prenom_professeur);

    if (query.exec()) {
        // Insertion succeeded
        return true;
    } else {
        // Insertion failed, handle the error
        qDebug() << "Error inserting data:" << query.lastError().text();
        return false;
    }
}
bool Professeur::supprimerprof(int id_professeur) {

    if (!professeurtExiste(id_professeur)) {
        qDebug() << "Échec de la suppression : Étudiant avec l'ID" << id_professeur<< "n'existe pas.";
        return false;
    }
    QSqlQuery query;
    QString id_string = QString::number(id_professeur);
    query.prepare("update etudiant set id_professeur=NULL WHERE id_professeur = :id_professeur");
    query.bindValue(":id_professeur", id_string);
    query.exec();
    query.prepare("DELETE FROM professeur WHERE id_professeur = :id_professeur");
    query.bindValue(":id_professeur", id_string);

    return query.exec();




}

bool Professeur::modifierprof() {
    if (!Professeur::professeurtExiste(id_professeur)) {
        qDebug() << "Échec de la modification : professeur avec l'ID" << id_professeur << "n'existe pas.";
        return false;
    }

    QSqlQuery query;
    query.prepare("UPDATE professeur SET nom_professeur = :nom_professeur, prenom_professeur = :prenom_professeur WHERE id_professeur = :id_professeur");
    query.bindValue(":nom_professeur", nom_professeur);
    query.bindValue(":prenom_professeur", prenom_professeur);
    query.bindValue(":id_professeur", id_professeur);

    return query.exec();
}

bool Professeur::professeurtExiste(int id_professeur) {
    QSqlQuery query;
    query.prepare("SELECT id_professeur FROM professeur WHERE id_professeur = :id_professeur");
    query.bindValue(":id_professeur", id_professeur);
    if (query.exec() && query.next()) {
        return true; // professeur existe
    }
    return false; // professeur n'existe pas
}


QSqlQueryModel* Professeur::afficherprof() {
    QSqlQueryModel* model = new QSqlQueryModel();
    QSqlQuery query;
    query.prepare("SELECT * FROM Professeur");
    if (query.exec()) {
        model->setQuery(query);
        return model;
    } else {
        // Handle the error (e.g., log it or show an error message)
        qDebug() << "Error fetching data:" << query.lastError().text();
        return nullptr;
    }
}
Professeur Professeur::getProfesseurById(int id_professeur) {
    QSqlQuery query;
    query.prepare("SELECT * FROM professeur WHERE id_professeur = :id");
    query.bindValue(":id", id_professeur);

    if (query.exec() && query.next()) {

        int fetchedId_professeur = query.value(0).toInt();
        QString fetchedNom_professeur = query.value(1).toString();
        QString fetchedPrenom_professeur = query.value(2).toString();

        Professeur professeur(fetchedId_professeur, fetchedNom_professeur, fetchedPrenom_professeur);
        return professeur;
    } else {
        // Gérer le cas où l'étudiant n'a pas pu être trouvé
        Professeur professeur; // Vous pouvez définir un étudiant "vide" ou retourner une valeur spéciale
        return professeur;
    }
}
