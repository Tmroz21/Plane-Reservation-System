#ifndef ADDFLIGHTWINDOW_H
#define ADDFLIGHTWINDOW_H

#include <QWidget>

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
