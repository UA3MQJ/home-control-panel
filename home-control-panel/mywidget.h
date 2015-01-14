#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>
/* Добавляем заголовочные файлы для работы с таймером и UDP портом */
#include <QTimer>
#include <QUdpSocket>


namespace Ui {
class MyWidget;
}

class MyWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MyWidget(QWidget *parent = 0);
    ~MyWidget();


private slots:
    void onPushButton_2_clicked();
    void onPushButton_3_clicked();
    void onPushButton_4_clicked();
    /*Слоты для первой крутилки на изменение графика и текстовой метки*/
    void onDial_valueChanged();
    void onDial_valueChanged1();
    /*******************************/

    /*Слоты для первой крутилки на изменение графика и текстовой метки*/
    void onDial_valueChanged2();
    void onDial_valueChanged3();
    /*******************************/


    /* Добавляем слоты для приема/передачи датаграмм */
   // void onMyTimerTimeout();
  //  void onReadyRead();

private:
    Ui::MyWidget *ui;
    //QTimer *myTimer;
    //QUdpSocket *soket;



};

#endif // MYWIDGET_H
