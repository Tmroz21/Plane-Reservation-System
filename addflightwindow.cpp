#include "addflightwindow.h"
#include "ui_addflightwindow.h"
#include "planetypedatabasecontroller.h"

static const QString planeTypeDB_path = "plane_type_db.db";
PlaneTypeDatabaseController planeTypeDB(planeTypeDB_path);

AddFlightWindow::AddFlightWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddFlightWindow)
{
    ui->setupUi(this);
    AddItemsToPlaneTypeComboBox();
}

AddFlightWindow::~AddFlightWindow()
{
    delete ui;
}

void AddFlightWindow::AddItemsToPlaneTypeComboBox()
{

    for(int i=1;i<=planeTypeDB.CountItemsInDatabase();i++)
    {
        ui->planeTypeComboBox->addItem("test");
    }

}
