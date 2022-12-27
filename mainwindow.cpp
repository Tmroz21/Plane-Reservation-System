#include "mainwindow.h"
#include "qgridlayout.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    QGridLayout *grid = new QGridLayout;
    grid->addWidget(CreateSeatView(),0,1);
     grid->addWidget(CreatePlaneView(), 0, 0);
    setLayout(grid);
    ui->setupUi(this);
    ui->Centralwidget->setLayout(grid);

}
MainWindow::~MainWindow()
{
    delete ui;
}
QGroupBox *MainWindow::CreateSeatView()
{
    QGroupBox *groupBox = new QGroupBox(tr("Seats"));
    QRadioButton *radio1 = new QRadioButton(tr("&Radio button 1"));
    QRadioButton *radio2 = new QRadioButton(tr("R&adio button 2"));
    QRadioButton *radio3 = new QRadioButton(tr("Ra&dio button 3"));

    radio1->setChecked(true);
    QVBoxLayout *vbox = new QVBoxLayout;
    vbox->addWidget(radio1);
    vbox->addWidget(radio2);
    vbox->addWidget(radio3);
    vbox->addStretch(1);
    groupBox->setLayout(vbox);

    return groupBox;
}
QGroupBox *MainWindow::CreatePlaneView()
{
    QGroupBox *groupBox = new QGroupBox(tr("Planes"));
    QListWidget *list = new  QListWidget();
    QVBoxLayout *vbox = new QVBoxLayout;

    vbox->addWidget(list);
    //vbox->addStretch(1);
    groupBox->setLayout(vbox);

    return groupBox;
}

