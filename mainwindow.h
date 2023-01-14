#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGroupBox>
#include <QListWidget>
#include <QCheckBox>
#include <QSignalMapper>
#include <QObject>
#include <QLayoutItem>
#include <flightsdatabasecontroller.h>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

    ~MainWindow();

    void *CreateSeatView(QString code);

    void AddFlightToList(int id);

    void UpdateFlightsList();


private slots:
    void on_pushButton_clicked();

    void on_actionAdd_flight_triggered();


    void on_listWidget_itemClicked(QListWidgetItem *item);

private:
    Ui::MainWindow *ui;

    bool m_isObjectReadyToBeDelete{};

    QString m_code{};


};
#endif // MAINWINDOW_H
