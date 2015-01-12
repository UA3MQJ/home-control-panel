#include "mywidget.h"
#include "ui_mywidget.h"
int number_graph=0;

MyWidget::MyWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MyWidget)
{
    ui->setupUi(this);
    //QObject::connect(ui->pushButton_2,SIGNAL(clicked()),ui->graph,SLOT(on_pushButton_2_clicked()));
    //QObject::connect(ui->pushButton_3,SIGNAL(clicked()),ui->graph,SLOT(on_pushButton_3_clicked()));
    //QObject::connect(ui->pushButton_4,SIGNAL(clicked()),ui->graph,SLOT(on_pushButton_4_clicked()));
    //QObject::connect(ui->dial,SIGNAL(valueChanged()),ui->graph,SLOT(on_dial_valueChanged()));
    //QObject::connect(ui->dial,SIGNAL(valueChanged()),ui->graph,SLOT(on_pushButton_2_clicked()));
}

MyWidget::~MyWidget()
{
    delete ui;
}

//Слот для создания графика при нажатии на кнопку
void MyWidget::on_pushButton_2_clicked()
{
    //generate some data

   double Limit;
   int shet=0;
   Limit=(ui->dial->value())*0.01;
    for (int i=0;i<101;++i)
    {
        x.append(i/50.0-1); // x в диапазоне от 0 до 1
        y.append(x[i]*x[i]);
      if (y[i]>Limit)
        {
        y_red.append(y[i]);
        x_red.append(x[i]);
        shet++;
        }
    }

    //Создаем график и данные для него
    ui->graph->addGraph();
    ui->graph->graph(0)->setData(x,y);
    number_graph=number_graph+1;
    /*if(shet!=0){
        ui->graph->addGraph();
        ui->graph->graph(1)->setData(x_red,y_red);
        ui->graph->graph(1)->setPen(QPen(Qt::red));
        //ui->graph->graph(1)->setPen(QColor(50,50,50,255));
        //ui->graph->graph(1)->setLineStyle(QCPGraph::lsNone);
        //ui->graph->graph(1)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle,4));
    }*/

       //помещаем метки на оси
    ui->graph->xAxis->setLabel("x");
    ui->graph->yAxis->setLabel("y");
    ui->graph->graph(0)->setPen(QPen(Qt::blue));
    ui->graph->graph(0)->setBrush(QBrush(QColor(0,0,255,20)));

    // устанавливаем диапазон для осей, чтобы увидеть все данные
    ui->graph->xAxis->setRange(-1,1);
    ui->graph->yAxis->setRange(0,1);
    ui->graph->replot();
}

void MyWidget::on_pushButton_3_clicked()
{
    for (int i(0);i<4;i++)
    ui->graph->graph(i)->clearData();
    ui->graph->replot();
    number_graph=0;
}

void MyWidget::on_pushButton_4_clicked()
{
    //generate some data
    QVector<double> x1(101), y1(101); //Инициализируем два вектора по 101-у элементу

    for (int i=0;i<101;++i)
    {
        x1[i]=i/50.0-1; // x в диапазоне от -1 до 1
        y1[i]=2*x1[i]*x1[i];
    }
    //Создаем график и данные для него
    ui->graph->addGraph();
    ui->graph->graph(2)->setData(x1,y1);
        ui->graph->xAxis->setLabel("x");
    ui->graph->yAxis->setLabel("y");
    ui->graph->graph(2)->setPen(QPen(Qt::green));
    ui->graph->graph(2)->setBrush(QBrush(QColor(0,19,236,17)));
    ui->graph->graph(2)->setLineStyle(QCPGraph::lsLine);
    ui->graph->graph(2)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDot,1));
    number_graph=number_graph+1;
    ui->graph->xAxis->setRange(-1,1);
    ui->graph->yAxis->setRange(0,1);
    ui->graph->replot();
}

void MyWidget::on_dial_valueChanged()
{
   /* double x;
    x=(ui->dial->value())*0.01;
    QVector<double> x2(101), y2(101);
    for (int i=0;i<101;++i)
    {
        x2[i]=i/50.0-1; // x в диапазоне от -1 до 1
        y2[i]=x;
    }*/
    double Limit;
    int shet=0;
    Limit=(ui->dial->value())*0.01;
     for (int i=0;i<101;++i)
     {
       if (y[i]>Limit)
         {
         y_red.append(y[i]);
         x_red.append(x[i]);
         shet++;
         }
     }
     ui->graph->addGraph();
     ui->graph->graph(1)->setData(x_red,y_red);
     ui->graph->graph(1)->setPen(QPen(Qt::red));
    /*ui->graph->addGraph();
    ui->graph->graph(3)->setData(x2,y2);
    ui->graph->replot();
    */

}
