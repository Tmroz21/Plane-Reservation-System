#ifndef ADDFLIGHTWINDOW_H
#define ADDFLIGHTWINDOW_H

#include <QWidget>

static const QString planeTypeDB_path = "plane_type_db.db";
static const QString flightsDB_path = "flights_db.db";
static const QString seatsDB_path = "seats_db.db";

namespace Ui {
class AddFlightWindow;
}

class AddFlightWindow : public QWidget
{
    Q_OBJECT

public:
    explicit AddFlightWindow(QWidget *parent = nullptr);

    ~AddFlightWindow();

    void AddItemsToPlaneTypeComboBox();

private slots:
    void on_addFlightPushButton_clicked();

private:
    Ui::AddFlightWindow *ui;
};

#endif // ADDFLIGHTWINDOW_H
