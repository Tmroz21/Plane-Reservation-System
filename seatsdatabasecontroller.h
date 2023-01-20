#ifndef SEATSDATABASECONTROLLER_H
#define SEATSDATABASECONTROLLER_H

#include <QString>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QDebug>


class SeatsDatabaseController
{
public:
    SeatsDatabaseController(const QString& path);

    ~SeatsDatabaseController();

    bool IsOpen();

    bool CreatTable(const QString tableName);

    bool AddSeat(int isChecked,const QString code);

    int IsSeatChecked(int id, const QString code);

    void updateSeatCheckedValue(int id, int isChecked, const QString code);

private:

    QSqlDatabase m_seatsDatabase;

};

#endif // SEATSDATABASECONTROLLER_H
