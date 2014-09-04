#ifndef DATABASE_H
#define DATABASE_H

#include <QtSql>

class DtDataBase
{
public:
    static QSqlDatabase &getDtDataBase();
private:
    DtDataBase() {}
    static QSqlDatabase db;
    static bool is_initialized;
};

#endif // DATABASE_H
