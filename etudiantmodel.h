// etudiantmodel.h
#ifndef ETUDIANTMODEL_H
#define ETUDIANTMODEL_H

#include <QSqlTableModel>

class EtudiantModel : public QSqlTableModel
{
    Q_OBJECT
public:
    EtudiantModel(QObject *parent = nullptr);
    void filtrer(const QString &critere);
};

#endif // ETUDIANTMODEL_H
