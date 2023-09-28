#ifndef ETUDIANT_H
#define ETUDIANT_H
#include<QString>
#include<QSqlQuery>
#include<QSqlQueryModel>



class Etudiant
{
private:
    QString nom , prenom;
    int id,id_professeur;


public:
    bool modifier();

public:
    bool etudiantExiste(int id);
    //Constructeurs
    Etudiant();
    Etudiant(int,QString,QString,int);
    static Etudiant getEtudiantById(int id);
    //Getters
    QString getNom();
    QString getPrenom();
    int getid();
    int getid_professeur();



    //Setter

    void setNom(QString n);
    void setPrenom(QString p);
    void setid(int id);
    void setid_professeur(int id_professeur);

    //fonctionnalites de base relatives a lentite etudiant

    bool ajouter();
    QSqlQueryModel* afficher();
    bool supprimer(int);




};

#endif // ETUDIANT_H
