#include "planeseatcheckbox.h"

PlaneSeatCheckBox::PlaneSeatCheckBox(QCheckBox *parent,int id): QWidget{parent}
{
    this->m_id = id;
    this->seatBox = parent;
    qDebug() << "plane_seat_checkbox: create id:" << id <<", state: "<<seatBox->checkState();
    connect(parent,SIGNAL(clicked()),this,SLOT(on_seat_clicked()));
}

void PlaneSeatCheckBox::on_seat_clicked()
{
     qDebug() << "plane_seat_checkbox: clicked "<<m_id<<",state changed to:"<<seatBox->checkState();
}
