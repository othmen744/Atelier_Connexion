// buttondelegate.h
#ifndef BUTTONDELEGATE_H
#define BUTTONDELEGATE_H

#include <QItemDelegate>

class ButtonDelegate : public QItemDelegate {
    Q_OBJECT

public:
    explicit ButtonDelegate(QObject *parent = nullptr);

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override;

signals:
    void editButtonClicked(const QModelIndex &index);
};

#endif // BUTTONDELEGATE_H
