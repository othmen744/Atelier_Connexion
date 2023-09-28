#ifndef PROFESSEUR_H
#define PROFESSEUR_H
#include<QString>
#include<QSqlQuery>
#include<QSqlQueryModel>

#include <QString>

class Professeur
{
private:
    int id_professeur;
    QString nom_professeur;
    QString prenom_professeur;

public:

    Professeur();
    Professeur(int , QString,  QString);
    static QSqlQueryModel* afficherprof();
bool professeurtExiste(int id_professeur);
static Professeur getProfesseurById(int id_professeur);

    // Getters
    int getid_professeur();
        QString getnom_professeur();
        QString getprenom_professeur();
        // Setters
        void setid_professeur(int id_professeur);
            void setnom_professeur(QString &nom_professeur);
            void setprenom_professeur(QString &prenom_professeur);

    // Database operations
     bool ajouterprof();    // Add a new professeur to the database
    bool supprimerprof(int id_professeur);  // Remove a professeur from the database
    bool modifierprof();   // Update professeur information in the database
    static QList<Professeur> afficherTous(); // Retrieve all professeurs from the database
};

#endif // PROFESSEUR_H
