#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidget>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:

    void on_ApplicationExit();

private slots:

    void on_pushButton_LoadImage_clicked();

    void on_pushButton_SaveAsCCode_clicked();

    void update();

    void on_pushButton_4_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_Ipeak_sliderMoved(int position);

private:
    Ui::MainWindow *ui;

    int loadImage(QString filename);

    int initIceCreamHat();

    static void Image_Show();

    static void VCNL_INT();
    static void JoyUP_INT();
    static void JoyDOWN_INT();
    static void JoyLEFT_INT();
    static void JoyRIGHT_INT();
    static void JoySELECT_INT();


};

#endif // MAINWINDOW_H
