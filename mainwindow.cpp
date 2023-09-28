#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QValidator>
#include <QSqlQueryModel>
#include <QModelIndex>
#include <QPushButton>
#include <QTableView>
#include "buttondelegate.h"
#include "etudiantmodel.h"
#include "etudiant.h"
#include "professeur.h"
#include "professeurmodel.h"
#include <QDebug>
#include <QSqlError>
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    P(1, "", "")
{
    ui->setupUi(this);
    ui->le_id->setValidator(new QIntValidator(1, 1000, this));
    ui->tab_etudiant->setModel(E.afficher());
connect(ui->critaire_rechercher, &QLineEdit::textChanged, this, &MainWindow::filtrerTableView);
    ui->le_id_professeur->setValidator(new QIntValidator(1, 1000, this));
    ui->tab_professeur->setModel(P.afficherprof());

    // Utiliser le modèle personnalisé EtudiantModel
    EtudiantModel *etudiantModel = new EtudiantModel(this);
    ui->tab_etudiant->setModel(etudiantModel);
    ProfesseurModel *professeurModel = new ProfesseurModel(this);
    ui->tab_professeur->setModel(professeurModel);

    // Dans le constructeur de MainWindow
    ui->combo_critere_tri->addItem("ID");
    ui->combo_critere_tri->addItem("Nom");
    ui->combo_critere_tri->addItem("Prenom");

    ui->combo_critere_tri1->addItem("ID_prof");
    ui->combo_critere_tri1->addItem("Nom_prof");
    ui->combo_critere_tri1->addItem("Prenom_prof");

    // Dans le constructeur de MainWindow
    connect(ui->combo_critere_tri, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &MainWindow::trierTableView);
    connect(ui->combo_critere_tri1, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &MainWindow::trierTableView);

}

void MainWindow::setupTableView() {
    // Create and set the custom student model
    EtudiantModel *etudiantModel = new EtudiantModel(this);
    ui->tab_etudiant->setModel(etudiantModel);

    // Enable single selection
    ui->tab_etudiant->setSelectionMode(QAbstractItemView::SingleSelection);
    ProfesseurModel *professeurModel = new ProfesseurModel(this);
    ui->tab_professeur->setModel(professeurModel);

    // Enable single selection
    ui->tab_professeur->setSelectionMode(QAbstractItemView::SingleSelection);
}



MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::trierTableView(int index) {
    // Handle sorting for student table
    if (ui->tab_etudiant->isVisible()) {
        EtudiantModel *etudiantModel = qobject_cast<EtudiantModel *>(ui->tab_etudiant->model());
        if (etudiantModel) {
            QString critereTri;
            switch (index) {
                case 0: critereTri = "id"; break;
                case 1: critereTri = "nom"; break;
                case 2: critereTri = "prenom"; break;
            }
            etudiantModel->setSort(etudiantModel->fieldIndex(critereTri), Qt::AscendingOrder);
            etudiantModel->select();
        }
    }

    // Handle sorting for professor table
    if (ui->tab_professeur->isVisible()) {
            // Sorting for Professeur
            ProfesseurModel *professeurModel = qobject_cast<ProfesseurModel *>(ui->tab_professeur->model());
            if (professeurModel) {
                QString critereTri;
                // Handle sorting criteria for Professeur
                switch (index) {
                    case 0: critereTri = "id_professeur"; break;
                    case 1: critereTri = "nom_professeur"; break;
                    case 2: critereTri = "prenom_professeur"; break;
                }
                professeurModel->setSort(professeurModel->fieldIndex(critereTri), Qt::AscendingOrder);
                professeurModel->select();
            }
        }

}
void MainWindow::filtrerTableView(const QString &critere) {
    EtudiantModel *etudiantModel = qobject_cast<EtudiantModel *>(ui->tab_etudiant->model());
    if (etudiantModel) {
        etudiantModel->filtrer(critere);
    }
    if (ui->tab_professeur->isVisible()) {
            // Filtering for Professeur
            ProfesseurModel *professeurModel = qobject_cast<ProfesseurModel *>(ui->tab_professeur->model());
            if (professeurModel) {
                professeurModel->filtrer(critere);
            }
        }
}


void MainWindow::on_bp_ajouter_clicked()
{

        int id = ui->le_id->text().toInt();
        int id_professeur = ui->le_idprof->text().toInt();
        QString nom = ui->le_nom->text();
        QString prenom = ui->le_prenom->text();

        // Validation des données
        if (id <= 0 || id_professeur <= 0 || nom.length() < 5 || prenom.length() < 5) {
            QMessageBox::warning(this, "Erreur", "Veuillez remplir tous les champs correctement. Les noms et prénoms doivent contenir au moins 5 caractères.");
            return; // Ne pas ajouter l'étudiant si les données sont invalides
        }

        Etudiant etudiant(id, nom, prenom, id_professeur);

        if (etudiant.ajouter()) {
            QMessageBox::information(this, "Succès", "Etudiant ajouté !");
            ui->tab_etudiant->setModel(E.afficher());
        } else {
            QMessageBox::warning(this, "Erreur", "Échec de l'ajout de l'étudiant.");
        }
    }



