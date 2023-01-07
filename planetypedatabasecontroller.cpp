#include "planetypedatabasecontroller.h"

PlaneTypeDatabaseController::PlaneTypeDatabaseController(const QString& path)
{
    m_planeDatabase = QSqlDatabase::addDatabase("QSQLITE");
    m_planeDatabase.setDatabaseName(path);

    if(!m_planeDatabase.open())
    {
        qDebug() << "Error: connection with database failed";
    }
    else
    {
        qDebug() << "Database: connection ok ";
    }
}

PlaneTypeDatabaseController::~PlaneTypeDatabaseController()
{
    if(m_planeDatabase.isOpen())
    {
        m_planeDatabase.close();
    }
}

bool PlaneTypeDatabaseController::IsOpen() const
{
    return m_planeDatabase.isOpen();
}

bool PlaneTypeDatabaseController::CreateTable()
{
    bool success = false;

    QSqlQuery query;
    query.prepare("CREATE TABLE plane_type_db(id INTEGER PRIMARY KEY, plane_type TEXT, seats INT(255), rows INT(255), columns INT(255));");

    if (!query.exec())
    {
        qDebug() << "Couldn't create the table 'plane_type': one might already exist.";
        success = false;
    }

    return success;
}

bool PlaneTypeDatabaseController::AddPlaneType(const QString planeModel, int seats, int rows, int columns)
{
    bool success = false;

    if(!planeModel.isEmpty())
    {
        QSqlQuery queryAdd;
        queryAdd.prepare("INSERT INTO plane_type_db (plane_type, seats, rows, columns) VALUES (:plane_type, :seats, :rows, :columns )");
        queryAdd.bindValue(":plane_type", planeModel);
        queryAdd.bindValue(":seats", seats);
        queryAdd.bindValue(":rows", rows);
        queryAdd.bindValue(":columns", columns);
        if(queryAdd.exec())
        {
            success = true;
        }
        else
        {
            qDebug() << "add plane_type failed" << queryAdd.lastError();
        }
    }
    else
    {
        qDebug() << "add plane_type failed: name cannot be empty";
    }

    return success;
}

bool PlaneTypeDatabaseController::PlaneTypeExists(const QString planeType)
{
    bool exists = false;
    QSqlQuery queryCheck;

    queryCheck.prepare("SELECT plane_type FROM plane_type_db WHERE plane_type = (:plane_type)");
    queryCheck.bindValue(":plane_type", planeType);

    if(queryCheck.exec())
    {
        if(queryCheck.next())
        {
            exists = true;
            qDebug() << "plane_type already exist in plane_type_db";
        }
    }
    else
    {
        qDebug() << "plane_type exist failed: " << queryCheck.lastError();
    }

    return exists;
}

int PlaneTypeDatabaseController::CountItemsInDatabase()
{
    QSqlQuery query("SELECT COUNT(*) as count FROM plane_type_db");
    if (query.next())
    {
        return query.value(0).toInt();
    }
    return 0;
}

QString PlaneTypeDatabaseController::GetPlaneTypeByID(int id)
{
    QSqlQuery queryGet;
       queryGet.prepare("SELECT plane_type FROM plane_type_db WHERE id = (:id)");
       queryGet.bindValue(":id",id);
       if(queryGet.exec())
       {
           while (queryGet.next())
           {
               qDebug() << queryGet.value(0).toString();
               return queryGet.value(0).toString();
           }
       }
       else
       {
           qDebug() << "plane_type_database error while getting plane_type To String by ID " << queryGet.lastError();
       }
       return 0;
}

int PlaneTypeDatabaseController::GetRowsByPlaneType(QString planeType)
{
    QSqlQuery queryGet;
       queryGet.prepare("SELECT rows FROM plane_type_db WHERE plane_type = (:plane_type)");
       queryGet.bindValue(":plane_type",planeType);
       if(queryGet.exec())
       {
           while (queryGet.next())
           {
               qDebug() << queryGet.value(0).toInt();
               return queryGet.value(0).toInt();
           }
       }
       else
       {
           qDebug() << "plane_type_database error while getting plane_type To String by ID " << queryGet.lastError();
       }
       return 0;
}

int PlaneTypeDatabaseController::GetColumnsByPlaneType(QString planeType)
{
    QSqlQuery queryGet;
       queryGet.prepare("SELECT columns FROM plane_type_db WHERE plane_type = (:plane_type)");
       queryGet.bindValue(":plane_type",planeType);
       if(queryGet.exec())
       {
           while (queryGet.next())
           {
               qDebug() << queryGet.value(0).toInt();
               return queryGet.value(0).toInt();
           }
       }
       else
       {
           qDebug() << "plane_type_database error while getting plane_type To String by ID " << queryGet.lastError();
       }
       return 0;
}

int PlaneTypeDatabaseController::GetSeatsByPlaneType(QString planeType)
{
    QSqlQuery queryGet;
       queryGet.prepare("SELECT seats FROM plane_type_db WHERE plane_type = (:plane_type)");
       queryGet.bindValue(":plane_type",planeType);
       if(queryGet.exec())
       {
           while (queryGet.next())
           {
               qDebug() << queryGet.value(0).toInt();
               return queryGet.value(0).toInt();
           }
       }
       else
       {
           qDebug() << "plane_type_database error while getting plane_type To String by ID " << queryGet.lastError();
       }
       return 0;
}
