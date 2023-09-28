#ifndef ETUDIANT_H
#define ETUDIANT_H
#include<QString>
#include<QSqlQuery>
#include<QSqlQueryModel>



class Etudiant
{
private:
    QString nom , prenom;
    int id;


public:
    bool modifier();

public:
    bool etudiantExiste(int id);
    //Constructeurs
    Etudiant();
    Etudiant(int,QString,QString);
    static Etudiant getEtudiantById(int id);
    //Getters
    QString getNom();
    QString getPrenom();
    int getid();



    //Setter

    void setNom(QString n);
    void setPrenom(QString p);
    void setid(int id);

    //fonctionnalites de base relatives a lentite etudiant

    bool ajouter();
    QSqlQueryModel* afficher();
    bool supprimer(int);




};

#endif // ETUDIANT_H
