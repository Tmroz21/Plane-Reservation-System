#include "mainwindow.h"
#include "qgridlayout.h"
#include "qobjectdefs.h"
#include "ui_mainwindow.h"
#include "planeseatcheckbox.h"
#include "addflightwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    QGridLayout *grid = new QGridLayout;
    grid->addWidget(CreateSeatView());
    ui->setupUi(this);
    ui->horizontalLayout->addLayout(grid);

}
MainWindow::~MainWindow()
{
    delete ui;
}
QGroupBox *MainWindow::CreateSeatView()
{
    QGroupBox *groupBox = new QGroupBox(tr("Seats"));
    QGridLayout *vbox = new QGridLayout;

    for(int i=1;i<=60;i++)
    {
        //std::string istr = std::to_string(i);
        //const char * ich = istr.c_str();

        QCheckBox* seat = new QCheckBox();
        PlaneSeatCheckBox *st = new PlaneSeatCheckBox(seat,i);

        vbox->addWidget(st->parentWidget(),(i-1)/6,(i-1)%6);
    }
    groupBox->setLayout(vbox);
    return groupBox;
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

