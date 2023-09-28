// etudiantmodel.cpp
#include "etudiantmodel.h"

EtudiantModel::EtudiantModel(QObject *parent)
    : QSqlTableModel(parent)
{
    setTable("etudiant");
    select();
}

void EtudiantModel::filtrer(const QString &critere) {
    setFilter(QString("nom LIKE '%%1%' OR prenom LIKE '%%1%' OR id LIKE '%%1%'").arg(critere));
    select();
}
