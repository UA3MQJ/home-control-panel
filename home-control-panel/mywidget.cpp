/*
Есть график функции, есть крутилка dial. По значению с нее рисуем вторую функцию y=dial_value.
Мы должны нарисовать график первой функции красным, если У точки больше У линии крутилки и синим, если У фунции графика 1 мельше У функции линии от крутилки.
Пока это реализовано рисованием 2-го графика поверх первого, что есть некрасивый костыль.


*/
#include "mywidget.h"
#include "ui_mywidget.h"

MyWidget::MyWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MyWidget)
{
    ui->setupUi(this);
    connect(ui->pushButton_2,SIGNAL(clicked()),SLOT(onPushButton_2_clicked()));//при нажатии кнопки рисуем график 1
    connect(ui->pushButton_3,SIGNAL(clicked()),SLOT(onPushButton_3_clicked()));//при нажатии кнопки рисуем график 2
    connect(ui->pushButton_4,SIGNAL(clicked()),SLOT(onPushButton_4_clicked()));// очищаем координатную сетку от всех графиков
    connect(ui->dial,SIGNAL(valueChanged(int)),SLOT(onDial_valueChanged())); // рисуем линию от крутилки 1
    connect(ui->dial,SIGNAL(valueChanged(int)),SLOT(onPushButton_2_clicked())); //подрезаем график 1 по значению крутилки 1
    connect(ui->dial,SIGNAL(valueChanged(int)),SLOT(onDial_valueChanged1())); //в соответствии с положением крутилки
    for (int i=0;i<4;i++)
    {
    ui->graph->addGraph();//добавляем 4 графика но не отрисовываем их пока и не задаеи значений точкам этих графиков
    }

}

MyWidget::~MyWidget()
{
    delete ui;
}


//Слот для создания графика при нажатии на кнопку
void MyWidget::onPushButton_2_clicked()
{
    //generate some data
    QVector<double> x(101),y(101),x_red,y_red; //Инициализируем четыре вектора
   double Limit;
   int shet=0;
   Limit=(ui->dial->value())*0.01;
    for (int i=0;i<101;++i)
    {
        x[i]=i/50.0-1; // x в диапазоне от 0 до 1
        y[i]=x[i]*x[i];
      if (y[i]>Limit) //выделяем точки для второго графика по условию
        {
        y_red.append(y[i]);
        x_red.append(x[i]);
        shet++;
        }
    }

    //Создаем график и данные для него
    ui->graph->graph(0)->setData(x,y);
      if(shet!=0)
    {
        //ui->graph->addGraph();
        ui->graph->graph(1)->setData(x_red,y_red);
        ui->graph->graph(1)->setPen(QPen(Qt::red));

    }

       //помещаем метки на оси
    ui->graph->xAxis->setLabel("x");
    ui->graph->yAxis->setLabel("y");
    ui->graph->graph(0)->setPen(QPen(Qt::blue));
    ui->graph->graph(0)->setBrush(QBrush(QColor(0,0,255,20)));//заливка под графиком

    // устанавливаем диапазон для осей, чтобы увидеть все данные
    ui->graph->xAxis->setRange(-1,1);
    ui->graph->yAxis->setRange(0,1);
    ui->graph->replot();
}

void MyWidget::onPushButton_3_clicked()
{
    for (int i(0);i<4;i++)
    ui->graph->graph(i)->clearData();//очищаем коорд оси от графиков
    ui->graph->replot();
}

void MyWidget::onPushButton_4_clicked() //данный график пока просто для опытов прикрутили
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
    ui->graph->graph(2)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDot,1));
    ui->graph->xAxis->setRange(-1,1);
    ui->graph->yAxis->setRange(0,1);
    ui->graph->replot();
}

void MyWidget::onDial_valueChanged() // в данном слоте обрабатываем крутилку
{
    double x;
    x=(ui->dial->value())*0.01;
    QVector<double> x2(101), y2(101);//криво и расточительно рисуем линию :)
    for (int i=0;i<101;++i)
    {
        x2[i]=i/50.0-1; // x в диапазоне от -1 до 1
        y2[i]=x;
    }

    ui->graph->graph(3)->setData(x2,y2);
    ui->graph->graph(3)->setPen(QPen(Qt::green));
    ui->graph->replot();
}

void MyWidget::onDial_valueChanged1()
{
    ui->label_dial->setText(QString::number(ui->dial->value()));
}
