/*
Есть график функции, есть крутилка dial. По значению с нее рисуем вторую функцию y=dial_value.
Мы должны нарисовать график первой функции красным, если У точки больше У линии крутилки и синим, если У фунции графика 1 мельше У функции линии от крутилки.
Пока это реализовано рисованием 2-го графика поверх первого, что есть некрасивый костыль.


*/
#include "mywidget.h"
#include "ui_mywidget.h"
#include <QDebug>


QByteArray datagram="$T25252525252500000014200000252525252525252525252525025"; //Создаем датаграмму для отправки в МК

MyWidget::MyWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MyWidget)
{
    ui->setupUi(this);

    /*в данном блоке  добавляем работу с сетью*/
   /* socket = new QUdpSocket(this);
    connect(socket,SIGNAL(readyRead()),SLOT(onReadyRead()));
    socket->bind(55000);

    myTimer = new QTimer(this);
    connect(myTimer,SIGNAL(timeout()),SLOT(onMyTimerTimeout()));
    myTimer->start(5000);
   */

    ui->dial_2->setDisabled(true);
    connect(ui->pushButton_2,SIGNAL(clicked()),SLOT(onPushButton_2_clicked()));//при нажатии кнопки рисуем график 1
    connect(ui->pushButton_3,SIGNAL(clicked()),SLOT(onPushButton_3_clicked()));//при нажатии кнопки рисуем график 2
    connect(ui->pushButton_4,SIGNAL(clicked()),SLOT(onPushButton_4_clicked()));// очищаем координатную сетку от всех графиков
    connect(ui->dial,SIGNAL(valueChanged(int)),SLOT(onDial_valueChanged())); // рисуем линию от крутилки 1
    connect(ui->dial,SIGNAL(valueChanged(int)),SLOT(onPushButton_2_clicked())); //подрезаем график 1 по значению крутилки 1
    connect(ui->dial,SIGNAL(valueChanged(int)),SLOT(onDial_valueChanged1())); //в соответствии с положением крутилки
    connect(ui->dial_2,SIGNAL(valueChanged(int)),SLOT(onDial_valueChanged2())); // рисуем горизонтальную линию от крутилки 2
    connect(ui->dial_2,SIGNAL(valueChanged(int)),SLOT(onPushButton_2_clicked())); //подрезаем график 1 по значению крутилки 1
    connect(ui->dial_2,SIGNAL(valueChanged(int)),SLOT(onDial_valueChanged3())); //в соответствии с положением крутилки 2

    for (int i=0;i<5;i++)
    {
    ui->graph->addGraph();//добавляем 4 графика но не отрисовываем их пока и не задаеи значений точкам этих графиков
    }

    }

MyWidget::~MyWidget()
{
    delete ui;
}
/*
//Слот для отправки датаграммы по сети после исполнения таймаута
void MyWidget::onMyTimerTimeout()
{
    ui->textEdit->insertPlainText("On Timer\n");

    QDebug()<<"SEND"<<datagram.toHex();
    socket->writeDatagram(datargam,QHostAdress("192.168.20.60"),10001);
}

// Слот для получения датаграммы от МК
void MyWidget::onReadyRead()
{
    qDebug()<<"onReadyReady()";
    QByteArray buffer;
    buffer.resize(socket->pendingDatagramSize());
    socket->readDatagram(buffer.data(),buffer.size());

    qDebug()<<buffer.toHex();
}
*/

//Слот для создания графика при нажатии на кнопку
void MyWidget::onPushButton_2_clicked()
{
    //generate some data
    QVector<double> x(101),y(101),x_red,y_red,x_blue,y_blue; //Инициализируем четыре вектора
   double Limit_hot, Limit_cold;
   int shet_hot=0, shet_cold;
   Limit_hot=(ui->dial->value())*0.01;
   Limit_cold=(ui->dial_2->value())*0.01;
    for (int i=0;i<101;++i)
    {
        x[i]=i/50.0-1; // x в диапазоне от 0 до 1
        y[i]=x[i]*x[i];
      if (y[i]>Limit_hot) //выделяем точки для второго графика по условию
        {
        y_red.append(y[i]);
        x_red.append(x[i]);
        shet_hot++;
        }
      if (y[i]<Limit_cold)
      {
          y_blue.append(y[i]);
          x_blue.append(x[i]);
          shet_cold++;
      }
    }




    //Создаем график и данные для него
    ui->graph->graph(0)->setData(x,y);
      if(shet_hot!=0)
    {
        ui->graph->graph(1)->setData(x_red,y_red);
        ui->graph->graph(1)->setPen(QPen(Qt::red));
    }
      if(shet_cold!=0)
      {
          ui->graph->graph(4)->setData(x_blue,y_blue);
          ui->graph->graph(4)->setPen(QPen(Qt::blue));
      }


       //помещаем метки на оси
    ui->graph->xAxis->setLabel("x");
    ui->graph->yAxis->setLabel("y");
    ui->graph->graph(0)->setPen(QPen(Qt::green));
    ui->graph->graph(0)->setBrush(QBrush(QColor(0,0,255,20)));//заливка под графиком

    // устанавливаем диапазон для осей, чтобы увидеть все данные
    ui->graph->xAxis->setRange(-1,1);
    ui->graph->yAxis->setRange(0,1);
    ui->graph->replot();
}

