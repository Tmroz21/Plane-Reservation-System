#include "planeseatcheckbox.h"
//#include "globals.h"

extern QMap<int,int> isCheckedMap;

PlaneSeatCheckBox::PlaneSeatCheckBox(QCheckBox *parent,int id): QWidget{parent}
{
    this->m_id = id;
    this->seatBox = parent;
    qDebug() << "plane_seat_checkbox: create id:" << id <<", state: "<<seatBox->checkState();
    connect(parent,SIGNAL(stateChanged(int)),this,SLOT(on_seat_clicked()));
}

void PlaneSeatCheckBox::on_seat_clicked()
{
     qDebug() << "plane_seat_checkbox: clicked "<<m_id<<",state changed to:"<<seatBox->checkState();
     if(seatBox->checkState() == Qt::Checked)
     {
        isCheckedMap.insert(m_id,1);
     }
     else
     {
        switch(isCheckedMap.constFind(m_id).value())
        {
            case(1):
                isCheckedMap.remove(m_id);
                break;
            case(0):
                isCheckedMap.remove(m_id);
                break;
        }
     }
     qDebug() << isCheckedMap;
}
