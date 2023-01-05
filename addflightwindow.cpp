#include "addflightwindow.h"
#include "ui_addflightwindow.h"
#include "planetypedatabasecontroller.h"
#include "flightsdatabasecontroller.h"

static const QString planeTypeDB_path = "plane_type_db.db";
static const QString flightsDB_path = "flights_db.db";


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
{;
    //bool checkStr;
    FlightsDatabaseController flightsDB(flightsDB_path);
    QString planeType, code ,departure, arrival;
    planeType = ui->planeTypeComboBox->currentText();
    departure = ui->departureLineEdit->text();
    arrival = ui->arrivalLineEdit->text();
    code = ui->codeLineEdit->text();
    //double departureTest = departure.toDouble(&checkStr);
    //if(!checkStr){
    //    qDebug() << "ok";
    //}
    if(flightsDB.FlightExists(code) == 0)
    {
       flightsDB.AddFlightToTable(planeType,code,departure,arrival);
    }
}

