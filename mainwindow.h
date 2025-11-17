#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "mux.h"
#include "can.h"

#include <QMainWindow>
#include <QDebug>
#include<QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void configurerBusCAN();

private slots:
    void initialiserComboCartes();


    void on_connection_clicked();

    void on_refresh_clicked();

private:
    Ui::MainWindow *ui;
    Mux *mux;
    CAN *can;


};
#endif // MAINWINDOW_H
