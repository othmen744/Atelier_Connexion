// professeurmodel.cpp
#include "professeurmodel.h"

ProfesseurModel::ProfesseurModel(QObject *parent)
    : QSqlTableModel(parent)
{
    setTable("professeur");
    select();
}

void ProfesseurModel::filtrer(const QString &critere) {
    setFilter(QString("nom_professeur LIKE '%%1%' OR prenom_professeur LIKE '%%1%' OR id_professeur LIKE '%%1%'").arg(critere));
    select();
}
