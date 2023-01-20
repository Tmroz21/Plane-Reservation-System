#include "addflightwindow.h"
#include "ui_addflightwindow.h"
#include "planetypedatabasecontroller.h"
#include "flightsdatabasecontroller.h"
#include "seatsdatabasecontroller.h"

AddFlightWindow::AddFlightWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddFlightWindow)
{
    ui->setupUi(this);
    AddItemsToPlaneTypeComboBox();
    PlaneTypeDatabaseController planeTypeDB(planeTypeDB_path);
    planeTypeDB.CreateTable();
    FlightsDatabaseController flightsDB(flightsDB_path);
    flightsDB.CreateTable();
    //SeatsDatabaseController seatsDB(seatsDB_path);

}

AddFlightWindow::~AddFlightWindow()
{
    delete ui;
}

void AddFlightWindow::AddItemsToPlaneTypeComboBox()
{
    PlaneTypeDatabaseController planeTypeDB(planeTypeDB_path);
    for(int i=1;i<=planeTypeDB.CountItemsInDatabase();i++)
    {
        ui->planeTypeComboBox->addItem(planeTypeDB.GetPlaneTypeByID(i));
    }
}

void AddFlightWindow::on_addFlightPushButton_clicked()
{
    bool isDepartureDigit, isArrivalDigit;
    FlightsDatabaseController flightsDB(flightsDB_path);
    QString planeType, code ,departure, arrival;
    planeType = ui->planeTypeComboBox->currentText();
    departure = ui->departureLineEdit->text();
    arrival = ui->arrivalLineEdit->text();
    code = ui->codeLineEdit->text();
    qDebug() << code.size();

    if(!flightsDB.FlightExists(code) && code.size() == 4)
    {
        if(!departure.toDouble(&isDepartureDigit) && !arrival.toDouble(&isArrivalDigit) && !planeType.isEmpty() && !departure.isEmpty() && !arrival.isEmpty() && !code.isEmpty())
        {
            if(flightsDB.AddFlightToTable(planeType,code,departure,arrival))
            {
                ui->informationLabel->setText("Flight " + code + " added");

                PlaneTypeDatabaseController planeTypeDB(planeTypeDB_path);
                int seats = planeTypeDB.GetSeatsByPlaneType(planeType);
                SeatsDatabaseController seatsDB(seatsDB_path);
                seatsDB.CreatTable(code);
                //MainWindow().UpdateFlightsList();
                for(int i=1;i<=seats;i++)
                {
                    seatsDB.AddSeat(0,code);
                }
            }
        }
        else
        {
           ui->informationLabel->setText("departure and arrival can not be a digit or empty");
        }
    }
    else
    {
     ui->informationLabel->setText("Flight " + code + " already exist or code is given in wrong format");
    }
}

