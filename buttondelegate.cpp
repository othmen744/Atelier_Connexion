// buttondelegate.cpp
#include "buttondelegate.h"
#include <QPainter>
#include <QPushButton>
#include <QApplication>
#include <QStyleOptionButton>
#include <QModelIndex>
#include <QPainter>

#include "buttondelegate.h"
ButtonDelegate::ButtonDelegate(QObject *parent) : QItemDelegate(parent) {}

void ButtonDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const {
    if (index.column() == 3) { // Assuming the "Modifier" column is the 4th column
        QStyleOptionButton button;
        button.rect = option.rect;
        button.text = "Modifier";
        button.state = QStyle::State_Enabled;

        // Draw the button
        QApplication::style()->drawControl(QStyle::CE_PushButton, &button, painter);
    } else {
        QItemDelegate::paint(painter, option, index);
    }
}



QSize ButtonDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const {
    if (index.column() == 3) { // Assuming the "Modifier" column is the 4th column
        return QSize(100, option.rect.height());
    }
    return QItemDelegate::sizeHint(option, index);
}
