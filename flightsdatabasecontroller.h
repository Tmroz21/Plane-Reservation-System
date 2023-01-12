#ifndef FLIGHTSDATABASECONTROLLER_H
#define FLIGHTSDATABASECONTROLLER_H

#include <QString>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QDebug>

class FlightsDatabaseController
{
public:
    FlightsDatabaseController(const QString& path);

    ~FlightsDatabaseController();

    bool IsOpen() const;

    bool CreateTable();

    bool AddFlightToTable(const QString planeType, const QString code, const QString departure, const QString arrival);

    bool FlightExists(const QString code) const;

    QString GetPlaneTypeByCode(const QString code);

    QString GetStringRecordByID(int id, const QString date);

    int CountItemsInDatabase();

private:

    QSqlDatabase m_flightsDatabase;


};

#endif // FLIGHTSDATABASECONTROLLER_H
