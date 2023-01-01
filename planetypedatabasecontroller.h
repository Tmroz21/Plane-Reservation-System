#ifndef PLANETYPEDATABASECONTROLLER_H
#define PLANETYPEDATABASECONTROLLER_H

#include <QString>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QDebug>

class PlaneTypeDatabaseController
{
public:

    PlaneTypeDatabaseController(const QString& path);

    ~PlaneTypeDatabaseController();

    bool IsOpen() const;

    bool CreateTable();

    bool AddPlaneType(const QString planeType, int seats, int rows, int columns);

    bool PlaneTypeExists(const QString planeType);

    int CountItemsInDatabase();



private:

    QSqlDatabase m_planeDatabase;

};

#endif // PLANETYPEDATABASECONTROLLER_H
