#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "mux.h"
#include "can.h"

#include <QMainWindow>
#include <QDebug>
#include<QMessageBox>
#include <QStandardItemModel>


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

    void recevoir();

    void on_connection_clicked();

    void on_refresh_clicked();

    void on_EnvoyerTrames_clicked();

    void envoyerTrameSuivante();

    void on_StopTrames_clicked();

private:
    Ui::MainWindow *ui;
    Mux *mux;
    CAN *can;
    QStandardItemModel *modelCan;
    QTimer *timermsg;

    QTimer *timerTrames;
    int indexTrame = 0;

    QVector<unsigned long> tramesPSA = {
        0x0F6, 0x036, 0x168, 0x128, 0x0B6, 0x161
    };

};
#endif // MAINWINDOW_H