void MainWindow::on_pb_supprimer_clicked()
{
    Etudiant E1;
    E1.setid(ui->le_idsupp->text().toInt());
    bool test = E1.supprimer(E1.getid());

    QMessageBox msgBox;
    if (test) {
        msgBox.setText("Etudiant supprimé !");
        ui->tab_etudiant->setModel(E.afficher());
    } else {
        msgBox.setText("Échec de suppression !");
    }
    msgBox.exec();
}

void MainWindow::on_pb_modifier_clicked()
{
    QMessageBox::information(this, "Succès", "teste.");

    int id = ui->le_id_modification->text().toInt();

    QString nouveauNom = ui->le_nouveau_nom->text();
    QString nouveauPrenom = ui->le_nouveau_prenom->text();

    Etudiant etudiant = Etudiant::getEtudiantById(id);

    if (!etudiant.etudiantExiste(id)) {
        QMessageBox::warning(this, "Erreur", "L'étudiant avec cet ID n'existe pas.");
        return;
    }

    etudiant.setNom(nouveauNom);
    etudiant.setPrenom(nouveauPrenom);

    if (etudiant.modifier()) {
        QMessageBox::information(this, "Succès", "Les informations de l'étudiant ont été modifiées.");
        ui->tab_etudiant->setModel(E.afficher());
    } else {
        QMessageBox::warning(this, "Erreur", "Échec de la modification des informations de l'étudiant.");
    }
}
void MainWindow::on_pb_rechercher_clicked()
{
    QString critereRecherche = ui->critaire_rechercher->text();

    QString queryStr = "SELECT * FROM etudiant WHERE id LIKE '%" + critereRecherche + "%' OR nom LIKE '%" + critereRecherche + "%' OR prenom LIKE '%" + critereRecherche + "%'";

    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery(queryStr);
    ui->tab_etudiant->setModel(model);
}
void MainWindow::on_pb_ajout_prof_clicked()
{
    int id_professeur = ui->le_id_professeur->text().toInt();
        QString nom_professeur = ui->le_nom_professeur->text();
        QString prenom_professeur = ui->le_prenom_professeur->text();

        // Validation des données
        if (id_professeur <= 0 || nom_professeur.length() < 5 || prenom_professeur.length() < 5) {
            QMessageBox::warning(this, "Erreur", "Veuillez remplir tous les champs correctement. Les noms et prénoms doivent contenir au moins 5 caractères.");
            return; // Ne pas ajouter le professeur si les données sont invalides
        }

        Professeur P(id_professeur, nom_professeur, prenom_professeur);

        if (P.ajouterprof()) {
            QMessageBox::information(this, "Succès", "Professeur ajouté !");
            ui->tab_professeur->setModel(P.afficherprof());
        } else {
            QMessageBox::warning(this, "Erreur", "Échec de l'ajout du Professeur.");
        }

}


void MainWindow::on_pb_modif_prof_clicked()
{
    QMessageBox::information(this, "Succès", "teste.");
    int id_professeur = ui->le_id_prof_modification->text().toInt();

    QString nouveauNom = ui->le_nouveaux_nomprof->text();
    QString nouveauPrenom = ui->le_nouveau_prenomprof->text();


    Professeur professeur = Professeur::getProfesseurById( id_professeur) ;

    if (!professeur.professeurtExiste(id_professeur)) {
        QMessageBox::warning(this, "Erreur", "L'étudiant avec cet ID n'existe pas.");
        return;
    }

    professeur.setnom_professeur(nouveauNom);
    professeur.setprenom_professeur(nouveauPrenom);

    if (professeur.modifierprof()) {
        QMessageBox::information(this, "Succès", "Les informations du professeur ont été modifiées.");
        ui->tab_professeur->setModel(P.afficherprof());
    } else {
        QMessageBox::warning(this, "Erreur", "Échec de la modification des informations de l'étudiant.");
    }
}


void MainWindow::on_pb_supprimer_prof_clicked()
{

    Professeur P1;
    P1.setid_professeur(ui->le_id_prof_supp->text().toInt());
    bool test = P1.supprimerprof(P1.getid_professeur());

    QMessageBox msgBox;
    if (test) {
        msgBox.setText("professeur supprimé !");
        ui->tab_professeur->setModel(P.afficherprof());
    } else {
        msgBox.setText("Échec de suppression !");
    }
    msgBox.exec();


}

void MainWindow::on_rechercherprof_clicked()
{
    QString critaire_rechercher1 = ui->critaire_rechercher1->text();

    QString queryStr = "SELECT * FROM professeur WHERE id_professeur LIKE '%" + critaire_rechercher1 + "%' OR nom_professeur LIKE '%" + critaire_rechercher1 + "%' OR prenom_professeur LIKE '%" + critaire_rechercher1 + "%'";

    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery(queryStr);
    ui->tab_professeur->setModel(model);







}
