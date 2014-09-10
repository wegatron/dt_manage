#include "excel.h"

#include <libxl.h>

using namespace libxl;

void ExportExcel(const QString &filename, const QSortFilterProxyModel *sort_filter)
{
    Book* book = xlCreateBook();
    if(book)
    {
        Sheet* sheet = book->addSheet("Custom formats");
        if(sheet)
        {
            sheet->writeStr(0,0, "哈哈!");
        }

        if(book->save(filename.toStdString().c_str())) {
            //std::cout << "File custom.xls has been created." << std::endl;
        }
        book->release();
    }

    return;
}
