#include "mainwindow.h"
#include "qgridlayout.h"
#include "qobjectdefs.h"
#include "ui_mainwindow.h"
#include "planeseatcheckbox.h"
#include "addflightwindow.h"
#include "planetypedatabasecontroller.h"
#include "flightsdatabasecontroller.h"
#include "seatsdatabasecontroller.h"

FlightsDatabaseController flightsDB(flightsDB_path);
//PlaneTypeDatabaseController planeTypeDB(planeTypeDB_path);

QMap<int,int> isCheckedMap;


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    UpdateFlightsList();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void *MainWindow::CreateSeatView(QString code)
{
    QGroupBox *groupBox = new QGroupBox(tr("Seats"));
    QGridLayout *vbox = new QGridLayout;
    FlightsDatabaseController flightsDB(flightsDB_path);
    QString planeType = flightsDB.GetPlaneTypeByCode(code);
    qDebug() << "planetype" + planeType;
    PlaneTypeDatabaseController planeTypeDB(planeTypeDB_path);
    int columns = planeTypeDB.GetColumnsByPlaneType(planeType);
    int seats = planeTypeDB.GetSeatsByPlaneType(planeType);

    SeatsDatabaseController seatDB(seatsDB_path);
    for(int i=1;i<=seats;i++)
    {
        QCheckBox* seat = new QCheckBox();

        switch(seatDB.IsSeatChecked(i,code))
        {
            case 1:
                seat->setChecked(1);
                seat->setDisabled(1);
                qDebug()<< "seat checked";
            break;
            case 0:
                seat->setChecked(0);
                seat->setDisabled(0);
                qDebug()<< "seat not checked";
            break;
        }
        PlaneSeatCheckBox *st = new PlaneSeatCheckBox(seat,i);
        vbox->addWidget(st->parentWidget(),(i-1)/columns,(i-1)%columns);
    }
    groupBox->setLayout(vbox);
    QGridLayout *grid = new QGridLayout;
    grid->addWidget(groupBox);
    ui->horizontalLayout->addLayout(grid);
    if(m_isObjectReadyToBeDelete)
    {
        if ( ui->horizontalLayout->itemAt(2)->layout() != NULL )
        {
            QLayoutItem* item;
            while ( ( item = ui->horizontalLayout->itemAt(2)->layout()->takeAt( 0 ) ) != NULL )
            {
                delete item->widget();
                delete item;
            }
            delete ui->horizontalLayout->itemAt(2)->layout();
        }
    }
    m_isObjectReadyToBeDelete = true;
}

void MainWindow::on_pushButton_clicked()
{
    qDebug() << "booking_button: Clicked";
    qDebug() << isCheckedMap;
    qDebug() << m_code;
    qDebug() << isCheckedMap.count();
//    for(int i=0;i<=isCheckedMap.count()+1;i++)
//    {
//        qDebug() <<i  << " booking" << isCheckedMap;
//        SeatsDatabaseController seatDB(seatsDB_path);
//        seatDB.updateSeatCheckedValue(isCheckedMap.lastKey(),isCheckedMap.value(isCheckedMap.lastKey()),m_code);
//        isCheckedMap.remove(isCheckedMap.lastKey());
//    }
    do
    {
        qDebug()  << " booking" << isCheckedMap;
        SeatsDatabaseController seatDB(seatsDB_path);
        seatDB.updateSeatCheckedValue(isCheckedMap.lastKey(),isCheckedMap.value(isCheckedMap.lastKey()),m_code);
        isCheckedMap.remove(isCheckedMap.lastKey());
    }
    while (!isCheckedMap.empty());
    isCheckedMap.clear();
}
void MainWindow::on_actionAdd_flight_triggered()
{
    AddFlightWindow *addFlightWindow = new AddFlightWindow();
    addFlightWindow->show();
}

void MainWindow::on_listWidget_itemClicked(QListWidgetItem *item)
{
    PlaneTypeDatabaseController planeTypeDB(planeTypeDB_path);
    m_code =  item->text().first(4);
    //qDebug() << code;
    CreateSeatView(m_code);
}

void MainWindow::AddFlightToList(int id)
{
    //FlightsDatabaseController flightsDB(flightsDB_path);
    qDebug() << flightsDB.GetStringRecordByID(id,"code");
    ui->listWidget->addItem(flightsDB.GetStringRecordByID(id,"code") + " " + flightsDB.GetStringRecordByID(id,"Departure") + " - " + flightsDB.GetStringRecordByID(id,"Arrival"));

}

void MainWindow::UpdateFlightsList()
{
    //FlightsDatabaseController flightsDB(flightsDB_path);
    ui->listWidget->clear();
    for(int i=1;i<=flightsDB.CountItemsInDatabase();i++)
    {
        qDebug() << "adding flight to list" << i <<" from "<< flightsDB.CountItemsInDatabase();
        AddFlightToList(i);
    }
}
