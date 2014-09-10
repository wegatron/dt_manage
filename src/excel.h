#ifndef EXCEL_H
#define EXCEL_H

#include <QtGui>
#include <QStandardItemModel>

void ExportExcel(const QString &filename, const QSortFilterProxyModel *sort_filter);

#endif // EXCEL_H
