#include "planeseatcheckbox.h"

PlaneSeatCheckBox::PlaneSeatCheckBox(QCheckBox *parent,int id): QWidget{parent}
{
    this->m_id = id;
    this->seatBox = parent;
    qDebug() << "object" << id <<"create";
    connect(parent,SIGNAL(clicked()),this,SLOT(on_seat_clicked()));
}
//void PlaneSeatCheckBox::onSeatClicked()
//{
//    qDebug() << "test"<< m_id;
//}
void PlaneSeatCheckBox::on_seat_clicked()
{
     qDebug() << "seat_clicked"<<m_id<<seatBox->checkState();
}
