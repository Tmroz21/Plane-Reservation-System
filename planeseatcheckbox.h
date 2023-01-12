#ifndef PLANESEATCHECKBOX_H
#define PLANESEATCHECKBOX_H

#include "qcheckbox.h"
#include <QWidget>
#include <QMap>

class PlaneSeatCheckBox : public QWidget
{
    Q_OBJECT
public:
    explicit PlaneSeatCheckBox(QCheckBox *parent = nullptr,int id = 0);


signals:

private slots:
//    void onSeatClicked();
    void on_seat_clicked();

private:
    QCheckBox *seatBox{};
    int m_id{};
};

#endif // PLANESEATCHECKBOX_H