//Слод ля очистки координатной плоскости от графиков
void MyWidget::onPushButton_3_clicked()
{
    for (int i(0);i<5;i++)
    ui->graph->graph(i)->clearData();//очищаем коорд оси от графиков
    ui->graph->replot();
}

//данный график пока просто для опытов прикрутили
void MyWidget::onPushButton_4_clicked()
{
    //generate some data
    QVector<double> x1(101), y1(101); //Инициализируем два вектора по 101-у элементу

    for (int i=0;i<101;++i)
    {
        x1[i]=i/50.0-1; // x в диапазоне от -1 до 1
        y1[i]=2*x1[i]*x1[i];
    }
    //Создаем график и данные для него
    //ui->graph->addGraph();
    ui->graph->graph(2)->setData(x1,y1);
    ui->graph->xAxis->setLabel("x");
    ui->graph->yAxis->setLabel("y");
    ui->graph->graph(2)->setPen(QPen(Qt::green));
    ui->graph->graph(2)->setBrush(QBrush(QColor(0,19,236,17)));
    ui->graph->graph(2)->setLineStyle(QCPGraph::lsLine);
    ui->graph->graph(2)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDot,4));
    ui->graph->xAxis->setRange(-1,1);
    ui->graph->yAxis->setRange(0,1);
    ui->graph->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
    ui->graph->replot();
}

// в данном слоте обрабатываем крутилку 1 на рисование верхней границы
void MyWidget::onDial_valueChanged()
{
    if((ui->dial->value())!=0)
        ui->dial_2->setEnabled(true);
    else
        ui->dial_2->setEnabled(false);
    ui->dial->setMinimum(ui->dial_2->value());



    double x;
    x=(ui->dial->value())*0.01;
    QVector<double> x2(101), y2(101);//криво и расточительно рисуем линию :)
    for (int i=0;i<101;++i)
    {
        x2[i]=i/50.0-1; // x в диапазоне от -1 до 1
        y2[i]=x;
    }

    ui->graph->graph(3)->setData(x2,y2);
    ui->graph->graph(3)->setPen(QPen(Qt::red));
    ui->graph->replot();
}

// в данном слоте обрабатываем крутилку 1 на изменение значения в метке под крутилкой
void MyWidget::onDial_valueChanged1()
{

    QByteArray data_dial;
    ui->label_dial->setText(QString::number(ui->dial->value()));
    data_dial=QByteArray::number((ui->dial->value()));
    datagram[2]=data_dial[0];
    datagram[3]=data_dial[1];
    ui->textEdit->setText(datagram);
}

// в данном слоте обрабатываем крутилку 2 на рисование нижней границы
void MyWidget::onDial_valueChanged2()
{
    ui->dial_2->setMaximum(ui->dial->value());
    double x;
    x=(ui->dial_2->value())*0.01;
    QVector<double> x2(101), y2(101);//криво и расточительно рисуем вторую линию :)
    for (int i=0;i<101;++i)
    {
        x2[i]=i/50.0-1; // x в диапазоне от -1 до 1
        y2[i]=x;
    }

    ui->graph->graph(4)->setData(x2,y2);
    ui->graph->graph(4)->setPen(QPen(Qt::green));
    ui->graph->replot();
}

// в данном слоте обрабатываем крутилку 2 на изменение значения в метке под крутилкой
void MyWidget::onDial_valueChanged3()
{
    QByteArray data_dial;
    ui->label_dial2->setText(QString::number(ui->dial_2->value()));
    data_dial=QByteArray::number((ui->dial_2->value()));
    datagram[4]=data_dial[0];
    datagram[5]=data_dial[1];
    ui->textEdit->setText(datagram);
}
