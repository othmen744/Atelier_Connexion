#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "etudiant.h"
#include "professeur.h"
#include<QSqlQuery>
#include<QSqlQueryModel>

#include <QString>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void on_pb_modifier_clicked();

private slots:
    void trierTableView(int index);






    void on_pb_rechercher_clicked();

    void on_pb_ajout_prof_clicked();
void on_pb_modif_prof_clicked();
    void filtrerTableView(const QString &critere);

    void on_bp_ajouter_clicked();

    void on_pb_supprimer_clicked();



    ;






    void on_pb_supprimer_prof_clicked();

    void on_rechercherprof_clicked();

private:
    void setupTableView();
    Ui::MainWindow *ui;
    Etudiant E;
    Professeur P;
};

#endif // MAINWINDOW_H
