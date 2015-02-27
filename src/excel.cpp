#include "excel.h"

#include "stdio.h"

#include "encode.h"

void ExportExcel(const QString &filename, const QSortFilterProxyModel *sort_filter,
                 const std::string &header, const std::string &remark)
{

    QMessageBox::information(NULL,"info",filename);
    std::string std_filename = filename.toStdString();
    std::string r_filename = UTF8ToGB2312(std_filename);
    FILE *fp = fopen(r_filename.c_str(), "w");

    if(fp == NULL) {
        QMessageBox::information(NULL, "错误", "打开文件:"+filename+"失败！");
        return;
    }
    fprintf(fp, "%s\n",UTF8ToGB2312( header).c_str() );
    int row = sort_filter->rowCount();
    int col = sort_filter->columnCount();

    for(int i=0; i<row; ++i)
    {
        int j=0;
        for (; j<col-1; ++j)
        {
            std::string tmp_pre = sort_filter->data(sort_filter->index(i,j)).toString().toStdString();
            std::string tmp_after = UTF8ToGB2312(tmp_pre);
            fprintf(fp, "%s ,", tmp_after.c_str() );
        }
        std::string tmp_pre = sort_filter->data(sort_filter->index(i,j)).toString().toStdString();
        std::string tmp_after = UTF8ToGB2312(tmp_pre);
        fprintf(fp, "%s\n", tmp_after.c_str() );
    }
    fprintf(fp, "%s\n",UTF8ToGB2312( remark ).c_str() );
    fclose(fp);
    return;
}
