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

    void on_btnVoyantsOn_clicked();
    void on_btnVoyantsOff_clicked();

    void on_sliderRegime_valueChanged(int value);
    void on_sliderVitesse_valueChanged(int value);
    void on_sliderEssence_valueChanged(int value);
    void on_sliderTempEau_valueChanged(int value);

    void on_sliderRapportBVA_valueChanged(int value);
    void on_sliderModeBVA_valueChanged(int value);
    void on_sliderLuminosite_valueChanged(int value);

    void on_clignotantGauche_clicked();
    void on_clignotantDroite_clicked();
    void on_feuxBrouillardAr_clicked();
    void on_feuxBrouillardAv_clicked();
    void on_feuxCroisement_clicked();
    void on_feuxDeRoute_clicked();
    void on_Frpk_clicked();
    void on_service_clicked();
    void on_abs_clicked();
    void on_AlerteHuile_clicked();
    void on_esp_clicked();
    void on_secPassDef_clicked();
    void on_AirBag_clicked();

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

    bool m_clignoGaucheOn = false;
    bool m_clignoDroiteOn = false;
    bool m_brouilAr = false;
    bool m_brouilAv = false;
    bool m_Crois = false;
    bool m_Route = false;
    bool m_service = false;
    bool m_frpk = false;
    bool m_abs = false;
    bool m_alerteHuile = false;
    bool m_esp = false;
    bool m_secPassDef = false;
    bool m_airBag = false;
};
#endif // MAINWINDOW_H
