
#ifndef PROFESSEURMODEL_H
#define PROFESSEURMODEL_H

#include <QSqlTableModel>

class ProfesseurModel : public QSqlTableModel
{
    Q_OBJECT
public:
    ProfesseurModel(QObject *parent = nullptr);
    void filtrer(const QString &critere);
};

#endif // PROFESSEURMODEL_H
