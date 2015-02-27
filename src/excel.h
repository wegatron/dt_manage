#ifndef EXCEL_H
#define EXCEL_H

#include <string>

#include <QtGui>
#include <QStandardItemModel>

void ExportExcel(const QString &filename, const QSortFilterProxyModel *sort_filter,
                 const std::string &header, const std::string &remark="");

#endif // EXCEL_H
