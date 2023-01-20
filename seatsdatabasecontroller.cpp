#include "seatsdatabasecontroller.h"

SeatsDatabaseController::SeatsDatabaseController(const QString &path)
{
    m_seatsDatabase = QSqlDatabase::addDatabase("QSQLITE");
    m_seatsDatabase.setDatabaseName(path);

    if(!m_seatsDatabase.open())
    {
        qDebug() << "Error: connection with database failed";
    }
    else
    {
        qDebug() << "Database: connection ok ";
    }
}

SeatsDatabaseController::~SeatsDatabaseController()
{
    if(m_seatsDatabase.isOpen())
    {
        m_seatsDatabase.close();
    }
}

bool SeatsDatabaseController::IsOpen()
{
    return m_seatsDatabase.isOpen();
}

bool SeatsDatabaseController::CreatTable(const QString code)
{
    bool success = false;

    QSqlQuery query;
    query.prepare("CREATE TABLE "+ code +"(id INTEGER PRIMARY KEY, is_checked INT(255));");

    if (!query.exec())
    {
        qDebug() << "Couldn't create the table '" + code + "': one might already exist.";
        success = false;
    }

    return success;
}

bool SeatsDatabaseController::AddSeat(int isChecked,const QString code)
{
    bool success = false;

        QSqlQuery queryAdd;
        queryAdd.prepare("INSERT INTO " + code + " (is_checked) VALUES (:is_checked)");
        queryAdd.bindValue(":is_checked",isChecked );
        if(queryAdd.exec())
        {
            success = true;
            qDebug() << "seat added";
        }
        else
        {
            qDebug() << "add "+ code +" failed" << queryAdd.lastError();
        }

    return success;
}

int SeatsDatabaseController::IsSeatChecked(int id, const QString code)
{
    QSqlQuery queryGet;
    queryGet.prepare("SELECT is_checked FROM " + code + " WHERE id = (:id)");
    queryGet.bindValue(":id",id);
    if(queryGet.exec())
    {
        while (queryGet.next())
        {
            return queryGet.value(0).toInt();
        }
    }
    else
    {
        qDebug() << queryGet.lastError();
    }
    return 0;
}
void SeatsDatabaseController::updateSeatCheckedValue(int id, int isChecked, const QString code)
{
    QSqlQuery query;
    query.prepare("UPDATE " + code + " SET is_checked = :is_checked WHERE id = (:id)");
    query.bindValue(":id",id);
    query.bindValue(":is_checked",isChecked);
    if (query.exec())
    {
        qDebug() << "updated";
    }
    else
    {
        qDebug() << "remove all trains failed: " << query.lastError();
    }
}
