#include "flightsdatabasecontroller.h"

FlightsDatabaseController::FlightsDatabaseController(const QString &path)
{
    m_flightsDatabase = QSqlDatabase::addDatabase("QSQLITE");
    m_flightsDatabase.setDatabaseName(path);

    if(!m_flightsDatabase.open())
    {
        qDebug() << "Error: connection with database failed";
    }
    else
    {
        qDebug() << "Database: connection ok ";
    }
}

FlightsDatabaseController::~FlightsDatabaseController()
{
    if(m_flightsDatabase.isOpen())
    {
        m_flightsDatabase.close();
    }
}

bool FlightsDatabaseController::IsOpen() const
{
    return m_flightsDatabase.isOpen();
}

bool FlightsDatabaseController::CreateTable()
{
    bool success = false;

    QSqlQuery query;
    query.prepare("CREATE TABLE flights_db(id INTEGER PRIMARY KEY, plane_type TEXT, code TEXT, departure TEXT, arrival TEXT);");

    if (!query.exec())
    {
        qDebug() << "Couldn't create the table 'plane_type': one might already exist.";
        success = false;
    }

    return success;
}

bool FlightsDatabaseController::AddFlightToTable(const QString planeType, const QString code, const QString departure, const QString arrival)
{
    bool success = false;

    if(!planeType.isEmpty())
    {
        QSqlQuery queryAdd;
        queryAdd.prepare("INSERT INTO flights_db (plane_type, seats, rows, columns) VALUES (:plane_type, :seats, :rows, :columns )");
        queryAdd.bindValue(":plane_type", planeType);
        queryAdd.bindValue(":code", code);
        queryAdd.bindValue(":departure", departure);
        queryAdd.bindValue(":arrival", arrival);
        if(queryAdd.exec())
        {
            success = true;
        }
        else
        {
            qDebug() << "add flights failed" << queryAdd.lastError();
        }
    }
    else
    {
        qDebug() << "add flights failed: name cannot be empty";
    }

    return success;
}
