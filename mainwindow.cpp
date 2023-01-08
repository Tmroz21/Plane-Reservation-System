#include "mainwindow.h"
#include "qgridlayout.h"
#include "qobjectdefs.h"
#include "ui_mainwindow.h"
#include "planeseatcheckbox.h"
#include "addflightwindow.h"
#include "planetypedatabasecontroller.h"
#include "flightsdatabasecontroller.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

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
    PlaneTypeDatabaseController planeTypeDB(planeTypeDB_path);
    int columns = planeTypeDB.GetColumnsByPlaneType(planeType);
    for(int i=1;i<=planeTypeDB.GetSeatsByPlaneType(planeType);i++)
    {
        //std::string istr = std::to_string(i);
        //const char * ich = istr.c_str();

        QCheckBox* seat = new QCheckBox();
        //seat->setCheckState(Qt::Checked);
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
}

void MainWindow::on_actionAdd_flight_triggered()
{
    AddFlightWindow *addFlightWindow = new AddFlightWindow();
    addFlightWindow->show();
}


void MainWindow::on_listWidget_itemClicked(QListWidgetItem *item)
{
    QString code =  item->text().first(4);
    //qDebug() << code;
    CreateSeatView(code);
}

