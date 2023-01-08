#include "addflightwindow.h"
#include "ui_addflightwindow.h"
#include "planetypedatabasecontroller.h"
#include "flightsdatabasecontroller.h"

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

    if(!flightsDB.FlightExists(code))
    {
        if(!departure.toDouble(&isDepartureDigit) && !arrival.toDouble(&isArrivalDigit))
        {
            if(flightsDB.AddFlightToTable(planeType,code,departure,arrival))
            {
                ui->informationLabel->setText("Flight " + code + " added");
            }
        }
        else
        {
           ui->informationLabel->setText("departure and arrival can not be a digit");
        }
    }
    else
    {
     ui->informationLabel->setText("Flight " + code + " already exist");
    }
}

